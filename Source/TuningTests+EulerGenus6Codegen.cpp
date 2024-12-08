/*
 ==============================================================================

 TuningTests+EulerGenus6Codegen.cpp
 Created: 25 Dec 2021 2:34:58pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

#include "TuningTests.h"
#include "EulerGenusModel.h"
#include "EulerGenus_6.h"
#include "CPS_4_1.h"
#include "CPS_4_2.h"
#include "CPS_4_3.h"
#include "CPS_4_4.h"
#include "CPS_6_1.h"
#include "CPS_6_2.h"
#include "CPS_6_3.h"
#include "CPS_6_4.h"
#include "CPS_6_5.h"
#include "CPS_6_6.h"

// code gen...creates code for 13 files

void TuningTests::testEulerGenus6CodeGen()
{
    EulerGenusModel::eulerGenusCodeGen();
}
