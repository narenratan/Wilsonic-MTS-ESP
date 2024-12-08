/*
  ==============================================================================

    EulerGenusModel+_createTuningSelectionMap.cpp
    Created: 23 Dec 2021 12:17:02pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "EulerGenusModel.h"
#include "EulerGenusViewModel.h"

#pragma mark - lifecycle

#pragma mark - CODEGEN

void EulerGenusModel::_createTuningSelectionMap()
{
    // called only once during construction
    jassert(_tuningSelectionMap == nullptr);

    _tuningSelectionMap = make_unique<TuningSelectionFunctionMap> ();

    // this calls the codegen methods
#include "./EulerGenusModelCodegen/EulerGenusModel+_createTuningSelectionMap_methods.txt"
}
