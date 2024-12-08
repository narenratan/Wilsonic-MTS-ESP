/*
  ==============================================================================

    EulerGenusModel+_createViewModelConstructorMap.cpp
    Created: 21 Dec 2021 6:42:10pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "EulerGenusMorphModel.h"
#include "EulerGenusViewModel.h"

#pragma mark - CODEGEN

void EulerGenusMorphModel::_createViewModelConstructorMap()
{
    // called only once during construction
    jassert (_viewModelConstructorMap == nullptr);

    _viewModelConstructorMap = make_unique<ViewModelConstructorMap>();

    // this calls the codegen methods
#include "./EulerGenusMorphModelCodegen/EulerGenusMorphModel+_createViewModelConstructorMap_methods.txt"
}

