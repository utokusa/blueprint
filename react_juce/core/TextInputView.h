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
/** The TextView class is a core container abstraction for declaring text components
    within Blueprint's layout system.
 */
class TextInputView : public View
{
 public:
  static inline juce::Identifier placeholderProp    = "placeholder";

  //==============================================================================
//  TextInputView() = default;
  TextInputView() {
    addAndMakeVisible(textEditor);
//    textEditor.setBounds(0, 0, 100, 100);
    std::cout << "construct test text editor" << std::endl;
  }

  //==============================================================================
  void setProperty (const juce::Identifier& name, const juce::var& value) override {
    View::setProperty(name, value);
    if (name == placeholderProp) {
      placeholderStr = value;
    }
  }


  //==============================================================================
  void paint (juce::Graphics& g) override {
    View::paint(g);
    g.fillAll (juce::Colour(255, 0, 0));
    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    if (textEditor.getText().isEmpty()) {
      textEditor.setText(placeholderStr);
    }
    textEditor.paint(g);
  }

  //==============================================================================
  void resized() override
  {
    View::resized();
    textEditor.setBounds(0, 0, getWidth(), getHeight());
  }

 private:
  //==============================================================================
  juce::TextEditor textEditor {"test text editor"};
  juce::String placeholderStr;

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextInputView)
};

}
