/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
Juce_testAudioProcessor::Juce_testAudioProcessor()
    :x1(2, 2) // x1(channel, bufferSize)
{
 //     setAudioChannels (2, 2); // no inputs, two outputs
 //x1.clear();
}

Juce_testAudioProcessor::~Juce_testAudioProcessor()
{
    // shutdownAudio();
}

//==============================================================================
const String Juce_testAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Juce_testAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Juce_testAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double Juce_testAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Juce_testAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Juce_testAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Juce_testAudioProcessor::setCurrentProgram (int index)
{
}

const String Juce_testAudioProcessor::getProgramName (int index)
{
    return String();
}

void Juce_testAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Juce_testAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
   // String message;
   // message << "Preparing to play audio..." << newLine;
   // message << " samplesPerBlockExpected = " << samplesPerBlockExpected << newLine;
   // message << " sampleRate = " << sampleRate;
   // Logger::getCurrentLogger()->writeToLog (message);
   //x = 0.0;
   x1.clear();
}

void Juce_testAudioProcessor::releaseResources()
{
     //Logger::getCurrentLogger()->writeToLog ("Releasing audio resources");
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
   //x = 0.0;
   x1.clear();

}

void Juce_testAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    //static float x = 0.0; 
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer (channel);
        float* z = x1.getWritePointer (channel);
        float y;
            
            for(int i=0;i<buffer.getNumSamples();i++){
            y = channelData[i];
            channelData[i] = y - z[0] + z[1]*0.5;
            z[0] = y;
            z[1] = z[0];
            }
        // ..do something to the data...
    }
}

//==============================================================================
bool Juce_testAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Juce_testAudioProcessor::createEditor()
{
    return new Juce_testAudioProcessorEditor (*this);
}

//==============================================================================
void Juce_testAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Juce_testAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Juce_testAudioProcessor();
}
