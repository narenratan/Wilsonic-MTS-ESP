/*
 ==============================================================================
 
 SeedSliderComponent.cpp
 Created: 19 Sep 2021 11:30:36am
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include <JuceHeader.h>
#include "SeedSliderComponent.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

SeedSliderComponent::SeedSliderComponent(WilsonicProcessor& processor)
: _processor(processor)
{
    // pre-allocate and add sliders to simplify component lifecycle and flows
    auto defaultSliderCallback = [](float ) {};
    _A = make_shared<SeedSlider>(_processor,
                                 "A",
                                 rangeMin,
                                 1,
                                 rangeMax,
                                 rangeStep,
                                 defaultSliderCallback);
    _B = make_shared<SeedSlider>(_processor,
                                 "B",
                                 rangeMin,
                                 3,
                                 rangeMax,
                                 rangeStep,
                                 defaultSliderCallback);
    _C = make_shared<SeedSlider>(_processor,
                                 "C",
                                 rangeMin,
                                 5,
                                 rangeMax,
                                 rangeStep,
                                 defaultSliderCallback);
    _D = make_shared<SeedSlider>(_processor,
                                 "D",
                                 rangeMin,
                                 7,
                                 rangeMax,
                                 rangeStep,
                                 defaultSliderCallback);
    _E = make_shared<SeedSlider>(_processor,
                                 "E",
                                 rangeMin,
                                 9,
                                 rangeMax,
                                 rangeStep,
                                 defaultSliderCallback);
    _F = make_shared<SeedSlider>(_processor,
                                 "F",
                                 rangeMin,
                                 11,
                                 rangeMax,
                                 rangeStep,
                                 defaultSliderCallback);
    _G = make_shared<SeedSlider>(_processor,
                                 "G",
                                 rangeMin,
                                 13,
                                 rangeMax,
                                 rangeStep,
                                 defaultSliderCallback);
    _H = make_shared<SeedSlider>(_processor,
                                 "H",
                                 rangeMin,
                                 15,
                                 rangeMax,
                                 rangeStep,
                                 defaultSliderCallback);
    
    // tab/return callback.  pass in your own index.  helper will know what to do
    _A->setOnTabReturnCallback([this](){_tabReturnHelper(0);});
    _B->setOnTabReturnCallback([this](){_tabReturnHelper(1);});
    _C->setOnTabReturnCallback([this](){_tabReturnHelper(2);});
    _D->setOnTabReturnCallback([this](){_tabReturnHelper(3);});
    _E->setOnTabReturnCallback([this](){_tabReturnHelper(4);});
    _F->setOnTabReturnCallback([this](){_tabReturnHelper(5);});
    _G->setOnTabReturnCallback([this](){_tabReturnHelper(6);});
    _H->setOnTabReturnCallback([this](){_tabReturnHelper(7);});
    
    // populate sliderArray
    _sliderArray.push_back(_A);
    _sliderArray.push_back(_B);
    _sliderArray.push_back(_C);
    _sliderArray.push_back(_D);
    _sliderArray.push_back(_E);
    _sliderArray.push_back(_F);
    _sliderArray.push_back(_G);
    _sliderArray.push_back(_H);
    jassert(_sliderArray.size() == 8);
    
    addAndMakeVisible(*_A);
    addAndMakeVisible(*_B);
    addAndMakeVisible(*_C);
    addAndMakeVisible(*_D);
    addAndMakeVisible(*_E);
    addAndMakeVisible(*_F);
    addAndMakeVisible(*_G);
    addAndMakeVisible(*_H);
    
    // default window size
    setSize(_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());
    
    setWantsKeyboardFocus(true);
}

SeedSliderComponent::~SeedSliderComponent() {
    
}

#pragma mark - drawing

void SeedSliderComponent::paint(Graphics& g)
{
    g.fillAll(_processor.getAppSkin().getBgColor());
    
    // DEBUG
    if(AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::purple);
        g.drawRect(getLocalBounds(), 1);
    }
}

// | . [80] . | . [80] . | . [80] . | . [80] . | . [80] . | . [80] . |
void SeedSliderComponent::resized() {
    const ScopedLock sl(_lock); // lock because _number_of_sliders can change
    if(_sliderArray.size() == 0) {
        return;
    }
    
    // resize each slider
    auto area = getLocalBounds();
    auto const sliderWidth = area.getWidth() / (float)_number_of_sliders_to_show;
    auto offscreen = getLocalBounds();
    offscreen.setX(offscreen.getX() + offscreen.getWidth());
    offscreen.setWidth(static_cast<int>(sliderWidth));
    for(unsigned long i = 0; i < _sliderArray.size(); i++) {
        auto const s = _sliderArray[i];
        if(i < _number_of_sliders_to_show) {
            auto sa = area.removeFromLeft(static_cast<int>(sliderWidth));
            s->setBounds(sa);
        } else {
            s->setBounds(offscreen);
        }
    }
}

#pragma mark - methods

void SeedSliderComponent::setSliderAtIndex(unsigned long index, string label, float val, function<void(float)> onValueChangeF) {
    const ScopedLock sl(_lock);
    jassert(index <= _sliderArray.size() &&
             label.size() > 0 &&
             val >= rangeMin && val < rangeMax &&
             onValueChangeF != nullptr);
    auto s = _sliderArray[index];
    s->setText(label);
    s->setValue(val, dontSendNotification);
    s->setOnValueChangedF(onValueChangeF);
}

void SeedSliderComponent::setA(float a, NotificationType type) {
    _setXHelper(a, 0, type);
}

void SeedSliderComponent::setAB(float a, float b, NotificationType type) {
    _setXHelper(a, 0, type);
    _setXHelper(b, 1, type);
}

void SeedSliderComponent::setABC(float a, float b, float c, NotificationType type) {
    _setXHelper(a, 0, type);
    _setXHelper(b, 1, type);
    _setXHelper(c, 2, type);
}

void SeedSliderComponent::setABCD(float a, float b, float c, float d, NotificationType type) {
    _setXHelper(a, 0, type);
    _setXHelper(b, 1, type);
    _setXHelper(c, 2, type);
    _setXHelper(d, 3, type);
}

void SeedSliderComponent::setABCDE(float a, float b, float c, float d, float e, NotificationType type) {
    _setXHelper(a, 0, type);
    _setXHelper(b, 1, type);
    _setXHelper(c, 2, type);
    _setXHelper(d, 3, type);
    _setXHelper(e, 4, type);
}

void SeedSliderComponent::setABCDEF(float a, float b, float c, float d, float e, float f, NotificationType type) {
    _setXHelper(a, 0, type);
    _setXHelper(b, 1, type);
    _setXHelper(c, 2, type);
    _setXHelper(d, 3, type);
    _setXHelper(e, 4, type);
    _setXHelper(f, 5, type);
}

void SeedSliderComponent::setABCDEFG(float a, float b, float c, float d, float e, float f, float g, NotificationType type) {
    _setXHelper(a, 0, type);
    _setXHelper(b, 1, type);
    _setXHelper(c, 2, type);
    _setXHelper(d, 3, type);
    _setXHelper(e, 4, type);
    _setXHelper(f, 5, type);
    _setXHelper(g, 6, type);
}

void SeedSliderComponent::setABCDEFGH(float a, float b, float c, float d, float e, float f, float g, float h, NotificationType type) {
    _setXHelper(a, 0, type);
    _setXHelper(b, 1, type);
    _setXHelper(c, 2, type);
    _setXHelper(d, 3, type);
    _setXHelper(e, 4, type);
    _setXHelper(f, 5, type);
    _setXHelper(g, 6, type);
    _setXHelper(h, 7, type);
}

void SeedSliderComponent::showNumberOfSliders(unsigned long number_of_sliders_to_show) {
    const ScopedLock sl(_lock);
    jassert(number_of_sliders_to_show <= _sliderArray.size());
    _number_of_sliders_to_show = number_of_sliders_to_show;
    resized();
}

void SeedSliderComponent::_setXHelper(float val, unsigned long index, NotificationType type) {
    jassert(index < _sliderArray.size());
    const ScopedLock sl(_lock);
    auto s = _sliderArray[index];
    s->setValue(val, type);
}

// sliders pass in *their own index*
void SeedSliderComponent::_tabReturnHelper(unsigned long sliderIndex) {
    jassert(sliderIndex < _sliderArray.size());
    if(_number_of_sliders_to_show == 0) {
        return; // NOP
    }
    
    const ScopedLock sl(_lock);
    auto index =(sliderIndex + 1) % _number_of_sliders_to_show;
    auto s = _sliderArray[index];
    s->grabFocus();
}
