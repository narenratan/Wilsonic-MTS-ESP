/*
  ==============================================================================

    MorphABModel.cpp
    Created: 22 Dec 2023 4:37:15pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/
// ADD NEW SCALE DESIGN HERE

#include "MorphABModel.h"
#include "Brun2Model.h"
#include "Brun2MorphModel.h"
#include "CoPrimeModel.h"
#include "CoPrimeMorphModel.h"
#include "CPSModel.h"
#include "CPSMorphModel.h"
#include "DiamondsModel.h"
#include "DiamondsMorphModel.h"
#include "EqualTemperamentModel.h"
#include "EqualTemperamentMorphModel.h"
#include "EulerGenusModel.h"
#include "EulerGenusMorphModel.h"
#include "FavoritesModelV2.h"
#include "MorphModel.h"
#include "MorphModelBase.h"
#include "PartchMorphModel.h"
#include "Persian17NorthIndianModel.h"
#include "Persian17NorthIndianMorphModel.h"
#include "PresetsModel.h"
#include "PresetsMorphModel.h"
#include "RecurrenceRelationModel.h"
#include "RecurrenceRelationMorphModel.h"
#include "ScalaModel.h"
#include "ScalaMorphModel.h"
#include "TritriadicModel.h"
#include "TritriadicMorphModel.h"
#include "WilsonicProcessor.h"

// ADD NEW SCALE DESIGN HERE

MorphABModel::MorphABModel(WilsonicProcessor& processor)
: _processor(processor)
, _brun2MorphModel(make_shared<Brun2MorphModel>())
, _cpsMorphModel(make_shared<CPSMorphModel>())
, _coPrimeMorphModel(make_shared<CoPrimeMorphModel>())
, _diamondsMorphModel(make_shared<DiamondsMorphModel>())
, _equalTemperamentMorphModel(make_shared<EqualTemperamentMorphModel>())
, _eulerGenusMorphModel(make_shared<EulerGenusMorphModel>(_processor))
, _partchMorphModel(make_shared<PartchMorphModel>(_processor))
, _persian17NorthIndianMorphModel(make_shared<Persian17NorthIndianMorphModel>())
, _presetsMorphModel(make_shared<PresetsMorphModel>())
, _recurrenceRelationMorphModel(make_shared<RecurrenceRelationMorphModel>())
, _scalaMorphModel(make_shared<ScalaMorphModel>(_processor))
, _tritriadicMorphModel(make_shared<TritriadicMorphModel>())
, _tuning(make_shared<TuningImp>()) {
    // see defaults for _favorite in Favorites.h
}

MorphABModel::~MorphABModel() {
}

shared_ptr<Tuning> MorphABModel::getTuningForFavoritesID(int ID) {
    _favorite = _processor.getFavoritesModelV2()->_getFavoriteForID(ID);
    
    //
//    int ID = 0;
//    shared_ptr<Image> iconImage;
//    int designIndex = 0;
//    String designDescription = "";
//    int NPO = 1;
//    String tuningDescription = "";
//    vector<FavoriteParam01> parameters;
    
    // ADD NEW SCALE DESIGN HERE

    if(_favorite.designIndex == _processor.getPresetsModel()->getDesignIndex()) {
        _tuning = _getFavoriteAppliedToMorphModel(_favorite, _presetsMorphModel);
    } else if(_favorite.designIndex == _processor.getBrun2Model()->getDesignIndex()) {
        _tuning = _getFavoriteAppliedToMorphModel(_favorite, _brun2MorphModel);
    } else if(_favorite.designIndex == _processor.getPersian17NorthIndianModel()->getDesignIndex()) {
        _tuning = _getFavoriteAppliedToMorphModel(_favorite, _persian17NorthIndianMorphModel);
    } else if(_favorite.designIndex == _processor.getCPSModel()->getDesignIndex()) {
        _tuning = _getFavoriteAppliedToMorphModel(_favorite, _cpsMorphModel);
    } else if(_favorite.designIndex == _processor.getEulerGenusModel()->getDesignIndex()) {
        _tuning = _getFavoriteAppliedToMorphModel(_favorite, _eulerGenusMorphModel);
    } else if(_favorite.designIndex == _processor.getRecurrenceRelationModel()->getDesignIndex()) {
        _tuning = _getFavoriteAppliedToMorphModel(_favorite, _recurrenceRelationMorphModel);
    } else if(_favorite.designIndex == _processor.getEqualTemperamentModel()->getDesignIndex()) {
        _tuning = _getFavoriteAppliedToMorphModel(_favorite, _equalTemperamentMorphModel);
    } else if(_favorite.designIndex == _processor.getTritriadicModel()->getDesignIndex()) {
        _tuning = _getFavoriteAppliedToMorphModel(_favorite, _tritriadicMorphModel);
    } else if(_favorite.designIndex == _processor.getScalaModel()->getDesignIndex()) {
        _tuning = _getFavoriteAppliedToMorphModel(_favorite, _scalaMorphModel);
    } else if(_favorite.designIndex == _processor.getCoPrimeModel()->getDesignIndex()) {
        _tuning = _getFavoriteAppliedToMorphModel(_favorite, _coPrimeMorphModel);
    } else if(_favorite.designIndex == _processor.getDiamondsModel()->getDesignIndex()) {
        _tuning = _getFavoriteAppliedToMorphModel(_favorite, _diamondsMorphModel);
    } else if(_favorite.designIndex == _processor.getMorphModel()->getDesignIndex()) {
        jassertfalse; // You cannot morph a morph
    } else if(_favorite.designIndex == _processor.getPartchModel()->getDesignIndex()) {
        _tuning = _getFavoriteAppliedToMorphModel(_favorite, _partchMorphModel);
    } else {
        jassertfalse;
    }

    return _tuning;
}


shared_ptr<Tuning> MorphABModel::_getFavoriteAppliedToMorphModel(Favorite favorite, shared_ptr<MorphModelBase> morphModel) {
    //    int ID = 0;
    //    shared_ptr<Image> iconImage;
    //    int designIndex = 0;
    //    String designDescription = "";
    //    int NPO = 1;
    //    String tuningDescription = "";
    //    vector<FavoriteParam01> parameters;
        
    for(auto param : favorite.parameters) {
        morphModel->parameterChanged(param.parameterName, param.value);
    }
    
    // assumes that each parameter change updates the tuning of the morph model
    auto retVal = morphModel->getTuning();
    jassert(retVal != nullptr);
    
    // sync with AppTuningModel BEFORE morphing
    auto const atm = _processor.getAppTuningModel();
    retVal->setOctaveMiddleC(static_cast<int>(atm->uiGetOctaveMiddleC()));
    retVal->setNoteNumberMiddleC(static_cast<unsigned long>(atm->uiGetNoteNumberMiddleC()));
    retVal->setFrequencyMiddleC(atm->uiGetFrequencyMiddleC());
    retVal->setNPOOverride(static_cast<int>(atm->uiGetNPOOverride()));
    retVal->setNPOOverrideEnable(atm->uiGetNPOOverrideEnable());

    return retVal;
}
