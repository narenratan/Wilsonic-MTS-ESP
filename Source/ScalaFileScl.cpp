/*
 ==============================================================================
 
 ScalaFileScl.cpp
 Created: 2 Dec 2022 6:30:52pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "ScalaFileScl.h"

ScalaFileScl::ScalaFileScl ()
{
    // The first degree is a scala file is always implicit. Make it explicit.
    degrees.push_back( *(new ScalaFileDegree(0.0)));
}

ScalaFileScl::ScalaFileScl(ifstream& input_file)
: ScalaFileScl()
{
    /*
     C++ Code to parse the Scala scale file, as documented here:
     
     http://www.huygens-fokker.org/scala/scl_format.html
     
     A couple of extensions:
     
     - Allow white-space before the comment character.  Spec is a little ambiguous.
     - Allow blank lines. In the standard only the scale name is mentioned as potentially blank.
     */
    
    // this guy wasn't clear that c++ regex "." does not match line feeds \r \n
    
    int non_comments_processed = 0;
    //int entries = 0;
    unsigned long long numerator = 1, denominator = 1;
    string buffer;
    smatch match, trimmed;
    //bool description_parsed = false ;
    bool file_name_parsed = false;
    regex COMMENT_REGEX = regex ("[ \t]*!(.|\\r|\\n)*");
    
    while(getline(input_file, buffer)) // ends on EOF
    {
        add_scala_content(buffer); // accumulate scala file
        
        //
        if(regex_match(buffer, COMMENT_REGEX)) // ! desc
        {
            // We're defining a comment as the first non-whitespace character being a "!".
            add_description(buffer);
            
            // the first comment is by convention the filename
            if (!file_name_parsed)
            {
                file_name = "";
                file_name += buffer;
                file_name_parsed = true;
            }
        }
        else if(regex_match(buffer, regex ("[ \t]*") ))
        {
            // Blank line. Discard. This may be an extension of the format.
            if(non_comments_processed == 0)
            {
                //description_parsed = true;
            }
            non_comments_processed = non_comments_processed + 1;
        }
        else
        {
            // Extract the part after optional leading whitespace and before an optional space and label
            regex_search(buffer, trimmed, regex ("([ \t]*)([^ \t]*)(.*)"));
            string entry = trimmed[2];
            if(non_comments_processed == 0)
            {
                // First non-comment is the description. Can be ignored
                non_comments_processed = non_comments_processed + 1;
                //description_parsed = true;
                add_description(buffer);
                continue;
            }
            else if(non_comments_processed == 1)
            {
                // TODO: we don't even need the number of entries really except for validation
                // Second non-comment line contains the number of entries.
                //entries  = stoi(entry);
                non_comments_processed = non_comments_processed + 1;
                continue;
            }
            else if(regex_match(entry, regex (".*[\\.]+.*[\\n|\\r]*") ))
            {
                // Cent values *must* have a period. It's the law.
                double cents = stod(entry);
                add_degree (*new ScalaFileDegree(cents));
            }
            else if(regex_match(entry, regex (".*[/]{1}.*[\\n|\\r]*") ))
            {
                // A ratio
                regex_search(entry, match, regex ("(.*)/(.*)"));
                numerator = stoull(match.str(1));
                denominator = stoull(match.str(2));
                add_degree (*new ScalaFileDegree(numerator, denominator));
            }
            else if(regex_match(entry, regex("^[0-9]+[\\r\\n]*$")))
            {
                // According to the standard, single numbers should be treated as ratios
                numerator = stoull(entry);
                denominator = 1;
                add_degree (*new ScalaFileDegree(numerator, denominator));
            }
        }
    }
}

// this is so embarassing...so much duplicate code from above
ScalaFileScl::ScalaFileScl(String in_input)
: ScalaFileScl()
{
    if(in_input.isEmpty())
    {
        DBG ("ScalaFileScl: input String is empty");
        jassertfalse;
    }
    
    string input = in_input.toStdString();
    istringstream input_stream(input);
    int non_comments_processed = 0;
    //int entries = 0;
    unsigned long long numerator = 1, denominator = 1;
    string buffer;
    smatch match, trimmed;
    //bool description_parsed = false ;
    bool file_name_parsed = false;
    regex COMMENT_REGEX = regex ("[ \t]*!(.|\\r|\\n)*");
    
    while(getline(input_stream, buffer))
    {
        // accumulate scala file
        add_scala_content(buffer);
        
        //
        if(regex_match(buffer, COMMENT_REGEX)) // ! desc
        {
            // We're defining a comment as the first non-whitespace character being a "!".
            add_description(buffer);
            
            // the first comment is by convention the filename
            if (!file_name_parsed)
            {
                file_name = "";
                file_name += buffer;
                file_name_parsed = true;
            }
        }
        else if(regex_match(buffer, regex ("[ \t]*") ))
        {
            // Blank line. Discard. This may be an extension of the format.
            if(non_comments_processed == 0)
            {
                //description_parsed = true;
            }
            non_comments_processed = non_comments_processed + 1;
        }
        else
        {
            // Extract the part after optional leading whitespace and before an optional space and label
            regex_search(buffer, trimmed, regex ("([ \t]*)([^ \t]*)(.*)"));
            string entry = trimmed[2];
            if(non_comments_processed == 0)
            {
                // First non-comment is the description. Can be ignored
                non_comments_processed = non_comments_processed + 1;
                //description_parsed = true;
                add_description(buffer);
                continue;
            }
            else if(non_comments_processed == 1)
            {
                // TODO: we don't even need the number of entries really except for validation
                // Second non-comment line contains the number of entries.
                //entries  = stoi(entry);
                non_comments_processed = non_comments_processed + 1;
                continue;
            }
            else if(regex_match(entry, regex (".*[\\.]+.*[\\n|\\r]*") ))
            {
                // Cent values *must* have a period. It's the law.
                double cents = stod(entry);
                add_degree (*new ScalaFileDegree(cents));
            }
            else if(regex_match(entry, regex (".*[/]{1}.*[\\n|\\r]*") ))
            {
                // A ratio
                regex_search(entry, match, regex ("(.*)/(.*)"));
                numerator = stoull(match.str(1));
                denominator = stoull(match.str(2));
                add_degree (*new ScalaFileDegree(numerator, denominator));
            }
            else if(regex_match(entry, regex ("^[0-9]+[\\r\\n]*$")))
            {
                // According to the standard, single numbers should be treated as ratios
                numerator = stoull(entry);
                denominator = 1;
                add_degree (*new ScalaFileDegree(numerator, denominator));
            }
        }
    }
    
}

ScalaFileScl::~ScalaFileScl()
{
    degrees.clear();
    vector<ScalaFileDegree>().swap(degrees);
}

/*
 ScalaFileScl& ScalaFileScl::operator=(const ScalaFileScl& other)
 {
 if (this != &other) {
 degrees = other.degrees;
 file_name = other.file_name;
 desc = other.desc;
 scala_content = other.scala_content;
 }
 return *this;
 }
 
 // Move constructor
 ScalaFileScl::ScalaFileScl(ScalaFileScl&& other) noexcept
 : degrees(std::move(other.degrees))
 , file_name(std::move(other.file_name))
 , desc(std::move(other.desc))
 , scala_content(std::move(other.scala_content))
 {
 
 }
 
 // Move assignment operator
 ScalaFileScl& ScalaFileScl::operator=(ScalaFileScl&& other)
 {
 if (this != &other) {
 degrees = std::move(other.degrees);
 file_name = std::move(other.file_name);
 desc = std::move(other.desc);
 scala_content = std::move(other.scala_content);
 }
 return *this;
 }
 */

ScalaFileScl::ScalaFileScl(const ScalaFileScl &s2)
{
    for(size_t i = 0; i < s2.degrees.size(); i++)
    {
        degrees.push_back(s2.degrees[i]);
    }
}

ScalaFileDegree ScalaFileScl::get_degree(size_t i)
{
    jassert(i < degrees.size());
    return degrees[i];
}


// add a new degree
void ScalaFileScl::add_degree(ScalaFileDegree d)
{
    degrees.push_back(d);
}

// set the description of the entire scale
void ScalaFileScl::set_desc(string d)
{
    desc = d;
}

// add only the comment content
void ScalaFileScl::add_description(string d)
{
    desc += d;
    desc += "\n";
}

// return the filename
string ScalaFileScl::get_filename()
{
    return file_name;
}

// return the cumulative comment content
string ScalaFileScl::get_description()
{
    return desc;
}

// get the frequency at index i
double ScalaFileScl::get_ratio(size_t i)
{
    return degrees[i].get_ratio();
}

// get the description of the frequency at index i
string ScalaFileScl::get_desc(size_t i)
{
    return degrees[i].get_desc();
}

// accumulate the scala file(it's read from a stream)
void ScalaFileScl::add_scala_content(string sc)
{
    scala_content += sc;
}

// return the parsed scala file
string ScalaFileScl::get_scala_content()
{
    return scala_content;
}

// Note this includes the 1 AND the repeating interval, no bueno
size_t ScalaFileScl::get_scale_length()
{
    return degrees.size();
}

double ScalaFileScl::get_period()
{
    jassert(get_scale_length() >= 1);
    auto scale_repeating_interval = get_ratio(get_scale_length() - 1);
    
    return scale_repeating_interval;
}
