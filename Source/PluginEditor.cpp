/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TLimiterAudioProcessorEditor::TLimiterAudioProcessorEditor (TLimiterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize(740, 180);

    buildElements();

    startTimerHz(60);
}

TLimiterAudioProcessorEditor::~TLimiterAudioProcessorEditor()
{
}

//==============================================================================
void TLimiterAudioProcessorEditor::buildElements()
{

    thresholdAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "threshold", threshold);
    threshold.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    threshold.setTextBoxStyle(Slider::TextBoxBelow, false, 120, 20);
    threshold.setRange(-50.0f, 10.0f); addAndMakeVisible(&threshold);
    threshold.setTextValueSuffix(" dB");

    kneeAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "knee", knee);
    knee.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    knee.setTextBoxStyle(Slider::TextBoxBelow, false, 120, 20);
    knee.setRange(0.0f, 30.0f); addAndMakeVisible(&knee);
    knee.setTextValueSuffix(" dB");

    attackAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "attack", attack);
    attack.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    attack.setTextBoxStyle(Slider::TextBoxBelow, false, 120, 20);
    attack.setRange(0.0f, 100.0f); addAndMakeVisible(&attack);
    attack.setTextValueSuffix(" ms");

    releaseAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "release", release);
    release.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    release.setTextBoxStyle(Slider::TextBoxBelow, false, 120, 20);
    release.setRange(0.0f, 800.0f); addAndMakeVisible(&release);
    release.setTextValueSuffix(" ms");

    ratioAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "ratio", ratio);
    ratio.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    ratio.setTextBoxStyle(Slider::TextBoxBelow, false, 120, 20);
    ratio.setRange(1.0f, 16.0f); addAndMakeVisible(&ratio);
    ratio.setTextValueSuffix(" : 1");

    makeUpAttachment = make_unique<AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "makeUp", makeUp);
    makeUp.setSliderStyle(Slider::SliderStyle::RotaryVerticalDrag);
    makeUp.setTextBoxStyle(Slider::TextBoxBelow, false, 120, 20);
    makeUp.setRange(-10.0f, 20.0f); addAndMakeVisible(&makeUp);
    makeUp.setTextValueSuffix(" dB");

}

void TLimiterAudioProcessorEditor::paint (juce::Graphics& g)
{

    g.fillAll(Colours::darkslategrey);

    g.setColour(Colours::white);
    g.setFont(15.0f);


    g.drawText("Threshold", 20,     (getHeight() / 2) - 50, 100, 30, Justification::centred);
    g.drawText("Knee",      140,    (getHeight() / 2) - 50, 100, 30, Justification::centred);
    g.drawText("Attack", 260,    (getHeight() / 2) - 50, 100, 30, Justification::centred);
    g.drawText("Release", 380,    (getHeight() / 2) - 50, 100, 30, Justification::centred);
    g.drawText("Ratio", 500,    (getHeight() / 2) - 50, 100, 30, Justification::centred);
    g.drawText("MakeUp", 620,    (getHeight() / 2) - 50, 100, 30, Justification::centred);


    //g.drawFittedText("Knee", labelRow.removeFromLeft(60), 12, Justification::centred, 1);
    //g.drawFittedText("Attack", labelRow.removeFromLeft(60), 12, Justification::centred, 1);
    //g.drawFittedText("Release", labelRow.removeFromLeft(60), 12, Justification::centred, 1);
    //g.drawFittedText("Ratio", labelRow.removeFromLeft(60), 12, Justification::centred, 1);
    //g.drawFittedText("MakeUp", labelRow.removeFromLeft(60), 12, Justification::centred, 1);

}

void TLimiterAudioProcessorEditor::resized()
{
    threshold.setBounds(20, getHeight() / 2 - 20, 100, 100);
    knee.setBounds(140,     getHeight() / 2 - 20, 100, 100);
    attack.setBounds(260,   getHeight() / 2 - 20, 100, 100);
    release.setBounds(380,  getHeight() / 2 - 20, 100, 100);
    ratio.setBounds(500,    getHeight() / 2 - 20, 100, 100);
    makeUp.setBounds(620,   getHeight() / 2 - 20, 100, 100);
}

void TLimiterAudioProcessorEditor::timerCallback()
{
    if (audioProcessor.characteristicChanged.get())
    {
        audioProcessor.characteristicChanged = false;
    }
}


