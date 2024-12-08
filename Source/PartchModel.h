/*
  ==============================================================================

    PartchModel.h
    Created: 27 May 2024 1:53:38pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppVersion.h"
#include "ModelBase.h"
#include "Partch.h"
#include "TuningImp.h"
#include "Tuning_Include.h"

class WilsonicProcessor;

class PartchModel final
: public ModelBase
, public ActionBroadcaster
{
public:
    static const ParameterID getPartchScaleParameterID() { return ParameterID ("PARTCHSCALE", AppVersion::getVersionHint()); }
    static const String getPartchScaleParameterName() { return "Partch|Scale"; }

    // lifecycle
    PartchModel(WilsonicProcessor& processor);
    ~PartchModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PartchModel)
    
public:
    // public methods
    shared_ptr<Tuning> getTuning() override;

    // called only once: on construction of processor
    unique_ptr<AudioProcessorParameterGroup> createParams() override;
    String getGroupID() override;
    String getGroupName() override;
    String getSubgroupSeparator() override;
    ParameterID getDesignParameterID() override; // key for this design's Favorites array
    StringArray getFavoritesParameterIDs() override; // used for Favorites
    void attachParameterListeners() override;// called only once: when assigning _avpts
    void parameterChanged(const String& parameterID, float newValue) override;
    void updateProperties() override;
    
    // ui methods
    int getNumScales();
    StringArray getScaleNames();
    int uiGetSelectedScaleIndex();
    void uiSetScale(int index = 0);
    void uiSetGralHexScale(float newScale);
    float uiGetGralHexScale();
    void uiSetGralHexRotationRadians(float newRotationRadians);
    float uiGetGralHexRotationRadians();
    void uiSetGralHexShearX(float newHexShearX);
    float uiGetGralHexShearX();
    void uiSetGralHexOriginOffsetFactorX(float newOffsetX);
    float uiGetGralHexOriginOffsetFactorX();
    void uiSetGralHexOriginOffsetFactorY(float newOffsetY);
    float uiGetGralHexOriginOffsetFactorY();
    int nnForDeviceSpace(Point<int> xy);
    void uiSetO1(bool o1);
    bool uiGetO1() const;
    void uiSetU1(bool u1);
    bool uiGetU1() const;
    void uiSetO3(bool o3);
    bool uiGetO3() const;
    void uiSetU3(bool u3);
    bool uiGetU3() const;
    void uiSetO5(bool o5);
    bool uiGetO5() const;
    void uiSetU5(bool u5);
    bool uiGetU5() const;
    void uiSetO7(bool o7);
    bool uiGetO7() const;
    void uiSetU7(bool u7);
    bool uiGetU7() const;
    void uiSetO9(bool o9);
    bool uiGetO9() const;
    void uiSetU9(bool u9);
    bool uiGetU9() const;
    void uiSetO11(bool o11);
    bool uiGetO11() const;
    void uiSetU11(bool u11);
    bool uiGetU11() const;

protected:
    void detachParameterListeners() override;

private:
    WilsonicProcessor& _processor;
    shared_ptr<Partch> _partch;
    void _tuningChangedUpdateUI() override;
};
