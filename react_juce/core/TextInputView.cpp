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

    void TextInput::setControlledValue(const juce::String &value)
    {
        preventUndoForControlledValue = true;
        setText(value);
    }

    void TextInput::setMaxLength(const int maxLen)
    {
        maxLength = maxLen;
        setInputRestrictions(maxLen);
    }

    void TextInput::setPlaceholderText(const juce::String &text)
    {
        placeholderText = text;
        setTextToShowWhenEmpty(placeholderText, placeholderColour);
    }

    void TextInput::setPlaceholderColour(const juce::Colour &colourToUse)
    {
        placeholderColour = colourToUse;
        setTextToShowWhenEmpty(placeholderText, placeholderColour);
    }

    void TextInput::insertTextAtCaret(const juce::String &textToInsert)
    {
        juce::String currentValue = getText();
        juce::TextEditor::insertTextAtCaret(textToInsert);
        juce::String newValue = getText();
        if (currentValue == newValue)
        {
            return;
        }

        if ((*props).contains(TextInputView::onInputProp) && (*props)[TextInputView::onInputProp].isMethod())
        {
            std::array<juce::var, 1> args{{detail::makeInputEventObject(getText())}};
            juce::var::NativeFunctionArgs nfArgs(juce::var(), args.data(), static_cast<int>(args.size()));
            std::invoke((*props)[TextInputView::onInputProp].getNativeFunction(), nfArgs);
        }
        dirty = true;

        if (controlled && !preventUndoForControlledValue)
        {
            undo();
        }
        preventUndoForControlledValue = false;
    }

    //==============================================================================
    void TextInput::textEditorTextChanged(juce::TextEditor &)
    {
    }

    void TextInput::textEditorReturnKeyPressed(juce::TextEditor &te)
    {
        invokeChangeIfNeeded(te);
    }

    // NOTE: JavaScript's change event is not invoked when Esc is pressed.
    //       This behavior is react-juce specific.
    void TextInput::textEditorEscapeKeyPressed(juce::TextEditor &te)
    {
        invokeChangeIfNeeded(te);
    }

    void TextInput::textEditorFocusLost(juce::TextEditor &te)
    {

        invokeChangeIfNeeded(te);
    }

    void TextInput::invokeChangeIfNeeded(juce::TextEditor &te)
    {
        if (dirty)
        {
            if ((*props).contains(TextInputView::onChangeProp) && (*props)[TextInputView::onChangeProp].isMethod())
            {
                std::array<juce::var, 1> args{{detail::makeChangeEventObject(te.getText())}};
                juce::var::NativeFunctionArgs nfArgs(juce::var(), args.data(), static_cast<int>(args.size()));
                std::invoke((*props)[TextInputView::onChangeProp].getNativeFunction(), nfArgs);
            }
            dirty = false;
        }
    }

    //==============================================================================

    TextInputView::TextInputView()
        : textInput(&props),
          dirty(false)
    {
        addAndMakeVisible(textInput);
        textInput.addListener(&textInput);
    }

    void TextInputView::setProperty(const juce::Identifier &name, const juce::var &value)
    {
        View::setProperty(name, value);
        if (name == valueProp)
        {
            if (!value.isString())
                throw std::invalid_argument("Invalid prop value. Prop \'value\' must be a string.");
            textInput.setControlled(true);
            textInput.setControlledValue(value);
        }
        if (name == placeholderProp)
        {
            textInput.setPlaceholderText(value);
        }
        if (name == placeholderColorProp)
        {
            if (!value.isString())
                throw std::invalid_argument("Invalid prop value. Prop \'placeholder-color\' must be a color string.");
            juce::String hexColor = value;
            juce::Colour colour = juce::Colour::fromString(hexColor);
            textInput.setPlaceholderColour(colour);
        }
        if (name == maxlengthProp)
        {
            if (!props[maxlengthProp].isDouble())
              throw std::invalid_argument("Invalid prop value. Prop \'maxlength\' must be a number.");
            textInput.setMaxLength(value);
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
}
