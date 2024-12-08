/*
  ==============================================================================

    DeltaComboBox.h
    Created: 12 Sep 2021 3:53:28pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DeltaSlider.h"
#include "Tuning_Include.h"
#include "WilsonicComponentBase.h"

// widget used to support:
// a daw-automatable combo box
// if constructed with "showDelta" = true then also show an accompanying slider with +/- to inc/dec the combo box,
// a combo box attachment to attach to the daw param

class DeltaComboBox 
: public WilsonicComponentBase
{
    // lifecycle
public:
    DeltaComboBox(WilsonicProcessor&, bool showDelta = true);
    ~DeltaComboBox() override;
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeltaComboBox)

public:
    // drawing
    void paint(Graphics&) override;
    void resized() override;

    // public members
    // these callbacks have a useful default when nullptr
    function<void()> onValueIncremented {nullptr};
    function<void()> onValueDecremented {nullptr};

    // public methods
    void clear(const NotificationType notification);
    void setSelectedItemIndex(const int index, const NotificationType notification);
    int getSelectedItemIndex() const;
    String getSelectedItemText();
    String getSelectedItemText(int index);
    int getNumItems() const noexcept;
    void addItem(const String& newItemText, int newItemId);
    void addItemList(const StringArray& itemsToAdd, int firstItemID);
    void setOnChange(function<void()>);
    void setComboBoxAttachment(shared_ptr<AudioProcessorValueTreeState> stateToUse, const String& parameterID);
    void setIsSelected(bool isSelected);
    bool getIsSelected();
    void setToolTip(const String& newTooltip);

private:
    // private members
    ComboBox _comboBox;
    DeltaSlider _deltaSlider;
    unique_ptr<AudioProcessorValueTreeState::ComboBoxAttachment> _comboBoxAttachment;
    bool _isSelected {false};
    bool _showDelta {true};

    // private methods
    void _incrementSelection();
    void _decrementSelection();
};
