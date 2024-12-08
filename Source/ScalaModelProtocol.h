/*
  ==============================================================================

    ScalaModelProtocol.h
    Created: 3 Apr 2023 6:20:35pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ScalaTuningImp.h"

// Abstract base class for methods common to ScalaUserModel and ScalaBundleModel
class ScalaModelProtocol
{
public:
    virtual ~ScalaModelProtocol() noexcept = default;
    
    virtual shared_ptr<ScalaTuningImp> getScalaTuningForID(int ID) = 0;// return nullptr if row is out of range
    virtual shared_ptr<ScalaTuningImp> getScalaTuningForRow(int row_number) = 0;// return nullptr if row is out of range
    virtual shared_ptr<ScalaTuningImp> recallPreviousScala() = 0;
    virtual shared_ptr<ScalaTuningImp> recallNextScala() = 0;
    virtual int getSelectedRowNumber() = 0;
    virtual int getSelectedID() = 0;
    virtual unordered_map<int, int> getIntegrityCheck() = 0;
    
    // TableListBoxModel delegates
    virtual int getNumRows() = 0;
    virtual String getText(int row_number, int column_id) = 0;
    virtual int getColumnAutoSizeWidth(int column_id) = 0;
    virtual void sortOrderChanged(int new_sort_column_id, bool is_forwards) = 0;
    virtual int getIsSelectedForRow(const int row_number) const = 0;
    virtual void selectRow(const int row_number) = 0;

    // lazily creates icon
    virtual shared_ptr<Image> getIcon(int rowNumber) = 0;
};
