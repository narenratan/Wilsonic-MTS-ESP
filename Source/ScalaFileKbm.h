/*
  ==============================================================================

    ScalaFileKbm.h
    Created: 2 Dec 2022 6:31:04pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"

class ScalaFileKbm
{
public:
    enum current_entry_map
    {
        MAP_SIZE,
        FIRST_NOTE,
        LAST_NOTE,
        MIDDLE_NOTE,
        REFERENCE_NOTE,
        REFERENCE_FREQUENCY,
        OCTAVE_DEGREE,
        ACTUAL_MAP
    };

    static constexpr int KBM_NON_ENTRY = -1;

    ScalaFileKbm();
    ScalaFileKbm(ifstream& input_file);
    ~ScalaFileKbm();
    ScalaFileKbm(const ScalaFileKbm &k2);
    
    void add_mapping(int n);
    double reference_frequency;
    int map_size;
    int first_note;
    int last_note;
    int middle_note;
    int reference_note;
    int octave_degree;
    vector<int> mapping;
};
