/*
 ==============================================================================

 WilsonicProcessor+Params.cpp
 Created: 30 Oct 2021 7:37:28pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

// ADD NEW SCALE DESIGN HERE
#include <algorithm>
#include "AppTuningModel.h"
#include "Brun2Model.h"
#include "CoPrimeModel.h"
#include "CPSModel.h"
#include "DesignsModel.h"
#include "DiamondsModel.h"
#include "EqualTemperamentModel.h"
#include "EulerGenusModel.h"
#include "FavoritesModelV2.h"
#include "MorphModel.h"
#include "PartchModel.h"
#include "Persian17NorthIndianModel.h"
#include "PresetsModel.h"
#include "RecurrenceRelationModel.h"
#include "ScalaModel.h"
#include "TritriadicModel.h"
#include "WilsonicEditor.h"
#include "WilsonicProcessor.h"

#pragma mark - params

// PARAMETER GROUPS

// ADD NEW SCALE DESIGN HERE

/**
 * @brief This function creates a parameter group for the WilsonicProcessor.
 * @return A ParameterLayout object containing the parameter group.
 */
AudioProcessorValueTreeState::ParameterLayout WilsonicProcessor::_createParamGroup() {
    // This pattern is used to manage the state of each page.
    // Each page has a model that is responsible for its entire, automatable state.
    // To release a new version without breaking automation, new parameters must be added to the end.
    // Note: Parameter groups do not seem to be a thing in the avpts
    // 0.20Beta
    auto designsParamGroup = _designsModel->createParams();
    auto brun2ParamGroup = _designsModel->getBrun2Model()->createParams(); // 0.22B added period
    auto coPrimeParamGroup = _designsModel->getCoPrimeModel()->createParams(); // added 0.25b
    auto cpsParamGroup = _designsModel->getCPSModel()->createParams();
    auto etParamGroup = _designsModel->getEqualTemperamentModel()->createParams();
    auto eulerGenusParamGroup = _designsModel->getEulerGenusModel()->createParams();
    auto persian17NorthIndianParamGroup = _designsModel->getPersian17NorthIndianModel()->createParams();
    auto presetParamGroup = _designsModel->getPresetsModel()->createParams();
    auto recurrenceRelationParamGroup = _designsModel->getRecurrenceRelationModel()->createParams();
    auto tritriadicParamGroup = _designsModel->getTritriadicModel()->createParams();
    auto appTuningParamGroup = _designsModel->getAppTuningModel()->createParams();
    auto scalaTuningParamGroup = _designsModel->getScalaModel()->createParams();
    auto diamondsParamGroup = _designsModel->getDiamondsModel()->createParams();
    auto morphParamGroup = _designsModel->getMorphModel()->createParams();
    auto partchParamGroup = _designsModel->getPartchModel()->createParams();
    auto favoritesParamGroup = _designsModel->getFavoritesModelV2()->createParams();

#if JucePlugin_IsSynth
    // If the plugin is a synthesizer, create a parameter group for the synth.
    auto synthParamGroup = _createSynthParams();
#endif
    // To release a new version without breaking automation, new parameters must be added to the end: HERE!

    // Create a unique_ptr to an AudioProcessorParameterGroup, which will contain all the parameter groups.
    auto wilsonicParamGroup = make_unique<AudioProcessorParameterGroup>
    ("Wilsonic", "Wilsonic", " | ",
     std::move(designsParamGroup),
     std::move(brun2ParamGroup),
     std::move(cpsParamGroup),
     std::move(etParamGroup),
     std::move(eulerGenusParamGroup),
     std::move(persian17NorthIndianParamGroup),
     std::move(presetParamGroup),
     std::move(recurrenceRelationParamGroup),
     std::move(tritriadicParamGroup),
#if JucePlugin_IsSynth
     std::move(synthParamGroup),
#endif
     std::move(appTuningParamGroup),
     std::move(coPrimeParamGroup),
     std::move(scalaTuningParamGroup),
     std::move(diamondsParamGroup),
     std::move(morphParamGroup),
     std::move(partchParamGroup),
     std::move(favoritesParamGroup)
     // To release a new version without breaking automation, new parameters must be added to the end
     );

    // Return a ParameterLayout object containing the parameter group.
    return AudioProcessorValueTreeState::ParameterLayout(std::move(wilsonicParamGroup));
}
