/*
 ==============================================================================

 SynthComponent.cpp
 Created: 13 Mar 2021 3:40:40pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include <JuceHeader.h>
#include "SynthComponent.h"
#include "AppExperiments.h"

#pragma mark - lifecycle

SynthComponent::SynthComponent(WilsonicProcessor& processor)
: WilsonicAppTuningComponent(processor)
, _osc1 (_processor.getApvts(), "SYNTHOSC1", "SYNTHOSC1GAIN", "SYNTHOSC1PITCH", "SYNTHOSC1FMFREQ", "SYNTHOSC1FMDEPTH")
, _osc2 (_processor.getApvts(), "SYNTHOSC2", "SYNTHOSC2GAIN", "SYNTHOSC2PITCH", "SYNTHOSC2FMFREQ", "SYNTHOSC2FMDEPTH")
, _filter (_processor.getApvts(), "SYNTHFILTERTYPE", "SYNTHFILTERCUTOFF", "SYNTHFILTERRESONANCE")
, _adsr (_processor.getApvts(), "SYNTHATTACK", "SYNTHDECAY", "SYNTHSUSTAIN", "SYNTHRELEASE")
, _lfo1 (_processor.getApvts(), "SYNTHLFO1FREQ", "SYNTHLFO1DEPTH")
, _filterAdsr (_processor.getApvts(), "SYNTHFILTERATTACK", "SYNTHFILTERDECAY", "SYNTHFILTERSUSTAIN", "SYNTHFILTERRELEASE")
, _reverb (_processor.getApvts(), "SYNTHREVERBSIZE", "SYNTHREVERBDAMPING", "SYNTHREVERBWIDTH", "SYNTHREVERBDRY", "SYNTHREVERBWET", "SYNTHREVERBFREEZE")
, _meter (_processor)
{
    addAndMakeVisible(_osc1);
    addAndMakeVisible(_osc2);
    addAndMakeVisible(_filter);
    addAndMakeVisible(_adsr);
    addAndMakeVisible(_lfo1);
    addAndMakeVisible(_filterAdsr);
    addAndMakeVisible(_reverb);
    addAndMakeVisible(_meter);

    _osc1.setCustomName("Oscillator 1");
    _osc2.setCustomName("Oscillator 2");
    _filter.setCustomName("Filter");
    _lfo1.setCustomName("Filter LFO");
    _filterAdsr.setCustomName("Filter ADSR");
    _adsr.setCustomName("ADSR");
    _meter.setCustomName("Meter");

    auto oscColour = Colour::fromRGB(247, 190, 67);
    auto filterColour = Colour::fromRGB(246, 87, 64);

    _osc1.setBoundsColour(oscColour);
    _osc2.setBoundsColour(oscColour);

    _filterAdsr.setBoundsColour(filterColour);
    _filter.setBoundsColour(filterColour);
    _lfo1.setBoundsColour(filterColour);

    //
//    startTimerHz (AppExperiments::defaultTimerFrameRate);

    //
    setSize(_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());
}

SynthComponent::~SynthComponent()
{

}

#pragma mark - drawing

void SynthComponent::paint(Graphics& g)
{
    // BG
    g.fillAll(_processor.getAppSkin().getBgColor());

    if (AppExperiments::showDebugBoundingBox)
    {
        // DEBUG
        g.setColour(Colours::blueviolet);
        g.drawRect(getLocalBounds(), 1);

        // counter
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
}

void SynthComponent::resized()
{
    FlexBox oscFlexBox;
    oscFlexBox.flexDirection = FlexBox::Direction::column;
    oscFlexBox.items.add(FlexItem(_osc1).withFlex(1).withWidth(420).withHeight(180));
    oscFlexBox.items.add(FlexItem(_osc2).withFlex(1).withWidth(420).withHeight(180));
    oscFlexBox.items.add(FlexItem(_reverb).withFlex(1).withWidth(420).withHeight(150));

    FlexBox rightFlexBox;
    rightFlexBox.flexDirection = FlexBox::Direction::column;
    rightFlexBox.items.add(FlexItem(_filter).withFlex(1).withWidth(180).withHeight(200));
    rightFlexBox.items.add(FlexItem(_lfo1).withFlex(1).withWidth(180).withHeight(160));

    FlexBox adsrFlexBox;
    adsrFlexBox.flexDirection = FlexBox::Direction::column;
    adsrFlexBox.items.add(FlexItem(_filterAdsr).withFlex(1).withWidth(230).withHeight(360));
    adsrFlexBox.items.add(FlexItem(_adsr).withFlex(1).withWidth(230).withHeight(360));

    FlexBox bottomFlexBox;
    bottomFlexBox.flexDirection = FlexBox::Direction::column;
    bottomFlexBox.items.add(FlexItem(_meter).withFlex(1).withWidth(410).withHeight(150)); // 230 + 180 = 410

    FlexBox mainFlexBox;
    mainFlexBox.flexDirection = FlexBox::Direction::row;
    mainFlexBox.alignContent = FlexBox::AlignContent::spaceBetween;
    mainFlexBox.items.add(FlexItem(oscFlexBox).withFlex(1));
    mainFlexBox.items.add(FlexItem(rightFlexBox).withFlex(1));
    mainFlexBox.items.add(FlexItem(adsrFlexBox).withFlex(1));
    mainFlexBox.items.add(FlexItem(bottomFlexBox).withFlex(1));

    mainFlexBox.performLayout(getLocalBounds());
}

#pragma mark - App Tuning Title

const string SynthComponent::getAppTuningTitle()
{
    return "Synthesizer";
}

#pragma mark - timer

void SynthComponent::timerCallback()
{
    repaint();
}

