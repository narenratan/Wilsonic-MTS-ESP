/*
  ==============================================================================

    EulerGenusModel+_createDAWKeys.cpp
    Created: 28 Nov 2021 7:14:41pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "EulerGenusModel.h"

#pragma mark - lifecycle

#pragma mark - CODEGEN

void EulerGenusModel::_createDAWKeys()
{
    // called only once during construction
    jassert(_dawKeys == nullptr);

    _dawKeys = make_unique<DAWKeys>();

    // this calls the codegen methods
#include "./EulerGenusModelCodegen/EulerGenusModel+_createDAWKeys_methods.txt"
}
