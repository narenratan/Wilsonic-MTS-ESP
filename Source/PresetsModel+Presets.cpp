/*
 ==============================================================================
 
 PresetsModel+Presets.cpp
 Created: 31 May 2022 5:10:00pm
 Author:  Marcus W. Hobbs
 
 ==============================================================================
 */

#include "PresetsModel.h"
#include "MicrotoneArray.h"

// convenience

MicrotoneArray PresetsModel::MAF(vector<float> float_array)
{
    return MicrotoneArray::microtoneArrayFromArrayOfFloats(float_array);
}

MicrotoneArray PresetsModel::MAD(vector<int> num_den_pairs)
{
    return MicrotoneArray::microtoneArrayFromArrayOfNumDenPairs(num_den_pairs);
}

// the order can never change or it will break automation

vector<PresetHelper> PresetsModel::__presetsHelpers
{
    PresetHelper
    ("12 ET",
     [](){ return MAF({
        1.f,
        1.0594630943592953f,
        1.122462048309373f,
        1.189207115002721f,
        1.2599210498948732f,
        1.3348398541700344f,
        1.4142135623730951f,
        1.4983070768766815f,
        1.5874010519681994f,
        1.681792830507429f,
        1.7817974362806785f,
        1.8877486253633868f
    }); } ,
     "Twelve Tone Equal Temperament"
     ),
    
    PresetHelper
    ("Chain of pure fifths",
     [](){ return MAD(vector<int>{
        1,1,
        3,1,
        9,1,
        27,1,
        81,1,
        243,1,
        729,1,
        2187,1,
        6561,1,
        19683,1,
        59049,1,
        177147,1
    }); },
     "12 tone scale of a chain of 3's"
     ),
    
    PresetHelper
    ("Harmonic Series: Dyad",
     [](){ return MAD(vector<int>{
        2,1,
        3,1
    }); },
     "Harmonic Series: 2, 3"
     ),
    
    PresetHelper
    ("Subharmonic Series: Dyad",
     [](){ return MAD(vector<int>{
        1,2,
        1,3
    }); },
     "Subharmonic Series: 2, 3"
     ),
    
    PresetHelper
    ("Harmonic+Subharmonic Series: Dyad",
     [](){ return MAD(vector<int>{
        1,1,
        1,3,
        3,1
    }); },
     "Combining the Harmonic and Subharmonic Series: 1, 1/3, 3"
     ),
    
    PresetHelper
    ("Harmonic Series: Triad",
     [](){ return MAD(vector<int>{
        3,3,
        4,3,
        5,3
    }); },
     "Harmonic Series: 3, 4, 5"
     ),
    
    PresetHelper
    ("Subharmonic Series: Triad",
     [](){ return MAD(vector<int>{
        3,3,
        3,4,
        3,5
    }); },
     "Subharmonic Series: 3, 4, 5"
     ),
    
    PresetHelper
    ("Harmonic+Subharmonic Series: Triad",
[](){ return MAD({
    3,3,
    4,3,
    5,3,
    3,4,
    3,5
}); } ,
     "Harmonic+Subharmonic Series: 3, 4, 5"
     ),
    
    PresetHelper
    ("Harmonic Series: Tetrad",
[](){ return MAD({
    4,4,
    5,4,
    6,4,
    7,4
}); } ,
     "Harmonic Series: 4, 5, 6, 7"
     ),
    
    PresetHelper
    ("Subharmonic Series: Tetrad",
[](){ return MAD({
    4,4,
    4,5,
    4,6,
    4,7
}); } ,
     "Subharmonic Series: 4, 5, 6, 7"
     ),
    
    PresetHelper
    ("Harmonic+Subharmonic Series: Tetrad",
[](){ return MAD({
    4,4,
    5,4,
    6,4,
    7,4,
    4,5,
    4,6,
    4,7
}); } ,
     "Harmonic+Subharmonic Series: Tetrad"
     ),
    
    PresetHelper
    ("Subharmonic Series: Triad and Tetrad",
[](){ return MAD({
    4,4,
    4,5,
    4,6,
    4,7,
    3,4,
    3,5
}); } ,
     "Subharmonic Series: Triad and Tetrad, combined"
     ),
    
    PresetHelper
    ("Harmonic Series: Pentad",
[](){ return MAD({
    5,5,
    6,5,
    7,5,
    8,5,
    9,5
}); } ,
     "Harmonic Series: Pentad"
     ),
    
    PresetHelper
    ("Subharmonic Series: Pentad",
[](){ return MAD({
    5,5,
    5,6,
    5,7,
    5,8,
    5,9
}); } ,
     "Subharmonic Series: Pentad"
     ),
    
    PresetHelper
    ("Harmonic+Subharmonic Series: Pentad",
[](){ return MAD({
    5,5,
    6,5,
    7,5,
    8,5,
    9,5,
    5,6,
    5,7,
    5,8,
    5,9
}); } ,
     "Harmonic+Subharmonic Series: Pentad"
     ),
    
    PresetHelper
    ("Harmonic Series: 12",
[](){ return MAD({
    12,12,
    13,12,
    14,12,
    15,12,
    16,12,
    17,12,
    18,12,
    19,12,
    20,12,
    21,12,
    22,12,
    23,12
}); } ,
     "Harmonic Series"
     ),
    
    
    PresetHelper
    ("Wilson Hexany(1, 3, 5, 7)",
[](){ return MAF({
    3.f,
    5.f,
    7.f,
    15.f,
    21.f,
    35.f
}); } ,
     "Wilson Hexany(1, 3, 5, 7)"
     ),
    
    PresetHelper
    ("Wilson Hexany(1, 3, 5, 45)",
[](){ return MAF({
    3.f,
    5.f,
    45.f,
    15.f,
    135.f,
    225.f
}); } ,
     "Wilson Hexany(1, 3, 5, 45)"
     ),
    
    PresetHelper
    ("Wilson Hexany(1, 3, 5, 9)",
[](){ return MAF({
    3.f,
    5.f,
    9.f,
    15.f,
    27.f,
    45.f
}); } ,
     "Wilson Hexany(1, 3, 5, 9)"
     ),
    
    PresetHelper
    ("Wilson Hexany(1, 3, 5, 15)",
[](){ return MAF({
    3.f,
    5.f,
    15.f,
    15.f,
    45.f,
    75.f
}); } ,
     "Wilson Hexany(1, 3, 5, 15)"
     ),
    
    PresetHelper
    ("Wilson Hexany(1, 3, 5, 81)",
[](){ return MAF({
    3.f,
    5.f,
    81.f,
    15.f,
    243.f,
    405.f
}); } ,
     "Wilson Hexany(1, 3, 5, 81)"
     ),
    
    PresetHelper
    ("Wilson Dekany(1, 3, 5, 9, 81)",
[](){ return MAF({
    3.f,
    5.f,
    9.f,
    81.f,
    15.f,
    27.f,
    243.f,
    45.f,
    405.f,
    729.f
}); } ,
     "Wilson Dekany(1, 3, 5, 9, 81)"
     ),
    
    PresetHelper
    ("Wilson Hexany(1, 3, 5, 121)",
[](){ return MAF({
    3.f,
    5.f,
    121.f,
    15.f,
    363.f,
    605.f
}); } ,
     "Wilson Hexany(1, 3, 5, 121)"
     ),
    
    PresetHelper
    ("Wilson Hexany(1, 15, 45, 75)",
[](){ return MAF({
    15.f,
    45.f,
    75.f,
    675.f,
    1125.f,
    3375.f
}); } ,
     "Wilson Hexany(1, 15, 45, 75)"
     ),
    
    PresetHelper
    ("Wilson Hexany(1, 17, 19, 23)",
[](){ return MAF({
    17.f,
    19.f,
    23.f,
    323.f,
    391.f,
    437.f
}); } ,
     "Wilson Hexany(1, 17, 19, 23)"
     ),
    
    PresetHelper
    ("Wilson Hexany(1, 45, 135, 225)",
[](){ return MAF({
    45.f,
    135.f,
    225.f,
    6075.f,
    10125.f,
    30375.f
}); } ,
     "Wilson Hexany(1, 45, 135, 225)"
     ),
    
    PresetHelper
    ("Wilson Hexany(3, 5, 7, 9)",
[](){ return MAF({
    15.f,
    21.f,
    27.f,
    35.f,
    45.f,
    63.f
}); } ,
     "Wilson Hexany(3, 5, 7, 9)"
     ),
    
    PresetHelper
    ("Wilson Hexany(3, 5, 15, 19)",
[](){ return MAF({
    15.f,
    45.f,
    57.f,
    75.f,
    95.f,
    285.f
}); } ,
     "Wilson Hexany(3, 5, 15, 19)"
     ),
    
    PresetHelper
    ("Wilson Diaphonic",
[](){ return MAD({
    1 ,1,
    27,26,
    9 ,8,
    4 ,3,
    18,13,
    3 ,2,
    27,16
}); } ,
     "Wilson Diaphonic"
     ),
    
    PresetHelper
    ("Wilson Hexany(3, 5, 15, 27)",
[](){ return MAF({
    15.f,
    45.f,
    81.f,
    75.f,
    135.f,
    405.f
}); } ,
     "Wilson Hexany(3, 5, 15, 27)"
     ),
    
    PresetHelper
    ("Wilson Hexany(5, 7, 21, 35)",
[](){ return MAF({
    35.f,
    105.f,
    175.f,
    147.f,
    245.f,
    735.f
}); } ,
     "Wilson Hexany(5, 7, 21, 35)"
     ),
    
    PresetHelper
    ("Wilson Highland Bagpipes",
[](){ return MAD({
    32,1,
    36,1,
    39,1,
    171,1,
    48,1,
    52,1,
    57,1
}); } ,
     "Wilson Highland Bagpipes"
     ),
    
    PresetHelper
    ("Wilson Fibonacci Triplets of Meta-Pelog 1",
[](){ return MAF({
    4.f,
    6.f,
    9.f,
    13.f,
    19.f,
    28.f,
    41.f,
    60.f,
    88.f
}); } ,
     "Wilson Fibonacci Triplets of Meta-Pelog 1"
     ),
    
    PresetHelper
    ("Wilson Fibonacci Triplets of Meta-Pelog 2",
[](){ return MAF({
    7.f,
    10.f,
    15.f,
    22.f,
    32.f,
    47.f,
    69.f,
    101.f,
    148.f
}); } ,
     "Wilson Fibonacci Triplets of Meta-Pelog 2"
     ),
    
    PresetHelper
    ("Wilson Fibonacci Triplets of Meta-S'lendro 1",
[](){ return MAF({
    9.f,
    12.f,
    16.f,
    21.f,
    28.f,
    37.f,
    49.f
}); } ,
     "Wilson Fibonacci Triplets of Meta-S'lendro 1"
     ),
    
    PresetHelper
    ("Wilson Fibonacci Triplets of Meta-S'lendro 2",
[](){ return MAF({
    15.f,
    20.f,
    26.f,
    35.f,
    46.f,
    61.f,
    81.f
}); } ,
     "Wilson Fibonacci Triplets of Meta-S'lendro 2"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.238186456",
[](){ return MAF({
    1.f,
    1.141501f,
    1.179509f,
    1.346411f,
    1.391242f,
    1.588104f,
    1.640982f,
    1.873183f,
    1.935553f
}); } ,
     "Wilson MOS G:0.238186456"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.2641",
[](){ return MAF({
    1.f,
    1.039868f,
    1.200887f,
    1.248763f,
    1.442129f,
    1.499623f,
    1.731833f
}); } ,
     "Wilson MOS G:0.2641"
     ),
    
    PresetHelper
    ("Wilson MOS G:1.27155330316",
[](){ return MAF({
    1.f,
    1.06158f,
    1.207107f,
    1.28144f,
    1.457107f,
    1.546836f,
    1.758883f
}); } ,
     "Wilson MOS G:1.27155330316"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.292787482510",
[](){ return MAF({
    1.f,
    1.125956f,
    1.225005f,
    1.379301f,
    1.500637f,
    1.689651f,
    1.838288f
}); } ,
     "Wilson MOS G:0.292787482510"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.328173",
[](){ return MAF({
    1.f,
    1.139859f,
    1.152155f,
    1.164584f,
    1.177147f,
    1.189846f,
    1.202681f,
    1.215655f,
    1.228769f,
    1.242024f,
    1.255423f,
    1.431005f,
    1.446442f,
    1.462045f,
    1.477817f,
    1.493759f,
    1.509873f,
    1.526161f,
    1.542625f,
    1.559266f,
    1.576087f,
    1.796516f,
    1.815896f,
    1.835485f,
    1.855286f,
    1.8753f,
    1.89553f,
    1.915978f,
    1.936646f,
    1.957538f,
    1.978655f
}); } ,
     "Wilson MOS G:0.328173"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.357018636",
[](){ return MAF({
    1.f,
    1.050485f,
    1.103519f,
    1.280776f,
    1.345437f,
    1.413361f,
    1.640388f,
    1.723204f
}); } ,
     "Wilson MOS G:0.357018636"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.394619733",
[](){ return MAF({
    1.f,
    1.135918f,
    1.290311f,
    1.314596f,
    1.493274f,
    1.696237f,
    1.728163f,
    1.963052f
}); } ,
     "Wilson MOS G:0.394619733"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.405685213",
[](){ return MAF({
    1.f,
    1.019899f,
    1.162359f,
    1.324718f,
    1.351078f,
    1.539798f,
    1.754878f
}); } ,
     "Wilson MOS G:0.405685213"
     ),
    
    PresetHelper
    ("Wilson Meta-S'lendro Reseed",
[](){ return MAF({
    9.f,
    12.f,
    16.f,
    21.f,
    28.f,
    37.f,
    49.f
}); } ,
     "Wilson Meta-S'lendro Reseed"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.415226813",
[](){ return MAF({
    1.f,
    1.054189f,
    1.185652f,
    1.333508f,
    1.40577f,
    1.581077f,
    1.778244f
}); } ,
     "Wilson MOS G:0.415226813"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.418934662571",
[](){ return MAF({
    1.f,
    1.067824f,
    1.194829f,
    1.33694f,
    1.427616f,
    1.597414f,
    1.787408f
}); } ,
     "Wilson MOS G:0.418934662571"
     ),
    
    PresetHelper
    ("Wilson Meantone Reseed",
[](){ return MAF({
    27.f,
    36.f,
    48.f,
    64.f,
    86.f,
    115.f,
    153.5f
}); } ,
     "Wilson Meantone Reseed"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.420307969",
[](){ return MAF({
    1.f,
    1.072918f,
    1.198246f,
    1.338213f,
    1.435793f,
    1.603508f,
    1.790815f
}); } ,
     "Wilson MOS G:0.420307969"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.436385705",
[](){ return MAF({
    1.f,
    1.134399f,
    1.238984f,
    1.35321f,
    1.53508f,
    1.676605f,
    1.831177f
}); } ,
     "Wilson MOS G:0.436385705"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.449984313472",
[](){ return MAF({
    1.f,
    1.189142f,
    1.274519f,
    1.366025f,
    1.624399f,
    1.741025f,
    1.866025f
}); } ,
     "Wilson MOS G:0.449984313472"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.551463089738",
[](){ return MAF({
    1.f,
    1.07395f,
    1.153368f,
    1.238659f,
    1.465571f,
    1.57395f,
    1.690342f
}); } ,
     "Wilson MOS G:0.551463089738"
     ),
    
    PresetHelper
    ("Wilson Meta-Pelog Reseed 1",
[](){ return MAF({
    4.f,
    6.f,
    9.f,
    13.f,
    19.f
}); } ,
     "Wilson Meta-Pelog Reseed 1"
     ),
    
    PresetHelper
    ("Wilson Meta-Pelog Reseed 2",
[](){ return MAF({
    7.f,
    10.f,
    15.f,
    22.f,
    32.f
}); } ,
     "Wilson Meta-Pelog Reseed 2"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.579692031",
[](){ return MAF({
    1.f,
    1.11681f,
    1.247265f,
    1.392958f,
    1.49453f,
    1.669107f,
    1.864075f
}); } ,
     "Wilson MOS G:0.579692031"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.580889653448",
[](){ return MAF({
    1.f,
    1.118666f,
    1.251414f,
    1.399914f,
    1.495771f,
    1.673268f,
    1.871829f
}); } ,
     "Wilson MOS G:0.580889653448"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.591780292",
[](){ return MAF({
    1.f,
    1.135683f,
    1.289777f,
    1.464778f,
    1.507105f,
    1.711594f,
    1.943829f
}); } ,
     "Wilson MOS G:0.591780292"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.605380266640",
[](){ return MAF({
    1.f,
    1.157298f,
    1.339339f,
    1.52138f,
    1.76069f
}); } ,
     "Wilson MOS G:0.605380266640"
     ),
    
    PresetHelper
    ("Wilson Iso-S'lendro Reseed",
[](){ return MAF({
    21.f,
    32.f,
    49.f,
    74.f,
    113.f
}); } ,
     "Wilson Iso-S'lendro Reseed"
     ),
    
    PresetHelper
    ("Wilson MOS G:0.694241913631",
[](){ return MAF({
    1.f,
    1.059017f,
    1.121517f,
    1.309017f,
    1.386271f,
    1.618034f,
    1.713526f
}); } ,
     "Wilson MOS G:0.694241913631"
     ),
    
    PresetHelper
    ("Wilson Phi Reseed 1",
[](){ return MAF({
    1.f,
    3.f,
    5.f,
    13.f,
    21.f,
    34.f,
    55.f
}); } ,
     "Wilson Phi Reseed 1"
     ),
    
    PresetHelper
    ("Wilson Phi Reseed 2",
[](){ return MAF({
    1.f,
    3.f,
    7.f,
    11.f,
    18.f,
    29.f,
    47.f
}); } ,
     "Wilson Phi Reseed 2"
     ),
    
    PresetHelper
    ("Wilson Evangelina",
[](){ return MAD({
    1, 1,
    135,128,
    13,12,
    10,9,
    9,8,
    7,6,
    11,9,
    5,4,
    81,64,
    4,3,
    11,8,
    45,32,
    17,12,
    3,2,
    19,12,
    13,8,
    5,3,
    27,16,
    7,4,
    11,6,
    15,8,
    243,128
}); } ,
     "Wilson Evangelina"
     ),
    
    PresetHelper
    ("Garcia: Meta Mavila (37-50-67-91)",
[](){ return MAD({
    1,1,
    1027,1024,
    67,64,
    559,512,
    37,32,
    153,128,
    2539,2048,
    167,128,
    1389,1024,
    91,64,
    189,128,
    25,16,
    415,256,
    225,128,
    937,512,
    31,16
}); } ,
     "Garcia: Meta Mavila (37-50-67-91)"
     ),
    
    PresetHelper
    ("Garcia: Wilson 7-limit marimba",
[](){ return MAD({
    1,1,
    28,27,
    16,15,
    10,9,
    9,8,
    7,6,
    6,5,
    5,4,
    35,27,
    4,3,
    27,20,
    45,32,
    35,24,
    3,2,
    14,9,
    8,5,
    5,3,
    27,16,
    7,4,
    9,5,
    15,8,
    35,18
}); } ,
     "Garcia: Wilson 7-limit marimba"
     ),
    
    PresetHelper
    ("Garcia: linear 15/13-52/45 alternating",
[](){ return MAD({
    1,1,
    40,39,
    27,26,
    16,15,
    128,117,
    9,8,
    15,13,
    32,27,
    6,5,
    16,13,
    81,64,
    135,104,
    4,3,
    160,117,
    18,13,
    64,45,
    512,351,
    3,2,
    20,13,
    81,52,
    8,5,
    64,39,
    27,16,
    45,26,
    16,9,
    9,5,
    24,13,
    256,135,
    405,208
}); } ,
     "Garcia: linear 15/13-52/45 alternating"
     ),
    
    PresetHelper
    ("Grady: S 7-limit Pentatonic",
[](){ return MAD({
    1,1,
    7,6,
    4,3,
    3,2,
    7,4
}); } ,
     "Grady: S 7-limit Pentatonic"
     ),
    
    PresetHelper
    ("Grady: S Pentatonic 11-limit Scale 1",
[](){ return MAD({
    1,1,
    9,8,
    11,8,
    3,2,
    7,4
}); } ,
     "Grady: S Pentatonic 11-limit Scale 1"
     ),
    
    PresetHelper
    ("Grady: S Pentatonic 11-limit Scale 2",
[](){ return MAD({
    1,1, 5,4, 11,8, 3,2, 7,4
}); } ,
     "Grady: S Pentatonic 11-limit Scale 2"
     ),
    
    PresetHelper
    ("Grady: S Centaur 7-limit Minor",
[](){ return MAD({
    1,1, 9,8, 7,6, 4,3, 3,2, 14,9, 7,4
}); } ,
     "Grady: S Centaur 7-limit Minor"
     ),
    
    PresetHelper
    ("Grady: S Centaur Soft Major on E",
[](){ return MAD({
    1,1, 28,25, 56,46, 4,3, 3,2, 42,25, 28,15
}); } ,
     "Grady: S Centaur Soft Major on E"
     ),
    
    PresetHelper
    ("Grady: A Centaur",
[](){ return MAD({
    1,1, 21,20, 9,8, 7,6, 5,4, 4,3, 7,5, 3,2, 14,9, 5,3, 7,4, 15,8
}); } ,
     "Grady: A Centaur"
     ),
    
    PresetHelper
    ("Grady: Double Dekany 14-tone",
[](){ return MAD({
    1,1, 35,32, 9,8, 7,6, 5,4, 21,16, 45,32, 35,24, 3,2, 105,64, 5,3, 7,4, 15,8, 63,32
}); } ,
     "Grady: Double Dekany 14-tone"
     ),
    
    PresetHelper
    ("Grady: A-Narushima 19-tone 7-limit",
[](){ return MAD({
    1,1, 21,20, 35,32, 9,8, 7,6, 6,5, 5,4, 21,16, 4,3, 7,5, 35,24, 3,2, 14,9, 8,5, 5,3, 7,4, 9,5, 15,8, 63,32
}); } ,
     "Grady: A-Narushima 19-tone 7-limit"
     ),
    
    PresetHelper
    ("Grady: Sisiutl 12-tone",
[](){ return MAD({
    1,1, 28,27, 9,8, 7,6, 14,11, 4,3, 11,8, 3,2, 14,9, 56,33, 7,4, 11,6
}); } ,
     "Grady: Sisiutl 12-tone"
     ),
    
    PresetHelper
    ("Grady: Wilson pre-Sisiutl 17",
[](){ return MAD({
    1,1, 28,27, 9,8, 7,6, 14,11, 4,3, 11,8, 3,2, 14,9, 3,2, 14,9, 56,33, 7,4, 11,6
}); } ,
     "Grady: Wilson pre-Sisiutl 17"
     ),
    
    PresetHelper
    ("Grady: Beebalm 7-limit",
[](){ return MAD({
    1,1, 17,16, 9,8, 7,6, 5,4, 4,3, 17,12, 3,2, 14,9, 5,3, 16,9, 17,9
}); } ,
     "Grady: Beebalm 7-limit"
     ),
    
    PresetHelper
    ("Grady: Schulter Zeta Centauri 12 tone",
[](){ return MAD({
    1,1, 13,12, 9,8, 7,6, 11,9, 4,3, 13,9, 3,2, 14,9, 13,8, 7,4, 11,6
}); } ,
     "Grady: Schulter Zeta Centauri 12 tone"
     ),
    
    PresetHelper
    ("Grady: Schulter Shur",
[](){ return MAD({
    1,1, 27,26, 9,8, 27,22, 4,3, 18,13, 3,2, 18,11, 16,9, 24,13
}); } ,
     "Grady: Schulter Shur"
     ),
    
    PresetHelper
    ("Grady: Poole 17",
[](){ return MAD({
    1,1, 33,32, 13,12, 9,8, 7,6, 11,9, 14,11, 4,3, 11,8, 13,9, 3,2, 14,9, 44,27, 27,16, 7,4, 11,6, 21,11
}); } ,
     "Grady: Poole 17"
     ),
    
    PresetHelper
    ("Grady: 11-limit Helix Song",
[](){ return MAD({
    1,1, 9,8, 7,6, 5,4, 4,3, 11,8, 3,2, 5,3, 7,4, 11,6
}); } ,
     "Grady: 11-limit Helix Song"
     ),
    
    PresetHelper
    ("David: Double 1-3-5-7 Hexany 12-Tone",
[](){ return MAD({
    1,1, 16,15, 35,32, 7,6, 5,4, 4,3, 7,5, 35,24, 8,5, 5,3, 7,4, 28,15
}); } ,
     "David: Double 1-3-5-7 Hexany 12-Tone"
     ),
    
    PresetHelper
    ("Wilson Double Hexany+ 12 tone",
[](){ return MAD({
    1,1, 49,48, 8,7, 7,6, 5,4, 4,3, 10,7, 35,24, 80,49, 5,3, 7,4, 40,21
}); } ,
     "Wilson Double Hexany+ 12 tone"
     ),
    
    PresetHelper
    ("Grady: Wilson Triple Hexany +",
[](){ return MAD({
    1,1, 15,14, 9,8, 7,6, 5,4, 21,16, 10,7, 3,2, 45,28, 5,3, 7,4, 15,8
}); } ,
     "Grady: Wilson Triple Hexany +"
     ),
    
    PresetHelper
    ("Grady: Wilson Super 7",
[](){ return MAD({
    1,1, 35,32, 8,7, 5,4, 245,192, 10,7, 35,24, 3,2, 49,32, 12,7, 7,4, 245,128
}); } ,
     "Grady: Wilson Super 7"
     ),
    
    PresetHelper
    ("David: Dual Harmonic Subharmonic",
[](){ return MAD({
    1,1, 16,15, 9,8, 6,5, 9,7, 4,3, 7,5, 3,2, 8,5, 12,7, 9,5, 28,15
}); } ,
     "David: Dual Harmonic Subharmonic"
     ),
    
    PresetHelper
    ("Wilson/David: Enharmonics",
[](){ return MAD({
    1,1, 28,27, 9,8, 7,6, 6,5, 4,3, 35,24, 3,2, 14,9, 8,5, 7,4, 25,18
}); } ,
     "Wilson/David: Enharmonics"
     ),
    
    PresetHelper
    ("Grady: Wilson First Pelog",
[](){ return MAD({
    1,1, 16,15, 64,55, 5,4, 4,3, 16,11, 8,5, 128,75, 20,11
}); } ,
     "Grady: Wilson First Pelog"
     ),
    
    PresetHelper
    ("Grady: Wilson Meta-Pelog 1",
[](){ return MAD({
    1,1, 571,512, 153,128, 41,32, 4,3, 11,8, 209,128, 7,4, 15,8
}); } ,
     "Grady: Wilson Meta-Pelog 1"
     ),
    
    PresetHelper
    ("Grady: Wilson Meta-Pelog 2",
[](){ return MAD({
    1,1, 9,8, 19,16, 41,32, 11,8, 3,2, 13,8, 7,4, 15,8
}); } ,
     "Grady: Wilson Meta-Pelog 2"
     ),
    
    PresetHelper
    ("Grady: Wilson Meta-Ptolemy 10",
[](){ return MAD({
    1,1, 33,32, 9,8, 73,64, 5,4, 11,8, 3,2, 49,32, 27,16, 15,8
}); } ,
     "Grady: Wilson Meta-Ptolemy 10"
     ),
    
    PresetHelper
    ("Grady: Olympos Staircase",
[](){ return MAD({
    1,1, 28,27, 9,8, 7,6, 9,7, 4,3, 49,36, 3,2, 14,9, 12,7, 7,4, 49,27
}); } ,
     "Grady: Olympos Staircase"
     ),
    
    PresetHelper
    ("Hobbs: Hexany(9, 25, 49, 81)",
[](){ return MAF({
    225.f,
    441.f,
    729.f,
    1225.f,
    2025.f,
    3969.f
}); } ,
     "Hobbs: Hexany(9, 25, 49, 81)"
     ),
    
    PresetHelper
    ("Hobbs: Hexany(3, 2.111, 5.111, 8.111)",
[](){ return MAF({
    6.333f,
    15.333f,
    24.333f,
    10.789321f,
    17.12232f,
    41.455322f
}); } ,
     "Hobbs: Hexany(3, 2.111, 5.111, 8.111): A Hexany seeded with a Fibonacci Triplet"
     ),
    
    PresetHelper
    ("Hobbs: Hexany(3, 1.346, 4.346, 7.346)",
[](){ return MAF({
    4.038f,
    13.038f,
    22.038f,
    5.849716f,
    9.887716f,
    31.925716f
}); } ,
     "Hobbs: Hexany(3, 1.346, 4.346, 7.346): A Hexany seeded with a Fibonacci Triplet"
     ),
    
    PresetHelper
    ("Hobbs: Hexany Subharmonic Tetrad",
[](){ return MAF({
    0.333333f,
    0.2f,
    0.142857f,
    0.066667f,
    0.047619f,
    0.028571f
}); } ,
     "Hobbs: Hexany Subharmonic Tetrad"
     ),
    
    PresetHelper
    ("Hobbs: Recurrence Relation 01",
[](){ return MAF({
    1.f,
    19.f,
    5.f,
    3.f,
    15.f
}); } ,
     "Hobbs: Recurrence Relation 01"
     ),
    
    PresetHelper
    ("Hobbs: Recurrence Relation 02",
[](){ return MAF({
    35.f,
    74.f,
    23.f,
    51.f,
    61.f
}); } ,
     "Hobbs: Recurrence Relation 02"
     ),
    
    PresetHelper
    ("Hobbs: Recurrence Relation 03",
[](){ return MAF({
    74.f,
    150.f,
    85.f,
    106.f,
    120.f,
    61.f
}); } ,
     "Hobbs: Recurrence Relation 03"
     ),
    
    PresetHelper
    ("Hobbs: Recurrence Relation 04",
[](){ return MAF({
    1.f,
    9.f,
    5.f,
    23.f,
    48.f,
    7.f
}); } ,
     "Hobbs: Recurrence Relation 04"
     ),
    
    PresetHelper
    ("Hobbs: Recurrence Relation 05",
[](){ return MAF({
    1.f,
    9.f,
    21.f,
    3.f,
    25.f,
    15.f
}); } ,
     "Hobbs: Recurrence Relation 05"
     ),
    
    PresetHelper
    ("Hobbs: Recurrence Relation 06",
[](){ return MAF({
    1.f,
    75.f,
    19.f,
    5.f,
    3.f,
    15.f
}); } ,
     "Hobbs: Recurrence Relation 06"
     ),
    
    PresetHelper
    ("Hobbs: Recurrence Relation 07",
[](){ return MAF({
    1.f,
    17.f,
    10.f,
    47.f,
    3.f,
    13.f,
    7.f
}); } ,
     "Hobbs: Recurrence Relation 07"
     ),
    
    PresetHelper
    ("Hobbs: Recurrence Relation 08",
[](){ return MAF({
    1.f,
    9.f,
    5.f,
    21.f,
    3.f,
    27.f,
    7.f
}); } ,
     "Hobbs: Recurrence Relation 08"
     ),
    
    PresetHelper
    ("Hobbs: Recurrence Relation 09",
[](){ return MAF({
    1.f,
    9.f,
    21.f,
    3.f,
    25.f,
    15.f,
    31.f
}); } ,
     "Hobbs: Recurrence Relation 09"
     ),
    
    PresetHelper
    ("Hobbs: Recurrence Relation 10",
[](){ return MAF({
    1.f,
    75.f,
    19.f,
    5.f,
    94.f,
    3.f,
    15.f
}); } ,
     "Hobbs: Recurrence Relation 10"
     ),
    
    PresetHelper
    ("Hobbs: Recurrence Relation 11",
[](){ return MAF({
    9.f,
    40.f,
    21.f,
    25.f,
    52.f,
    15.f,
    31.f
}); } ,
     "Hobbs: Recurrence Relation 11"
     ),
    
    PresetHelper
    ("Hobbs: Recurrence Relation 12",
[](){ return MAF({
    1.f,
    18.f,
    5.f,
    21.f,
    3.f,
    25.f,
    15.f
}); } ,
     "Hobbs: Recurrence Relation 12"
     ),
    
    PresetHelper
    ("Hobbs: Recurrence Relation 13",
[](){ return MAF({
    1.f,
    65.f,
    9.f,
    37.f,
    151.f,
    21.f,
    86.f,
    12.f,
    49.f,
    200.f,
    28.f,
    114.f
}); } ,
     "Hobbs: Recurrence Relation 13"
     ),
    
    PresetHelper
    ("Taylor: MOS G: 0.855088",
[](){ return MAF({
    1.f,
    1.210363f,
    1.338254f,
    1.479658f,
    1.636004f,
    1.808869f
}); } ,
     "Taylor: MOS G: 0.855088"
     ),
    
    PresetHelper
    ("Taylor: MOS G: 0.855088",
[](){ return MAF({
    1.f,
    1.094694f,
    1.198356f,
    1.210363f,
    1.324978f,
    1.338254f,
    1.464979f,
    1.479658f,
    1.619773f,
    1.636004f,
    1.790924f,
    1.808869f,
    1.980159f
}); } ,
     "Taylor: MOS G: 0.855088"
     ),
    
    PresetHelper
    ("Taylor: MOS G: 0.791400",
[](){ return MAF({
    1.f,
    1.121632f,
    1.296121f,
    1.497753f,
    1.730753f
}); } ,
     "Taylor: MOS G: 0.791400"
     ),
    
    PresetHelper
    ("Taylor: MOS G: 0.78207964",
[](){ return MAF({
    1.f,
    1.093019f,
    1.271242f,
    1.478526f,
    1.719608f
}); } ,
     "Taylor: MOS G: 0.78207964"
     ),
    
    PresetHelper
    ("Taylor: MOS G: 0.618033",
[](){ return MAF({
    1.f,
    1.177777f,
    1.387158f,
    1.534781f,
    1.807629f
}); } ,
     "Taylor: MOS G: 0.618033"
     ),
    
    PresetHelper
    ("Taylor: MOS G: 0.232587",
[](){ return MAF({
    1.f,
    1.17494f,
    1.380484f,
    1.621986f,
    1.905736f
}); } ,
     "Taylor: MOS G: 0.232587"
     ),
    
    PresetHelper
    ("Taylor: MOS G: 0.5757381",
[](){ return MAF({
    1.f,
    1.02113f,
    1.110705f,
    1.134175f,
    1.233666f,
    1.259734f,
    1.37024f,
    1.49044f,
    1.521933f,
    1.655439f,
    1.690419f,
    1.838706f
}); } ,
     "Taylor: MOS G: 0.5757381"
     ),
    
    PresetHelper
    ("Taylor: Pasadena JI 27",
[](){ return MAD({
    1,1, 81,80, 17,16, 16,15, 10,9, 9,8, 8,7, 7,6, 19,16, 6,5, 11,9, 5,4, 9,7, 21,16, 4,3, 11,8, 7,5, 3,2, 11,7, 8,5, 5,3, 13,8, 27,16, 7,4, 9,5, 11,6, 15,8
}); } ,
     "Taylor: Pasadena JI 27"
     ),
    
    PresetHelper
    ("Partch",
[](){ return MAD({
    1,1, 81,80, 33,32, 21,20, 16,15, 12,11, 11,10, 10,9, 9,8, 8,7, 7,6, 32,27, 6,5, 11,9, 5,4, 14,11, 9,7, 21,16, 4,3, 27,20, 11,8, 7,5, 10,7, 16,11, 40,27, 3,2, 32,21, 14,9, 11,7, 8,5, 18,11, 5,3, 27,16, 12,7, 7,4, 16,9, 9,5, 20,11, 11,6, 15,8, 40,21, 64,33, 160,81
}); } ,
     "Partch"
     ),
    
    PresetHelper
    ("Tetrany Major:[1, 3, 5, 25]",
[](){ return MAF({
    1.f,
    3.f,
    5.f,
    25.f
}); } ,
     "Tetrany Major:[1, 3, 5, 25]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[1, 3, 5, 25]",
[](){ return MAF({
    375.f,
    125.f,
    75.f,
    15.f
}); } ,
     "Tetrany Minor:[1, 3, 5, 25]"
     ),
    
    PresetHelper
    ("HEXANY:[1, 3, 5, 25]",
[](){ return MAF({
    3.f,
    5.f,
    25.f,
    15.f,
    75.f,
    125.f
}); } ,
     "HEXANY:[1, 3, 5, 25]"
     ),
    
    PresetHelper
    ("Tetrany Major:[1, 3, 9, 15]",
[](){ return MAF({
    1.f,
    3.f,
    9.f,
    15.f
}); } ,
     "Tetrany Major:[1, 3, 9, 15]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[1, 3, 9, 15]",
[](){ return MAF({
    405.f,
    135.f,
    45.f,
    27.f
}); } ,
     "Tetrany Minor:[1, 3, 9, 15]"
     ),
    
    PresetHelper
    ("HEXANY:[1, 3, 9, 15]",
[](){ return MAF({
    3.f,
    9.f,
    15.f,
    27.f,
    45.f,
    135.f
}); } ,
     "HEXANY:[1, 3, 9, 15]"
     ),
    
    PresetHelper
    ("Tetrany Major:[1, 5, 15, 25]",
[](){ return MAF({
    1.f,
    5.f,
    15.f,
    25.f
}); } ,
     "Tetrany Major:[1, 5, 15, 25]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[1, 5, 15, 25]",
[](){ return MAF({
    1875.f,
    375.f,
    125.f,
    75.f
}); } ,
     "Tetrany Minor:[1, 5, 15, 25]"
     ),
    
    PresetHelper
    ("HEXANY:[1, 5, 15, 25]",
[](){ return MAF({
    5.f,
    15.f,
    25.f,
    75.f,
    125.f,
    375.f
}); } ,
     "HEXANY:[1, 5, 15, 25]"
     ),
    
    PresetHelper
    ("Tetrany Major:[3, 5, 7, 15]",
[](){ return MAF({
    3.f,
    5.f,
    7.f,
    15.f
}); } ,
     "Tetrany Major:[3, 5, 7, 15]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[3, 5, 7, 15]",
[](){ return MAF({
    525.f,
    315.f,
    225.f,
    105.f
}); } ,
     "Tetrany Minor:[3, 5, 7, 15]"
     ),
    
    PresetHelper
    ("HEXANY:[3, 5, 7, 15]",
[](){ return MAF({
    15.f,
    21.f,
    45.f,
    35.f,
    75.f,
    105.f
}); } ,
     "HEXANY:[3, 5, 7, 15]"
     ),
    
    PresetHelper
    ("Tetrany Major:[3, 5, 7, 21]",
[](){ return MAF({
    3.f,
    5.f,
    7.f,
    21.f
}); } ,
     "Tetrany Major:[3, 5, 7, 21]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[3, 5, 7, 21]",
[](){ return MAF({
    735.f,
    441.f,
    315.f,
    105.f
}); } ,
     "Tetrany Minor:[3, 5, 7, 21]"
     ),
    
    PresetHelper
    ("HEXANY:[3, 5, 7, 21]",
[](){ return MAF({
    15.f,
    21.f,
    63.f,
    35.f,
    105.f,
    147.f
}); } ,
     "HEXANY:[3, 5, 7, 21]"
     ),
    
    PresetHelper
    ("Tetrany Major:[3, 5, 7, 35]",
[](){ return MAF({
    3.f,
    5.f,
    7.f,
    35.f
}); } ,
     "Tetrany Major:[3, 5, 7, 35]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[3, 5, 7, 35]",
[](){ return MAF({
    1225.f,
    735.f,
    525.f,
    105.f
}); } ,
     "Tetrany Minor:[3, 5, 7, 35]"
     ),
    
    PresetHelper
    ("HEXANY:[3, 5, 7, 35]",
[](){ return MAF({
    15.f,
    21.f,
    105.f,
    35.f,
    175.f,
    245.f
}); } ,
     "HEXANY:[3, 5, 7, 35]"
     ),
    
    PresetHelper
    ("Tetrany Major:[3, 5, 15, 21]",
[](){ return MAF({
    3.f,
    5.f,
    15.f,
    21.f
}); } ,
     "Tetrany Major:[3, 5, 15, 21]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[3, 5, 15, 21]",
[](){ return MAF({
    1575.f,
    945.f,
    315.f,
    225.f
}); } ,
     "Tetrany Minor:[3, 5, 15, 21]"
     ),
    
    PresetHelper
    ("HEXANY:[3, 5, 15, 21]",
[](){ return MAF({
    15.f,
    45.f,
    63.f,
    75.f,
    105.f,
    315.f
}); } ,
     "HEXANY:[3, 5, 15, 21]"
     ),
    
    PresetHelper
    ("Tetrany Major:[3, 5, 15, 35]",
[](){ return MAF({
    3.f,
    5.f,
    15.f,
    35.f
}); } ,
     "Tetrany Major:[3, 5, 15, 35]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[3, 5, 15, 35]",
[](){ return MAF({
    2625.f,
    1575.f,
    525.f,
    225.f
}); } ,
     "Tetrany Minor:[3, 5, 15, 35]"
     ),
    
    PresetHelper
    ("HEXANY:[3, 5, 15, 35]",
[](){ return MAF({
    15.f,
    45.f,
    105.f,
    75.f,
    175.f,
    525.f
}); } ,
     "HEXANY:[3, 5, 15, 35]"
     ),
    
    PresetHelper
    ("Tetrany Major:[3, 5, 15, 45]",
[](){ return MAF({
    3.f,
    5.f,
    15.f,
    45.f
}); } ,
     "Tetrany Major:[3, 5, 15, 45]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[3, 5, 15, 45]",
[](){ return MAF({
    3375.f,
    2025.f,
    675.f,
    225.f
}); } ,
     "Tetrany Minor:[3, 5, 15, 45]"
     ),
    
    PresetHelper
    ("HEXANY:[3, 5, 15, 45]",
[](){ return MAF({
    15.f,
    45.f,
    135.f,
    75.f,
    225.f,
    675.f
}); } ,
     "HEXANY:[3, 5, 15, 45]"
     ),
    
    PresetHelper
    ("Tetrany Major:[3, 5, 15, 75]",
[](){ return MAF({
    3.f,
    5.f,
    15.f,
    75.f
}); } ,
     "Tetrany Major:[3, 5, 15, 75]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[3, 5, 15, 75]",
[](){ return MAF({
    5625.f,
    3375.f,
    1125.f,
    225.f
}); } ,
     "Tetrany Minor:[3, 5, 15, 75]"
     ),
    
    PresetHelper
    ("HEXANY:[3, 5, 15, 75]",
[](){ return MAF({
    15.f,
    45.f,
    225.f,
    75.f,
    375.f,
    1125.f
}); } ,
     "HEXANY:[3, 5, 15, 75]"
     ),
    
    PresetHelper
    ("Tetrany Major:[3, 7, 21, 35]",
[](){ return MAF({
    3.f,
    7.f,
    21.f,
    35.f
}); } ,
     "Tetrany Major:[3, 7, 21, 35]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[3, 7, 21, 35]",
[](){ return MAF({
    5145.f,
    2205.f,
    735.f,
    441.f
}); } ,
     "Tetrany Minor:[3, 7, 21, 35]"
     ),
    
    PresetHelper
    ("HEXANY:[3, 7, 21, 35]",
[](){ return MAF({
    21.f,
    63.f,
    105.f,
    147.f,
    245.f,
    735.f
}); } ,
     "HEXANY:[3, 7, 21, 35]"
     ),
    
    PresetHelper
    ("Tetrany Major:[3, 9, 15, 25]",
[](){ return MAF({
    3.f,
    9.f,
    15.f,
    25.f
}); } ,
     "Tetrany Major:[3, 9, 15, 25]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[3, 9, 15, 25]",
[](){ return MAF({
    3375.f,
    1125.f,
    675.f,
    405.f
}); } ,
     "Tetrany Minor:[3, 9, 15, 25]"
     ),
    
    PresetHelper
    ("HEXANY:[3, 9, 15, 25]",
[](){ return MAF({
    27.f,
    45.f,
    75.f,
    135.f,
    225.f,
    375.f
}); } ,
     "HEXANY:[3, 9, 15, 25]"
     ),
    
    PresetHelper
    ("Tetrany Major:[3, 15, 21, 35]",
[](){ return MAF({
    3.f,
    15.f,
    21.f,
    35.f
}); } ,
     "Tetrany Major:[3, 15, 21, 35]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[3, 15, 21, 35]",
[](){ return MAF({
    11025.f,
    2205.f,
    1575.f,
    945.f
}); } ,
     "Tetrany Minor:[3, 15, 21, 35]"
     ),
    
    PresetHelper
    ("HEXANY:[3, 15, 21, 35]",
[](){ return MAF({
    45.f,
    63.f,
    105.f,
    315.f,
    525.f,
    735.f
}); } ,
     "HEXANY:[3, 15, 21, 35]"
     ),
    
    PresetHelper
    ("Tetrany Major:[3, 15, 25, 75]",
[](){ return MAF({
    3.f,
    15.f,
    25.f,
    75.f
}); } ,
     "Tetrany Major:[3, 15, 25, 75]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[3, 15, 25, 75]",
[](){ return MAF({
    28125.f,
    5625.f,
    3375.f,
    1125.f
}); } ,
     "Tetrany Minor:[3, 15, 25, 75]"
     ),
    
    PresetHelper
    ("HEXANY:[3, 15, 25, 75]",
[](){ return MAF({
    45.f,
    75.f,
    225.f,
    375.f,
    1125.f,
    1875.f
}); } ,
     "HEXANY:[3, 15, 25, 75]"
     ),
    
    PresetHelper
    ("Tetrany Major:[5, 7, 15, 35]",
[](){ return MAF({
    5.f,
    7.f,
    15.f,
    35.f
}); } ,
     "Tetrany Major:[5, 7, 15, 35]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[5, 7, 15, 35]",
[](){ return MAF({
    3675.f,
    2625.f,
    1225.f,
    525.f
}); } ,
     "Tetrany Minor:[5, 7, 15, 35]"
     ),
    
    PresetHelper
    ("HEXANY:[5, 7, 15, 35]",
[](){ return MAF({
    35.f,
    75.f,
    175.f,
    105.f,
    245.f,
    525.f
}); } ,
     "HEXANY:[5, 7, 15, 35]"
     ),
    
    PresetHelper
    ("Tetrany Major:[5, 7, 21, 35]",
[](){ return MAF({
    5.f,
    7.f,
    21.f,
    35.f
}); } ,
     "Tetrany Major:[5, 7, 21, 35]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[5, 7, 21, 35]",
[](){ return MAF({
    5145.f,
    3675.f,
    1225.f,
    735.f
}); } ,
     "Tetrany Minor:[5, 7, 21, 35]"
     ),
    
    PresetHelper
    ("HEXANY:[5, 7, 21, 35]",
[](){ return MAF({
    35.f,
    105.f,
    175.f,
    147.f,
    245.f,
    735.f
}); } ,
     "HEXANY:[5, 7, 21, 35]"
     ),
    
    PresetHelper
    ("Tetrany Major:[5, 9, 15, 25]",
[](){ return MAF({
    5.f,
    9.f,
    15.f,
    25.f
}); } ,
     "Tetrany Major:[5, 9, 15, 25]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[5, 9, 15, 25]",
[](){ return MAF({
    3375.f,
    1875.f,
    1125.f,
    675.f
}); } ,
     "Tetrany Minor:[5, 9, 15, 25]"
     ),
    
    PresetHelper
    ("HEXANY:[5, 9, 15, 25]",
[](){ return MAF({
    45.f,
    75.f,
    125.f,
    135.f,
    225.f,
    375.f
}); } ,
     "HEXANY:[5, 9, 15, 25]"
     ),
    
    PresetHelper
    ("Tetrany Major:[5, 9, 15, 45]",
[](){ return MAF({
    5.f,
    9.f,
    15.f,
    45.f
}); } ,
     "Tetrany Major:[5, 9, 15, 45]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[5, 9, 15, 45]",
[](){ return MAF({
    6075.f,
    3375.f,
    2025.f,
    675.f
}); } ,
     "Tetrany Minor:[5, 9, 15, 45]"
     ),
    
    PresetHelper
    ("HEXANY:[5, 9, 15, 45]",
[](){ return MAF({
    45.f,
    75.f,
    225.f,
    135.f,
    405.f,
    675.f
}); } ,
     "HEXANY:[5, 9, 15, 45]"
     ),
    
    PresetHelper
    ("Tetrany Major:[7, 15, 21, 35]",
[](){ return MAF({
    7.f,
    15.f,
    21.f,
    35.f
}); } ,
     "Tetrany Major:[7, 15, 21, 35]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[7, 15, 21, 35]",
[](){ return MAF({
    11025.f,
    5145.f,
    3675.f,
    2205.f
}); } ,
     "Tetrany Minor:[7, 15, 21, 35]"
     ),
    
    PresetHelper
    ("HEXANY:[7, 15, 21, 35]",
[](){ return MAF({
    105.f,
    147.f,
    245.f,
    315.f,
    525.f,
    735.f
}); } ,
     "HEXANY:[7, 15, 21, 35]"
     ),
    
    PresetHelper
    ("Tetrany Major:[9, 11, 15, 33]",
[](){ return MAF({
    9.f,
    11.f,
    15.f,
    33.f
}); } ,
     "Tetrany Major:[9, 11, 15, 33]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[9, 11, 15, 33]",
[](){ return MAF({
    5445.f,
    4455.f,
    3267.f,
    1485.f
}); } ,
     "Tetrany Minor:[9, 11, 15, 33]"
     ),
    
    PresetHelper
    ("HEXANY:[9, 11, 15, 33]",
[](){ return MAF({
    99.f,
    135.f,
    297.f,
    165.f,
    363.f,
    495.f
}); } ,
     "HEXANY:[9, 11, 15, 33]"
     ),
    
    PresetHelper
    ("Tetrany Major:[9, 15, 25, 45]",
[](){ return MAF({
    9.f,
    15.f,
    25.f,
    45.f
}); } ,
     "Tetrany Major:[9, 15, 25, 45]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[9, 15, 25, 45]",
[](){ return MAF({
    16875.f,
    10125.f,
    6075.f,
    3375.f
}); } ,
     "Tetrany Minor:[9, 15, 25, 45]"
     ),
    
    PresetHelper
    ("HEXANY:[9, 15, 25, 45]",
[](){ return MAF({
    135.f,
    225.f,
    405.f,
    375.f,
    675.f,
    1125.f
}); } ,
     "HEXANY:[9, 15, 25, 45]"
     ),
    
    PresetHelper
    ("Tetrany Major:[9, 15, 25, 75]",
[](){ return MAF({
    9.f,
    15.f,
    25.f,
    75.f
}); } ,
     "Tetrany Major:[9, 15, 25, 75]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[9, 15, 25, 75]",
[](){ return MAF({
    28125.f,
    16875.f,
    10125.f,
    3375.f
}); } ,
     "Tetrany Minor:[9, 15, 25, 75]"
     ),
    
    PresetHelper
    ("HEXANY:[9, 15, 25, 75]",
[](){ return MAF({
    135.f,
    225.f,
    675.f,
    375.f,
    1125.f,
    1875.f
}); } ,
     "HEXANY:[9, 15, 25, 75]"
     ),
    
    PresetHelper
    ("Tetrany Major:[15, 21, 35, 45]",
[](){ return MAF({
    15.f,
    21.f,
    35.f,
    45.f
}); } ,
     "Tetrany Major:[15, 21, 35, 45]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[15, 21, 35, 45]",
[](){ return MAF({
    33075.f,
    23625.f,
    14175.f,
    11025.f
}); } ,
     "Tetrany Minor:[15, 21, 35, 45]"
     ),
    
    PresetHelper
    ("HEXANY:[15, 21, 35, 45]",
[](){ return MAF({
    315.f,
    525.f,
    675.f,
    735.f,
    945.f,
    1575.f
}); } ,
     "HEXANY:[15, 21, 35, 45]"
     ),
    
    PresetHelper
    ("Tetrany Major:[15, 33, 45, 55]",
[](){ return MAF({
    15.f,
    33.f,
    45.f,
    55.f
}); } ,
     "Tetrany Major:[15, 33, 45, 55]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[15, 33, 45, 55]",
[](){ return MAF({
    81675.f,
    37125.f,
    27225.f,
    22275.f
}); } ,
     "Tetrany Minor:[15, 33, 45, 55]"
     ),
    
    PresetHelper
    ("HEXANY:[15, 33, 45, 55]",
[](){ return MAF({
    495.f,
    675.f,
    825.f,
    1485.f,
    1815.f,
    2475.f
}); } ,
     "HEXANY:[15, 33, 45, 55]"
     ),
    
    PresetHelper
    ("Tetrany Major:[41, 67, 97, 127]",
[](){ return MAF({
    41.f,
    67.f,
    97.f,
    127.f
}); } ,
     "Tetrany Major:[41, 67, 97, 127]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[41, 67, 97, 127]",
[](){ return MAF({
    825373.f,
    505079.f,
    348869.f,
    266459.f
}); } ,
     "Tetrany Minor:[41, 67, 97, 127]"
     ),
    
    PresetHelper
    ("HEXANY:[41, 67, 97, 127]",
[](){ return MAF({
    2747.f,
    3977.f,
    5207.f,
    6499.f,
    8509.f,
    12319.f
}); } ,
     "HEXANY:[41, 67, 97, 127]"
     ),
    
    PresetHelper
    ("Tetrany Major:[31, 41, 61, 103]",
[](){ return MAF({
    31.f,
    41.f,
    61.f,
    103.f
}); } ,
     "Tetrany Major:[31, 41, 61, 103]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[31, 41, 61, 103]",
[](){ return MAF({
    257603.f,
    194773.f,
    130913.f,
    77531.f
}); } ,
     "Tetrany Minor:[31, 41, 61, 103]"
     ),
    
    PresetHelper
    ("HEXANY:[31, 41, 61, 103]",
[](){ return MAF({
    1271.f,
    1891.f,
    3193.f,
    2501.f,
    4223.f,
    6283.f
}); } ,
     "HEXANY:[31, 41, 61, 103]"
     ),
    
    PresetHelper
    ("Tetrany Major:[19, 23, 31, 61]",
[](){ return MAF({
    19.f,
    23.f,
    31.f,
    61.f
}); } ,
     "Tetrany Major:[19, 23, 31, 61]"
     ),
    
    PresetHelper
    ("Tetrany Minor:[19, 23, 31, 61]",
[](){ return MAF({
    43493.f,
    35929.f,
    26657.f,
    13547.f
}); } ,
     "Tetrany Minor:[19, 23, 31, 61]"
     ),
    
    PresetHelper
    ("HEXANY:[19, 23, 31, 61]",
[](){ return MAF({
    437.f,
    589.f,
    1159.f,
    713.f,
    1403.f,
    1891.f
}); } ,
     "HEXANY:[19, 23, 31, 61]"
     ),
    
    PresetHelper
    ("CPS(4,1):[1, 15, 45, 75]",
[](){ return MAF({
    1.f,
    15.f,
    45.f,
    75.f
}); } ,
     "CPS(4,1):[1, 15, 45, 75]"
     ),
    
    PresetHelper
    ("CPS(4,2):[1, 15, 45, 75]",
[](){ return MAF({
    1125.f,
    75.f,
    675.f,
    45.f,
    3375.f,
    15.f
}); } ,
     "CPS(4,2):[1, 15, 45, 75]"
     ),
    
    PresetHelper
    ("CPS(4,3):[1, 15, 45, 75]",
[](){ return MAF({
    1125.f,
    675.f,
    50625.f,
    3375.f
}); } ,
     "CPS(4,3):[1, 15, 45, 75]"
     ),
    
    PresetHelper
    ("CPS(4,1):[1, 45, 135, 225]",
[](){ return MAF({
    1.f,
    45.f,
    135.f,
    225.f
}); } ,
     "CPS(4,1):[1, 45, 135, 225]"
     ),
    
    PresetHelper
    ("CPS(4,2):[1, 45, 135, 225]",
[](){ return MAF({
    45.f,
    135.f,
    225.f,
    6075.f,
    10125.f,
    30375.f
}); } ,
     "CPS(4,2):[1, 45, 135, 225]"
     ),
    
    PresetHelper
    ("CPS(4,3):[1, 45, 135, 225]",
[](){ return MAF({
    6075.f,
    10125.f,
    30375.f,
    1366875.f
}); } ,
     "CPS(4,3):[1, 45, 135, 225]"
     ),
    
    PresetHelper
    ("CPS(5,1):[1, 45, 135, 225, 17]",
[](){ return MAF({
    1.f,
    45.f,
    135.f,
    225.f,
    17.f
}); } ,
     "CPS(5,1):[1, 45, 135, 225, 17]"
     ),
    
    PresetHelper
    ("CPS(5,2):[1, 45, 135, 225, 17]",
[](){ return MAF({
    45.f,
    135.f,
    225.f,
    17.f,
    6075.f,
    10125.f,
    765.f,
    30375.f,
    2295.f,
    3825.f
}); } ,
     "CPS(5,2):[1, 45, 135, 225, 17]"
     ),
    
    PresetHelper
    ("CPS(5,3):[1, 45, 135, 225, 17]",
[](){ return MAF({
    6075.f,
    10125.f,
    765.f,
    30375.f,
    2295.f,
    3825.f,
    1366875.f,
    103275.f,
    172125.f,
    516375.f
}); } ,
     "CPS(5,3):[1, 45, 135, 225, 17]"
     ),
    
    PresetHelper
    ("CPS(5,4):[1, 45, 135, 225, 17]",
[](){ return MAF({
    1366875.f,
    103275.f,
    172125.f,
    516375.f,
    23236876.f
}); } ,
     "CPS(5,4):[1, 45, 135, 225, 17]"
     ),
    
    PresetHelper
    ("CPS(5,1):[1, 3, 5, 9, 121]",
[](){ return MAF({
    1.f,
    3.f,
    5.f,
    9.f,
    121.f
}); } ,
     "CPS(5,1):[1, 3, 5, 9, 121]"
     ),
    
    PresetHelper
    ("CPS(5,2):[1, 3, 5, 9, 121]",
[](){ return MAF({
    3.f,
    5.f,
    9.f,
    121.f,
    15.f,
    27.f,
    363.f,
    45.f,
    605.f,
    1089.f
}); } ,
     "CPS(5,2):[1, 3, 5, 9, 121]"
     ),
    
    PresetHelper
    ("CPS(5,3):[1, 3, 5, 9, 121]",
[](){ return MAF({
    15.f,
    27.f,
    363.f,
    45.f,
    605.f,
    1089.f,
    135.f,
    1815.f,
    3267.f,
    5445.f
}); } ,
     "CPS(5,3):[1, 3, 5, 9, 121]"
     ),
    
    PresetHelper
    ("CPS(5,4):[1, 3, 5, 9, 121]",
[](){ return MAF({
    135.f,
    1815.f,
    3267.f,
    5445.f,
    16335.f
}); } ,
     "CPS(5,4):[1, 3, 5, 9, 121]"
     ),
    
    PresetHelper
    ("CPS(5,1):[1, 3, 5, 81, 121]",
[](){ return MAF({
    1.f,
    3.f,
    5.f,
    81.f,
    121.f
}); } ,
     "CPS(5,1):[1, 3, 5, 81, 121]"
     ),
    
    PresetHelper
    ("CPS(5,2):[1, 3, 5, 81, 121]",
[](){ return MAF({
    605.f,
    9801.f,
    5.f,
    81.f,
    363.f,
    3.f,
    405.f,
    15.f,
    121.f,
    243.f
}); } ,
     "CPS(5,2):[1, 3, 5, 81, 121]"
     ),
    
    PresetHelper
    ("CPS(5,3):[1, 3, 5, 81, 121]",
[](){ return MAF({
    605.f,
    1215.f,
    9801.f,
    363.f,
    49005.f,
    405.f,
    1815.f,
    29403.f,
    15.f,
    243.f
}); } ,
     "CPS(5,3):[1, 3, 5, 81, 121]"
     ),
    
    PresetHelper
    ("CPS(5,4):[1, 3, 5, 81, 121]",
[](){ return MAF({
    147015.f,
    1215.f,
    49005.f,
    1815.f,
    29403.f
}); } ,
     "CPS(5,4):[1, 3, 5, 81, 121]"
     ),
    
    PresetHelper
    ("CPS(4,1):[1, 3, 9, 15]",
[](){ return MAF({
    1.f,
    3.f,
    9.f,
    15.f
}); } ,
     "CPS(4,1):[1, 3, 9, 15]"
     ),
    
    PresetHelper
    ("CPS(4,2):[1, 3, 9, 15]",
[](){ return MAF({
    3.f,
    9.f,
    15.f,
    27.f,
    45.f,
    135.f
}); } ,
     "CPS(4,2):[1, 3, 9, 15]"
     ),
    
    PresetHelper
    ("CPS(4,3):[1, 3, 9, 15]",
[](){ return MAF({
    27.f,
    45.f,
    135.f,
    405.f
}); } ,
     "CPS(4,3):[1, 3, 9, 15]"
     ),
    
    PresetHelper
    ("CPS(5,1):[1, 19, 5, 3, 15]",
[](){ return MAF({
    1.f,
    19.f,
    5.f,
    3.f,
    15.f
}); } ,
     "CPS(5,1):[1, 19, 5, 3, 15]"
     ),
    
    PresetHelper
    ("CPS(5,2):[1, 19, 5, 3, 15]",
[](){ return MAF({
    285.f,
    75.f,
    19.f,
    5.f,
    45.f,
    95.f,
    3.f,
    57.f,
    15.f,
    15.f
}); } ,
     "CPS(5,2):[1, 19, 5, 3, 15]"
     ),
    
    PresetHelper
    ("CPS(5,3):[1, 19, 5, 3, 15]",
[](){ return MAF({
    285.f,
    285.f,
    75.f,
    1425.f,
    45.f,
    95.f,
    855.f,
    225.f,
    57.f,
    15.f
}); } ,
     "CPS(5,3):[1, 19, 5, 3, 15]"
     ),
    
    PresetHelper
    ("CPS(5,4):[1, 19, 5, 3, 15]",
[](){ return MAF({
    4275.f,
    285.f,
    1425.f,
    855.f,
    225.f
}); } ,
     "CPS(5,4):[1, 19, 5, 3, 15]"
     ),
    
    PresetHelper
    ("CPS(5,1):[8, 10, 11, 12, 14]",
[](){ return MAF({
    8.f,
    10.f,
    11.f,
    12.f,
    14.f
}); } ,
     "CPS(5,1):[8, 10, 11, 12, 14]"
     ),
    
    PresetHelper
    ("CPS(5,2):[8, 10, 11, 12, 14]",
[](){ return MAF({
    80.f,
    88.f,
    96.f,
    112.f,
    110.f,
    120.f,
    140.f,
    132.f,
    154.f,
    168.f
}); } ,
     "CPS(5,2):[8, 10, 11, 12, 14]"
     ),
    
    PresetHelper
    ("CPS(5,3):[8, 10, 11, 12, 14]",
[](){ return MAF({
    880.f,
    960.f,
    1120.f,
    1056.f,
    1232.f,
    1344.f,
    1320.f,
    1540.f,
    1680.f,
    1848.f
}); } ,
     "CPS(5,3):[8, 10, 11, 12, 14]"
     ),
    
    PresetHelper
    ("CPS(5,4):[8, 10, 11, 12, 14]",
[](){ return MAF({
    10560.f,
    12320.f,
    13440.f,
    14784.f,
    18480.f
}); } ,
     "CPS(5,4):[8, 10, 11, 12, 14]"
     ),
    
    PresetHelper
    ("CPS(4,1):[5, 9, 27, 45]",
[](){ return MAF({
    5.f,
    9.f,
    27.f,
    45.f
}); } ,
     "CPS(4,1):[5, 9, 27, 45]"
     ),
    
    PresetHelper
    ("CPS(4,2):[5, 9, 27, 45]",
[](){ return MAF({
    45.f,
    135.f,
    225.f,
    243.f,
    405.f,
    1215.f
}); } ,
     "CPS(4,2):[5, 9, 27, 45]"
     ),
    
    PresetHelper
    ("CPS(4,3):[5, 9, 27, 45]",
[](){ return MAF({
    1215.f,
    2025.f,
    6075.f,
    10935.f
}); } ,
     "CPS(4,3):[5, 9, 27, 45]"
     ),
    
    PresetHelper
    ("CPS(5,1):[3, 5, 7, 15, 35]",
[](){ return MAF({
    3.f,
    5.f,
    7.f,
    15.f,
    35.f
}); } ,
     "CPS(5,1):[3, 5, 7, 15, 35]"
     ),
    
    PresetHelper
    ("CPS(5,2):[3, 5, 7, 15, 35]",
[](){ return MAF({
    15.f,
    21.f,
    45.f,
    105.f,
    35.f,
    75.f,
    175.f,
    105.f,
    245.f,
    525.f
}); } ,
     "CPS(5,2):[3, 5, 7, 15, 35]"
     ),
    
    PresetHelper
    ("CPS(5,3):[3, 5, 7, 15, 35]",
[](){ return MAF({
    105.f,
    225.f,
    525.f,
    315.f,
    735.f,
    1575.f,
    525.f,
    1225.f,
    2625.f,
    3675.f
}); } ,
     "CPS(5,3):[3, 5, 7, 15, 35]"
     ),
    
    PresetHelper
    ("CPS(5,4):[3, 5, 7, 15, 35]",
[](){ return MAF({
    1575.f,
    3675.f,
    7875.f,
    11025.f,
    18375.f
}); } ,
     "CPS(5,4):[3, 5, 7, 15, 35]"
     ),
    
    PresetHelper
    ("CPS(5,1):[1, 3, 5, 75, 15]",
[](){ return MAF({
    1.f,
    3.f,
    5.f,
    75.f,
    15.f
}); } ,
     "CPS(5,1):[1, 3, 5, 75, 15]"
     ),
    
    PresetHelper
    ("CPS(5,2):[1, 3, 5, 75, 15]",
[](){ return MAF({
    3.f,
    5.f,
    75.f,
    15.f,
    15.f,
    225.f,
    45.f,
    375.f,
    75.f,
    1125.f
}); } ,
     "CPS(5,2):[1, 3, 5, 75, 15]"
     ),
    
    PresetHelper
    ("CPS(5,3):[1, 3, 5, 75, 15]",
[](){ return MAF({
    1065.f,
    1065.f,
    75.f,
    5325.f,
    355.f,
    45.f,
    3195.f,
    213.f,
    225.f,
    15.f
}); } ,
     "CPS(5,3):[1, 3, 5, 75, 15]"
     ),
    
    PresetHelper
    ("CPS(5,4):[1, 3, 5, 75, 15]",
[](){ return MAF({
    1065.f,
    5325.f,
    3195.f,
    225.f,
    15975.f
}); } ,
     "CPS(5,4):[1, 3, 5, 75, 15]"
     ),
    
    PresetHelper
    ("CPS(4,1):[1, 5, 3, 15]",
[](){ return MAF({
    1.f,
    5.f,
    3.f,
    15.f
}); } ,
     "CPS(4,1):[1, 5, 3, 15]"
     ),
    
    PresetHelper
    ("CPS(4,1):[1, 161, 191, 241]",
[](){ return MAF({
    1.f,
    161.f,
    191.f,
    241.f
}); } ,
     "CPS(4,1):[1, 161, 191, 241]"
     ),
    
    PresetHelper
    ("CPS(4,2):[1, 5, 3, 15]",
[](){ return MAF({
    5.f,
    3.f,
    15.f,
    15.f,
    75.f,
    45.f
}); } ,
     "CPS(4,2):[1, 5, 3, 15]"
     ),
    
    PresetHelper
    ("CPS(4,2):[1, 161, 191, 241]",
[](){ return MAF({
    161.f,
    191.f,
    241.f,
    30751.f,
    38801.f,
    46031.f
}); } ,
     "CPS(4,2):[1, 161, 191, 241]"
     ),
    
    PresetHelper
    ("CPS(4,3):[1, 5, 3, 15]",
[](){ return MAF({
    15.f,
    75.f,
    45.f,
    225.f
}); } ,
     "CPS(4,3):[1, 5, 3, 15]"
     ),
    
    PresetHelper
    ("CPS(4,3):[1, 161, 191, 241]",
[](){ return MAF({
    30751.f,
    38801.f,
    46031.f,
    7410991.f
}); } ,
     "CPS(4,3):[1, 161, 191, 241]"
     ),
    
    PresetHelper
    ("CPS(4,1):[5, 9, 15, 25]",
[](){ return MAF({
    5.f,
    9.f,
    15.f,
    25.f
}); } ,
     "CPS(4,1):[5, 9, 15, 25]"
     ),
    
    PresetHelper
    ("CPS(4,2):[5, 9, 15, 25]",
[](){ return MAF({
    135.f,
    75.f,
    45.f,
    375.f,
    225.f,
    125.f
}); } ,
     "CPS(4,2):[5, 9, 15, 25]"
     ),
    
    PresetHelper
    ("CPS(4,3):[5, 9, 27, 45]",
[](){ return MAF({
    1125.f,
    675.f,
    3375.f,
    1875.f
}); } ,
     "CPS(4,3):[5, 9, 27, 45]"
     )
};
