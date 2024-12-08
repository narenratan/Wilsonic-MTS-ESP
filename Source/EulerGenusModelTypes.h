/*
  ==============================================================================

    EulerGenusModelTypes.h
    Created: 17 Jan 2024 7:53:36pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

// types
struct EulerGenusViewModel;
using DAWKey = String;
using DAWKeys = StringArray;
using ViewModelCache = unordered_map<DAWKey, shared_ptr<EulerGenusViewModel>>;
using ViewModelConstructor = function<shared_ptr<EulerGenusViewModel>(void)>;
using ViewModelConstructorMap = unordered_map<DAWKey, ViewModelConstructor>;
using TuningKey = String;
using TuningCache = unordered_map<TuningKey, shared_ptr<CPSTuningBase>>;
using TuningConstructor = function<shared_ptr<CPSTuningBase>(void)>;
using TuningConstructorMap = unordered_map<TuningKey, TuningConstructor>;
using TuningUpdateFunction = function<void()>;
using TuningUpdateFunctionMap = unordered_map<TuningKey, TuningUpdateFunction>;
using TuningSelectionFunction = function<void()>;
using TuningSelectionFunctionMap = unordered_map<DAWKey, TuningSelectionFunction>;
