/*
 ==============================================================================

 Persian17NorthIndian.cpp
 Created: 18 Mar 2022 7:42:43pm
 Author:  Marcus W. Hobbs

 This file contains the implementation of the Persian17NorthIndian class, which
 represents a specific musical scale used in Persian and North Indian music.

 ==============================================================================
 */

#include "Persian17NorthIndian.h"
#include "WilsonicProcessor.h"

#pragma mark - static members

// __scaleNames is a static member that holds the names of all the scales
// represented by the Persian17NorthIndian class.
const StringArray Persian17NorthIndian::__scaleNames {
    "Persian 17",
    "Kalyan",
    "Bilawal",
    "Khamaj",
    "Khafi (Old)",
    "Kafi",
    "Asawari",
    "Bhairavi",
    "Marwa",
    "Purvi",
    "Lalit 2",
    "Todi",
    "Lalit",
    "(No Name)",
    "Anand Bhairav",
    "Bhairav",
    "Jogiya Todi",
    "Madhubanti",
    "Nat Bhairav",
    "Ahir Bhairav",
    "Chandra Kanada",
    "Basant Mukhari",
    "Champakali",
    "Patdeep",
    "Mohan Kanuns",
    "Parameswari"
};

// all_scales is a static member that holds all the scales represented by the
// Persian17NorthIndian class.
const vector<Persian17NorthIndian::Scale> Persian17NorthIndian::all_scales {
    Persian17NorthIndian::Scale::Master       ,
    Persian17NorthIndian::Scale::Kalyan       ,
    Persian17NorthIndian::Scale::Bilawal      ,
    Persian17NorthIndian::Scale::Khamaj       ,
    Persian17NorthIndian::Scale::KhafiOld     ,
    Persian17NorthIndian::Scale::Kafi         ,
    Persian17NorthIndian::Scale::Asawari      ,
    Persian17NorthIndian::Scale::Bhairavi     ,
    Persian17NorthIndian::Scale::Marwa        ,
    Persian17NorthIndian::Scale::Purvi        ,
    Persian17NorthIndian::Scale::Lalit2       ,
    Persian17NorthIndian::Scale::Todi         ,
    Persian17NorthIndian::Scale::Lalit        ,
    Persian17NorthIndian::Scale::NoName       ,
    Persian17NorthIndian::Scale::AnandBhairav ,
    Persian17NorthIndian::Scale::Bhairav      ,
    Persian17NorthIndian::Scale::JogiyaTodi   ,
    Persian17NorthIndian::Scale::Madhubanti   ,
    Persian17NorthIndian::Scale::NatBhairav   ,
    Persian17NorthIndian::Scale::AhirBhairav  ,
    Persian17NorthIndian::Scale::ChandraKanada,
    Persian17NorthIndian::Scale::BasantMukhari,
    Persian17NorthIndian::Scale::Champakali   ,
    Persian17NorthIndian::Scale::Patdeep      ,
    Persian17NorthIndian::Scale::MohanKanuns  ,
    Persian17NorthIndian::Scale::Parameswari
};

// __persian17 is a static member that holds the microtones for the Persian 17 scale.
MicrotoneArray Persian17NorthIndian::__persian17 {vector<Microtone_p> {
        make_shared<Microtone>(1, 1),
        make_shared<Microtone>(135, 128),
        make_shared<Microtone>(10, 9),
        make_shared<Microtone>(9, 8),
        make_shared<Microtone>(1215, 1024),
        make_shared<Microtone>(5, 4),
        make_shared<Microtone>(81, 64),
        make_shared<Microtone>(4, 3),
        make_shared<Microtone>(45, 32),
        make_shared<Microtone>(729, 512),
        make_shared<Microtone>(3, 2),
        make_shared<Microtone>(405, 256),
        make_shared<Microtone>(5, 3),
        make_shared<Microtone>(27, 16),
        make_shared<Microtone>(16, 9),
        make_shared<Microtone>(15, 8),
        make_shared<Microtone>(243, 128)
    }
};

// __pitch_array is a static member that holds the pitch values for each scale.
const vector<float> Persian17NorthIndian::__pitch_array[num_scales] {
    { 0.f, 0.0768156f, 0.152003f, 0.169925f, 0.246741f, 0.321928f, 0.33985f, 0.415038f, 0.491853f, 0.509775f, 0.584962f, 0.661778f, 0.736966f, 0.754888f, 0.830075f, 0.906891f, 0.924812f },
    { 0.f, 0.1699250f, 0.321928f, 0.491853f, 0.584962f, 0.736966f, 0.906891f },
    { 0.f, 0.1699250f, 0.321928f, 0.415038f, 0.584962f, 0.754888f, 0.906891f },
    { 0.f, 0.1699250f, 0.321928f, 0.415038f, 0.584962f, 0.736966f, 0.830075f },
    { 0.f, 0.1520030f, 0.246741f, 0.415038f, 0.584962f, 0.736966f, 0.830075f },
    { 0.f, 0.1699250f, 0.246741f, 0.415038f, 0.584962f, 0.754888f, 0.830075f },
    { 0.f, 0.1699250f, 0.246741f, 0.415038f, 0.584962f, 0.661778f, 0.830075f },
    { 0.f, 0.0768156f, 0.246741f, 0.415038f, 0.584962f, 0.661778f, 0.830075f },
    { 0.f, 0.0768156f, 0.321928f, 0.491853f, 0.584962f, 0.736966f, 0.906891f },
    { 0.f, 0.0768156f, 0.321928f, 0.491853f, 0.584962f, 0.661778f, 0.906891f },
    { 0.f, 0.0768156f, 0.321928f, 0.415038f, 0.491853f, 0.736966f, 0.906891f },
    { 0.f, 0.0768156f, 0.246741f, 0.491853f, 0.584962f, 0.661778f, 0.906891f },
    { 0.f, 0.0768156f, 0.321928f, 0.415038f, 0.491853f, 0.661778f, 0.906891f },
    { 0.f, 0.0768156f, 0.246741f, 0.491853f, 0.584962f, 0.661778f, 0.830075f },
    { 0.f, 0.0768156f, 0.321928f, 0.415038f, 0.584962f, 0.736966f, 0.906891f },
    { 0.f, 0.0768156f, 0.321928f, 0.415038f, 0.584962f, 0.661778f, 0.906891f },
    { 0.f, 0.0768156f, 0.246741f, 0.415038f, 0.584962f, 0.661778f, 0.906891f },
    { 0.f, 0.1699250f, 0.246741f, 0.491853f, 0.584962f, 0.736966f, 0.906891f },
    { 0.f, 0.1699250f, 0.321928f, 0.415038f, 0.584962f, 0.661778f, 0.906891f },
    { 0.f, 0.0768156f, 0.321928f, 0.415038f, 0.584962f, 0.736966f, 0.830075f },
    { 0.f, 0.1699250f, 0.246741f, 0.415038f, 0.584962f, 0.661778f, 0.906891f },
    { 0.f, 0.0768156f, 0.321928f, 0.415038f, 0.584962f, 0.661778f, 0.830075f },
    { 0.f, 0.1699250f, 0.339850f, 0.491853f, 0.584962f, 0.754888f, 0.830075f },
    { 0.f, 0.1699250f, 0.246741f, 0.415038f, 0.584962f, 0.754888f, 0.906891f },
    { 0.f, 0.1699250f, 0.321928f, 0.415038f, 0.584962f, 0.661778f, 0.830075f },
    { 0.f, 0.0768156f, 0.246741f, 0.415038f, 0.584962f, 0.736966f, 0.830075f }
};

// created by TuningTests+Persian17NorthIndian::persian17NorthIndianCodeGen()

const vector<String> Persian17NorthIndian::__interval_array[num_scales] {
    { "135/128", "256/243", "81/80", "135/128", "256/243", "81/80", "256/243", "135/128", "81/80", "256/243", "135/128", "256/243", "81/80", "256/243", "135/128", "81/80", "256/243" },
    { "9/8", "10/9", "9/8", "16/15", "10/9", "9/8", "16/15" },
    { "9/8", "10/9", "16/15", "9/8", "9/8", "10/9", "16/15" },
    { "9/8", "10/9", "16/15", "9/8", "10/9", "16/15", "9/8" },
    { "10/9", "2187/2048", "4096/3645", "9/8", "10/9", "16/15", "9/8" },
    { "9/8", "135/128", "4096/3645", "9/8", "9/8", "256/243", "9/8" },
    { "9/8", "135/128", "4096/3645", "9/8", "135/128", "4096/3645", "9/8" },
    { "135/128", "9/8", "4096/3645", "9/8", "135/128", "4096/3645", "9/8" },
    { "135/128", "32/27", "9/8", "16/15", "10/9", "9/8", "16/15" },
    { "135/128", "32/27", "9/8", "16/15", "135/128", "32/27", "16/15" },
    { "135/128", "32/27", "16/15", "135/128", "32/27", "9/8", "16/15" },
    { "135/128", "9/8", "32/27", "16/15", "135/128", "32/27", "16/15" },
    { "135/128", "32/27", "16/15", "135/128", "9/8", "32/27", "16/15" },
    { "135/128", "9/8", "32/27", "16/15", "135/128", "4096/3645", "9/8" },
    { "135/128", "32/27", "16/15", "9/8", "10/9", "9/8", "16/15" },
    { "135/128", "32/27", "16/15", "9/8", "135/128", "32/27", "16/15" },
    { "135/128", "9/8", "4096/3645", "9/8", "135/128", "32/27", "16/15" },
    { "9/8", "135/128", "32/27", "16/15", "10/9", "9/8", "16/15" },
    { "9/8", "10/9", "16/15", "9/8", "135/128", "32/27", "16/15" },
    { "135/128", "32/27", "16/15", "9/8", "10/9", "16/15", "9/8" },
    { "9/8", "135/128", "4096/3645", "9/8", "135/128", "32/27", "16/15" },
    { "135/128", "32/27", "16/15", "9/8", "135/128", "4096/3645", "9/8" },
    { "9/8", "9/8", "10/9", "16/15", "9/8", "256/243", "9/8" },
    { "9/8", "135/128", "4096/3645", "9/8", "9/8", "10/9", "16/15" },
    { "9/8", "10/9", "16/15", "9/8", "135/128", "4096/3645", "9/8" },
    { "135/128", "9/8", "4096/3645", "9/8", "10/9", "16/15", "9/8" }
};

#pragma mark - lifecycle

Persian17NorthIndian::Persian17NorthIndian() {
    setCanNPOOverride(true);
    setCanUniquify(false); // static and defined as unique
    setCanSort(false); // static and defined as sorted
    setSort(false);
    setScale(_scale);
}

Persian17NorthIndian::~Persian17NorthIndian() {

}

// public methods

void Persian17NorthIndian::setScale(Scale mode) {
    const ScopedLock sl(_lock);

    // set mode, and name
    _scale = mode;
    auto const name = __scaleNames[static_cast<int>(_scale)];
    auto tn = "Persian 17 North Indian: " + name;
    setTuningName(tn.toStdString());

    switch(_scale) {
        case Scale::Master:
            setMicrotoneArray(_mt_scale({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}));
            break;
        case Scale::Kalyan:
            setMicrotoneArray(_mt_scale({0, 3, 5, 8, 10, 12, 15}));
            break;
        case Scale::Bilawal:
            setMicrotoneArray(_mt_scale({0, 3, 5, 7, 10, 13, 15}));
            break;
        case Scale::Khamaj:
            setMicrotoneArray(_mt_scale({0, 3, 5, 7, 10, 12, 14}));
            break;
        case Scale::KhafiOld:
            setMicrotoneArray(_mt_scale({0, 2, 4, 7, 10, 12, 14}));
            break;
        case Scale::Kafi:
            setMicrotoneArray(_mt_scale({0, 3, 4, 7, 10, 13, 14}));
            break;
        case Scale::Asawari:
            setMicrotoneArray(_mt_scale({0, 3, 4, 7, 10, 11, 14}));
            break;
        case Scale::Bhairavi:
            setMicrotoneArray(_mt_scale({0, 1, 4, 7, 10, 11, 14}));
            break;
        case Scale::Marwa:
            setMicrotoneArray(_mt_scale({0, 1, 5, 8, 10, 12, 15}));
            break;
        case Scale::Purvi:
            setMicrotoneArray(_mt_scale({0, 1, 5, 8, 10, 11, 15}));
            break;
        case Scale::Lalit2:
            setMicrotoneArray(_mt_scale({0, 1, 5, 7, 8, 12, 15}));
            break;
        case Scale::Todi:
            setMicrotoneArray(_mt_scale({0, 1, 4, 8, 10, 11, 15}));
            break;
        case Scale::Lalit:
            setMicrotoneArray(_mt_scale({0, 1, 5, 7, 8, 11, 15}));
            break;
        case Scale::NoName:
            setMicrotoneArray(_mt_scale({0, 1, 4, 8, 10, 11, 14}));
            break;
        case Scale::AnandBhairav:
            setMicrotoneArray(_mt_scale({0, 1, 5, 7, 10, 12, 15}));
            break;
        case Scale::Bhairav:
            setMicrotoneArray(_mt_scale({0, 1, 5, 7, 10, 11, 15}));
            break;
        case Scale::JogiyaTodi:
            setMicrotoneArray(_mt_scale({0, 1, 4, 7, 10, 11, 15}));
            break;
        case Scale::Madhubanti:
            setMicrotoneArray(_mt_scale({0, 3, 4, 8, 10, 12, 15}));
            break;
        case Scale::NatBhairav:
            setMicrotoneArray(_mt_scale({0, 3, 5, 7, 10, 11, 15}));
            break;
        case Scale::AhirBhairav:
            setMicrotoneArray(_mt_scale({0, 1, 5, 7, 10, 12, 14}));
            break;
        case Scale::ChandraKanada:
            setMicrotoneArray(_mt_scale({0, 3, 4, 7, 10, 11, 15}));
            break;
        case Scale::BasantMukhari:
            setMicrotoneArray(_mt_scale({0, 1, 5, 7, 10, 11, 14}));
            break;
        case Scale::Champakali:
            setMicrotoneArray(_mt_scale({0, 3, 6, 8, 10, 13, 14}));
            break;
        case Scale::Patdeep:
            setMicrotoneArray(_mt_scale({0, 3, 4, 7, 10, 13, 15}));
            break;
        case Scale::MohanKanuns:
            setMicrotoneArray(_mt_scale({0, 3, 5, 7, 10, 11, 14}));
            break;
        case Scale::Parameswari:
            setMicrotoneArray(_mt_scale({0, 1, 4, 7, 10, 12, 14}));
            break;
        default:
            jassertfalse;
            break;
    }
}

int const Persian17NorthIndian::getScale() {
    return static_cast<int>(_scale);
}

#pragma mark - drawing

// drawing

bool Persian17NorthIndian::canPaintTuning() {
    return true;
}

void Persian17NorthIndian::paint(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds) {
    g.fillAll(processor.getAppSkin().getBgColor());
    if(AppExperiments::showDebugBoundingBox) {
        g.setColour(Colours::green);
        g.drawRect(bounds, 2);
    }

    paint01(processor, g, bounds);
}

// original...super busy...text too small
void Persian17NorthIndian::paint00(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds) {
    // TODO: Draw 17 as well

    // x                   x0                    x1
    // | scale_label_width |  [pitches]          |
    auto const scale_label_width = 100;
    auto const slx0 = bounds.getX();
    auto const slx1 = bounds.getX() + scale_label_width - 5; // padding
    auto const intervals_width = bounds.getWidth() - scale_label_width;
    auto const x0 = scale_label_width + bounds.getX();
    auto const x1 = x0 + intervals_width;
    auto const ch = bounds.getHeight() / float(num_scales);
    auto const level = getScale();
    auto const lt0 = 1;
    auto const lt1 = 2;
    auto const lt2 = 4;
    for(auto i = 0; i < num_scales; i++) {
        // TODO: render the subset within the master 0

        auto const selected_scale = (i == level);

        // this scale rect outline
        auto const y0 = bounds.getY() + i * ch;
        auto const y1 = y0 + ch;
        auto const r = Rectangle<int>::leftTopRightBottom(x0, static_cast<int>(y0), x1, static_cast<int>(y1));
        auto outlineColor = selected_scale ? Colours::white : Colours::darkslategrey;
        g.setColour(outlineColor);
        g.drawRect(r, lt0);
        auto const slr = Rectangle<int>::leftTopRightBottom(slx0, static_cast<int>(y0), slx1, static_cast<int>(y1));
        auto const scale_name = __scaleNames[i];
        g.drawFittedText(scale_name, slr, Justification::right, 0);

        //TODO: convert to lambda and include octave
        // each pitch
        auto pitches = __pitch_array[i];
        for (auto p : pitches) {
            // color of line based on pitch and selection
            auto cp = processor.getAppTuningModel()->colorForPitch01(p);
            if (! selected_scale)
                cp = cp.darker().darker().darker();
            g.setColour(cp);
            auto px = x0 + p * intervals_width;
            auto lt = selected_scale ? lt2 : lt1;
            g.drawLine(px, y0, px, y1, lt);
        }

        // each interval label
        auto intervals = __interval_array[i];
        for (unsigned long j = 0; j < pitches.size(); j++) {
            auto p0 = pitches[j];
            auto p1 = (j < pitches.size() - 1) ? pitches[j+1] : 1;
            auto ix0 = x0 + p0 * intervals_width;
            auto ix1 = x0 + p1 * intervals_width;
            auto const ir = Rectangle<int>::leftTopRightBottom(static_cast<int>(ix0), static_cast<int>(y0), static_cast<int>(ix1), static_cast<int>(y1));
            auto cp = selected_scale ? Colours::white : Colours::grey;
            g.setColour(cp);
            auto interval = intervals[j];
            g.drawFittedText(interval, ir, Justification::centred, 0);
        }
    }

#if JucePlugin_IsSynth
    // optimization
    auto vs = processor.getVoiceStates();
    if(vs.noVoicesPlaying()) {
        return;
    }
#elif JucePlugin_IsMidiEffect
#else
    jassertfalse;
#endif
    // TODO: Draw playing notes
}

// simpler version
void Persian17NorthIndian::paint01(WilsonicProcessor& processor, Graphics& g, Rectangle<int> bounds) {
    // x                   x0                    x1
    // | scale_label_width |  [pitches]          |
    auto const x0 = bounds.getX();
    auto const intervals_width = bounds.getWidth();
    auto const x1 = x0 + intervals_width;
    auto const scale = getScale();
    auto const line_thickness = 4;

    // this scale rect outline (2 horizontal lines)
    auto const y0 = bounds.getY();
    auto const y1 = y0 + bounds.getHeight();
    auto outlineColor = Colours::white;
    g.setColour(outlineColor);
    g.fillRect(x0, y0, intervals_width, line_thickness);
    g.fillRect(x0, y1 - line_thickness, intervals_width, line_thickness);

    // draw root and octave
    auto co = processor.getAppTuningModel()->colorForPitch01(0);
    g.setColour(co);
    g.fillRect(x0, y0, line_thickness, bounds.getHeight());
    g.fillRect(x1 - line_thickness, y0, line_thickness, bounds.getHeight());

    // draw each pitch as a vertical line
    auto pitches = __pitch_array[scale];
    for(auto p : pitches) {
        // color of line based on pitch and selection
        auto cp = processor.getAppTuningModel()->colorForPitch01(p);
        g.setColour(cp);
        auto const px = x0 + p * intervals_width;
        g.fillRect(static_cast<int>(px - 0.5 * line_thickness), y0, line_thickness, bounds.getHeight());
    }

    // each interval label
    auto intervals = __interval_array[scale];
    for(unsigned long j = 0; j < pitches.size(); j++) {
        auto p0 = pitches[j];
        auto p1 = (j < pitches.size() - 1) ? pitches[j+1] : 1;
        auto ix0 = x0 + p0 * intervals_width;
        auto ix1 = x0 + p1 * intervals_width;
        auto const ir = Rectangle<int>::leftTopRightBottom(static_cast<int>(ix0), y0, static_cast<int>(ix1), y1);
        auto cp = Colours::white;
        g.setColour(cp);
        auto interval = intervals[j];
        g.drawFittedText(interval, ir, Justification::centred, 0);
    }
}

#pragma mark - Scala

String Persian17NorthIndian::defaultScalaName() {
    auto n = String("persian17_");
    auto sn = __scaleNames[int(_scale)];
    if(_scale != Scale::Master) {
        n += sn;
    }
    sn += ".scl";
    auto snn = sn.toStdString();
    WilsonicAppSkin::replaceAll(snn, " ", "_");
    WilsonicAppSkin::replaceAll(snn, "(", "_");
    WilsonicAppSkin::replaceAll(snn, ")", "_");
    transform(snn.begin(), snn.end(), snn.begin(), [](unsigned char c) { return tolower(c); });

    return String(snn);
}

String Persian17NorthIndian::scalaComments() {
    return TuningImp::scalaComments();
}

#pragma mark -

MicrotoneArray Persian17NorthIndian::_mt_scale(vector<unsigned long> degrees) {
    jassert(degrees.size() == 17 || degrees.size() == 7);
    auto mt = MicrotoneArray();
    for(auto i : degrees) {
        mt.addMicrotone(__persian17.microtoneAtIndex((unsigned long)i));
    }
    
    return mt;
}
