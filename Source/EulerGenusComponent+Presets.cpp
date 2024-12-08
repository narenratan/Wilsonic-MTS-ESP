///*
//  ==============================================================================
//
//    EulerGenusComponent+Presets.cpp
//    Created: 16 Nov 2021 4:44:31pm
//    Author:  Marcus W. Hobbs
//
//  ==============================================================================
//*/
//
//// TODO: Deprecate in favor of EulerGenusComponentV2
//
//#include "EulerGenusComponent.h"
//#include "EulerGenus_1.h"
//#include "EulerGenus_2.h"
//#include "EulerGenus_3.h"
//#include "EulerGenus_4.h"
//#include "EulerGenus_5.h"
//#include "EulerGenus_6.h"
//
//#pragma mark - Component Presets
//
//// tears down and rebuilds root component with new EulerGenus tuning
//
//void EulerGenusComponent::_addEulerGenus6Component()
//{
//    // tuning
//    auto eulerGenus6 = make_shared<EulerGenus_6> (CPS::A (1), CPS::B (3), CPS::C (5), CPS::D (7), CPS::E (9), CPS::F (11));
//    eulerGenus6->setOnTuningUpdate ([this] () {updateAppTuning(); } );
//    _setEulerGenus (eulerGenus6);
//
//    // seed slider
//    _seedSliderComponent->reset();
//    _seedSliderComponent->addSlider ("A", 1 , [eulerGenus6] (float v) { eulerGenus6->setA (v); } );
//    _seedSliderComponent->addSlider ("B", 3 , [eulerGenus6] (float v) { eulerGenus6->setB (v); } );
//    _seedSliderComponent->addSlider ("C", 5 , [eulerGenus6] (float v) { eulerGenus6->setC (v); } );
//    _seedSliderComponent->addSlider ("D", 7 , [eulerGenus6] (float v) { eulerGenus6->setD (v); } );
//    _seedSliderComponent->addSlider ("E", 9 , [eulerGenus6] (float v) { eulerGenus6->setE (v); } );
//    _seedSliderComponent->addSlider ("F", 11, [eulerGenus6] (float v) { eulerGenus6->setF (v); } );
//
//    // eg 6 presets
//    auto notification_type = NotificationType::dontSendNotification;
//    _presetsComboBox->clear (notification_type);
//    vector<EGPresetHelper> presets
//    {
//        // mind the index
//        {"1, 3, 5, 7, 9, 11",         1, [this, notification_type] () {_seedSliderComponent->setABCDEF (1, 3, 5, 7, 9, 11, notification_type);}},
//        {"1, 45, 135, 225, 17, 65",   2, [this, notification_type] () {_seedSliderComponent->setABCDEF (1, 45, 135, 225, 17, 65, notification_type);}},
//        {"1, 75, 19, 5, 3, 15",       3, [this, notification_type] () {_seedSliderComponent->setABCDEF (1, 75, 19, 5, 3, 15, notification_type);}},
//        {"6, 7, 8, 9, 10, 11: Grady", 4, [this, notification_type] () {_seedSliderComponent->setABCDEF (6, 7, 8, 9, 10, 11, notification_type);}},//octave 4
//
//    };
//
//    for (auto p : presets)
//    {
//        _presetsComboBox->addItem (p.title, p.index);
//    }
//
//    auto onChange = [this, presets]()
//    {
//        if (isShowing())
//        {
//            auto const selectedItemIndex = _presetsComboBox->getSelectedItemIndex();
//            for (auto p : presets)
//            {
//                if (p.index == selectedItemIndex + 1)
//                {
//                    p.callback();
//                }
//            }
//        }
//    };
//
//    _presetsComboBox->setOnChange (onChange);
//    _presetsComboBox->setSelectedItemIndex (1, NotificationType::sendNotificationAsync);
//
//    // draw
//    repaint();
//}
//
//void EulerGenusComponent::_addEulerGenus5Component()
//{
//    // tuning
//    auto eulerGenus5 = make_shared<EulerGenus_5> (CPS::A (1), CPS::B (3), CPS::C (5), CPS::D (7), CPS::E (9));
//    eulerGenus5->setOnTuningUpdate ([this] () {updateAppTuning(); } );
//    _setEulerGenus (eulerGenus5);
//
//    // seed slider
//    _seedSliderComponent->reset();
//    _seedSliderComponent->addSlider ("A", 1 , [eulerGenus5] (float v) { eulerGenus5->setA (v); } );
//    _seedSliderComponent->addSlider ("B", 3 , [eulerGenus5] (float v) { eulerGenus5->setB (v); } );
//    _seedSliderComponent->addSlider ("C", 5 , [eulerGenus5] (float v) { eulerGenus5->setC (v); } );
//    _seedSliderComponent->addSlider ("D", 7 , [eulerGenus5] (float v) { eulerGenus5->setD (v); } );
//    _seedSliderComponent->addSlider ("E", 9 , [eulerGenus5] (float v) { eulerGenus5->setE (v); } );
//
//    // eg 5 presets
//    auto notification_type = NotificationType::dontSendNotification;
//    _presetsComboBox->clear (notification_type);
//    vector<EGPresetHelper> presets
//    {
//        // mind the index
//        {"1, 3, 5, 7, 9",        1, [this, notification_type](){_seedSliderComponent->setABCDE (1, 3, 5, 7, 9, notification_type);}},
//        {"1, 45, 135, 225, 17",  2, [this, notification_type](){_seedSliderComponent->setABCDE (1, 45, 135, 225, 17, notification_type);}},
//        {"1, 3, 5, 9, 121",      3, [this, notification_type](){_seedSliderComponent->setABCDE (1, 3, 5, 9, 121, notification_type);}},
//        {"1, 3, 5, 81, 121",     4, [this, notification_type](){_seedSliderComponent->setABCDE (1, 3, 5, 9, 121, notification_type);}},
//        {"1, 19, 5, 3, 15",      5, [this, notification_type](){_seedSliderComponent->setABCDE (1, 19, 5, 3, 15, notification_type);}},
//        {"8, 10, 11, 12, 14",    6, [this, notification_type](){_seedSliderComponent->setABCDE (8, 10, 11, 12, 14, notification_type);}},
//        {"3, 5, 7, 15, 35",      7, [this, notification_type](){_seedSliderComponent->setABCDE (3, 5, 7, 15, 35, notification_type);}},
//        {"1, 3, 5, 75, 15",      8, [this, notification_type](){_seedSliderComponent->setABCDE (1, 3, 5, 75, 15, notification_type);}},
//        {"4, 5, 6, 7, 9: Grady", 9, [this, notification_type](){_seedSliderComponent->setABCDE (4, 5, 6, 7, 9, notification_type);}},
//    };
//    for (auto p : presets)
//    {
//        _presetsComboBox->addItem (p.title, p.index);
//    }
//    auto onChange = [this, presets]()
//    {
//        if (isShowing())
//        {
//            auto const selectedItemIndex = _presetsComboBox->getSelectedItemIndex();
//            for (auto p : presets)
//            {
//                if (p.index == selectedItemIndex + 1)
//                {
//                    p.callback();
//                }
//            }
//        }
//    };
//    _presetsComboBox->setOnChange (onChange);
//    _presetsComboBox->setSelectedItemIndex (1, NotificationType::sendNotificationAsync);
//
//    // draw
//    repaint();
//}
//
//void EulerGenusComponent::_addEulerGenus4Component()
//{
//    // tuning
//    auto eulerGenus4 = make_shared<EulerGenus_4> (CPS::A (1), CPS::B (3), CPS::C (5), CPS::D (121));
//    eulerGenus4->setOnTuningUpdate ([this] () {updateAppTuning(); } );
//    _setEulerGenus (eulerGenus4);
//
//    // seed slider
//    _seedSliderComponent->reset();
//    _seedSliderComponent->addSlider ("A", 1  , [eulerGenus4](float v) { eulerGenus4->setA (v); } );
//    _seedSliderComponent->addSlider ("B", 3  , [eulerGenus4](float v) { eulerGenus4->setB (v); } );
//    _seedSliderComponent->addSlider ("C", 5  , [eulerGenus4](float v) { eulerGenus4->setC (v); } );
//    _seedSliderComponent->addSlider ("D", 121, [eulerGenus4](float v) { eulerGenus4->setD (v); } );
//
//    // eg 4 presets
//    auto notification_type = NotificationType::dontSendNotification;
//    _presetsComboBox->clear(NotificationType::dontSendNotification);
//    vector<EGPresetHelper> presets
//    {
//        {"1, 3, 5, 7",       1, [this, notification_type](){_seedSliderComponent->setABCD (1, 3, 5, 7, notification_type);}},
//        {"1, 3, 5, 45",      2, [this, notification_type](){_seedSliderComponent->setABCD (1, 3, 5, 45, notification_type);}},
//        {"1, 3, 5, 9",       3, [this, notification_type](){_seedSliderComponent->setABCD (1, 3, 5, 9, notification_type);}},
//        {"1, 3, 5, 15",      4, [this, notification_type](){_seedSliderComponent->setABCD (1, 3, 5, 15, notification_type);}},
//        {"1, 3, 5, 81",      5, [this, notification_type](){_seedSliderComponent->setABCD (1, 3, 5, 81, notification_type);}},
//        {"1, 3, 5, 121",     6, [this, notification_type](){_seedSliderComponent->setABCD (1, 3, 5, 121, notification_type);}},
//        {"1, 15, 45, 75",    7, [this, notification_type](){_seedSliderComponent->setABCD (1, 15, 45, 75, notification_type);}},
//        {"1, 17, 19, 23",    8, [this, notification_type](){_seedSliderComponent->setABCD (1, 17, 19, 23, notification_type);}},
//        {"1, 45, 135, 225",  9, [this, notification_type](){_seedSliderComponent->setABCD (1, 45, 135, 225, notification_type);}},
//        {"3, 5, 7, 9",      10, [this, notification_type](){_seedSliderComponent->setABCD (3, 5, 7, 9, notification_type);}},
//        {"3, 5, 15, 19",    11, [this, notification_type](){_seedSliderComponent->setABCD (3, 5, 15, 19, notification_type);}},
//        {"5, 7, 21, 35",    12, [this, notification_type](){_seedSliderComponent->setABCD (5, 7, 21, 35, notification_type);}},
//        {"9, 25, 49, 81",   13, [this, notification_type](){_seedSliderComponent->setABCD (9, 25, 49, 81, notification_type);}},
//
//        // add these when you figure out incremental (i.e., integer or float)
//        //{"3, 2.111, 5.111, 8.111", 14, [this](){_seedSliderComponent->setABCD (3, 2.111f, 5.111f, 8.111f);}},
//        //{"3, 1.346, 4.346, 7.346", 15, [this](){_seedSliderComponent->setABCD (3, 1.346f, 4.346f, 7.346f);}},
//        //{"8/8, 8/7, 8/6, 8/5", 16, [this](){_seedSliderComponent->setABCD (8/8.f, 8/7.f, 8/6.f, 8/5.f);}},
//        // until then, use these x1000 integer step size versions
//        {"3000, 2111, 5111, 8111", 14, [this, notification_type](){_seedSliderComponent->setABCD (3000, 2111, 5111, 8111, notification_type);}},
//        {"3000, 1346, 4346, 7346", 15, [this, notification_type](){_seedSliderComponent->setABCD (3000, 1346, 4346, 7346, notification_type);}},
//
//        // cool re-seeding experiment...use eg 3 as a proportional triad and leave D as the wildcard...try subcontrary sometime
//        {"3, 4, 5  , *", 16, [this, notification_type](){_seedSliderComponent->setABCD (3, 4, 5  , 1, notification_type);}},
//        {"4, 5, 6  , *", 17, [this, notification_type](){_seedSliderComponent->setABCD (4, 5, 6  , 1, notification_type);}},
//        {"5, 6, 7  , *", 18, [this, notification_type](){_seedSliderComponent->setABCD (5, 6, 7  , 1, notification_type);}},
//        {"6, 7, 8  , *", 19, [this, notification_type](){_seedSliderComponent->setABCD (6, 7, 8  , 1, notification_type);}},
//        {"6, 8, 10 , *", 20, [this, notification_type](){_seedSliderComponent->setABCD (6, 8, 10 , 1, notification_type);}},
//        {"7, 8, 9  , *", 21, [this, notification_type](){_seedSliderComponent->setABCD (7, 8, 9  , 1, notification_type);}},
//        {"7, 9, 11 , *", 22, [this, notification_type](){_seedSliderComponent->setABCD (7, 9, 11 , 1, notification_type);}},
//        {"7, 10, 13, *", 23, [this, notification_type](){_seedSliderComponent->setABCD (7, 10, 13, 1, notification_type);}},
//        {"8, 9, 10 , *", 24, [this, notification_type](){_seedSliderComponent->setABCD (8, 9, 10 , 1, notification_type);}},
//        {"8, 10, 12, *", 25, [this, notification_type](){_seedSliderComponent->setABCD (8, 10, 12, 1, notification_type);}},
//        {"8, 11, 14, *", 26, [this, notification_type](){_seedSliderComponent->setABCD (8, 11, 14, 1, notification_type);}},
//        {"9, 10, 11, *", 27, [this, notification_type](){_seedSliderComponent->setABCD (9, 10, 11, 1, notification_type);}},
//        {"9, 11, 13, *", 28, [this, notification_type](){_seedSliderComponent->setABCD (9, 11, 13, 1, notification_type);}},
//        {"9, 12, 15, *", 29, [this, notification_type](){_seedSliderComponent->setABCD (9, 12, 15, 1, notification_type);}},
//        {"9, 13, 17, *", 30, [this, notification_type](){_seedSliderComponent->setABCD (9, 13, 17, 1, notification_type);}},
//
//
//    };
//    for (auto p : presets)
//    {
//        _presetsComboBox->addItem (p.title, p.index);
//    }
//    auto onChange = [this, presets]()
//    {
//        if (isShowing())
//        {
//            auto const selectedItemIndex = _presetsComboBox->getSelectedItemIndex();
//            for (auto p : presets)
//            {
//                if (p.index == selectedItemIndex + 1)
//                {
//                    p.callback();
//                }
//            }
//        }
//    };
//    _presetsComboBox->setOnChange (onChange);
//    _presetsComboBox->setSelectedItemIndex (1, NotificationType::sendNotificationAsync);
//
//    // draw
//    repaint();
//}
//
//void EulerGenusComponent::_addEulerGenus3Component()
//{
//    // tuning
//    auto eulerGenus3 = make_shared<EulerGenus_3> (CPS::A (1), CPS::B (3), CPS::C (5));
//    eulerGenus3->setOnTuningUpdate ([this] () {updateAppTuning(); } );
//    _setEulerGenus (eulerGenus3);
//
//    // seed slider
//    _seedSliderComponent->reset();
//    _seedSliderComponent->addSlider ("A", 1 , [eulerGenus3] (float v) { eulerGenus3->setA (v); } );
//    _seedSliderComponent->addSlider ("B", 3 , [eulerGenus3] (float v) { eulerGenus3->setB (v); } );
//    _seedSliderComponent->addSlider ("C", 5 , [eulerGenus3] (float v) { eulerGenus3->setC (v); } );
//
//    // eg 3 presets
//    auto notification_type = NotificationType::dontSendNotification;
//    _presetsComboBox->clear (notification_type);
//    vector<EGPresetHelper> presets
//    {
//        // cool experiment with proportional triads...try subcontrary next time!
//        {"3, 4, 5  ",  1, [this, notification_type](){_seedSliderComponent->setABC (3, 4, 5, notification_type  );}},
//        {"4, 5, 6  ",  2, [this, notification_type](){_seedSliderComponent->setABC (4, 5, 6, notification_type  );}},
//        {"5, 6, 7  ",  3, [this, notification_type](){_seedSliderComponent->setABC (5, 6, 7, notification_type  );}},
//        {"6, 7, 8  ",  4, [this, notification_type](){_seedSliderComponent->setABC (6, 7, 8, notification_type  );}},
//        {"6, 8, 10 ",  5, [this, notification_type](){_seedSliderComponent->setABC (6, 8, 10, notification_type );}},
//        {"7, 8, 9  ",  6, [this, notification_type](){_seedSliderComponent->setABC (7, 8, 9, notification_type  );}},
//        {"7, 9, 11 ",  7, [this, notification_type](){_seedSliderComponent->setABC (7, 9, 11, notification_type );}},
//        {"7, 10, 13",  8, [this, notification_type](){_seedSliderComponent->setABC (7, 10, 13, notification_type);}},
//        {"8, 9, 10 ",  9, [this, notification_type](){_seedSliderComponent->setABC (8, 9, 10, notification_type );}},
//        {"8, 10, 12", 10, [this, notification_type](){_seedSliderComponent->setABC (8, 10, 12, notification_type);}},
//        {"8, 11, 14", 11, [this, notification_type](){_seedSliderComponent->setABC (8, 11, 14, notification_type);}},
//        {"9, 10, 11", 12, [this, notification_type](){_seedSliderComponent->setABC (9, 10, 11, notification_type);}},
//        {"9, 11, 13", 13, [this, notification_type](){_seedSliderComponent->setABC (9, 11, 13, notification_type);}},
//        {"9, 12, 15", 14, [this, notification_type](){_seedSliderComponent->setABC (9, 12, 15, notification_type);}},
//        {"9, 13, 17", 15, [this, notification_type](){_seedSliderComponent->setABC (9, 13, 17, notification_type);}},
//    };
//    for (auto p : presets)
//    {
//        _presetsComboBox->addItem(p.title, p.index);
//    }
//    auto onChange = [this, presets]()
//    {
//        if (isShowing())
//        {
//            auto const selectedItemIndex = _presetsComboBox->getSelectedItemIndex();
//            for (auto p : presets)
//            {
//                if (p.index == selectedItemIndex + 1)
//                {
//                    p.callback();
//                }
//            }
//        }
//    };
//    _presetsComboBox->setOnChange (onChange);
//    _presetsComboBox->setSelectedItemIndex (1, NotificationType::sendNotificationAsync);
//
//    // draw
//    repaint();
//}
//
//void EulerGenusComponent::_addEulerGenus2Component()
//{
//    // tuning
//    auto eulerGenus2 = make_shared<EulerGenus_2> (CPS::A (1), CPS::B (3));
//    eulerGenus2->setOnTuningUpdate ([this] () {updateAppTuning(); } );
//    _setEulerGenus (eulerGenus2);
//
//    // seed slider
//    _seedSliderComponent->reset();
//    _seedSliderComponent->addSlider ("A", 1 , [eulerGenus2] (float v) { eulerGenus2->setA (v); } );
//    _seedSliderComponent->addSlider ("B", 3 , [eulerGenus2] (float v) { eulerGenus2->setB (v); } );
//
//    // presets
//    _presetsComboBox->clear (NotificationType::dontSendNotification);
//    auto onChange = [](){};
//    _presetsComboBox->setOnChange (onChange);
//
//    // draw
//    repaint();
//}
//
//void EulerGenusComponent::_addEulerGenus1Component()
//{
//    // tuning
//    auto eulerGenus1 = make_shared<EulerGenus_1> (CPS::A (1));
//    eulerGenus1->setOnTuningUpdate ([this] () {updateAppTuning(); } );
//    _setEulerGenus (eulerGenus1);
//
//    // seed slider
//    _seedSliderComponent->reset();
//    _seedSliderComponent->addSlider ("A", 1 , [eulerGenus1] (float v) { eulerGenus1->setA (v); } );
//
//    // presets
//    _presetsComboBox->clear (NotificationType::dontSendNotification);
//    auto onChange = [](){};
//    _presetsComboBox->setOnChange (onChange);
//
//    // draw
//    repaint();
//}
