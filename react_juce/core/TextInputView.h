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

class TextInput : public juce::TextEditor, juce::TextEditor::Listener
{
public:
  TextInput(View *parent) : parent(parent), change(false) {
    addListener(this);
  }

  void textEditorTextChanged (juce::TextEditor &te) override {
    parent->input(getText());
    change = true;
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
  void invokeChangeIfNeeded(juce::TextEditor &te) {
    if (change) {
      parent->change(te.getText());
      change = false;
    }
  }

  View *parent;
  bool change;
};

//==============================================================================
/** The TextView class is a core container abstraction for declaring text components
    within Blueprint's layout system.
 */
class TextInputView : public View
{
 public:
  static inline juce::Identifier placeholderProp = "placeholder";
  static inline juce::Identifier maxlengthProp = "maxlength";

  //==============================================================================
//  TextInputView() = default;
  TextInputView()
  : textInput(this) {
    addAndMakeVisible(textInput);
  }

  //==============================================================================
  void setProperty (const juce::Identifier& name, const juce::var& value) override {
    View::setProperty(name, value);
    if (name == placeholderProp) {
      textInput.setTextToShowWhenEmpty(value, juce::Colours::grey);
    }
    if (name == maxlengthProp) {
      textInput.setInputRestrictions(value);
    }
  }


  //==============================================================================
  void paint (juce::Graphics& g) override {
    View::paint(g);
    g.fillAll (juce::Colour(255, 0, 0));
    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
  }

  //==============================================================================
  void resized() override
  {
    View::resized();
    textInput.setBounds(0, 0, getWidth(), getHeight());
  }

 private:
  //==============================================================================
  TextInput textInput;
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextInputView)
};

}
