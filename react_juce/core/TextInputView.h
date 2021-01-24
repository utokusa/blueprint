/*
==============================================================================

  TextInputView.h
  Created: 20 Jan 2021 10:30pm

==============================================================================
*/

#pragma once

#include "View.h"

namespace blueprint
{
    //==============================================================================
    /** The TextInput class is an extended juce::TextEditor class for TextInputView
     * class. There are some features added.
     *
     * - Invoke JavaScript's 'input' and 'change' event.
     *
     *   Note: React.js has only 'onChange' callback which has same behavior as
     *   JavaScript's 'onInput' and does not have any callback corresponding to
     *   original JavaScript's 'onChange'.
     *   https://stackoverflow.com/questions/38256332/in-react-whats-the-difference-between-onchange-and-oninput
     *
     * - Support React's controlled component model.
     *   https://reactjs.org/docs/uncontrolled-components.html
     *   If field `controlled` is true,
     *   only the string value given by `setControlledValue()`
     *   is shown in the text editor.
     *
     * - Allow to set 'placeholder' text and 'placeholder-color' separately.
     */
    class TextInput : public juce::TextEditor, public juce::TextEditor::Listener
    {
    public:
        //==============================================================================
        explicit TextInput(const juce::NamedValueSet *_props)
            :
            props(_props),
            controlled(false),
            insertedAsControlledValue(false),
            dirty(false),
            maxLength(INT_MAX),
            placeholderText(),
            placeholderColour(juce::Colours::black) {}

        void insertTextAtCaret(const juce::String &textToInsert) override;
        void setControlled(bool _controlled) { controlled = _controlled; }
        void setControlledValue(const juce::String &value);
        void setMaxLength(int maxLen);
        void setPlaceholderText(const juce::String &text);
        void setPlaceholderColour(const juce::Colour &colourToUse);

        //==============================================================================
        void textEditorReturnKeyPressed(juce::TextEditor &) override;
        void textEditorFocusLost(juce::TextEditor &) override;
    private:
        //==============================================================================
        void invokeChangeEventIfNeeded();

        //==============================================================================
        const juce::NamedValueSet *props;
        bool controlled;
        bool insertedAsControlledValue;

        bool dirty; // for `onChange`
        int maxLength;
        juce::String placeholderText;
        juce::Colour placeholderColour;
    };

    //==============================================================================
    /** The TextInputView class is a core view for text editor
     * within Blueprint's layout system.
     */
    class TextInputView : public View
    {
    public:
        //==============================================================================
        static inline juce::Identifier valueProp = "value";

        static const inline juce::Identifier colorProp = "color";
        static const inline juce::Identifier justificationProp = "justification";

        static inline juce::Identifier placeholderProp = "placeholder";
        static inline juce::Identifier placeholderColorProp = "placeholder-color";
        static inline juce::Identifier maxlengthProp = "maxlength";
        static inline juce::Identifier readonly = "readonly";

        static const inline juce::Identifier outlineColorProp = "outline-color";
        static const inline juce::Identifier focusedOutlineColorProp = "focused-outline-color";
        static const inline juce::Identifier highlightedTextColorProp = "highlighted-text-color";
        static const inline juce::Identifier highlightColorProp = "highlight-color";
        static const inline juce::Identifier caretColorProp = "caret-color";

        static inline juce::Identifier onInputProp = "onInput";
        static inline juce::Identifier onChangeProp = "onChange";

        //==============================================================================
        TextInputView();
        void setProperty(const juce::Identifier &name, const juce::var &value) override;
        void paint(juce::Graphics &g) override;
        void resized() override;

    private:
        //==============================================================================
        juce::Font getFont();

        //==============================================================================
        TextInput textInput;

        //==============================================================================
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TextInputView)
    };

}
