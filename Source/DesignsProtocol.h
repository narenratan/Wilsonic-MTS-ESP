/*
  ==============================================================================

    DesignsProtocol.h
    Created: 12 Nov 2021 3:15:04pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

// ADD NEW SCALE DESIGN HERE

// adopted publically+privately by classes involved in changing the global app tuning
// ONLY tunings should be covered by this protocol; i.e., not the synth, settings, etc.

class DesignsProtocol {
public:
    virtual ~DesignsProtocol() = default;
    virtual void showBrunTuning() = 0;
    virtual void showCoPrimeTuning() = 0;
    virtual void showCPSTuning() = 0;
    virtual void showDiamondsTuning() = 0;
    virtual void showEqualTemperamentTuning() = 0;
    virtual void showEulerGenusV2Tuning() = 0;
    virtual void showMorphTuning() = 0;
    virtual void showPartchTuning() = 0;
    virtual void showPersian17NorthIndianTuning() = 0;
    virtual void showPresetsTuning() = 0;
    virtual void showRecurrenceRelationTuning() = 0;
    virtual void showScalaTuning() = 0;
    virtual void showTritriadicTuning() = 0;
};
