/*
 ==============================================================================
 
 ScalaFile.h
 Created: 2 Dec 2022 6:30:41pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "ScalaFileScl.h"
#include "ScalaFileKbm.h"
#include "Tuning_Include.h"

class ScalaFile
{
public:
    ScalaFile();
    string fileName;
    ScalaFileScl scl;
    ScalaFileKbm kbm;
};
