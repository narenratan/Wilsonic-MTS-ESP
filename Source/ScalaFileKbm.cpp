/*
  ==============================================================================

    ScalaFileKbm.cpp
    Created: 2 Dec 2022 6:31:04pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "ScalaFileKbm.h"

ScalaFileKbm::ScalaFileKbm()
{
    reference_frequency = 0.0;
    map_size = 0;
    first_note = 0;
    last_note = 0;
    middle_note = 0;
    reference_note = 0;
    octave_degree = 0;
}

ScalaFileKbm::ScalaFileKbm(ifstream& input_file)
: ScalaFileKbm()
{
    string buffer;
    int current_entry = 0;
    ScalaFileKbm keyboard_mapping;
    regex COMMENT_REGEX = regex ("[ \t]*!.*");
    regex EX = regex ("^[ \t]*[xX]{1}.*");

    while(input_file)
    {
        getline(input_file, buffer); // TODO: should this go up in the while loop to detect EOF?
        if(regex_match(buffer, COMMENT_REGEX))
        {
            // Ignore comments
        }
        else if(regex_match(buffer, regex("[ \t]*") ))
        {
            // Blank line. If we're in strict mode this means end of file.
            // Stop parsing.
        }
        else
        {
            switch(current_entry)
            {
                case MAP_SIZE:
                    map_size = stoi(buffer);
                    current_entry += 1;
                    break;
                case FIRST_NOTE:
                    first_note = stoi(buffer);
                    current_entry += 1;
                    break;
                case LAST_NOTE:
                    last_note = stoi(buffer);
                    current_entry += 1;
                    break;
                case MIDDLE_NOTE:
                    middle_note = stoi(buffer);
                    current_entry += 1;
                    break;
                case REFERENCE_NOTE:
                    reference_note = stoi(buffer);
                    current_entry += 1;
                    break;
                case REFERENCE_FREQUENCY:
                    reference_frequency = stod(buffer);
                    current_entry += 1;
                    break;
                case OCTAVE_DEGREE:
                    octave_degree = stoi(buffer);
                    current_entry += 1;
                    break;
                case ACTUAL_MAP:
                    // This one is a little more complicated.  If we have an x
                    if(regex_match(buffer, EX))
                    {
                        // A non-entry
                        add_mapping(KBM_NON_ENTRY);
                        jassertfalse;
                    }
                    else
                    {
                        // A mapping entry
                        add_mapping(stoi(buffer));
                    }
            }
        }
    }

    if(static_cast <size_t> (keyboard_mapping.map_size) != keyboard_mapping.mapping.size())
    {
#if 0
        // This is an error, strict mode or not
        if(static_cast <size_t> (keyboard_mapping.map_size) < keyboard_mapping.mapping.size())
        {
            throw runtime_error ("ERROR: Too few entries in mapping file");
        }
        else
        {
            throw runtime_error ("ERROR: Too many entries in mapping file");
        }
#endif
        jassertfalse;
    }
}

ScalaFileKbm::~ScalaFileKbm()
{
    mapping.clear();
    vector<int>().swap(mapping);
}

ScalaFileKbm::ScalaFileKbm(const ScalaFileKbm &k2)
{
    for(size_t i = 0; i < k2.mapping.size(); i++)
    {
        mapping.push_back(k2.mapping[i]);
    }
    reference_frequency = k2.reference_frequency;
    map_size = k2.map_size;
    first_note = k2.first_note;
    last_note = k2.last_note;
    middle_note = k2.middle_note;
    reference_note = k2.reference_note;
    octave_degree = k2.octave_degree;
}

void ScalaFileKbm::add_mapping(int n)
{
    mapping.push_back(n);
}
