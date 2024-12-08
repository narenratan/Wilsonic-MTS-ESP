/**
 * @file CPSTuningBase.h
 * @brief CPS_N_K tunings inherit from this abstract base class.
 * @details Provides interface for subsets for CPSElementComponent.
 * There can be 0, 1, or 2 sets of subsets.
 * If there is 1 set of subsets it will be in subset0, and subset1 will be empty.
 * @date Created: 29 Aug 2021 10:06:04am
 * @author Marcus W. Hobbs
 */

#pragma once

#include "CPS.h"
#include "CPSMicrotone.h"
#include "TuningImp.h"

class WilsonicProcessor;

// don't know how to forward-declare "using".  this type is declared
// in EulerGenusModel and duplicated here
using DAWKey = String;

/**
 * @class CPSTuningBase
 * @brief Abstract base class for CPS_N_K tunings.
 * @details This class provides an interface for subsets for CPSElementComponent.
 * There can be 0, 1, or 2 sets of subsets.
 * If there is 1 set of subsets it will be in subset0, and subset1 will be empty.
 */
class CPSTuningBase : public TuningImp
{
public:
    CPSTuningBase();
    CPSTuningBase(vector<Microtone_p> master_set, vector<Microtone_p> common_tones);
    ~CPSTuningBase() noexcept override = default;

    // public methods
    virtual void update() = 0;
    virtual void set(vector<Microtone_p> master_set, vector<Microtone_p> common_tones) = 0;
    virtual const vector<Microtone_p> getMasterSet() = 0;
    String defaultScalaName() override;
    String scalaComments() override;
    void clearCommonTones();
    void addCommonTone(Microtone_p);
    const vector<Microtone_p> getCommonTones();
    void setCommonTones(Microtone_p, vector<Microtone_p>);
    Microtone_p multiplyByCommonTones(vector<Microtone_p>);
    const string getTuningName() override;
    virtual const string getTuningNameAsSymbols() = 0; // codegen
    virtual const string getTuningNameAsUnderscores() = 0; // codegen
    virtual const string getTuningCreationCodegen(string, vector<string>, vector<string>) = 0; // codegen
    virtual const string getTuningUpdateCodegen() = 0; // codegen
    const string getDebugDescription() override;
    const string getParameterDescription() override;
    const vector<shared_ptr<CPSTuningBase>> getSubsets0();
    const vector<shared_ptr<CPSTuningBase>> getSubsets1();
    void setDAWKey(DAWKey);
    const DAWKey getDAWKey();
    void setIsSelected(bool);
    void selectParent();

    // these member functions are capped based on codegen use cases...
    // no other reason to cap at 2 subset arrays, or 8 subsets per array
    virtual void selectS0_0() = 0;
    virtual void selectS0_1() = 0;
    virtual void selectS0_2() = 0;
    virtual void selectS0_3() = 0;
    virtual void selectS0_4() = 0;
    virtual void selectS0_5() = 0;
    virtual void selectS0_6() = 0;
    virtual void selectS0_7() = 0;
    virtual void selectS1_0() = 0;
    virtual void selectS1_1() = 0;
    virtual void selectS1_2() = 0;
    virtual void selectS1_3() = 0;
    virtual void selectS1_4() = 0;
    virtual void selectS1_5() = 0;
    virtual void selectS1_6() = 0;
    virtual void selectS1_7() = 0;
    const bool getIsSelected();

    // convenience returns selected subset or nullptr if parent
    const shared_ptr<CPSTuningBase> getSelectedSubset();

    // these are to compute the parent's subsets; i.e., NOT recursive
    const bool getShouldComputeSubsets();

    // you MUST default to false or no performance gains
    void setShouldComputeSubsets(bool shouldComputeSubsets);
    
    CPS_Class getTuningType();
    virtual bool isEulerGenusTuningType() = 0;

protected:
    CPS_Class _tuningType {CPS_Class::UNDEFINED}; ///< The tuning type.
    vector<Microtone_p> _commonTones {}; ///< The common tones.
    CPSMicrotone _p0; // origin for drawing, not part of the scale

    // sort common tones
    struct less_than_key {
        inline bool operator() (const Microtone_p mt0, const Microtone_p mt1) {
            return (mt0->getShortDescriptionText() < mt1->getShortDescriptionText());
        }
    };

    // line segments, non-unique
    vector<CPSMicrotoneLine> _lineArray {}; ///< The line array.

    // unique labeled points
    vector<CPSMicrotone> _labelArray {}; ///< The label array.

    // origin, plus unique points
    vector<CPSMicrotone> _masterPtArray {}; ///< The master point array.

    // add tuning subsets to these arrays in constructor
    vector<shared_ptr<CPSTuningBase>> _subsets0 {}; ///< The subsets0.
    vector<shared_ptr<CPSTuningBase>> _subsets1 {}; ///< The subsets1.

    // protected methods
    virtual void _allocateSubsets() = 0;
    const bool _getDidAllocateSubsets();
    void _setDidAllocateSubsets(bool didAllocate);
    void _clearSelection();

    // TODO: move to paint as lambda? downside is it can't be used for touches
    AffineTransform _tuningSpaceToDeviceSpaceForBounds(Rectangle<int>);

    // drawing
    bool canPaintTuning() override;
    void paint(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds) override;

private:
    // private members
    bool _shouldComputeSubsets {false}; // you MUST default to false or no performance gains
    bool _didAllocateSubsets {false};
    bool _isSelected {false};

    // default value "assert" is invalid
    DAWKey _dawKey {"assert"}; ///< The DAW key.
};

