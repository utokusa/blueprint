/*
==============================================================================

TextInputView.cpp
Created: 2021/01/20 22:30:35

==============================================================================
*/

#include "TextInputView.h"

namespace blueprint
{
    namespace detail
    {
        static juce::var makeInputEventObject(const juce::String &value)
        {
            juce::DynamicObject::Ptr obj = new juce::DynamicObject();
            obj->setProperty("value", value);
            return obj.get();
        }

        static juce::var makeChangeEventObject(const juce::String &value)
        {
            juce::DynamicObject::Ptr obj = new juce::DynamicObject();
            obj->setProperty("value", value);
            return obj.get();
        }
    }

    TextInputView::TextInputView()
        : textInput(), placeholderText(), placeholderColour(juce::Colours::black), dirty(false)
    {
        addAndMakeVisible(textInput);
        textInput.addListener(this);
    }

    void TextInputView::setProperty(const juce::Identifier &name, const juce::var &value)
    {
        View::setProperty(name, value);
        if (name == placeholderProp)
        {
            setPlaceholderText(value);
        }
        if (name == placeholderColorProp && value != "undefined")
        {
            juce::String hexColor = value;
            juce::Colour colour = juce::Colour::fromString(hexColor);
            setPlaceholderColour(colour);
        }
        if (name == maxlengthProp)
        {
            textInput.setInputRestrictions(value);
        }
        if (name == readonly)
        {
            textInput.setReadOnly(value);
        }

        textInput.applyFontToAllText(getFont());

        juce::String hexColor = props.getWithDefault(colorProp, "ff000000");
        juce::Colour colour = juce::Colour::fromString(hexColor);
        textInput.applyColourToAllText(colour);

        int just = props.getWithDefault(justificationProp, 1);
        textInput.setJustification(just);

        juce::Font::findAllTypefaceNames();

        //    textInput.setLineSpacing(props.getWithDefault(lineSpacingProp, 1.0f));
    }

    void TextInputView::paint(juce::Graphics &g)
    {
        View::paint(g);
        g.setColour(juce::Colours::white);
    }

    void TextInputView::resized()
    {
        View::resized();
        textInput.setBounds(0, 0, getWidth(), getHeight());
    }

    void TextInputView::textEditorTextChanged(juce::TextEditor &te)
    {
        if (props.contains(onInputProp) && props[onInputProp].isMethod())
        {
            std::array<juce::var, 1> args{{detail::makeInputEventObject(te.getText())}};
            juce::var::NativeFunctionArgs nfArgs(juce::var(), args.data(), static_cast<int>(args.size()));
            std::invoke(props[onInputProp].getNativeFunction(), nfArgs);
        }
        dirty = true;
    }

    void TextInputView::textEditorReturnKeyPressed(juce::TextEditor &te)
    {
        invokeChangeIfNeeded(te);
    }

    // NOTE: JavaScript's change event is not invoked when Esc is pressed.
    //       This behavior is react-juce specific.
    void TextInputView::textEditorEscapeKeyPressed(juce::TextEditor &te)
    {
        invokeChangeIfNeeded(te);
    }

    void TextInputView::textEditorFocusLost(juce::TextEditor &te)
    {

        invokeChangeIfNeeded(te);
    }

    // TODO: It was copied from TextView.h
    juce::Font TextInputView::getFont()
    {
        float fontHeight = props.getWithDefault(fontSizeProp, 12.0f);
        int textStyleFlags = props.getWithDefault(fontStyleProp, 0);

        juce::Font f(fontHeight);

        if (props.contains(fontFamilyProp))
            f = juce::Font(props[fontFamilyProp], fontHeight, textStyleFlags);

        f.setExtraKerningFactor(props.getWithDefault(kerningFactorProp, 0.0));
        return f;
    }

    void TextInputView::setPlaceholderText(const juce::String &text)
    {
        placeholderText = text;
        textInput.setTextToShowWhenEmpty(placeholderText, placeholderColour);
    }
    void TextInputView::setPlaceholderColour(const juce::Colour &colourToUse)
    {
        placeholderColour = colourToUse;
        textInput.setTextToShowWhenEmpty(placeholderText, placeholderColour);
    }

    void TextInputView::invokeChangeIfNeeded(juce::TextEditor &te)
    {
        if (dirty)
        {
            if (props.contains(onChangeProp) && props[onChangeProp].isMethod())
            {
                std::array<juce::var, 1> args{{detail::makeChangeEventObject(te.getText())}};
                juce::var::NativeFunctionArgs nfArgs(juce::var(), args.data(), static_cast<int>(args.size()));
                std::invoke(props[onChangeProp].getNativeFunction(), nfArgs);
            }
            dirty = false;
        }
    }
}
