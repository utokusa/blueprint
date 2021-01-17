#pragma once

// CMake builds don't use an AppConfig.h, so it's safe to include juce module headers
// directly. If you need to remain compatible with Projucer-generated builds, and
// have called `juce_generate_juce_header(<thisTarget>)` in your CMakeLists.txt,
// you could `#include <JuceHeader.h>` here instead, to make all your module headers visible.
#include <juce_gui_extra/juce_gui_extra.h>

 class MyTextEditor :public juce::TextEditor
 {
  public:
   MyTextEditor() {
     setWantsKeyboardFocus(true);
   }
   bool keyPressed	(const juce::KeyPress &k) override {
     std::cout << "key pressed" << std::endl;
     return juce::TextEditor::keyPressed(k);
//     juce::TextEditor::keyPressed(k);
//     return true;
   }
   void mouseDown(const juce::MouseEvent &e) override {
     std::cout << "mouse down" << std::endl;
     juce::TextEditor::mouseDown(e);
   }
 };

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public juce::Component
{
public:
    //==============================================================================
    MainComponent();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    // Your private member variables go here...
    MyTextEditor textEditor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};