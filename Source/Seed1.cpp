/*
  ==============================================================================

    Seed1.cpp
    Created: 15 Aug 2021 12:04:12pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "Seed1.h"

#pragma mark - lifecycle

Seed1::Seed1() {
    // properties
    setCanUniquify(false);
    setCanSort(true);
    setSort(true);
    setTuningName ("Seed 1");
}

Seed1::Seed1(Microtone_p A) : Seed1() {
    _A = A;
}

Seed1::Seed1(vector<Microtone_p> master_set, vector<Microtone_p> common_tones) : Seed1() {
    // can't use "set" because it calls update...so duplicate code here
    jassert(master_set.size() == 1);
    _A = master_set[0];
    clearCommonTones();
    for(auto ct : common_tones) {
        addCommonTone(ct);
    }
}

Seed1::~Seed1() {

}

#pragma mark - properties

void Seed1::set(vector<Microtone_p> master_set, vector<Microtone_p> common_tones) {
    // if you change this code you need to update the constructor
    jassert(master_set.size() >= 1);
    _A = master_set[0];
    clearCommonTones();
    for(auto ct : common_tones) {
        addCommonTone(ct);
    }
    update();
}

void Seed1::setA(Microtone_p A) {
    _A = A;
    update();
}

void Seed1::setA(float f) {
    _A->setFrequencyValue(f);
    auto fsdt = Microtone::getFrequencyValueDescription(f);
    _A->setShortDescriptionText2(fsdt);
    update();
}

const Microtone_p Seed1::getA() {
    return _A;
}

#pragma mark - methods

const vector<Microtone_p> Seed1::getMasterSet() {
    return vector<Microtone_p>{_A};
}

const string Seed1::getTuningName() {
    auto basename = TuningImp::getTuningName();
    auto retVal = basename + "(" + _A->getFrequencyValueDescription() + ")";
    // TODO: fix this
    if(getCommonTones().size() > 0) {
        auto t = multiplyByCommonTones(vector<Microtone_p> {});
        retVal += "*" + t->getShortDescriptionText2();
    }
    return retVal;
}

const string Seed1::getTuningNameAsSymbols() {
    auto basename = TuningImp::getTuningName();
    auto retVal = basename + "(" +
    _A->getShortDescriptionText() + 
    ")";
    sort(_commonTones.begin(), _commonTones.end(), less_than_key());
    for(auto ct : _commonTones) {
        retVal += "*" + ct->getShortDescriptionText();
    }
    return retVal;
}

const string Seed1::getTuningNameAsUnderscores() {
    auto basename = TuningImp::getTuningName();
    auto retVal = basename + "_" + _A->getShortDescriptionText();
    if(_commonTones.size() > 0) {
        retVal += "__X";
    }
    sort(_commonTones.begin(), _commonTones.end(), less_than_key());
    for(auto ct : _commonTones) {
        retVal += "_" + ct->getShortDescriptionText();
    }
    return retVal;
}

const string Seed1::getTuningCreationCodegen(string parent_key, vector<string> s0_keys, vector<string> s1_keys) {
    // common tones
    string ctstr = "";
    if(_commonTones.size() > 0) {
        ctstr = "{";
        sort(_commonTones.begin(), _commonTones.end(), less_than_key());
        for(auto ct : _commonTones) {
            ctstr += "_" + ct->getShortDescriptionText() + ",";
        }
        ctstr.pop_back(); // remove last ","
        ctstr += "}";
    } else {
        ctstr = "{}";
    }

    // theoretically no subsets but we keep these here for the common api

    // s0
    string s0str = "";
    if(s0_keys.size() > 0) {
        s0str = "{";
        for(auto ct : s0_keys) {
            s0str += "\"" + ct + "\"" + ",";
        }
        s0str.pop_back(); // remove last ","
        s0str += "}";
    } else {
        s0str = "{}";
    }

    // s1
    string s1str = "";
    if(s1_keys.size() > 0) {
        s1str = "{";
        for(auto ct : s1_keys) {
            s1str += "\"" + ct + "\"" + ",";
        }
        s1str.pop_back(); // remove last ","
        s1str += "}";
    } else {
        s1str = "{}";
    }
    auto a = _A->getShortDescriptionText();

    //shared_ptr<CPSTuningBase> _create_tuning (
    //CPS_Class tuning_class_name,
    //vector<Microtone_p> master_set,
    //vector<Microtone_p>,
    //common_terms,
    //string parent_key,
    //vector<string> s0_keys,
    //vector<string> s1_keys);

    // tuning class
    string tuning_class_name = TuningImp::getTuningName();
    string retVal = "[this](){ return _create_tuning (CPS_Class::" + tuning_class_name + ", ";

    // master set
    retVal += "{_" + a + "},";

    // common tones {}
    retVal += ctstr + ", ";

    // parent daw key
    retVal += "\"" + parent_key + "\", ";

    // s0 daw keys
    retVal += s0str + ", ";

    // s1 daw keys
    retVal += s1str;

    //
    retVal +=  + ");}";
    return retVal;
}

// used by codegen to create the string used to update this type of tuning:
//    cps->set ({_A}, {_B,_C,_D,_E,_F});
const string Seed1::getTuningUpdateCodegen() {
    string ctstr = "";
    if(_commonTones.size() > 0) {
        ctstr = "{";
        sort(_commonTones.begin(), _commonTones.end(), less_than_key());
        for(auto ct : _commonTones) {
            ctstr += "_" + ct->getShortDescriptionText() + ",";
        }
        ctstr.pop_back(); // remove last ","
        ctstr += "}";
    } else {
        ctstr = "{}";
    }
    auto a = _A->getShortDescriptionText();
    string retVal = "cps->set ({_" + a + "}," + ctstr + ");";
    return retVal;
}
