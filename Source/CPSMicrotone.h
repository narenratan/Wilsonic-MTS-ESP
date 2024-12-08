/*
  ==============================================================================

    CPSMicrotone.h
    Created: 10 Feb 2022 8:49:41pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "AppTuningModel.h"
#include "Microtone.h"
#include "TuningConstants.h"

struct CPSMicrotone_t; // forward decl
using CPSMicrotone = shared_ptr<CPSMicrotone_t>;
using CPSMicrotoneLine = tuple<CPSMicrotone, CPSMicrotone>;

struct CPSMicrotone_t
{
    // factory
    static CPSMicrotone create(Microtone_p mt_, Point<float> pt_) {
        return make_shared<CPSMicrotone_t>(mt_, pt_);
    }

    // factory: cps are centerless, but need an origin for drawing
    static CPSMicrotone create_center(Point<float> pt_) {
        return make_shared<CPSMicrotone_t>(make_shared<Microtone>(1, 1, "", Microtone::Space::Linear, TuningConstants::defaultPeriod), pt_);
    }

    // factory:
    static CPSMicrotoneLine create_line(CPSMicrotone x_, CPSMicrotone y_) {
        return make_tuple(x_, y_);
    }

    // lifecycle
    CPSMicrotone_t(Microtone_p mt_, Point<float> pt_) {
        mt = mt_;
        pt = pt_;
        isSubsetOfProcessorTuning = true;
    }
    
    ~CPSMicrotone_t() {}

    // members
    Microtone_p mt;
    Point<float> pt;

    // Updated in CPSTuningBase::paint
    // for efficiency in drawing routines where results of expensive double-for-loop
    // comparison of a cps processed array to the processor's processed array
    // need to be cached for point, text, playing point, and line drawing.
    // i.e., calculate once for 4 draw commands.
    bool isSubsetOfProcessorTuning;
};

