/*

    RecurrenceRelationCoeficcientComponent.cpp
    Created: 23 Mar 2022 8:03:18pm
    Author:  Marcus W. Hobbs

*/
#include <JuceHeader.h>
#include "DesignsModel.h"
#include "RecurrenceRelation.h"
#include "RecurrenceRelationModel.h"
#include "RecurrenceRelationCoefficientComponent.h"


#pragma mark - lifecycle

RecurrenceRelationCoefficientComponent::RecurrenceRelationCoefficientComponent(WilsonicProcessor& processor)
: WilsonicComponentBase(processor)
{
    // pre-allocate and add sliders to simplify component lifecycle and flows

    auto rrm = _processor.getDesignsModel()->getRecurrenceRelationModel();

    _Cn_1 = make_unique<DeltaComboBox>(_processor, false);
    _Cn_1->addItemList(RecurrenceRelation::getCoefficientsDescription(), 1);
    auto const cn1i = rrm->uiGetCoefficient(1);
    _Cn_1->setSelectedItemIndex(static_cast<int>(cn1i), NotificationType::dontSendNotification);
    _Cn_1->setOnChange([rrm, this](){rrm->uiSetCoefficient(static_cast<unsigned long>(_Cn_1->getSelectedItemIndex()), 1);});
    _Cn_1->setToolTip("C[n-1]");
    // order is important...setting the attachment calls the callback to properly init
    _Cn_1->setComboBoxAttachment(_processor.getApvts(), RecurrenceRelationModel::getRecurrenceRelationCn1ParameterID().getParamID());

    _Cn_2 = make_unique<DeltaComboBox>(_processor, false);
    _Cn_2->addItemList(RecurrenceRelation::getCoefficientsDescription(), 2);
    auto const cn2i = rrm->uiGetCoefficient(2);
    _Cn_2->setSelectedItemIndex(static_cast<int>(cn2i), NotificationType::dontSendNotification);
    _Cn_2->setOnChange([rrm, this](){rrm->uiSetCoefficient(static_cast<unsigned long>(_Cn_2->getSelectedItemIndex()), 2);});
    _Cn_2->setToolTip("C[n-2]");
    // order is important...setting the attachment calls the callback to properly init
    _Cn_2->setComboBoxAttachment(_processor.getApvts(), RecurrenceRelationModel::getRecurrenceRelationCn2ParameterID().getParamID());

    _Cn_3 = make_unique<DeltaComboBox>(_processor, false);
    _Cn_3->addItemList(RecurrenceRelation::getCoefficientsDescription(), 3);
    auto const cn3i = rrm->uiGetCoefficient(3);
    _Cn_3->setSelectedItemIndex(static_cast<int>(cn3i), NotificationType::dontSendNotification);
    _Cn_3->setOnChange([rrm, this](){rrm->uiSetCoefficient(static_cast<unsigned long>(_Cn_3->getSelectedItemIndex()), 3);});
    _Cn_3->setToolTip("C[n-3]");
    // order is important...setting the attachment calls the callback to properly init
    _Cn_3->setComboBoxAttachment(_processor.getApvts(), RecurrenceRelationModel::getRecurrenceRelationCn3ParameterID().getParamID());

    _Cn_4 = make_unique<DeltaComboBox>(_processor, false);
    _Cn_4->addItemList(RecurrenceRelation::getCoefficientsDescription(), 4);
    auto const cn4i = rrm->uiGetCoefficient(4);
    _Cn_4->setSelectedItemIndex(static_cast<int>(cn4i), NotificationType::dontSendNotification);
    _Cn_4->setOnChange([rrm, this](){rrm->uiSetCoefficient(static_cast<unsigned long>(_Cn_4->getSelectedItemIndex()), 4);});
    _Cn_4->setToolTip("C[n-4]");
    // order is important...setting the attachment calls the callback to properly init
    _Cn_4->setComboBoxAttachment(_processor.getApvts(), RecurrenceRelationModel::getRecurrenceRelationCn4ParameterID().getParamID());

    _Cn_5 = make_unique<DeltaComboBox>(_processor, false);
    _Cn_5->addItemList(RecurrenceRelation::getCoefficientsDescription(), 5);
    auto const cn5i = rrm->uiGetCoefficient(5);
    _Cn_5->setSelectedItemIndex(static_cast<int>(cn5i), NotificationType::dontSendNotification);
    _Cn_5->setOnChange([rrm, this](){rrm->uiSetCoefficient(static_cast<unsigned long>(_Cn_5->getSelectedItemIndex()), 5);});
    _Cn_5->setToolTip("C[n-5]");
    // order is important...setting the attachment calls the callback to properly init
    _Cn_5->setComboBoxAttachment(_processor.getApvts(), RecurrenceRelationModel::getRecurrenceRelationCn5ParameterID().getParamID());

    _Cn_6 = make_unique<DeltaComboBox>(_processor, false);
    _Cn_6->addItemList(RecurrenceRelation::getCoefficientsDescription(), 6);
    auto const cn6i = rrm->uiGetCoefficient(6);
    _Cn_6->setSelectedItemIndex(static_cast<int>(cn6i), NotificationType::dontSendNotification);
    _Cn_6->setOnChange([rrm, this](){rrm->uiSetCoefficient(static_cast<unsigned long>(_Cn_6->getSelectedItemIndex()), 6);});
    _Cn_6->setToolTip("C[n-6]");
    // order is important...setting the attachment calls the callback to properly init
    _Cn_6->setComboBoxAttachment(_processor.getApvts(), RecurrenceRelationModel::getRecurrenceRelationCn6ParameterID().getParamID());

    _Cn_7 = make_unique<DeltaComboBox>(_processor, false);
    _Cn_7->addItemList(RecurrenceRelation::getCoefficientsDescription(), 7);
    auto const cn7i = rrm->uiGetCoefficient(7);
    _Cn_7->setSelectedItemIndex(static_cast<int>(cn7i), NotificationType::dontSendNotification);
    _Cn_7->setOnChange([rrm, this](){rrm->uiSetCoefficient(static_cast<unsigned long>(_Cn_7->getSelectedItemIndex()), 7);});
    _Cn_7->setToolTip("C[n-7]");
    // order is important...setting the attachment calls the callback to properly init
    _Cn_7->setComboBoxAttachment(_processor.getApvts(), RecurrenceRelationModel::getRecurrenceRelationCn7ParameterID().getParamID());

    _Cn_8 = make_unique<DeltaComboBox>(_processor, false);
    _Cn_8->addItemList(RecurrenceRelation::getCoefficientsDescription(), 8);
    auto const cn8i = rrm->uiGetCoefficient(8);
    _Cn_8->setSelectedItemIndex(static_cast<int>(cn8i), NotificationType::dontSendNotification);
    _Cn_8->setOnChange([rrm, this](){rrm->uiSetCoefficient(static_cast<unsigned long>(_Cn_8->getSelectedItemIndex()), 8);});
    _Cn_8->setToolTip("C[n-8]");
    // order is important...setting the attachment calls the callback to properly init
    _Cn_8->setComboBoxAttachment(_processor.getApvts(), RecurrenceRelationModel::getRecurrenceRelationCn8ParameterID().getParamID());

    _Cn_9 = make_unique<DeltaComboBox>(_processor, false);
    _Cn_9->addItemList(RecurrenceRelation::getCoefficientsDescription(), 9);
    auto const cn9i = rrm->uiGetCoefficient(9);
    _Cn_9->setSelectedItemIndex(static_cast<int>(cn9i), NotificationType::dontSendNotification);
    _Cn_9->setOnChange([rrm, this](){rrm->uiSetCoefficient(static_cast<unsigned long>(_Cn_9->getSelectedItemIndex()), 9);});
    _Cn_9->setToolTip("C[n-9]");
    // order is important...setting the attachment calls the callback to properly init```
    _Cn_9->setComboBoxAttachment(_processor.getApvts(), RecurrenceRelationModel::getRecurrenceRelationCn9ParameterID().getParamID());

    // helper
    _comboBoxArray.push_back(_Cn_1);
    _comboBoxArray.push_back(_Cn_2);
    _comboBoxArray.push_back(_Cn_3);
    _comboBoxArray.push_back(_Cn_4);
    _comboBoxArray.push_back(_Cn_5);
    _comboBoxArray.push_back(_Cn_6);
    _comboBoxArray.push_back(_Cn_7);
    _comboBoxArray.push_back(_Cn_8);
    _comboBoxArray.push_back(_Cn_9);
    jassert(_comboBoxArray.size() == 9);

    // add to view hierarchy
    addAndMakeVisible(*_Cn_1);
    addAndMakeVisible(*_Cn_2);
    addAndMakeVisible(*_Cn_3);
    addAndMakeVisible(*_Cn_4);
    addAndMakeVisible(*_Cn_5);
    addAndMakeVisible(*_Cn_6);
    addAndMakeVisible(*_Cn_7);
    addAndMakeVisible(*_Cn_8);
    addAndMakeVisible(*_Cn_9);

    // default window size
    setSize(_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());
}

RecurrenceRelationCoefficientComponent::~RecurrenceRelationCoefficientComponent()
{

}

#pragma mark - drawing

void RecurrenceRelationCoefficientComponent::paint(Graphics& g)
{
    // BG
    g.fillAll(_processor.getAppSkin().getBgColor());

    if(AppExperiments::showDebugBoundingBox)
    {
        // DEBUG
        g.setColour(Colours::purple);
        g.drawRect(getLocalBounds(), 1);

        // counter
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
}

// | . [80] . | . [80] . | . [80] . | . [80] . | . [80] . | . [80] . |
void RecurrenceRelationCoefficientComponent::resized()
{
    // lock
    const ScopedLock sl(_lock);

    // resize each slider
    auto const numSliders = static_cast<float>(_comboBoxArray.size());
    auto area = getLocalBounds();
    auto const sliderWidth = area.getWidth() / numSliders;
    for(unsigned long i = 0; i < _comboBoxArray.size(); i++)
    {
        auto const comboBox = _comboBoxArray[i];
        auto ca = Rectangle<int>(static_cast<int>(area.getX() + i * sliderWidth), area.getY(), static_cast<int>(sliderWidth), area.getHeight());
        comboBox->setBounds(ca.reduced(5,0));
    }
}

#pragma mark - methods

void RecurrenceRelationCoefficientComponent::setC_1_9(unsigned long a, unsigned long b, unsigned long c, unsigned long d, unsigned long e, unsigned long f, unsigned long g, unsigned long h, unsigned long i,  NotificationType type)
{
    _setXHelper(a, 0, type);
    _setXHelper(b, 1, type);
    _setXHelper(c, 2, type);
    _setXHelper(d, 3, type);
    _setXHelper(e, 4, type);
    _setXHelper(f, 5, type);
    _setXHelper(g, 6, type);
    _setXHelper(h, 7, type);
    _setXHelper(i, 8, type);
}

void RecurrenceRelationCoefficientComponent::_setXHelper(unsigned long val, unsigned long index, NotificationType type)
{
    jassert(index < _comboBoxArray.size());

    // lock
    const ScopedLock sl(_lock);

    if(_comboBoxArray.size() >= index + 1)
    {
        auto s = _comboBoxArray[index];
        s->setSelectedItemIndex(static_cast<int>(val), type);
    }
    else
    {
        cout << "attempting to set a DeltaComboBox that is not visible: index:" << to_string(index) << endl;
        jassertfalse;
    }
}

void RecurrenceRelationCoefficientComponent::selectIJ(unsigned long i, unsigned long j)
{
    for(unsigned long index = 0; index < _comboBoxArray.size(); index++)
    {
        unsigned long index1 = index + 1; // array is [0,8], indices are [1,9]
        auto ss = _comboBoxArray[index];
        ss->setIsSelected(false);
        if(index1 == i || index1 == j)
        {
            ss->setIsSelected(true);
        }
    }
    repaint();
}
