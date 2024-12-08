/*
  ==============================================================================

    CodegenStream.h
    Created: 2 Jan 2022 4:31:58pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include <fstream>

// helper class for breaking up large codegen files into includes, declarations, and
// lambdas for selection, creation

class CodegenStream
{
public:
    CodegenStream (string file_basename, int entry_limit, string file_prefix, string file_suffix, string method_basename, string method_file_name, string include_file_name);
    ~CodegenStream();
    
    void write (string entry);
    void close();

private:
    string _file_basename {""};
    int _entry_limit {256};
    string _file_prefix {""};
    string _file_suffix {""};
    string _method_basename {""};
    void _open();
    void _close_file_stream();
    string _file_name();
    string _file_index_leading_zeros_str();
    unique_ptr<ofstream> _file_stream {nullptr};
    unique_ptr<ofstream> _method_stream {nullptr};
    unique_ptr<ofstream> _include_stream {nullptr};
    int _file_index {0};
    int _num_entries {0};
};
