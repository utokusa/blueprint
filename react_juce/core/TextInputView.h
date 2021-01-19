/*
  ==============================================================================

    blueprint_TextInputView.h
    Created: 28 Nov 2018 3:27:27pm

  ==============================================================================
*/

#pragma once

#include "View.h"


namespace blueprint
{

//==============================================================================
/** The TextInputView class
 *  TODO: comment
 */
class TextInputView : public View, juce::TextEditor::Listener
{
 public:
  static inline juce::Identifier placeholderProp = "placeholder";
  static inline juce::Identifier placeholderColorProp = "placeholderColor";
  static inline juce::Identifier maxlengthProp = "maxlength";
  static inline juce::Identifier readonly = "readonly";

  static const inline juce::Identifier colorProp         = "color";

  static const inline juce::Identifier fontSizeProp      = "font-size";
  static const inline juce::Identifier fontStyleProp     = "font-style";
  static const inline juce::Identifier fontFamilyProp    = "font-family";

  static const inline juce::Identifier justificationProp = "justification";
//  static const inline juce::Identifier kerningFactorProp = "kerning-factor";
// TODO: "kerning-factor"? Check TextView.h's kerningFactorProp.
  static const inline juce::Identifier fontKerningProp = "font-kerning";
//  static const inline juce::Identifier lineSpacingProp   = "line-spacing";
//  static const inline juce::Identifier wordWrapProp      = "word-wrap";

  //==============================================================================
//  TextInputView() = default;
  TextInputView()
  : textInput(), placeholderText(), placeholderColour(juce::Colours::black), dirty(false) {
    addAndMakeVisible(textInput);
    textInput.addListener(this);
  }

  //==============================================================================
  void setProperty (const juce::Identifier& name, const juce::var& value) override {
    View::setProperty(name, value);
    if ( name == placeholderProp) {
      setPlaceholderText(value);
    }
    if ( name == placeholderColorProp && value != "undefined") {
      juce::String hexColor = value;
      juce::Colour colour = juce::Colour::fromString(hexColor);
      setPlaceholderColour(colour);
    }
    if (name == maxlengthProp) {
      textInput.setInputRestrictions(value);
    }
    if (name == readonly) {
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


  //==============================================================================
  void paint (juce::Graphics& g) override {
    View::paint(g);
    g.setColour (juce::Colours::white);
  }

  //==============================================================================
  void resized() override
  {
    View::resized();
    textInput.setBounds(0, 0, getWidth(), getHeight());
  }

  // TODO: It was copied from TextView.h
  juce::Font getFont()
  {
    float fontHeight = props.getWithDefault(fontSizeProp, 12.0f);
    int textStyleFlags = props.getWithDefault(fontStyleProp, 0);

    juce::Font f (fontHeight);

    if (props.contains(fontFamilyProp))
      f = juce::Font (props[fontFamilyProp], fontHeight, textStyleFlags);

    f.setExtraKerningFactor(props.getWithDefault(fontKerningProp, 0.0));
    return f;
  }

  void textEditorTextChanged (juce::TextEditor &te) override {
    input(te.getText());
    dirty = true;
  }

  void textEditorReturnKeyPressed (juce::TextEditor &te) override {
    invokeChangeIfNeeded(te);
  }

  // NOTE: javascript's change event is not invoked when Esc is pressed.
  void textEditorEscapeKeyPressed (juce::TextEditor &te) override {
    invokeChangeIfNeeded(te);
  }

  void textEditorFocusLost (juce::TextEditor &te) override {

    invokeChangeIfNeeded(te);
  }


 private:
  void setPlaceholderText(const juce::String &text) {
    placeholderText = text;
    textInput.setTextToShowWhenEmpty(placeholderText, placeholderColour);
  }
  void setPlaceholderColour(const juce::Colour &colourToUse) {
    placeholderColour = colourToUse;
    textInput.setTextToShowWhenEmpty(placeholderText, placeholderColour);
  }

  void invokeChangeIfNeeded(juce::TextEditor &te) {
    if (dirty) {
      change(textInput.getText());
      dirty = false;
    }
  }
  //==============================================================================
  juce::TextEditor textInput;
  juce::String placeholderText;
  juce::Colour placeholderColour;
  bool dirty;
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextInputView)
};

}
