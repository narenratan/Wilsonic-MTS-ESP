/*
  ==============================================================================

    Seed1.h
    Created: 15 Aug 2021 12:04:12pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#pragma once

#include "CPSTuningBase.h"
#include "Microtone.h"

class Seed1 : public CPSTuningBase
{
public:
    // lifecycle
    Seed1();
    Seed1(Microtone_p A);
    Seed1(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~Seed1() override;

    // member functions
    void set(vector<Microtone_p> master_set, vector<Microtone_p> common_tones) override;
    void setA(Microtone_p A);
    void setA(float);
    const Microtone_p getA();
    const vector<Microtone_p> getMasterSet() override;
    const string getTuningName() override;
    const string getTuningNameAsSymbols() override;
    const string getTuningNameAsUnderscores() override;
    const string getTuningCreationCodegen(string, vector<string>, vector<string>) override;
    const string getTuningUpdateCodegen() override;

protected:
    // properties
    Microtone_p _A;
};
