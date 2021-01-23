/*
==============================================================================

TextInputView.h
Created: 2021/01/20 22:30:35

==============================================================================
*/

#pragma once

#include "View.h"

namespace blueprint
{
    //==============================================================================
    class TextInput : public juce::TextEditor, public juce::TextEditor::Listener
    {
    public:
        TextInput(const juce::NamedValueSet *props)
            : props(props),
              controlled(false),
              preventUndoForControlledValue(false),
              placeholderText(),
              placeholderColour(juce::Colours::black) {}
        void insertTextAtCaret(const juce::String &textToInsert) override;
        void setControlled(bool _controlled) { controlled = _controlled; }
        void setControlledValue(const juce::String &value);
        void setMaxLength(const int maxLen);
        void setPlaceholderText(const juce::String &text);
        void setPlaceholderColour(const juce::Colour &colourToUse);

        //==============================================================================
        void textEditorTextChanged(juce::TextEditor &te) override;
        void textEditorReturnKeyPressed(juce::TextEditor &te) override;
        void textEditorEscapeKeyPressed(juce::TextEditor &te) override;
        void textEditorFocusLost(juce::TextEditor &te) override;
    private:
        void invokeChangeIfNeeded(juce::TextEditor &te);
        bool dirty;
        bool controlled;
        // TODO: comment
        bool preventUndoForControlledValue;
        // We cannot get maxLength from juce::TextEditor.
        // So we save it here.
        int maxLength;
        juce::String placeholderText;
        juce::Colour placeholderColour;

        const juce::NamedValueSet *props;
    };

    //==============================================================================
    /** The TextInputView class
 *  TODO: comment
 */
    class TextInputView : public View
    {
    public:
        //==============================================================================
        static inline juce::Identifier valueProp = "value";
        static inline juce::Identifier placeholderProp = "placeholder";
        static inline juce::Identifier placeholderColorProp = "placeholder-color";
        static inline juce::Identifier maxlengthProp = "maxlength";
        static inline juce::Identifier readonly = "readonly";

        static const inline juce::Identifier colorProp = "color";
        static const inline juce::Identifier fontSizeProp = "font-size";
        static const inline juce::Identifier fontStyleProp = "font-style";
        static const inline juce::Identifier fontFamilyProp = "font-family";
        static const inline juce::Identifier justificationProp = "justification";
        static const inline juce::Identifier kerningFactorProp = "kerning-factor";

        static inline juce::Identifier onInputProp = "onInput";
        static inline juce::Identifier onChangeProp = "onChange";

        //==============================================================================
        TextInputView();

        //==============================================================================
        void setProperty(const juce::Identifier &name, const juce::var &value) override;

        //==============================================================================
        void paint(juce::Graphics &g) override;
        void resized() override;

    private:
        juce::Font getFont();

        //==============================================================================
        TextInput textInput;
        bool dirty;
        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TextInputView)
    };

}
