/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloSamplerAudioProcessor::HelloSamplerAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : MagicProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    using namespace juce;

    FOLEYS_SET_SOURCE_PATH(__FILE__);

    formatManager.registerBasicFormats();

    magicState.addTrigger("loadFile", [this]() { loadFile(); });

    addParameter(knob1 = new AudioParameterFloat("knob1", "Knob 1", 0.0f, 1.0f, 0.5f));

}

HelloSamplerAudioProcessor::~HelloSamplerAudioProcessor()
{
}

//==============================================================================
const juce::String HelloSamplerAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HelloSamplerAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HelloSamplerAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HelloSamplerAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HelloSamplerAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HelloSamplerAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HelloSamplerAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HelloSamplerAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String HelloSamplerAudioProcessor::getProgramName (int index)
{
    return {};
}

void HelloSamplerAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void HelloSamplerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void HelloSamplerAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HelloSamplerAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HelloSamplerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    std::vector<float*> bufs(totalNumOutputChannels);

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

    for (auto i = 0; i < totalNumOutputChannels; ++i) {
        bufs[i] = buffer.getWritePointer(i);
    }

    if (currSample.size() == 0) return;

    CatmullRomInterpolator interp;

    double speed = knob1->get();

    int samples = interp.process(speed, 
        currSample.data() + nextSampleIdx, 
        bufs[0], 
        buffer.getNumSamples(), 
        currSample.size() - nextSampleIdx, 0);
    nextSampleIdx = (nextSampleIdx + samples) % currSample.size();

    for (int i = 1; i < totalNumOutputChannels; i++) {
        memcpy(bufs[i], bufs[0], sizeof(float) * buffer.getNumSamples());
    }
}

void HelloSamplerAudioProcessor::loadFile()
{
    using namespace juce;
    
    DBG("Loading file");

    chooser.launchAsync(FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles,
        [this](const FileChooser& fc) {
            auto files = fc.getResults();
            if (files.size() < 1) return;

            auto file = files[0];

            DBG("File chosen: " + file.getFullPathName());
            auto* reader = formatManager.createReaderFor(file);

            BigInteger range;
            range.setRange(0, 128, true);

            currSample.resize(reader->lengthInSamples);

            float *channels[] = { currSample.data() };

            reader->read(channels, 1, 0, reader->lengthInSamples);

            nextSampleIdx = 0;
        });
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HelloSamplerAudioProcessor();
}
