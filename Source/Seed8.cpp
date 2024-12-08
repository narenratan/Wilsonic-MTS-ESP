/*
  ==============================================================================

    Seed8.cpp
    Created: 6 Jun 2023 4:10:07pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "Seed8.h"

#pragma mark - lifecycle

Seed8::Seed8()
{
    // properties
    setCanUniquify(false);
    setCanSort(true);
    setSort(true);
    setTuningName ("Seed 8");
}

Seed8::Seed8(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F, Microtone_p G, Microtone_p H)
: Seed8()
{
    _A = A;
    _B = B;
    _C = C;
    _D = D;
    _E = E;
    _F = F;
    _G = G;
    _H = H;
}

Seed8::Seed8(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
: Seed8 ()
{
    // can't use "set" because it calls update...so duplicate code here
    jassert(master_set.size() == 8);
    _A = master_set[0];
    _B = master_set[1];
    _C = master_set[2];
    _D = master_set[3];
    _E = master_set[4];
    _F = master_set[5];
    _G = master_set[6];
    _H = master_set[7];
    clearCommonTones();
    for(auto ct : common_tones)
    {
        addCommonTone(ct);
    }
}

Seed8::~Seed8()
{

}

#pragma mark - member functions

const vector<Microtone_p> Seed8::getMasterSet()
{
    return vector<Microtone_p> {_A, _B, _C, _D, _E, _F, _G, _H};
}

void Seed8::set(vector<Microtone_p> master_set, vector<Microtone_p> common_tones)
{
    // if you change this code you need to update the constructor
    jassert(master_set.size() == 8);
    _A = master_set[0];
    _B = master_set[1];
    _C = master_set[2];
    _D = master_set[3];
    _E = master_set[4];
    _F = master_set[5];
    _G = master_set[6];
    _H = master_set[7];
    clearCommonTones();
    for(auto ct : common_tones)
    {
        addCommonTone(ct);
    }
    update();
}

void Seed8::setA(Microtone_p A)
{
    _A = A;
    update();
}

void Seed8::setA(float f)
{
    _A->setFrequencyValue(f);
    auto fsdt = Microtone::getFrequencyValueDescription(f);
    _A->setShortDescriptionText2(fsdt);
    update();
}

const Microtone_p Seed8::getA()
{
    return _A;
}

void Seed8::setB(Microtone_p B)
{
    _B = B;
    update();
}

void Seed8::setB(float f)
{
    _B->setFrequencyValue(f);
    auto fsdt = Microtone::getFrequencyValueDescription(f);
    _B->setShortDescriptionText2(fsdt);
    update();
}

const Microtone_p Seed8::getB()
{
    return _B;
}

void Seed8::setC(Microtone_p C)
{
    _C = C;
    update();
}

void Seed8::setC(float f)
{
    _C->setFrequencyValue(f);
    auto fsdt = Microtone::getFrequencyValueDescription(f);
    _C->setShortDescriptionText2(fsdt);
    update();
}

const Microtone_p Seed8::getC()
{
    return _C;
}

void Seed8::setD(Microtone_p D)
{
    _D = D;
    update();
}

void Seed8::setD(float f)
{
    _D->setFrequencyValue(f);
    auto fsdt = Microtone::getFrequencyValueDescription(f);
    _D->setShortDescriptionText2(fsdt);
    update();
}

const Microtone_p Seed8::getD()
{
    return _D;
}

void Seed8::setE(Microtone_p E)
{
    _E = E;
    update();
}

void Seed8::setE(float f)
{
    _E->setFrequencyValue(f);
    auto fsdt = Microtone::getFrequencyValueDescription(f);
    _E->setShortDescriptionText2(fsdt);
    update();
}

const Microtone_p Seed8::getE()
{
    return _E;
}

void Seed8::setF(Microtone_p F)
{
    _F = F;
    update();
}

void Seed8::setF(float f)
{
    _F->setFrequencyValue(f);
    auto fsdt = Microtone::getFrequencyValueDescription(f);
    _F->setShortDescriptionText2(fsdt);
    update();
}

const Microtone_p Seed8::getF()
{
    return _F;
}

void Seed8::setG(Microtone_p G)
{
    _G = G;
    update();
}

void Seed8::setG(float f)
{
    _G->setFrequencyValue(f);
    auto fsdt = Microtone::getFrequencyValueDescription(f);
    _G->setShortDescriptionText2(fsdt);
    update();
}

const Microtone_p Seed8::getG()
{
    return _G;
}

void Seed8::setH(Microtone_p H)
{
    _H = H;
    update();
}

void Seed8::setH(float f)
{
    _H->setFrequencyValue(f);
    auto fsdt = Microtone::getFrequencyValueDescription(f);
    _H->setShortDescriptionText2(fsdt);
    update();
}

const Microtone_p Seed8::getH()
{
    return _H;
}

void Seed8::setABCDEFGH(Microtone_p A, Microtone_p B, Microtone_p C, Microtone_p D, Microtone_p E, Microtone_p F, Microtone_p G, Microtone_p H)
{
    _A = A;
    _B = B;
    _C = C;
    _D = D;
    _E = E;
    _F = F;
    _G = G;
    _H = H;
    update();
}

const string Seed8::getTuningName()
{
    auto basename = TuningImp::getTuningName();
    auto retVal = basename + "(" +
    _A->getFrequencyValueDescription() + "," +
    _B->getFrequencyValueDescription() + "," +
    _C->getFrequencyValueDescription() + "," +
    _D->getFrequencyValueDescription() + "," +
    _E->getFrequencyValueDescription() + "," +
    _F->getFrequencyValueDescription() + "," +
    _G->getFrequencyValueDescription() + "," +
    _H->getFrequencyValueDescription() +
    ")";

    if(getCommonTones().size() > 0)
    {
        auto t = multiplyByCommonTones(vector<Microtone_p> {});
        retVal += "*" + t->getShortDescriptionText2();
    }

    return retVal;
}

const string Seed8::getTuningNameAsSymbols()
{
    auto basename = TuningImp::getTuningName();
    auto retVal = basename + "(" +
    _A->getShortDescriptionText() + "," +
    _B->getShortDescriptionText() + "," +
    _C->getShortDescriptionText() + "," +
    _D->getShortDescriptionText() + "," +
    _E->getShortDescriptionText() + "," +
    _F->getShortDescriptionText() + "," +
    _G->getShortDescriptionText() + "," +
    _H->getShortDescriptionText() +
    ")";

    sort(_commonTones.begin(), _commonTones.end(), less_than_key());
    for(auto ct : _commonTones)
    {
        retVal += "*" + ct->getShortDescriptionText();
    }

    return retVal;
}

const string Seed8::getTuningNameAsUnderscores()
{
    auto basename = TuningImp::getTuningName();
    auto retVal = basename + "_" +
    _A->getShortDescriptionText() + "_" +
    _B->getShortDescriptionText() + "_" +
    _C->getShortDescriptionText() + "_" +
    _D->getShortDescriptionText() + "_" +
    _E->getShortDescriptionText() + "_" +
    _F->getShortDescriptionText() + "_" +
    _G->getShortDescriptionText() + "_" +
    _H->getShortDescriptionText();
    if(_commonTones.size() > 0)
    {
        retVal += "__X";
    }

    sort(_commonTones.begin(), _commonTones.end(), less_than_key());
    for(auto ct : _commonTones)
    {
        retVal += "_" + ct->getShortDescriptionText();
    }

    return retVal;
}

// used by codegen to create the string used to construct this type of tuning:
//shared_ptr<CPSTuningBase> EulerGenusModel::_create_tuning(CPS_Class tuning_class_name,
//                                                           vector<Microtone_p> master_set,
//                                                           vector<Microtone_p> common_terms,
//                                                           DAWKey parent_key,
//                                                           vector<DAWKey> s0_daw_keys,
//                                                           vector<DAWKey> s1_daw_keys)
//    cps->setShouldComputeSubsets(true); cps->selectParent();
//    return cps;

const string Seed8::getTuningCreationCodegen(string parent_key, vector<string> s0_keys, vector<string> s1_keys)
{
    // common tones
    string ctstr = "";
    if(_commonTones.size() > 0)
    {
        ctstr = "{";
        sort(_commonTones.begin(), _commonTones.end(), less_than_key());
        for(auto ct : _commonTones)
        {
            ctstr += "_" + ct->getShortDescriptionText() + ",";
        }
        ctstr.pop_back(); // remove last ","
        ctstr += "}";
    }
    else
    {
        ctstr = "{}";
    }

    // s0
    string s0str = "";
    if(s0_keys.size() > 0)
    {
        s0str = "{";
        for(auto ct : s0_keys)
        {
            s0str += "\"" + ct + "\"" + ",";
        }
        s0str.pop_back(); // remove last ","
        s0str += "}";
    }
    else
    {
        s0str = "{}";
    }

    // s1
    string s1str = "";
    if(s1_keys.size() > 0)
    {
        s1str = "{";
        for(auto ct : s1_keys)
        {
            s1str += "\"" + ct + "\"" + ",";
        }
        s1str.pop_back(); // remove last ","
        s1str += "}";
    }
    else
    {
        s1str = "{}";
    }

    auto a = _A->getShortDescriptionText();
    auto b = _B->getShortDescriptionText();
    auto c = _C->getShortDescriptionText();
    auto d = _D->getShortDescriptionText();
    auto e = _E->getShortDescriptionText();
    auto f = _F->getShortDescriptionText();
    auto g = _G->getShortDescriptionText();
    auto h = _H->getShortDescriptionText();

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
    string retVal = "[this](){ return _create_tuning(CPS_Class::" + tuning_class_name + ", ";

    // master set
    retVal += "{_" + a + ",_" + b + ",_" + c + ",_" + d + ",_" + e + ",_" + f + ",_" + g + "," + h + "}, ";

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
//    cps->set ({_A,_B,_C,_D,_E,_F,_G,_H}, {});
const string Seed8::getTuningUpdateCodegen()
{
    string ctstr = "";
    //bool hasCommonTones = false;
    if(_commonTones.size() > 0)
    {
        //hasCommonTones = true;
        ctstr = "{";
        sort(_commonTones.begin(), _commonTones.end(), less_than_key());
        for(auto ct : _commonTones)
        {
            ctstr += "_" + ct->getShortDescriptionText() + ",";
        }
        ctstr.pop_back(); // remove last ","
        ctstr += "}";
    }
    else
    {
        ctstr = "{}";
    }

    auto a = _A->getShortDescriptionText();
    auto b = _B->getShortDescriptionText();
    auto c = _C->getShortDescriptionText();
    auto d = _D->getShortDescriptionText();
    auto e = _E->getShortDescriptionText();
    auto f = _F->getShortDescriptionText();
    auto g = _G->getShortDescriptionText();
    auto h = _H->getShortDescriptionText();

    string retVal = "cps->set ({_" + a + ",_" + b + ",_" + c + ",_" + d + ",_" + e + ",_" + f + ",_" + g + ",_" + h + "}," + ctstr + ");";

    return retVal;
}
