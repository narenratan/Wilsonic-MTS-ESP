/*
  ==============================================================================

    RecurrenceRelationCoeficcientComponent.h
    Created: 23 Mar 2022 8:03:18pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DeltaComboBox.h"
#include "RecurrenceRelation.h"
#include "Tuning_Include.h"
#include "WilsonicProcessor.h"
#include "WilsonicAppTuningComponent.h"

// not intended to be reusable...tightly coupled with RecurrenceRelationModel

class RecurrenceRelationCoefficientComponent
: public WilsonicComponentBase
{
    // lifecycle
public:
    RecurrenceRelationCoefficientComponent(WilsonicProcessor&);
    ~RecurrenceRelationCoefficientComponent() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RecurrenceRelationCoefficientComponent)

public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;

    // public methods
    void setC_1_9(unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, unsigned long, NotificationType);
    void selectIJ(unsigned long i, unsigned long j); // also deselects terms not equal to i,j

private:
    vector<shared_ptr<DeltaComboBox>> _comboBoxArray {};
    shared_ptr<DeltaComboBox> _Cn_1;
    shared_ptr<DeltaComboBox> _Cn_2;
    shared_ptr<DeltaComboBox> _Cn_3;
    shared_ptr<DeltaComboBox> _Cn_4;
    shared_ptr<DeltaComboBox> _Cn_5;
    shared_ptr<DeltaComboBox> _Cn_6;
    shared_ptr<DeltaComboBox> _Cn_7;
    shared_ptr<DeltaComboBox> _Cn_8;
    shared_ptr<DeltaComboBox> _Cn_9;
    CriticalSection _lock;
    void _setXHelper(unsigned long, unsigned long, NotificationType);
};
