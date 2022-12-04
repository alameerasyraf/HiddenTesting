/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "../Modules/GainReductionComputer.h"
#include "../Modules/LookAheadGainReduction.h"
#include "../ThirdParty/Delay.h"

using namespace juce;
using namespace std;
using namespace dsp;

//==============================================================================
/**
*/
class TLimiterAudioProcessor  : public juce::AudioProcessor, public AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    TLimiterAudioProcessor();
    ~TLimiterAudioProcessor() override;

    //==============================================================================
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    //==============================================================================

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void parameterChanged(const String& parameterID, float newValue);

    AudioProcessorValueTreeState parameters;
    std::array<float, 2> gainReduction;

    GainReductionComputer& getCompressor() { return gainReductionComputer; };

    Atomic<bool> characteristicChanged = true;

private:

    AudioProcessorValueTreeState::ParameterLayout createParameters();

    GainReductionComputer gainReductionComputer;

    Delay delay;

    LookAheadGainReduction lookAheadFadeIn;
    AudioBuffer<float> sideChainBuffer;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TLimiterAudioProcessor)
};
