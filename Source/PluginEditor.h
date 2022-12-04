/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

using namespace std;

typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;

//==============================================================================
/**
*/
class TLimiterAudioProcessorEditor  : public juce::AudioProcessorEditor, private Timer

{
public:
    TLimiterAudioProcessorEditor (TLimiterAudioProcessor&);
    ~TLimiterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void timerCallback() override;

    void buildElements();

private:
    // This reference is provided as a quick way for your editor to access the processor object that created it.
    TLimiterAudioProcessor& audioProcessor;

    Slider inputGain, threshold, knee, attack, release, ratio, makeUp;

    unique_ptr<SliderAttachment> inputGainVal, thresholdAttachment, kneeAttachment, attackAttachment, releaseAttachment, ratioAttachment, makeUpAttachment;

    ToggleButton lookAhead;
    unique_ptr<ButtonAttachment> lookAheadAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TLimiterAudioProcessorEditor)
};
