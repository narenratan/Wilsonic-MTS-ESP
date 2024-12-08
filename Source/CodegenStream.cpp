/*
  ==============================================================================

    CodegenStream.cpp
    Created: 2 Jan 2022 4:31:58pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "CodegenStream.h"

CodegenStream::CodegenStream (string file_basename, int entry_limit, string file_prefix, string file_suffix, string method_basename, string method_file_name, string include_file_name)
: _file_basename (file_basename)
, _entry_limit (entry_limit)
, _file_prefix (file_prefix)
, _file_suffix (file_suffix)
, _method_basename (method_basename)
{
    jassert (_file_basename.length() > 0);
    jassert (_entry_limit > 0);
    jassert (_method_basename.length() > 0);
    jassert (method_file_name.length() > 0);
    jassert (include_file_name.length() > 0);

    // open the method and include streams
    _method_stream = make_unique<ofstream> (method_file_name);
    jassert (_method_stream != nullptr);
    _include_stream = make_unique<ofstream> (include_file_name);
    jassert (_include_stream != nullptr);

    // opens file stream
    _open();
}

CodegenStream::~CodegenStream()
{

}

void CodegenStream::write (string entry)
{
    jassert (_file_stream != nullptr);
    
    auto entry_copy = string (entry);
    if (_num_entries > _entry_limit)
    {
        // remove trailing ","
        entry_copy.pop_back();
    }

    // output
    (*_file_stream) << entry_copy;

    // if past entry limit close current file, open new file
    _num_entries++;
    if (_num_entries > _entry_limit)
    {
        _close_file_stream();
        _open();
    }
}

void CodegenStream::close()
{
    _close_file_stream();
    _method_stream->close();
    _method_stream = nullptr;
    _include_stream->close();
    _include_stream = nullptr;
}

void CodegenStream::_close_file_stream()
{
    // output suffix and close stream
    (*_file_stream) << _file_suffix;
    _file_stream->close();
    _file_stream = nullptr;
}

void CodegenStream::_open()
{
    // open new stream with file name
    _file_stream = make_unique<ofstream> (_file_name());
    jassert (_file_stream != nullptr);

    // padded file index
    auto zeros = _file_index_leading_zeros_str();

    // replace prefix substring XXXX with file index with padded zeros
    auto replaced_str = regex_replace (_file_prefix, regex("XXXX"), zeros);
    (*_file_stream) << replaced_str;

    // output to method and include streams
    (*_method_stream) << _method_basename << "_" << zeros << "();\n";
    (*_include_stream) << "void " << _method_basename << "_" << zeros << "();\n";

    // reset counter, bump up file index
    _num_entries = 0;
    _file_index++;
}

string CodegenStream::_file_name()
{
    // construct file name with file index
    auto file_index_str = _file_index_leading_zeros_str();
    return _file_basename + file_index_str + ".cpp";
}

string CodegenStream::_file_index_leading_zeros_str()
{
    // return file index as zero padded string
    ostringstream str;
    str << setw(4) << setfill('0') << _file_index;
    return str.str();
}
