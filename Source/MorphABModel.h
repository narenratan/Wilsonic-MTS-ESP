/*
  ==============================================================================

    MorphABModel.h
    Created: 22 Dec 2023 4:37:15pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AppVersion.h"
#include "Favorite.h"
#include "ModelBase.h"
#include "Morph.h"
#include "Tuning.h"

// ADD NEW SCALE DESIGN HERE

// forward
class Brun2MorphModel;
class CoPrimeMorphModel;
class CPSMorphModel;
class DiamondsMorphModel;
class EqualTemperamentMorphModel;
class EulerGenusMorphModel;
class FavoritesModelV2;
class MorphModelBase;
class PartchMorphModel;
class Persian17NorthIndianMorphModel;
class PresetsMorphModel;
class RecurrenceRelationMorphModel;
class ScalaMorphModel;
class TritriadicMorphModel;
class WilsonicProcessor;

//
class MorphABModel final
{
public:
    MorphABModel(WilsonicProcessor& processor);
    ~MorphABModel();
    shared_ptr<Tuning> getTuningForFavoritesID(int ID); // Tuning will be sync'd with AppTuningModel octave/middlec/freq

private:
    WilsonicProcessor& _processor;

    shared_ptr<Brun2MorphModel> _brun2MorphModel;
    shared_ptr<CPSMorphModel> _cpsMorphModel;
    shared_ptr<CoPrimeMorphModel> _coPrimeMorphModel;
    shared_ptr<DiamondsMorphModel> _diamondsMorphModel;
    shared_ptr<EqualTemperamentMorphModel> _equalTemperamentMorphModel;
    shared_ptr<EulerGenusMorphModel> _eulerGenusMorphModel;
    
    // you cannot morph a morph
    
    shared_ptr<PartchMorphModel> _partchMorphModel;
    shared_ptr<Persian17NorthIndianMorphModel> _persian17NorthIndianMorphModel;
    shared_ptr<PresetsMorphModel> _presetsMorphModel;
    shared_ptr<RecurrenceRelationMorphModel> _recurrenceRelationMorphModel;
    shared_ptr<ScalaMorphModel> _scalaMorphModel;
    shared_ptr<TritriadicMorphModel> _tritriadicMorphModel;
    // ADD NEW SCALE DESIGN HERE

    //
    shared_ptr<Tuning> _tuning;
    Favorite _favorite;
    
    // helper
    shared_ptr<Tuning> _getFavoriteAppliedToMorphModel(Favorite favorite, shared_ptr<MorphModelBase> morphModel);
};
