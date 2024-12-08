/*
  ==============================================================================

    EulerGenusViewModel.h
    Created: 10 Dec 2021 2:59:33pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>
#include "EulerGenusModel.h"
#include "Tuning_Include.h"
#include "CPSTuningBase.h"

// EulerGenusViewModel represents the parent tuning and it's 2 sets of subsets
// It parallels CPSTuningBase and provides all state for Components
// It's just a container, so all the logic still lies in EulerGenusModel
struct EulerGenusViewModel
{
    // The unique key for all tuning/selection states of EulerGenus 6
    // NOTE: dawKey, dawBackKey, and dawDrillKey are the same set.
    DAWKey dawKey; // i.e., "CPS_6_3(A,B,C,D,E,F)__CPS_5_2(A,B,C,D,E)*F"

    // the daw key for when you hit "back" for this selected state (command-click)
    DAWKey dawBackKey; // i.e., CPS_6_3(A,B,C,D,E,F)__CPS_6_3(A,B,C,D,E,F)

    // the daw key for when you hit "drill"
    DAWKey dawDrillKey; // i.e., CPS_5_2(A,B,C,D,E)*F__CPS_5_2(A,B,C,D,E)*F

    // The unique key for the parent CPSTuningBase and its subsets for the page
    TuningKey parentTuningKey; // i.e., "CPS_6_3(A,B,C,D,E,F)"

    // parent tuning.  either the parent itself, or one of it's subsets is selected
    shared_ptr<CPSTuningBase> parentTuning;
};
