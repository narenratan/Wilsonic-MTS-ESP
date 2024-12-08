/*
  ==============================================================================

    MorphFavoritesAComponent.cpp
    Created: 30 Jan 2024 7:32:58pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include <JuceHeader.h>
#include "DesignsModel.h"
#include "FavoritesIconRenderer.h"
#include "FavoritesModelV2.h"
#include "MorphFavoritesAComponent.h"
#include "MorphModel.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

MorphFavoritesAComponent::MorphFavoritesAComponent(WilsonicProcessor& processor)
: WilsonicComponentBase(processor)
{
    auto const fm = _processor.getFavoritesModelV2();
    auto const mm = _processor.getMorphModel();

    // configure table
    _table = make_unique<TableListBox>("Morph A", this); // TableListBoxModel is this
    addAndMakeVisible(*_table);
    _table->setRowHeight(FavoritesIconRenderer::tableviewHeight);
    _table->setColour(ListBox::outlineColourId, Colours::grey);
    _table->setOutlineThickness(1);
    _table->setMultipleSelectionEnabled(false);
    _table->getHeader().setStretchToFitActive(true);
    
    // configure columns for table
    bool found_first_sortable_column = false;
    auto columns = fm->getColumns();
    for(auto c : columns)
    {
        // this is lame...overwrite the column's propertyflags if visible == 0
        // the logic for columns is spread across the model, component, xml
        if(! c.visible)
        {
            c.propertyFlags = 0;
        }
        
        // default sort order to first sortable column
        if(c.sortable == 1)
        {
            if(found_first_sortable_column == false)
            {
                found_first_sortable_column = true;
                _table->getHeader().setSortColumnId(c.columnId, true);
            }
        }
        
        // add visible columns to header
        _table->getHeader().addColumn(c.columnName,
                                       c.columnId,
                                       c.width,
                                       c.minimumWidth,
                                       c.maximumWidth,
                                       c.propertyFlags,//could be overwritten above
                                       c.insertIndex);
    }
    
    // init
    actionListenerCallback(DesignsModel::getMorphTuningChangedActionMessage());
    
    // add self as listener for model changes
    mm->addActionListener(this);
}

MorphFavoritesAComponent::~MorphFavoritesAComponent()
{
    auto const mm = _processor.getMorphModel();
    mm->removeActionListener(this);
}

#pragma mark - drawing

void MorphFavoritesAComponent::paint(Graphics& g)
{
    // BG
    g.fillAll(_processor.getAppSkin().getBgColor());

    if (AppExperiments::showDebugBoundingBox)
    {
        // DEBUG
        g.setColour(Colours::lightgreen);
        g.drawRect(getLocalBounds(), 1);

        // counter
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
    
    _table->repaint();
}

void MorphFavoritesAComponent::resized()
{
    _table->setBounds(getLocalBounds());
    repaint();
}

#pragma mark - ActionListener

void MorphFavoritesAComponent::actionListenerCallback(const String& message)
{
    if(message == DesignsModel::getMorphTuningChangedActionMessage())
    {
        _table->updateContent();
        auto const index = _processor.getFavoritesModelV2()->getFavoriteRowNumber(FavoritesModelV2::DataList::FavoritesA);
        _table->selectRow(index, false, true);
        _table->repaint();

        return;
    }

    jassertfalse;
}

#pragma mark - TableListBoxModel

String MorphFavoritesAComponent::getCellTooltip(int row_number, int /* columnId */)
{
    auto const desc = getText(row_number, 5);
    auto const params = getText(row_number, 6);
    auto tip = String();
    if(desc.isNotEmpty())
    {
        tip += "Description:\n" + desc + "\n\n";
    }
    tip += "Parameters:\n" + params;

    return tip;
}

int MorphFavoritesAComponent::getNumRows()
{
    return _processor.getFavoritesModelV2()->getNumRows(FavoritesModelV2::DataList::FavoritesA);
}

void MorphFavoritesAComponent::returnKeyPressed(int rowNumber)
{
    auto const ID = _processor.getFavoritesModelV2()->_IDForRowNumber(rowNumber, FavoritesModelV2::DataList::FavoritesA);
    _processor.getMorphModel()->uiSetID_A(ID);
}

void MorphFavoritesAComponent::cellDoubleClicked(int rowNumber, int /* columnNumber */, const MouseEvent&)
{
    auto const ID = _processor.getFavoritesModelV2()->_IDForRowNumber(rowNumber, FavoritesModelV2::DataList::FavoritesA);
    _processor.getMorphModel()->uiSetID_A(ID);
}

int MorphFavoritesAComponent::getColumnAutoSizeWidth(int columnId)
{
    return _processor.getFavoritesModelV2()->getColumnAutoSizeWidth(columnId);
}

void MorphFavoritesAComponent::sortOrderChanged(int newSortColumnId, bool isForwards)
{
    _processor.getFavoritesModelV2()->sortOrderChanged(newSortColumnId, isForwards, FavoritesModelV2::DataList::FavoritesA);
    _table->updateContent();
}

// This is overloaded from TableListBoxModel, and must update any custom components that we're using
Component* MorphFavoritesAComponent::refreshComponentForCell
 (int rowNumber,
  int columnId,
  bool /*isRowSelected*/,
  Component* existingComponentToUpdate
  )
{
    // non-editable, non-icon
    if(columnId == 1 ||
       columnId == 3 ||
       columnId == 4 ||
       columnId == 5 || // was EditableTextCustomComponent
       columnId == 6 ||
       columnId == 7) // columns that have TextCustomComponent
    {
        auto* staticLabel = static_cast<TextCustomComponent*>(existingComponentToUpdate);
        if(staticLabel == nullptr)
        {
            staticLabel = new TextCustomComponent(*this);
        }
        staticLabel->setRowAndColumn(rowNumber, columnId);
        staticLabel->setInterceptsMouseClicks(false, false);

        return staticLabel;
    }
    // icon
    else if(columnId == 2)
    {
        auto* icon = static_cast<FavoritesIcon*>(existingComponentToUpdate);
        if(icon == nullptr)
        {
            icon = new FavoritesIcon(*this);
        }
        icon->setRowAndColumn(rowNumber, columnId);

        return icon;
    }
    else
    {
        DBG("WARNING: leftover columnID: " + String(columnId));
    }

    jassert(existingComponentToUpdate == nullptr);
    return nullptr;
}

void MorphFavoritesAComponent::paintRowBackground(Graphics& g,
                                            int rowNumber,
                                            int /* width */,
                                            int /* height */ ,
                                            bool rowIsSelected)
{
    if(rowIsSelected)
    {
        g.fillAll( _processor.getAppSkin().getTableListBoxBGColour());
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

void MorphFavoritesAComponent::paintCell(Graphics& g,
                                   int rowNumber,
                                   int columnId,
                                   int width,
                                   int height,
                                   bool rowIsSelected)
{
    g.setColour(rowIsSelected ? Colours::white : Colours::white);
    auto const fm = _processor.getFavoritesModelV2();
    g.setFont(fm->getFont());
    auto text = fm->getText(rowNumber, columnId, FavoritesModelV2::DataList::FavoritesA);
    g.drawText(text, 2, 0, width - 4, height, Justification::centredLeft, true);
    g.setColour(Colours::black);
    g.fillRect(width - 1, 0, 1, height); // rightmost vertical line
}

Font MorphFavoritesAComponent::getFont()
{
    return _processor.getFavoritesModelV2()->getFont();
}

String MorphFavoritesAComponent::getText(int rowNumber, int columnId)
{
    return _processor.getFavoritesModelV2()->getText(rowNumber, columnId, FavoritesModelV2::DataList::FavoritesA);
}

void MorphFavoritesAComponent::setText(const int /*columnNumber*/, const int /*rowNumber*/, const String& /*newText*/)
{
    // NOP
}

int MorphFavoritesAComponent::getSelection(const int rowNumber) const
{
    return _processor.getFavoritesModelV2()->getSelection(rowNumber, FavoritesModelV2::DataList::FavoritesA);
}

void MorphFavoritesAComponent::setSelection(const int rowNumber, const int newSelection)
{
    _processor.getFavoritesModelV2()->setSelection(rowNumber, newSelection, FavoritesModelV2::DataList::FavoritesA);
}

shared_ptr<Image> MorphFavoritesAComponent::getIcon(int rowNumber)
{
    return _processor.getFavoritesModelV2()->getIcon(rowNumber, FavoritesModelV2::DataList::FavoritesA);
}
