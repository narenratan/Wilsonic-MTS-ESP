/*
  ==============================================================================

    EulerGenusModel+_createTuningUpdateMap.cpp
    Created: 22 Dec 2021 9:38:20pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "EulerGenusMorphModel.h"

#pragma mark - CODEGEN

void EulerGenusMorphModel::_createTuningUpdateMap()
{
    // called only once during construction
    jassert(_tuningUpdateMap == nullptr);

    _tuningUpdateMap = make_unique<TuningUpdateFunctionMap> ();

    // this calls the codegen methods
#include "./EulerGenusMorphModelCodegen/EulerGenusMorphModel+_createTuningUpdateMap_methods.txt"
}
