/*
  ==============================================================================

    EulerGenusModel+_createTuningConstructorMap.cpp
    Created: 22 Dec 2021 9:36:28pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "EulerGenusMorphModel.h"

#pragma mark - lifecycle

#pragma mark - CODEGEN

void EulerGenusMorphModel::_createTuningConstructorMap()
{
    // called only once during construction
    jassert(_tuningConstructorMap == nullptr);

    _tuningConstructorMap = make_unique<TuningConstructorMap> ();

    // this calls the codegen methods
#include "./EulerGenusMorphModelCodegen/EulerGenusMorphModel+_createTuningConstructorMap_methods.txt"
}

