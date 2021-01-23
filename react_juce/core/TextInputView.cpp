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

    void TextInput::setMaxLength(int maxLen)
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
        : textInput(&props)
    {
        addAndMakeVisible(textInput);
        textInput.addListener(&textInput);
        textInput.setPopupMenuEnabled(false);
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
            juce::String hexPlaceholderColor = value;
            juce::Colour placeholderColor = juce::Colour::fromString(hexPlaceholderColor);
            textInput.setPlaceholderColour(placeholderColor);
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

        juce::String hexBackgroundColor = props.getWithDefault(backgroundColorProp, "00000000");
        juce::Colour backgroundColour = juce::Colour::fromString(hexBackgroundColor);
        textInput.setColour(juce::TextEditor::ColourIds::backgroundColourId, backgroundColour);

        if (name == outlineColorProp)
        {
            if (!value.isString())
                throw std::invalid_argument("Invalid prop value. Prop \'outline-color\' must be a color string.");
            juce::String hexOutlineColor = value;
            juce::Colour outlineColor = juce::Colour::fromString(hexOutlineColor);
            textInput.setColour(juce::TextEditor::ColourIds::outlineColourId, outlineColor);
        }
        if (name == focusedOutlineColorProp)
        {
            if (!value.isString())
                throw std::invalid_argument("Invalid prop value. Prop \'focused-outline-color\' must be a color string.");
            juce::String hexFocusedOutlineColor = value;
            juce::Colour focusedOutlineColor = juce::Colour::fromString(hexFocusedOutlineColor);
            textInput.setColour(juce::TextEditor::ColourIds::focusedOutlineColourId, focusedOutlineColor);
        }
        if (name == highlightedTextColorProp)
        {
            if (!value.isString())
                throw std::invalid_argument("Invalid prop value. Prop \'highlighted-text-color\' must be a color string.");
            juce::String hexHighlightedTextColor = value;
            juce::Colour highlightedTextColor = juce::Colour::fromString(hexHighlightedTextColor);
            textInput.setColour(juce::TextEditor::ColourIds::highlightedTextColourId, highlightedTextColor);
        }
        if (name == highlightColorProp)
        {
            if (!value.isString())
                throw std::invalid_argument("Invalid prop value. Prop \'highlighted-color\' must be a color string.");
            juce::String hexHighlightColor = value;
            juce::Colour highlightColor = juce::Colour::fromString(hexHighlightColor);
            textInput.setColour(juce::TextEditor::ColourIds::highlightColourId, highlightColor);
        }
        if (name == caretColorProp)
        {
            if (!value.isString())
                throw std::invalid_argument("Invalid prop value. Prop \'caret-color\' must be a color string.");
            juce::String hexCaretColor = value;
            juce::Colour caretColor = juce::Colour::fromString(hexCaretColor);
            textInput.setColour(juce::CaretComponent::ColourIds::caretColourId, caretColor);
        }
    }

    void TextInputView::paint(juce::Graphics &g)
    {
        View::paint(g);
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
