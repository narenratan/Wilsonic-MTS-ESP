/*
  ==============================================================================

    EulerGenusModel+_createTuningConstructorMap.cpp
    Created: 22 Dec 2021 9:36:28pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "EulerGenusModel.h"

#pragma mark - lifecycle

#pragma mark - CODEGEN

void EulerGenusModel::_createTuningConstructorMap()
{
    // called only once during construction
    jassert(_tuningConstructorMap == nullptr);

    _tuningConstructorMap = make_unique<TuningConstructorMap> ();

    // this calls the codegen methods
#include "./EulerGenusModelCodegen/EulerGenusModel+_createTuningConstructorMap_methods.txt"
}

