/*
 ==============================================================================
 
 ScalaComponent+TableListBoxModel.cpp
 Created: 14 Nov 2022 2:02:32pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "ScalaComponent.h"
#include "ScalaModel.h"

#pragma mark - TableListBoxModel

int ScalaComponent::getNumRows()
{
    return _processor.getScalaModel()->getNumRows();
}

String ScalaComponent::getCellTooltip(int row_number, int column_id)
{
    return _processor.getScalaModel()->getCellTooltip(row_number, column_id);
}

void ScalaComponent::deleteKeyPressed(int lastRowSelected)
{
    DBG ("ScalaComponent::deleteKeyPressed: " + String(lastRowSelected));
    
    AlertWindow::showOkCancelBox
    (MessageBoxIconType::WarningIcon,
     "Delete Scala File at row " + String(lastRowSelected) + "?",
     "This will delete this Scala File,\nand every Favorite that refers to it.\nThis cannot be undone!",
     "Delete",
     "Cancel",
     this,
     ModalCallbackFunction::forComponent(_deleteKeyModalCallback, this, lastRowSelected)
     );
}

void ScalaComponent::_deleteKeyModalCallback(int modalResult, ScalaComponent* t, int lastRowSelected)
{
    if(modalResult == 1 && t != nullptr)
    {
        t->_deleteScalaAtRow(lastRowSelected);
    }
}

void ScalaComponent::_deleteScalaAtRow(int row)
{
    _processor.getScalaModel()->deleteScala(row);
}

void ScalaComponent::returnKeyPressed(int lastRowSelected)
{
    _processor.getScalaModel()->recallScalaByRow(lastRowSelected);
}

void ScalaComponent::cellDoubleClicked(int rowNumber, int, const MouseEvent&)
{
    _processor.getScalaModel()->recallScalaByRow(rowNumber);
}

int ScalaComponent::getColumnAutoSizeWidth(int columnId)
{
    return _processor.getScalaModel()->getColumnAutoSizeWidth(columnId);
}

void ScalaComponent::sortOrderChanged(int newSortColumnId, bool isForwards)
{
    _processor.getScalaModel()->sortOrderChanged(newSortColumnId, isForwards);
    _table->updateContent();
}

// This is overloaded from TableListBoxModel, and must update any custom components that we're using
Component* ScalaComponent::refreshComponentForCell(int row_number, int column_id, bool /*isRowSelected*/, Component* existing_component_to_update)
{
    // non-editable, non-icon
    if(column_id == 1 ||
       column_id == 3 ||
       column_id == 4 ||
       column_id == 5 ||
       column_id == 6 ||
       column_id == 7 ||
       column_id == 8 ||
       column_id == 9) // columns that have TextCustomComponent
    {
        auto* staticLabel = static_cast<TextCustomComponent*>(existing_component_to_update);
        if(staticLabel == nullptr)
        {
            staticLabel = new TextCustomComponent(*this);
        }
        staticLabel->setRowAndColumn(row_number, column_id);
        staticLabel->setJustificationType(Justification::centred);
        
        if(column_id == 7 || column_id == 8 || column_id == 9)
        {
            // desc/scala/kbm files are large, so justify as top left
            staticLabel->setJustificationType(Justification::topLeft);
        }
        
        return staticLabel;
    }
    // icon
    else if(column_id == 2)
    {
        auto* icon = static_cast<ScalaIcon*> (existing_component_to_update);
        if(icon == nullptr)
        {
            icon = new ScalaIcon (*this);
        }
        icon->setRowAndColumn(row_number, column_id);
        
        return icon;
    }
    else
    {
        DBG ("ScalaComponent::refreshComponentForCell: leftover columnID: " + String(column_id));
    }
    
    jassert(existing_component_to_update == nullptr);
    return nullptr;
}

void ScalaComponent::paintRowBackground(Graphics& g,
                                        int rowNumber,
                                        int /* width */,
                                        int /* height */ ,
                                        bool rowIsSelected)
{
    if(rowIsSelected)
    {
        g.fillAll(_processor.getAppSkin().getTableListBoxBGColour());
    }
    else
    {
        // alternates rows for easy reading
        g.fillAll((rowNumber % 2)
                  ? _processor.getAppSkin().getTableListBoxRow1Colour()
                  : _processor.getAppSkin().getTableListBoxRow0Colour()
                  );
    }
}

void ScalaComponent::paintCell(Graphics& g,
                               int row_number,
                               int column_id,
                               int width,
                               int height,
                               bool rowIsSelected)
{
    g.setColour(rowIsSelected ? Colours::white : Colours::white);
    auto fm = _processor.getScalaModel();
    g.setFont(fm->getFont());
    auto text = fm->getText(row_number, column_id);
    g.drawText(text, 2, 0, width - 4, height, Justification::centredLeft, true);
    g.setColour(Colours::black);
    g.fillRect(width - 1, 0, 1, height); // rightmost vertical line
}

Font ScalaComponent::getFont()
{
    return _processor.getScalaModel()->getFont();
}

String ScalaComponent::getText(int rowNumber, int columnId)
{
    return _processor.getScalaModel()->getText(rowNumber, columnId);
}

void ScalaComponent::setText(const int columnNumber, const int rowNumber, const String& newText)
{
    const auto& columnName = _table->getHeader().getColumnName(columnNumber);
    _processor.getScalaModel()->setText(columnName, rowNumber, newText);
}

int ScalaComponent::getSelection(const int rowNumber) const
{
    return _processor.getScalaModel()->getIsSelectedForRow(rowNumber);
}

void ScalaComponent::setSelection(const int rowNumber, const int /* newSelection */)
{
    DBG("ScalaComponent::setSelection: rowNumber:"+String(rowNumber));
    _processor.getScalaModel()->selectRow(rowNumber);
}

shared_ptr<Image> ScalaComponent::getIcon(int rowNumber)
{
    return _processor.getScalaModel()->getIcon(rowNumber);
}
