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


class TextEditorListener : public juce::TextEditor::Listener
{
 public:
  TextEditorListener(View *parent) :change(false), parent(parent) {}

  void textEditorTextChanged (juce::TextEditor &te) override {
    std::cout << "TextEditorListener::textEditorTextChanged()" << std::endl;
    juce::TextEditor::Listener::textEditorTextChanged(te);
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
  bool change;
  View *parent;

};

class TextEditorWrapper : public juce::TextEditor
{
public:
  TextEditorWrapper(View *parent) : parent(parent) {
    addListener(new TextEditorListener(parent));
  }

  void insertTextAtCaret (const juce::String &textToInsert) override
  {
    std::cout << "MyTextEditor::insertTextAtCaret(): " << textToInsert << std::endl;
    juce::TextEditor::insertTextAtCaret(textToInsert);
    parent->input(getText());
  }

  bool keyPressed(const juce::KeyPress &key) override {
    std::cout << "MyTextEditor::keyPressed()" << std::endl;
    juce::TextEditor::keyPressed(key);
//    parent->keyPressed(key);
  }

  void mouseDown(const juce::MouseEvent &e) override {
    std::cout << "MyTextEditor::mouseDown()" << std::endl;
    juce::TextEditor::mouseDown(e);
    parent->mouseDown(e);
  }
private:
  View *parent;
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
  : textEditor(this)
  {
    addAndMakeVisible(textEditor);
//    textEditor.setBounds(0, 0, 100, 100);
    std::cout << "construct test text editor" << std::endl;
  }

  //==============================================================================
  void setProperty (const juce::Identifier& name, const juce::var& value) override {
    View::setProperty(name, value);
    if (name == placeholderProp) {
      textEditor.setTextToShowWhenEmpty(value, juce::Colours::grey);
    }
    if (name == maxlengthProp) {
      textEditor.setInputRestrictions(value);
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
    textEditor.setBounds(0, 0, getWidth(), getHeight());
  }

 private:
  //==============================================================================
  TextEditorWrapper textEditor;
//  juce::TextEditor textEditor;
  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextInputView)
};

}
