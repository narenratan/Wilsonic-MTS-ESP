/*
 ==============================================================================

 DiamondsComponent.cpp
 Created: 6 Jun 2023 4:30:27pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "DiamondsComponent.h"
#include "Diamonds.h"
#include "DesignsModel.h"

String const DiamondsComponent::__mainElementBubbleText = "Diamond:\nThe harmonic and subharmonic subsets to the right are\nall contained in this structure.\n\n* Selected scale is outlined in blue.\n* Shift-Mouse-Hover selects scale.\n* Cursor Left-Right-Up-Down selects scale.";
String const DiamondsComponent::__subsetsBubbleText = "Subsets:\nEach of these tunings is\ncontained in the diamond to the left.\nThe left column are the harmonic subsets.\nThe right column are the subharmonic subsets.\n\n* Shift-Mouse-Hover selects scale\n* Cursor Left-Right-Up-Down selects scale.";

DiamondsComponent::DiamondsComponent (WilsonicProcessor& processor)
: WilsonicAppTuningComponent(processor)
, _mainElementBubble(BubblePlacement::below, "M", __mainElementBubbleText)
, _subsetsBubble(BubblePlacement::below, "S", __subsetsBubbleText) {
    // model
    auto const dm = processor.getDiamondsModel();

    // bubbles
    addAndMakeVisible(_mainElementBubble);
    addAndMakeVisible(_subsetsBubble);

    // combo box
    _comboBox = make_unique<DeltaComboBox>(processor, true);
    addAndMakeVisible(*_comboBox);
    _comboBox->addItemList(dm->getScaleNames(), 1);
    _comboBox->setSelectedItemIndex(static_cast<int>(dm->uiGetSelectedScaleIndex()), NotificationType::dontSendNotification);
    auto onChange = [dm, this]() {
        auto const selectedItemIndex = static_cast<unsigned long>(_comboBox->getSelectedItemIndex());
        dm->uiSelectScale(selectedItemIndex);
        grabKeyboardFocus();
    };
    _comboBox->setOnChange(onChange);

    // Seed Slider
    _seedSliderComponent = make_unique<SeedSliderComponent>(processor);
    addAndMakeVisible (_seedSliderComponent.get());
    _seedSliderComponent->setSliderAtIndex(0, "A", dm->uiGetA(), [dm] (float f) {dm->uiSetA (f);});
    _seedSliderComponent->setSliderAtIndex(1, "B", dm->uiGetB(), [dm] (float f) {dm->uiSetB (f);});
    _seedSliderComponent->setSliderAtIndex(2, "C", dm->uiGetC(), [dm] (float f) {dm->uiSetC (f);});
    _seedSliderComponent->setSliderAtIndex(3, "D", dm->uiGetD(), [dm] (float f) {dm->uiSetD (f);});
    _seedSliderComponent->setSliderAtIndex(4, "E", dm->uiGetE(), [dm] (float f) {dm->uiSetE (f);});
    _seedSliderComponent->setSliderAtIndex(5, "F", dm->uiGetF(), [dm] (float f) {dm->uiSetF (f);});
    _seedSliderComponent->setSliderAtIndex(6, "G", dm->uiGetG(), [dm] (float f) {dm->uiSetG (f);});
    _seedSliderComponent->setSliderAtIndex(7, "H", dm->uiGetH(), [dm] (float f) {dm->uiSetH (f);});

    // parent
    _mainElement = make_unique<CPSElementComponentV2> (_processor);
    addAndMakeVisible(*_mainElement);

    // subsets
    for (auto i = 0; i < Diamonds::__MAX_NUM_DIAMOND_SUBSETS; i++) {
        auto s0 = make_shared<CPSElementComponentV2>(_processor);
        s0->setHideLabel(true);
        _subsets0.push_back(s0);
        addAndMakeVisible(*s0);
        s0->repaint();

        auto s1 = make_shared<CPSElementComponentV2>(_processor);
        s1->setHideLabel(true);
        _subsets1.push_back(s1);
        addAndMakeVisible(*s1);
        s1->repaint();
    }

    // default window size
    setSize(_processor.getAppSkin().getWindowWidth(), _processor.getAppSkin().getWindowHeight());

    // initialize the ui. [confirmed we need this here]
    _tuningChangedUpdateUI();

    // add self as action listener to model
    dm->addActionListener(this);

    // add self as action listener to processor
    _processor.getAppTuningModel()->addActionListener(this);

    // Component's "key listener"
    setWantsKeyboardFocus(true);
}

DiamondsComponent::~DiamondsComponent() {
    _processor.getAppTuningModel()->removeActionListener(this);
    _processor.getDiamondsModel()->removeActionListener(this);
}

#pragma mark - App Tuning Title

const string DiamondsComponent::getAppTuningTitle() {
    return "Diamonds";
}

#pragma mark - draw

void DiamondsComponent::paint(Graphics& g) {
    g.fillAll(_processor.getAppSkin().getBgColor());
    if(AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::lightgreen);
        g.drawRect(getLocalBounds(), 1);
        g.drawText(String(_debug_paint_counter++), getLocalBounds(), Justification::topRight);
    }
}


// chatgpt suggestion
/*
You can expand a component's bounds in JUCE by using the `Component::setBounds()` method in conjunction with the `Rectangle::expanded()` method.

Here is an example where a parent component expands the bounds of a child component:

```cpp
void ParentComponent::resized()
{
    juce::Rectangle<int> childBounds = childComponent.getBounds();
    childComponent.setBounds(childBounds.expanded(10));  // Expand the child's bounds by 10 units on all sides
}
```

In this example, `childComponent` is a member of `ParentComponent`. The `resized()` method is called whenever the `ParentComponent` is resized. This method gets the current bounds of the `childComponent`, expands those bounds by 10 units on all sides, and then sets the `childComponent`'s bounds to the expanded rectangle.

The `Rectangle::expanded()` method returns a new `Rectangle` that is larger than the original. The argument to `expanded()` is the amount to expand the rectangle on all sides. So `expanded(10)` will return a rectangle that is 20 units wider and 20 units taller than the original, and whose center is at the same position as the center of the original rectangle.

Please replace `childComponent` with the actual name of your child component and `10` with the actual number of units you want to expand the child's bounds.

 */
void DiamondsComponent::resized() {
    // Keep the main area the same size
    auto const margin = WilsonicAppSkin::tuningComponentInteriorMargin;
    auto area = getLocalBounds().reduced(static_cast<int>(margin));
    auto const componentHeight = static_cast<int>(WilsonicAppSkin::comboBoxHeight);
    auto const componentWidth = static_cast<int>(WilsonicAppSkin::comboBoxWidth);

    // Combobox
    auto tuningsArea = area.removeFromTop(componentHeight);
    tuningsArea.setWidth(componentWidth);
    tuningsArea.setX(tuningsArea.getX() + WilsonicAppTuningComponent::getFirstComboBoxInset());
    _comboBox->setBounds(tuningsArea);

    // Seeds
    auto seedsArea = area.removeFromTop(static_cast<int>(WilsonicAppSkin::seedSliderHeight));
    _seedSliderComponent->setBounds(seedsArea);

    // y margin between combo box and seeds
    area.removeFromTop(static_cast<int>(margin));

    // LAYOUT

    // vertical orientation of the subsets:
    // | combobox                                          |
    // | main element area 80% | subset0 10% | subset1 10% |
    //
    auto const mainWidthProportion = 0.5f;
    auto const bubble_width = static_cast<int>(WilsonicAppSkin::minHitPointSize);
    auto const singleSubsetWidthProportion = 0.5f * (1.f - mainWidthProportion);
    auto const columnWidth = area.getWidth() * singleSubsetWidthProportion; // calc first
    auto const subsetPitchWheelFontSizeMagic = 0.55f;
    auto const local_bounds = getLocalBounds();
    auto const offscreen_rect = Rectangle<int>(local_bounds.getWidth() + 1, local_bounds.getHeight()+1, 100, 100);
    auto move_offscreen = [offscreen_rect](shared_ptr<CPSElementComponentV2> element) {
        element->setBounds(offscreen_rect);
        element->setIsSelected (false);
    };

    // main element area
    auto parent_tuning = dynamic_cast<CPSTuningBase*>(_processor.getDiamondsModel()->getParentTuning().get());
    jassert(parent_tuning != nullptr);
    auto mainArea = area.removeFromLeft(static_cast<int>(area.getWidth() * mainWidthProportion));
    auto bubbleAreaMain = mainArea.removeFromTop(bubble_width);
    bubbleAreaMain.reduce(static_cast<int>(0.5f * bubbleAreaMain.getWidth() - 2 * bubble_width), 0);
    _mainElementBubble.setBounds(bubbleAreaMain);
    _mainElement->setIsSelected(parent_tuning->getIsSelected());
    _mainElement->setBounds(mainArea);
    _mainElement->setCustomFontScale(WilsonicAppSkin::defaultPitchWheelFontScale);
    _mainElement->repaint();

    // subset columns
    auto const num_s0 = parent_tuning->getSubsets0().size();
    auto const num_s1 = parent_tuning->getSubsets1().size();

    // bubble
    auto subsetBubbleArea = area.removeFromTop(bubble_width);
    subsetBubbleArea.reduce(static_cast<int>(0.5f * subsetBubbleArea.getWidth() - 2 * bubble_width), 0);
    _subsetsBubble.setBounds(subsetBubbleArea);

    // number of rows in subsets
    auto const numSubsetRows = static_cast<float>(num_s0); // subsets 0 and 1 are the same count
    auto const rowHeight = area.getHeight() / numSubsetRows;

    // loop through 2x8 subsets.  if they're defined resize them, else move them offscreen
    for (unsigned long i = 0; i < Diamonds::__MAX_NUM_DIAMOND_SUBSETS; i++) {
        auto sa = area.removeFromTop(static_cast<int>(rowHeight));
        auto s0Area = sa.withTrimmedRight(static_cast<int>(columnWidth)).reduced (3);
        auto s1Area = sa.withTrimmedLeft(static_cast<int>(columnWidth)).reduced (3);

        // subset0
        auto s0 = _subsets0[i];
        if (i < num_s0) {
            auto tuning0 = parent_tuning->getSubsets0()[i];
            s0->setBounds(s0Area);
            s0->setIsSelected(tuning0->getIsSelected());
            s0->setCustomFontScale (subsetPitchWheelFontSizeMagic);
            s0->repaint();
        } else {
            move_offscreen(s0);
        }

        // subset1
        auto s1 = _subsets1[i];
        if (i < num_s1) {
            auto tuning1 = parent_tuning->getSubsets1()[i];
            s1->setBounds(s1Area);
            s1->setIsSelected(tuning1->getIsSelected());
            s1->setCustomFontScale(subsetPitchWheelFontSizeMagic);
            s1->repaint();
        } else {
            move_offscreen(s1);
        }
    }
}

#pragma mark - key listener

bool DiamondsComponent::keyPressed(const KeyPress& key) {
    auto const dm = _processor.getDiamondsModel();
    if (key.isKeyCode (KeyPress::leftKey)) {
        dm->uiLeftArrowKeyPressed();
        return true;
    } else if (key.isKeyCode (KeyPress::upKey)) {
        dm->uiUpArrowKeyPressed();
        return true;
    } else if (key.isKeyCode(KeyPress::rightKey)) {
        dm->uiRightArrowKeyPressed();
        return true;
    } else if (key.isKeyCode(KeyPress::downKey)) {
        dm->uiDownArrowKeyPressed();
        return true;
    }

    return false;
}

#pragma mark - tuning changed

void DiamondsComponent::_tuningChangedUpdateUI() {
    // tuning model is updated...need to update UI
    // do NOT send notifications to update the model
    auto const dm = _processor.getDiamondsModel();
    _comboBox->setSelectedItemIndex(static_cast<int>(dm->uiGetSelectedScaleIndex()), dontSendNotification);

    // Update sliders and values
    _seedSliderComponent->showNumberOfSliders(dm->getNumberOfSeeds());
    _seedSliderComponent->setABCDEFGH(dm->uiGetA(), dm->uiGetB(), dm->uiGetC(), dm->uiGetD(), dm->uiGetE(), dm->uiGetF(), dm->uiGetG(), dm->uiGetH(), dontSendNotification);

    // Main element
    auto const dmp = dm->getParentTuning();
    _mainElement->setTuning(dmp);
    _mainElement->setSingleClickCompletionBlock([dm,dmp]() {dm->uiSelectScale(static_cast<unsigned long>(dmp->getDAWKey().getIntValue()));});

    // clear subset components
    for (auto s0_element_component : _subsets0) {
        s0_element_component->setTuning(nullptr);
        s0_element_component->setSingleClickCompletionBlock(nullptr);
    }
    for (auto s1_element_component : _subsets1) {
        s1_element_component->setTuning(nullptr);
        s1_element_component->setSingleClickCompletionBlock(nullptr);
    }

    // Subsets
    auto const num_s0 = dmp->getSubsets0().size();
    for(unsigned long i = 0; i < num_s0; i++) {
        // subset0
        auto const s0 = _subsets0[i];
        auto const t0 = dmp->getSubsets0()[i];
        s0->setTuning(t0);
        s0->setSingleClickCompletionBlock([dm,t0]() {dm->uiSelectScale(static_cast<unsigned long>(t0->getDAWKey().getIntValue()));});

        // subset1
        auto const s1 = _subsets1[i];
        auto const t1 = dmp->getSubsets1()[i];
        s1->setTuning(t1);
        s1->setSingleClickCompletionBlock([dm,t1]() {dm->uiSelectScale(static_cast<unsigned long>(t1->getDAWKey().getIntValue()));});
    }

    resized();
    repaint();
}

#pragma mark - ActionListener

void DiamondsComponent::actionListenerCallback(const String& message) {
    if(message == DesignsModel::getDiamondsTuningChangedActionMessage()) {
        _tuningChangedUpdateUI();
    } else if(message == AppTuningModel::getAppTuningModelChangedMessage()) { // pitch color changed
        // the CPSElementComponentV2's are listening to this message...let them repaint themselves
    }
}
