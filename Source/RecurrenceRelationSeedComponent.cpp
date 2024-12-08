/*

    RecurrenceRelationSeedComponent.cpp
    Created: 23 Mar 2022 7:57:21pm
    Author:  Marcus W. Hobbs

*/

#include <JuceHeader.h>
#include "RecurrenceRelation.h"
#include "RecurrenceRelationModel.h"
#include "RecurrenceRelationSeedComponent.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

RecurrenceRelationSeedComponent::RecurrenceRelationSeedComponent(WilsonicProcessor& processor)
: _processor(processor)
{
    auto const rrm = _processor.getRecurrenceRelationModel();

    // pre-allocate and add sliders to simplify component lifecycle and flows

    _Hn_1 = make_shared<SeedSlider>(_processor,
                                     "H [n-1]",
                                     RecurrenceRelation::getSeedMin(),
                                     rrm->uiGetSeed(1),
                                     RecurrenceRelation::getSeedMax(),
                                     RecurrenceRelation::getSeedIntervalValue(),
                                     [rrm] (float s) {rrm->uiSetSeed(s, 1);});
    _Hn_2 = make_shared<SeedSlider>(_processor,
                                     "H [n-2]",
                                     RecurrenceRelation::getSeedMin(),
                                     rrm->uiGetSeed(2),
                                     RecurrenceRelation::getSeedMax(),
                                     RecurrenceRelation::getSeedIntervalValue(),
                                     [rrm] (float s) {rrm->uiSetSeed(s, 2);});
    _Hn_3 = make_shared<SeedSlider>(_processor,
                                     "H [n-3]",
                                     RecurrenceRelation::getSeedMin(),
                                     rrm->uiGetSeed(3),
                                     RecurrenceRelation::getSeedMax(),
                                     RecurrenceRelation::getSeedIntervalValue(),
                                     [rrm] (float s) {rrm->uiSetSeed(s, 3);});
    _Hn_4 = make_shared<SeedSlider>(_processor,
                                     "H [n-4]",
                                     RecurrenceRelation::getSeedMin(),
                                     rrm->uiGetSeed(4),
                                     RecurrenceRelation::getSeedMax(),
                                     RecurrenceRelation::getSeedIntervalValue(),
                                     [rrm] (float s) {rrm->uiSetSeed(s, 4);});
    _Hn_5 = make_shared<SeedSlider>(_processor,
                                     "H [n-5]",
                                     RecurrenceRelation::getSeedMin(),
                                     rrm->uiGetSeed(5),
                                     RecurrenceRelation::getSeedMax(),
                                     RecurrenceRelation::getSeedIntervalValue(),
                                     [rrm] (float s) {rrm->uiSetSeed(s, 5);});
    _Hn_6 = make_shared<SeedSlider>(_processor,
                                     "H [n-6]",
                                     RecurrenceRelation::getSeedMin(),
                                     rrm->uiGetSeed(6),
                                     RecurrenceRelation::getSeedMax(),
                                     RecurrenceRelation::getSeedIntervalValue(),
                                     [rrm] (float s) {rrm->uiSetSeed(s, 6);});
    _Hn_7 = make_shared<SeedSlider>(_processor,
                                     "H [n-7]",
                                     RecurrenceRelation::getSeedMin(),
                                     rrm->uiGetSeed(7),
                                     RecurrenceRelation::getSeedMax(),
                                     RecurrenceRelation::getSeedIntervalValue(),
                                     [rrm] (float s) {rrm->uiSetSeed(s, 7);});
    _Hn_8 = make_shared<SeedSlider>(_processor,
                                     "H [n-8]",
                                     RecurrenceRelation::getSeedMin(),
                                     rrm->uiGetSeed(8),
                                     RecurrenceRelation::getSeedMax(),
                                     RecurrenceRelation::getSeedIntervalValue(),
                                     [rrm] (float s) {rrm->uiSetSeed(s, 8);});
    _Hn_9 = make_shared<SeedSlider>(_processor,
                                     "H [n-9]",
                                     RecurrenceRelation::getSeedMin(),
                                     rrm->uiGetSeed(9),
                                     RecurrenceRelation::getSeedMax(),
                                     RecurrenceRelation::getSeedIntervalValue(),
                                     [rrm] (float s) {rrm->uiSetSeed(s, 9);});
    
    // helper array
    _sliderArray.push_back(_Hn_1);
    _sliderArray.push_back(_Hn_2);
    _sliderArray.push_back(_Hn_3);
    _sliderArray.push_back(_Hn_4);
    _sliderArray.push_back(_Hn_5);
    _sliderArray.push_back(_Hn_6);
    _sliderArray.push_back(_Hn_7);
    _sliderArray.push_back(_Hn_8);
    _sliderArray.push_back(_Hn_9);
    jassert(_sliderArray.size() == 9);

    addAndMakeVisible(*_Hn_1);
    addAndMakeVisible(*_Hn_2);
    addAndMakeVisible(*_Hn_3);
    addAndMakeVisible(*_Hn_4);
    addAndMakeVisible(*_Hn_5);
    addAndMakeVisible(*_Hn_6);
    addAndMakeVisible(*_Hn_7);
    addAndMakeVisible(*_Hn_8);
    addAndMakeVisible(*_Hn_9);

    // default window size
    setSize(_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());
}

RecurrenceRelationSeedComponent::~RecurrenceRelationSeedComponent()
{

}

#pragma mark - drawing

void RecurrenceRelationSeedComponent::paint(Graphics& g)
{
    // BG
    g.fillAll(_processor.getAppSkin().getBgColor());

    if(AppExperiments::showDebugBoundingBox)
    {
        // DEBUG
        g.setColour(Colours::purple);
        g.drawRect(getLocalBounds(), 1);
    }
}

// | . [80] . | . [80] . | . [80] . | . [80] . | . [80] . | . [80] . |
void RecurrenceRelationSeedComponent::resized()
{
    // lock
    const ScopedLock sl(_lock);

    // resize each slider
    auto const numSliders = static_cast<float>(_sliderArray.size());
    auto area = getLocalBounds();
    auto const sliderWidth = area.getWidth() / numSliders;
    for(unsigned long i = 0; i < _sliderArray.size(); i++)
    {
        auto const slider = _sliderArray[i];
        auto sa = Rectangle<int>(static_cast<int>(area.getX() + i * sliderWidth), area.getY(), static_cast<int>(sliderWidth), area.getHeight());
        slider->setBounds(sa.reduced(5, 0));
    }
}

#pragma mark - methods

void RecurrenceRelationSeedComponent::setH_1_9(float a, float b, float c, float d, float e, float f, float g, float h, float i,  NotificationType type)
{
    _setXHelper(a, 0, type);
    _setXHelper(b, 1, type);
    _setXHelper(c, 2, type);
    _setXHelper(d, 3, type);
    _setXHelper(e, 4, type);
    _setXHelper(f, 5, type);
    _setXHelper(g, 6, type);
    _setXHelper(h, 7, type);
    _setXHelper(i, 8, type);
}

void RecurrenceRelationSeedComponent::_setXHelper(float val, unsigned long index, NotificationType type)
{
    jassert(index < _sliderArray.size());

    // lock
    const ScopedLock sl(_lock);

    if(_sliderArray.size() >= index + 1)
    {
        auto s = _sliderArray[index];
        s->setValue(val, type);
    }
    else
    {
        cout << "attempting to set a SeedSlider that is not visible: index:" << to_string(index) << endl;
        jassertfalse;
    }
}

void RecurrenceRelationSeedComponent::selectIJ(unsigned long i, unsigned long j)
{
    for(unsigned long index = 0; index < _sliderArray.size(); index++)
    {
        auto index1 = index + 1; // array is [0,8], indices are [1,9]
        auto ss = _sliderArray[index];
        ss->setIsSelected(false);
        if(index1 == i || index1 == j)
        {
            ss->setIsSelected(true);
        }
    }
    repaint();
}

