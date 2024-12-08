/*
  ==============================================================================

    Columns.h
    Created: 15 Oct 2022 11:41:02am
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

// helper struct

struct Columns
{
    Columns(String in_columnName,
             int in_columnId,
             int in_width,
             int in_minimumWidth,
             int in_maximumWidth,
             int in_propertyFlags,
             int in_insertIndex,
             int in_visible,
             int in_editable,
             int in_sortable
             )
    {
        columnName = in_columnName;
        columnId = in_columnId;
        width = in_width;
        minimumWidth = in_minimumWidth;
        maximumWidth = in_maximumWidth;
        propertyFlags = in_propertyFlags;
        insertIndex = in_insertIndex;
        visible = in_visible;
        editable = in_editable;
        sortable = in_sortable;
    }
    //~Columns() {}
    String columnName;
    int columnId;
    int width;
    int minimumWidth;
    int maximumWidth;
    int propertyFlags;
    int insertIndex;
    int visible;
    int editable;
    int sortable;
};
