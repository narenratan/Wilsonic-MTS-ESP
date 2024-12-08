/*
  ==============================================================================

    CoPrimeModel.h
    Created: 23 Apr 2023 12:40:48pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppVersion.h"
#include "CoPrime.h"
#include "ModelBase.h"
#include "TuningImp.h"
#include "Tuning_Include.h"

class AppTuningModel;

class CoPrimeModel final
: public ModelBase
, public ActionBroadcaster
{

public:

    // static

    // For variable A
    static const ParameterID getCoPrimeAParameterID() { return ParameterID ("COPRIMEA", AppVersion::getVersionHint()); }
    static const String getCoPrimeAParameterName() { return "CoPrime|A"; }

    // For variable B
    static const ParameterID getCoPrimeBParameterID() { return ParameterID ("COPRIMEB", AppVersion::getVersionHint()); }
    static const String getCoPrimeBParameterName() { return "CoPrime|B"; }

    // For variable C
    static const ParameterID getCoPrimeCParameterID() { return ParameterID ("COPRIMEC", AppVersion::getVersionHint()); }
    static const String getCoPrimeCParameterName() { return "CoPrime|C"; }

    // For variable D
    static const ParameterID getCoPrimeDParameterID() { return ParameterID ("COPRIMED", AppVersion::getVersionHint()); }
    static const String getCoPrimeDParameterName() { return "CoPrime|D"; }

    // For variable S
    static const ParameterID getCoPrimeSParameterID() { return ParameterID ("COPRIMES", AppVersion::getVersionHint()); }
    static const String getCoPrimeSParameterName() { return "CoPrime|S"; }

    // For variable T
    static const ParameterID getCoPrimeTParameterID() { return ParameterID ("COPRIMET", AppVersion::getVersionHint()); }
    static const String getCoPrimeTParameterName() { return "CoPrime|T"; }

    // For variable X
    static const ParameterID getCoPrimeXParameterID() { return ParameterID ("COPRIMEX", AppVersion::getVersionHint()); }
    static const String getCoPrimeXParameterName() { return "CoPrime|X"; }

    // For variable Y
    static const ParameterID getCoPrimeYParameterID() { return ParameterID ("COPRIMEY", AppVersion::getVersionHint()); }
    static const String getCoPrimeYParameterName() { return "CoPrime|Y"; }

    // Display Mode
    static const ParameterID getCoPrimeDisplayModeParameterID() { return ParameterID ("COPRIMEDISPLAYMODE", AppVersion::getVersionHint()); }
    static const String getCoPrimeDisplayModeParameterName() { return "CoPrime|Display Mode"; }

    // lifecycle
public:
    CoPrimeModel();
    ~CoPrimeModel() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CoPrimeModel)

public:
    // public methods
    shared_ptr<Tuning> getTuning() override;
    float uiGetA() const;
    void  uiSetA(float value);
    float uiGetB() const;
    void  uiSetB(float value);
    float uiGetC() const;
    void  uiSetC(float value);
    float uiGetD() const;
    void  uiSetD(float value);
    float uiGetS() const;
    void  uiSetS(float value);
    float uiGetT() const;
    void  uiSetT(float value);
    float uiGetX() const;
    void  uiSetX(float value);
    float uiGetY() const;
    void  uiSetY(float value);
    void  uiSetDisplayMode(CoPrime::DisplayMode new_mode);
    const int uiGetDisplayMode(); // yes return int instead of DisplayMode
    int nnForMouseInViewBounds(Point<int> xy, Rectangle<int> viewBounds); // starts at middleC

    // called only once: on construction of processor
    unique_ptr<AudioProcessorParameterGroup> createParams() override;
    String getGroupID() override;
    String getGroupName() override;
    String getSubgroupSeparator() override;
    ParameterID getDesignParameterID() override; // key for this design's Favorites array
    StringArray getFavoritesParameterIDs() override; // used for Favorites
    // called only once: when assigning _avpts
    void attachParameterListeners() override;
    void parameterChanged(const String& parameterID, float newValue) override;
    void updateProperties() override;

private:
    // private members
    shared_ptr<CoPrime> _coPrime;
    
    // private methods
    void _tuningChangedUpdateUI() override;
    void detachParameterListeners() override;
};

