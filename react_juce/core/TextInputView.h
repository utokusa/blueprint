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

  //==============================================================================
//  TextInputView() = default;
  TextInputView() {
    addAndMakeVisible(textEditor);
    textEditor.setBounds(0, 0, 100, 100);
    std::cout << "construct test text editor" << std::endl;
  }

  //==============================================================================
  void setProperty (const juce::Identifier& name, const juce::var& value) override {
  }


  //==============================================================================
  void paint (juce::Graphics& g) override {
    std::cout << "paint text editor" << std::endl;
    View::paint(g);
    g.fillAll (juce::Colour(255, 0, 0));
    g.setFont (juce::Font (16.0f));
    g.setColour (juce::Colours::white);
    textEditor.setText("TEST TEXT EDITOR HERE!!");
    textEditor.paint(g);
//    std::cout << "paint text editor" << std::endl;
  }

 private:
  //==============================================================================
  juce::TextEditor textEditor {"test text editor"};

  //==============================================================================
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TextInputView)
};

}
