/*
  ==============================================================================

    ScalaFileScl.h
    Created: 2 Dec 2022 6:30:52pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "ScalaFileDegree.h"
#include "Tuning_Include.h"

class ScalaFileScl
{
public:
    ScalaFileScl();
    ScalaFileScl(std::ifstream& input_file);
    ScalaFileScl(String input);
    ScalaFileScl(const ScalaFileScl &s2);
    ~ScalaFileScl();
    /*
    ScalaFileScl& operator=(const ScalaFileScl& other); // Copy assignment operator
    ScalaFileScl(ScalaFileScl&& other) noexcept; // Move constructor
    ScalaFileScl& operator=(ScalaFileScl&& other); // Move assignment operator
*/

    // add a new degree
    void add_degree (ScalaFileDegree d);

    // add only the comment content
    void add_description (string d);

    // get the first comment, which is typically the filename
    string get_filename();

    // return the cumulative comment content
    string get_description();

    // set the description of the scl file
    void set_desc (string d);

    // return the degree at index i.  0 = 1.
    ScalaFileDegree get_degree (size_t i);

    // get the frequency at index i
    double get_ratio (size_t i);

    // get the description of the frequency at index i
    string get_desc (size_t i);

    // accumulate the scala file (it's read from a stream)
    void add_scala_content (string sc);

    // return the parsed scala file
    string get_scala_content();

    // Note this includes the 1 AND the repeating interval, no bueno
    size_t get_scale_length();

    double get_period();

private:
    vector<ScalaFileDegree> degrees;
    string file_name = "placeholder.scl";
    string desc = "";
    string scala_content = "";
};
