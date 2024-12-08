/*
 ==============================================================================
 
 CoPrime.h
 Created: 23 Apr 2023 12:39:35pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#pragma once

#include <JuceHeader.h>
#include "Tuning_Include.h"
#include "CoPrimeMicrotone.h"
#include "MicrotoneArray.h"
#include "TuningImp.h"

class CoPrimeMicrotone;
using CoPrimeMicrotone_p = shared_ptr<CoPrimeMicrotone>;

class CoPrime : public TuningImp
{
public:
    static unsigned long GCD(unsigned long a, unsigned long b);
    
    // order should never change
    static const StringArray __displayModeNames;
    static StringArray getDisplayModeNames() { return __displayModeNames; }
    static constexpr int num_modes = 3; // unused?
    
    // **if you ever change these you will break automation**
    enum class DisplayMode
    {
        Subharmonic = 0,
        Triangle = 1,
        Harmonic = 2
    };
    // NOTE: all of these are used as unsigned longs, but are cast as
    // floats because they are automatable paramers.
    static float constexpr getMinA() {return 0;}
    static float constexpr getMaxA() {return 127;}
    static float constexpr getDefaultA() {return 0;}
    static float constexpr getMinB() {return 1;}
    static float constexpr getMaxB() {return 127;}
    static float constexpr getDefaultB() {return 1;}
    static float constexpr getMinC() {return 1;}
    static float constexpr getMaxC() {return 127;}
    static float constexpr getDefaultC() {return 1;}
    static float constexpr getMinD() {return 0;}
    static float constexpr getMaxD() {return 127;}
    static float constexpr getDefaultD() {return 0;}
    static float constexpr getMinS() {return 1;}
    static float constexpr getMaxS() {return 127;}
    static float constexpr getDefaultS() {return 1;}
    static float constexpr getMinT() {return 1;}
    static float constexpr getMaxT() {return 127;}
    static float constexpr getDefaultT() {return 1;}
    static float constexpr getIntervalValue() {return 1;}
    static float constexpr getMinX() {return 1;}
    static float constexpr getMaxX() {return 11;} // 11*11 = 121 < 128
    static float constexpr getDefaultX() {return 9;}
    static float constexpr getMinY() {return 1;}
    static float constexpr getMaxY() {return 11;} // 11*11 = 121 < 128
    static float constexpr getDefaultY() {return 9;}
    static int constexpr getDisplayModeDefault() {return 1;}
    
    // **if you ever change these you will break automation**
    
    // lifecycle
    
    CoPrime();
    ~CoPrime() noexcept override = default;
    
    // public member functions
    unsigned long getA() const;
    void setA (unsigned long value);
    unsigned long getB() const;
    void setB (unsigned long value);
    unsigned long getC() const;
    void setC (unsigned long value);
    unsigned long getD() const;
    void setD (unsigned long value);
    unsigned long getS() const;
    void setS (unsigned long value);
    unsigned long getT() const;
    void setT (unsigned long value);
    unsigned long getX() const; // 1-based index
    void setX (unsigned long value); // 1-based index
    unsigned long getY() const; // 1-based index
    void setY (unsigned long value); // 1-based index
    void setDisplayMode(CoPrime::DisplayMode new_mode);
    const int getDisplayMode(); // yes return int instead of DisplayMode
    CoPrimeMicrotone_p getMicrotoneAtXY(unsigned long x, unsigned long y); // 0-based indices x and y
    
    // drawing
    bool canPaintTuning() override;
    void paint(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds) override;
    
    // Mouse handling
    int cpgnnForDeviceSpace(Point<int> xy, Rectangle<int> viewSize); // return starts at noteNumberForMiddleC
    
    // Scala
    String defaultScalaName() override;
    String scalaComments() override;
    
private:
    // private members
    
    // if you change these values you will change the default behavior
    unsigned long _a = 0;
    unsigned long _b = 1;
    unsigned long _c = 1;
    unsigned long _d = 0;
    unsigned long _s = 1;
    unsigned long _t = 1;
    unsigned long _numX = static_cast<unsigned long>(getMinX()); // 1-based index
    unsigned long _numY = static_cast<unsigned long>(getMinY()); // 1-based index
    DisplayMode _displayMode = DisplayMode::Triangle;
    vector<vector<CoPrimeMicrotone_p>> _cpgArray; // 0-based indices
    
    // private methods
    void _validateABCDSTXY();
    void _updateCPG(); // calls _update by setting microtonearray
    AffineTransform tuningSpaceToDeviceSpaceForSize(const Rectangle<int>& viewSize);
    AffineTransform deviceSpaceToTuningSpaceForSize(const Rectangle<int>& viewSize);
    void _commonDrawingForRect(WilsonicProcessor& processor,
                               Graphics& g,
                               const Rectangle<int>& bounds,
                               CoPrimeMicrotone_p microtone,
                               float vMag);
};
