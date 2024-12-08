/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

// ADD NEW SCALE DESIGN HERE
#include <algorithm>
#include "AppTuningModel.h"
#include "Brun2Model.h"
#include "CoPrimeModel.h"
#include "CPSModel.h"
#include "DesignsModel.h"
#include "DiamondsModel.h"
#include "EqualTemperamentModel.h"
#include "EulerGenusModel.h"
#include "FavoritesModelV2.h"
#include "MorphModel.h"
#include "PartchModel.h"
#include "Persian17NorthIndianModel.h"
#include "PresetsModel.h"
#include "RecurrenceRelationModel.h"
#include "ScalaModel.h"
#include "TritriadicModel.h"
#include "TuningTests.h"
#include "WilsonicEditor.h"
#include "WilsonicMenuComponentMessageBus.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

WilsonicProcessor::WilsonicProcessor()
#if defined(JucePlugin_PreferredChannelConfigurations)
    : AudioProcessor(BusesProperties())
{
    jassertfalse; // This will trigger a breakpoint in debug indicating an incorrect configuration
}
#elif JucePlugin_IsMidiEffect
    : AudioProcessor(BusesProperties()) // MIDI Effect, no audio I/O
#elif JucePlugin_IsSynth
    : AudioProcessor(BusesProperties()
        .withInput("Input", AudioChannelSet::stereo(), true)
        .withOutput("Output", AudioChannelSet::stereo(), true)) // Synth with stereo I/O
#else
    : AudioProcessor(BusesProperties())
{
    jassertfalse; // catchall breakpoint in debug indicating an unexpected configuration
}
#endif
, _designsModel(make_shared<DesignsModel>(*this))
, _apvts(make_shared<AudioProcessorValueTreeState>(*this, nullptr, Identifier(WilsonicProcessorConstants::identifier)
, _createParamGroup())) {
    DBG("WilsonicProcessor::WilsonicProcessor: Input bus count: " << getBusCount(true));
    DBG("WilsonicProcessor::WilsonicProcessor: Output bus count: " << getBusCount(false));

    // PROPERTIES
    PropertiesFile::Options options;
    options.applicationName = String(ProjectInfo::projectName);
    options.filenameSuffix = "config";
    options.osxLibrarySubFolder = "Application Support";
    options.folderName = String(ProjectInfo::projectName);
    _properties = make_unique<PropertiesFile>(options);

#if JucePlugin_IsSynth
    // this has to happen for synth to even function properly
    // SYNTH
    _synth.addSound(new SynthSound());
    for (unsigned long i = 0; i < WilsonicProcessorConstants::numVoices; i++)
    {
        _synth.addVoice(new SynthVoice(*this));
    }
#endif
    
    // always do MidiKeyboardState for every target
    _keyboardState = make_shared<MidiKeyboardState>();
    
    // MTS-ESP is called on a timer
    startTimer(1000);

    // DESIGNS MODEL
    _designsModel->setApvts(_apvts);
    _designsModel->addActionListener(this);
    _designsModel->updateProperties();
    
#if DEBUG
    // WILSONIC TESTS
    TuningTests::runTests(*this);
#endif
}

void WilsonicProcessor::_MTS_helper() {
#if JUCE_IOS || JUCE_ANDROID
    _mtsEspStatus = MTS_ESP_Status::NotSupported;
    _mtsEspStatusPrevious = MTS_ESP_Status::NotSupported;
    
    return;
#else
    // MTS
    if(_mtsEspStatus == MTS_ESP_Status::Registered) {
        if(_mtsEspStatus != _mtsEspStatusPrevious) {
            WilsonicMenuComponentMessageBus::getInstance().broadcastMessage("Wilsonic registered as MTS-ESP Source");
            _mtsEspStatusPrevious = _mtsEspStatus;
            sendActionMessage(getMtsEspStatusDidChangeMessage());
        }
    } else if(MTS_CanRegisterMaster()) {
        DBG("MTS: registering Source!");
        MTS_RegisterMaster();
        MTS_ClearNoteFilter();
        MTS_SetScaleName("MTS-ESP Init");
        _mtsEspStatus = MTS_ESP_Status::Registered;
        if(_mtsEspStatus != _mtsEspStatusPrevious) {
            WilsonicMenuComponentMessageBus::getInstance().broadcastMessage("Wilsonic registered as MTS-ESP Source");
            _mtsEspStatusPrevious = _mtsEspStatus;
            sendActionMessage(getMtsEspStatusDidChangeMessage());
        }
    } else {
        if(MTS_HasIPC()) {
            _mtsEspStatus = MTS_ESP_Status::NeedToReregister;
            if(_mtsEspStatus != _mtsEspStatusPrevious) {
                DBG("MTS: has another source connected.  Doing nothing for now, will prompt user when UI is created");
                WilsonicMenuComponentMessageBus::getInstance().broadcastMessage("Wilsonic is NOT registered as MTS-ESP Source");
                _mtsEspStatusPrevious = _mtsEspStatus;
                sendActionMessage(getMtsEspStatusDidChangeMessage());
            }
        } else {
            _mtsEspStatus = MTS_ESP_Status::Failed;
            if(_mtsEspStatus != _mtsEspStatusPrevious) {
                DBG("MTS: another source is connected?  library failure?: Wilsonic is not registered, and cannot update global tuning table");
                WilsonicMenuComponentMessageBus::getInstance().broadcastMessage("Wilsonic can NOT be registered as MTS-ESP Source");
                _mtsEspStatusPrevious = _mtsEspStatus;
                sendActionMessage(getMtsEspStatusDidChangeMessage());
            }
        }
    }
#endif
}

WilsonicProcessor::~WilsonicProcessor() {
    _designsModel->removeActionListener(this);
    stopTimer();
    
#if JUCE_IOS || JUCE_ANDROID
    return;
#else
    MTS_DeregisterMaster();
#endif
}

void WilsonicProcessor::timerCallback() {
    _MTS_helper();
}

#pragma mark - Processor

const String WilsonicProcessor::getName() const {
    return JucePlugin_Name;
}

bool WilsonicProcessor::acceptsMidi() const {
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WilsonicProcessor::producesMidi() const {
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WilsonicProcessor::isMidiEffect() const {
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WilsonicProcessor::getTailLengthSeconds() const {
    return 0.0;
}

int WilsonicProcessor::getNumPrograms() {
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WilsonicProcessor::getCurrentProgram() {
    return 0;
}

void WilsonicProcessor::setCurrentProgram(int ) {
    //TODO: support current program
}

const String WilsonicProcessor::getProgramName(int ) {
    return "NONE";
}

void WilsonicProcessor::changeProgramName(int , const String& ) {
    //TODO: support current program
}

const atomic<float>& WilsonicProcessor::getRMS() {
    return _meter.getRMS();
}

const atomic<float>& WilsonicProcessor::getPeak() {
    return _meter.getPeak();
}

VoiceStates WilsonicProcessor::getVoiceStates() {
    return _voiceStates; // return by value
}

void WilsonicProcessor::setVoiceStateFrequency(unsigned long nn, float frequency) {
    jassert(nn >= 0 && nn < WilsonicProcessorConstants::numMidiNotes);
    _voiceStates.voiceState[nn].frequency = frequency;
}

shared_ptr<MidiKeyboardState> WilsonicProcessor::getKeyboardState() {
    return _keyboardState;
}

// TODO: this means you are drawing all 128 notes because keyboardState is not based on velocity
float WilsonicProcessor::getKeyboardRMSForNN(unsigned long nn) {
    jassert(nn >= 0 && nn < WilsonicProcessorConstants::numMidiNotes);
    return _keyboardState->isNoteOn(WilsonicProcessorConstants::defaultMidiChannel, static_cast<int>(nn)) ? 0.2f : 0.f;
}

void WilsonicProcessor::allNotesOff() {
    getKeyboardState()->allNotesOff(0);
    sendActionMessage(getMIDIPanicMessage());
}

WilsonicAppSkin& WilsonicProcessor::getAppSkin() {
    return _appSkin;
}

// ADD NEW SCALE DESIGN HERE

shared_ptr<AppTuningModel> WilsonicProcessor::getAppTuningModel() {
    return _designsModel->getAppTuningModel();
}

shared_ptr<Brun2Model> WilsonicProcessor::getBrun2Model() {
    return _designsModel->getBrun2Model();
}

shared_ptr<CoPrimeModel> WilsonicProcessor::getCoPrimeModel() {
    return _designsModel->getCoPrimeModel();
}

shared_ptr<CPSModel> WilsonicProcessor::getCPSModel() {
    return _designsModel->getCPSModel();
}

shared_ptr<DesignsModel> WilsonicProcessor::getDesignsModel() {
    return _designsModel;
}

shared_ptr<DiamondsModel> WilsonicProcessor::getDiamondsModel() {
    return _designsModel->getDiamondsModel();
}

shared_ptr<EqualTemperamentModel> WilsonicProcessor::getEqualTemperamentModel() {
    return _designsModel->getEqualTemperamentModel();
}

shared_ptr<EulerGenusModel> WilsonicProcessor::getEulerGenusModel() {
    return _designsModel->getEulerGenusModel();
}

shared_ptr<FavoritesModelV2> WilsonicProcessor::getFavoritesModelV2() {
    return _designsModel->getFavoritesModelV2();
}

shared_ptr<MorphModel> WilsonicProcessor::getMorphModel() {
    return _designsModel->getMorphModel();
}

shared_ptr<PartchModel> WilsonicProcessor::getPartchModel() {
    return _designsModel->getPartchModel();
}

shared_ptr<Persian17NorthIndianModel> WilsonicProcessor::getPersian17NorthIndianModel() {
    return _designsModel->getPersian17NorthIndianModel();
}

shared_ptr<PresetsModel> WilsonicProcessor::getPresetsModel() {
    return _designsModel->getPresetsModel();
}

shared_ptr<RecurrenceRelationModel> WilsonicProcessor::getRecurrenceRelationModel() {
    return _designsModel->getRecurrenceRelationModel();
}

shared_ptr<ScalaModel> WilsonicProcessor::getScalaModel() {
    return _designsModel->getScalaModel();
}

shared_ptr<TritriadicModel> WilsonicProcessor::getTritriadicModel() {
    return _designsModel->getTritriadicModel();
}

shared_ptr<AudioProcessorValueTreeState> WilsonicProcessor::getApvts() {
    jassert(_apvts != nullptr); // avoid race conditions
    return _apvts;
}

AudioProcessorValueTreeState::Listener* WilsonicProcessor::getProcessorAsListener() {
    auto l = dynamic_cast<AudioProcessorValueTreeState::Listener*>(this);
    return l;
}

#pragma mark - render

void WilsonicProcessor::prepareToPlay(double sampleRate, int samplesPerBlock) {
#if JucePlugin_IsSynth
    _synth.setCurrentPlaybackSampleRate(sampleRate);
    jassert(_synth.getNumVoices() == WilsonicProcessorConstants::numVoices);
    for (int i = 0; i < _synth.getNumVoices(); i++) {
        if (auto voice = dynamic_cast<SynthVoice*>(_synth.getVoice(i))) {
            voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
        }
    }

    dsp::ProcessSpec spec;
    spec.maximumBlockSize = (unsigned int)samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = (uint32)getTotalNumOutputChannels();

    _reverbParams.roomSize = 0.5f;
    _reverbParams.width = 1.0f;
    _reverbParams.damping = 0.5f;
    _reverbParams.freezeMode = 0.0f;
    _reverbParams.dryLevel = 1.0f;
    _reverbParams.wetLevel = 0.0f;
    _reverb.setParameters(_reverbParams);
#elif JucePlugin_IsMidiEffect
    ignoreUnused(samplesPerBlock);
    _sampleRateMIDIController = static_cast<float>(sampleRate);
#endif
    DBG("WilsonicProcessor::prepareToPlay: Input bus count: " << getBusCount(true));
    DBG("WilsonicProcessor::prepareToPlay: Output bus count: " << getBusCount(false));
}

void WilsonicProcessor::releaseResources() {
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    //DBG ("WilsonicProcessor::releaseResources()");
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WilsonicProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const {
#if JucePlugin_IsMidiEffect
    // For a MIDI effect, we require that there are no audio input or output channels
    return layouts.getMainOutputChannelSet().isDisabled() && layouts.getMainInputChannelSet().isDisabled();
#else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

/**
 * @brief Processes an audio block and MIDI messages.
 * @param buffer The audio buffer to process.
 * @param midiMessages The MIDI messages to process.
 */
void WilsonicProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages) {
#if JucePlugin_IsSynth
    // This code path is taken if the plugin is a synthesizer.

    // ScopedNoDenormals is a helper class that sets the floating point environment to avoid denormals.
    ScopedNoDenormals noDenormals;

    // Get the total number of input and output channels.
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // Clear the buffer for all output channels that don't have a corresponding input channel.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i) {
        buffer.clear(i, 0, buffer.getNumSamples());
    }

    // Process the MIDI buffer.
    _keyboardState->processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);
    if (! AppExperiments::enableSimpleSynth) {
        // If the simple synth is not enabled, render zeros.
        _synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    } else {
        // Update the synth parameters.
        _setSynthParams();

        // Render the synth.
        _synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());

        // Get the voice states. This may need a lock to avoid race conditions.
        VoiceStates vs = VoiceStates();
        auto const num_voices = _synth.getNumVoices();
        for (int i = 0; i < num_voices; i++) {
            if (auto voice = dynamic_cast<SynthVoice*>(_synth.getVoice(i))) {
                vs.voiceState[i] = voice->getVoiceState();
            }
        }
        _voiceStates = vs; // Copy the voice states by value.

        // Process the reverb.
        dsp::AudioBlock<float> block { buffer };
        _reverb.process(dsp::ProcessContextReplacing<float>(block));

        // Process the output meter at the processor level.
        _meter.process(buffer);
    }
#elif JucePlugin_IsMidiEffect
    // This code path is taken if the plugin is a MIDI effect.

    // A pure MIDI plugin shouldn't be provided any audio data.
    jassert (buffer.getNumChannels() == 0);

    // However, we use the buffer to get timing information.
    auto const numSamples = buffer.getNumSamples();

    // Process the MIDI buffer.
    _keyboardState->processNextMidiBuffer(midiMessages, 0, numSamples, true);
#else
    // This code path should never be taken. If it is, there's a problem with the plugin configuration.
    jassertfalse;
#endif
}

#pragma mark - Editor

bool WilsonicProcessor::hasEditor() const {
    return true;
}

AudioProcessorEditor* WilsonicProcessor::createEditor() {
    return new WilsonicEditor(*this);
}

// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new WilsonicProcessor();
}

// Section for managing the state of the WilsonicProcessor
#pragma mark - State Management

/**
 * @brief This function is used to get the current state of the WilsonicProcessor.
 * @param destData This is where the current state of the WilsonicProcessor will be stored.
 */
void WilsonicProcessor::getStateInformation(MemoryBlock& destData) {
    // Create an XML element from the current state of the AudioProcessorValueTreeState
    unique_ptr<XmlElement> xml(_apvts->state.createXml());
    // Copy the XML data to the destination MemoryBlock
    copyXmlToBinary(*xml, destData);
}

/**
 * @brief This function is used to set the state of the WilsonicProcessor.
 * @param data This is the data that will be used to set the state of the WilsonicProcessor.
 * @param sizeInBytes This is the size of the data in bytes.
 */
void WilsonicProcessor::setStateInformation(const void* data, int sizeInBytes) {
    // Create an XML element from the binary data
    unique_ptr<XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    // If the XML is valid and its tag name matches the type of the AudioProcessorValueTreeState,
    // then update the state of the AudioProcessorValueTreeState from the XML
    if (xml && xml->hasTagName(_apvts->state.getType())) {
        _apvts->state = ValueTree::fromXml(*xml);
    }
}

// Section for handling action events
#pragma mark - ActionListener

// ADD NEW SCALE DESIGN HERE

void WilsonicProcessor::actionListenerCallback(const String& message) {
    if (message == DesignsModel::getShowBrunTuningMessage()) {
        showBrunTuning();
    } else if (message == DesignsModel::getShowCoPrimeTuningMessage()) {
        showCoPrimeTuning();
    } else if (message == DesignsModel::getShowCPSTuningMessage()) {
        showCPSTuning();
    } else if (message == DesignsModel::getShowDiamondsTuningMessage()) {
        showDiamondsTuning();
    } else if (message == DesignsModel::getShowEqualTemperamentTuningMessage()) {
        showEqualTemperamentTuning();
    } else if (message == DesignsModel::getShowEulerGenusTuningMessage()) {
        showEulerGenusV2Tuning();
    } else if (message == DesignsModel::getShowMorphTuningMessage()) {
        showMorphTuning();
    } else if (message == DesignsModel::getShowPartchTuningMessage()) {
        showPartchTuning();
    } else if (message == DesignsModel::getShowPersian17NorthIndianTuningMessage()) {
        showPersian17NorthIndianTuning();
    } else if (message == DesignsModel::getShowPresetsTuningMessage()) {
        showPresetsTuning();
    } else if (message == DesignsModel::getShowRecurrenceRelationTuningMessage()) {
        showRecurrenceRelationTuning();
    } else if (message == DesignsModel::getShowScalaTuningMessage()) {
        showScalaTuning();
    } else if (message == DesignsModel::getShowTritriadicTuningMessage()) {
        showTritriadicTuning();
    } else {
        jassertfalse;
    }
}

void WilsonicProcessor::debugLogApvtsState() {
    auto state = _apvts->copyState();
    auto xmlElement = state.createXml();
    DBG(xmlElement->toString());
}

// ADD NEW SCALE DESIGN HERE

#pragma mark - DesignsProtocol

void WilsonicProcessor::showBrunTuning() {
    if (auto editor = dynamic_cast<WilsonicEditor*>(getActiveEditor())) {
        editor->showBrunTuning();
    } else {
        jassertfalse;
    }
}

void WilsonicProcessor::showCoPrimeTuning() {
    if (auto editor = dynamic_cast<WilsonicEditor*>(getActiveEditor())) {
        editor->showCoPrimeTuning();
    } else {
        jassertfalse;
    }
}

void WilsonicProcessor::showCPSTuning() {
    if (auto editor = dynamic_cast<WilsonicEditor*>(getActiveEditor())) {
        editor->showCPSTuning();
    } else {
        jassertfalse;
    }
}

void WilsonicProcessor::showDiamondsTuning() {
    if (auto editor = dynamic_cast<WilsonicEditor*>(getActiveEditor())) {
        editor->showDiamondsTuning();
    } else {
        jassertfalse;
    }
}

void WilsonicProcessor::showEqualTemperamentTuning() {
    if (auto editor = dynamic_cast<WilsonicEditor*>(getActiveEditor())) {
        editor->showEqualTemperamentTuning();
    } else {
        jassertfalse;
    }
}

void WilsonicProcessor::showEulerGenusV2Tuning() {
    if (auto editor = dynamic_cast<WilsonicEditor*>(getActiveEditor())) {
        editor->showEulerGenusV2Tuning();
    } else {
        jassertfalse;
    }
}

void WilsonicProcessor::showMorphTuning() {
    if(auto editor = dynamic_cast<WilsonicEditor*>(getActiveEditor())) {
        editor->showMorphTuning();
    } else {
        jassertfalse;
    }
}

void WilsonicProcessor::showPartchTuning() {
    if (auto editor = dynamic_cast<WilsonicEditor*>(getActiveEditor())) {
        editor->showPartchTuning();
    } else {
        jassertfalse;
    }
}

void WilsonicProcessor::showPersian17NorthIndianTuning() {
    if (auto editor = dynamic_cast<WilsonicEditor*>(getActiveEditor())) {
        editor->showPersian17NorthIndianTuning();
    } else {
        jassertfalse;
    }
}

void WilsonicProcessor::showPresetsTuning() {
    if (auto editor = dynamic_cast<WilsonicEditor*>(getActiveEditor())) {
        editor->showPresetsTuning();
    } else {
        jassertfalse;
    }
}

void WilsonicProcessor::showRecurrenceRelationTuning() {
    if (auto editor = dynamic_cast<WilsonicEditor*>(getActiveEditor())) {
        editor->showRecurrenceRelationTuning();
    } else {
        jassertfalse;
    }
}

void WilsonicProcessor::showScalaTuning() {
    if (auto editor = dynamic_cast<WilsonicEditor*>(getActiveEditor())) {
        editor->showScalaTuning();
    } else {
        jassertfalse;
    }
}

void WilsonicProcessor::showTritriadicTuning() {
    if (auto editor = dynamic_cast<WilsonicEditor*>(getActiveEditor())) {
        editor->showTritriadicTuning();
    } else {
        jassertfalse;
    }
}

#pragma mark - MTS-ESP Status

WilsonicProcessor::MTS_ESP_Status WilsonicProcessor::getMtsEspStatus() {
    return _mtsEspStatus;
}

int WilsonicProcessor::getMtsEspNumberOfClients() {
#if JUCE_IOS || JUCE_ANDROID
    return 0;
#else
    if (_mtsEspStatus == WilsonicProcessor::MTS_ESP_Status::Registered) {
        return MTS_GetNumClients();
    }

    return 0;
#endif
}

bool WilsonicProcessor::resetMtsEsp() {
#if JUCE_IOS || JUCE_ANDROID
    return false;
#else
    // you may only reset MTS-ESP if IPC is in use
    if (MTS_HasIPC()) {
        DBG("MTS: has another source connected...re-initializing, re-registering this as the Source");
        MTS_Reinitialize();
        MTS_RegisterMaster();
        MTS_ClearNoteFilter();
        _mtsEspStatus = MTS_ESP_Status::Registered;
        WilsonicMenuComponentMessageBus::getInstance().broadcastMessage("MTS-ESP: Wilsonic is registered as the source");
        sendActionMessage(getMtsEspStatusDidChangeMessage());

        return true;
    }

    // Fail once and don't retry...the user has to quit and restart
    _mtsEspStatus = MTS_ESP_Status::Failed;
    WilsonicMenuComponentMessageBus::getInstance().broadcastMessage("MTS-ESP: Wilsonic is not registered as the source");
    sendActionMessage(getMtsEspStatusDidChangeMessage());

    return false;
#endif
}
