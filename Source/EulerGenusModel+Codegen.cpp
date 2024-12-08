/*
 ==============================================================================

 EulerGenusModel+Codegen.cpp
 Created: 25 Dec 2021 2:20:08pm
 Author:  Marcus W. Hobbs

 ==============================================================================
 */

// creates the following files

#include "EulerGenusModel.h"

unique_ptr<CodegenStream> EulerGenusModel::__stream_daw_keys_cpp {nullptr};
unique_ptr<CodegenStream> EulerGenusModel::__stream_tuning_constructor_map_cpp {nullptr};
unique_ptr<CodegenStream> EulerGenusModel::__stream_tuning_selection_map_cpp {nullptr};
unique_ptr<CodegenStream> EulerGenusModel::__stream_tuning_update_map_cpp {nullptr};
unique_ptr<CodegenStream> EulerGenusModel::__stream_view_model_constructor_map_cpp {nullptr};
string EulerGenusModel::__daw_key_null = {"W_EG_CPS_LEAF"};

// generates static code for euler genus
void EulerGenusModel::eulerGenusCodeGen()
{

#if 1
    // disable codegen
    //DBG ("eulerGenusCodeGen: skipping codegen");
    return;
#else
    // enable codegen
    DBG ("eulerGenusCodeGen: running codegen");

    // keys

    // EulerGenusModel+_createDAWKeys.cpp
    // DAWKeys are Strings in a StringArray
    // they are added one by one
    string daw_key_basename = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createDAWKeys_";
    string daw_key_prefix = "#include \"../EulerGenusModel.h\"\n#include \"../EulerGenusViewModel.h\"\nvoid EulerGenusModel::_createDAWKeys_XXXX()\n{\n";
    string daw_key_suffix = "\n}\n";
    string daw_key_method_file_name = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createDAWKeys_methods.txt";
    string daw_key_include_file_name = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createDAWKeys_include.txt";
    __stream_daw_keys_cpp = make_unique<CodegenStream>(daw_key_basename,
                                                       __num_entries_limit,
                                                       daw_key_prefix,
                                                       daw_key_suffix,
                                                       "_createDAWKeys",
                                                       daw_key_method_file_name,
                                                       daw_key_include_file_name);
    if (!__stream_daw_keys_cpp)
    {
        DBG ("error opening __createDAWKeys_cpp for output");
        jassertfalse;
    }

    // tuning construction

    // EulerGenusModel+_createTuningConstructorMap.cpp
    string tuning_constructor_basename = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createTuningConstructorMap_";
    string tuning_constructor_prefix = "#include \"../EulerGenusModel.h\"\n#include \"../EulerGenusViewModel.h\"\nvoid EulerGenusModel::_createTuningConstructorMap_XXXX()\n{\n   _tuningConstructorMap->insert ({\n";
    string tuning_constructor_suffix = "\n });\n}\n";
    string tuning_constructor_method_file_name = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createTuningConstructorMap_methods.txt";
    string tuning_constructor_include_file_name = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createTuningConstructorMap_include.txt";
    __stream_tuning_constructor_map_cpp = make_unique<CodegenStream>(tuning_constructor_basename,
                                                                     __num_entries_limit,
                                                                     tuning_constructor_prefix,
                                                                     tuning_constructor_suffix,
                                                                     "_createTuningConstructorMap",
                                                                     tuning_constructor_method_file_name,
                                                                     tuning_constructor_include_file_name);
    if (!__stream_tuning_constructor_map_cpp)
    {
        DBG ("error opening __createTuningConstructorMap_cpp for output");
        jassertfalse;
    }

    // tuning selection

    // EulerGenusModel+_createTuningSelectionMap.cpp
    string tuning_selection_basename = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createTuningSelectionMap_";
    string tuning_selection_prefix = "#include \"../EulerGenusModel.h\"\n#include \"../EulerGenusViewModel.h\"\nvoid EulerGenusModel::_createTuningSelectionMap_XXXX()\n{\n   _tuningSelectionMap->insert ({\n";
    string tuning_selection_suffix = "\n });\n}\n";
    string tuning_selection_method_file_name = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createTuningSelectionMap_methods.txt";
    string tuning_selection_include_file_name = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createTuningSelectionMap_include.txt";
    __stream_tuning_selection_map_cpp = make_unique<CodegenStream>(tuning_selection_basename,
                                                                   __num_entries_limit,
                                                                   tuning_selection_prefix,
                                                                   tuning_selection_suffix,
                                                                   "_createTuningSelectionMap",
                                                                   tuning_selection_method_file_name,
                                                                   tuning_selection_include_file_name);
    if (!__stream_tuning_selection_map_cpp)
    {
        DBG ("error opening __createTuningSelectionMap_cpp for output");
        jassertfalse;
    }


    // tuning update

    // EulerGenusModel+_createTuningUpdateMap.cpp
    string tuning_update_basename = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createTuningUpdateMap_";
    string tuning_update_prefix = "#include \"../EulerGenusModel.h\"\n#include \"../EulerGenusViewModel.h\"\nvoid EulerGenusModel::_createTuningUpdateMap_XXXX()\n{\n   _tuningUpdateMap->insert ({\n";
    string tuning_update_suffix = "\n });\n}\n";
    string tuning_update_method_file_name = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createTuningUpdateMap_methods.txt";
    string tuning_update_include_file_name = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createTuningUpdateMap_include.txt";
    __stream_tuning_update_map_cpp = make_unique<CodegenStream>(tuning_update_basename,
                                                                __num_entries_limit,
                                                                tuning_update_prefix,
                                                                tuning_update_suffix,
                                                                "_createTuningUpdateMap",
                                                                tuning_update_method_file_name,
                                                                tuning_update_include_file_name);
    if (!__stream_tuning_update_map_cpp)
    {
        DBG ("error opening __createTuningUpdateMap_cpp for output");
        jassertfalse;
    }

    // view models

    // EulerGenusModel+_createViewModelConstructorMap.cpp
    string vm_constructor_basename = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createViewModelConstructorMap_";
    string vm_constructor_prefix = "#include \"../EulerGenusModel.h\"\n#include \"../EulerGenusViewModel.h\"\nvoid EulerGenusModel::_createViewModelConstructorMap_XXXX()\n{\n   _viewModelConstructorMap->insert ({\n";
    string vm_constructor_suffix = "\n });\n}\n";
    string vm_constructor_method_file_name = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createViewModelConstructorMap_methods.txt";
    string vm_constructor_include_file_name = "/Users/marcushobbs/IPHONE_PRODUCTION/Wilsonic_2021_juce/Wilsonic/Source/EulerGenusModelCodegen/EulerGenusModel+_createViewModelConstructorMap_include.txt";
    __stream_view_model_constructor_map_cpp = make_unique<CodegenStream>(vm_constructor_basename,
                                                                         __num_entries_limit,
                                                                         vm_constructor_prefix,
                                                                         vm_constructor_suffix,
                                                                         "_createViewModelConstructorMap",
                                                                         vm_constructor_method_file_name,
                                                                         vm_constructor_include_file_name);
    if (!__stream_view_model_constructor_map_cpp)
    {
        DBG ("error opening __createViewModelConstructorMap_cpp for output");
        jassertfalse;
    }

    /////////////////////////////////////////////
#if 0
    // this completes in 32gb ram
    auto cps_6_1 = make_shared<CPS_6_1> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126), CPS::E (127), CPS::F (128));
    cps_6_1->setShouldComputeSubsets (true);
    cps_6_1->update();
    codegenWalkCPSTuningBase (cps_6_1, "", "");
#elif 0
    // this crashes in 32Gb ram
    auto cps_6_2 = make_shared<CPS_6_2> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126), CPS::E (127), CPS::F (128));
    cps_6_2->setShouldComputeSubsets (true);
    cps_6_2->update();
    codegenWalkCPSTuningBase (cps_6_2, "", "");
#elif 0
    // this crashes in 32Gb ram
    auto cps_6_3 = make_shared<CPS_6_3> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126), CPS::E (127), CPS::F (128));
    cps_6_3->setShouldComputeSubsets (true);
    cps_6_3->update();
    codegenWalkCPSTuningBase (cps_6_3, "", "");
#elif 0
    // this completes in 32gb ram
    auto cps_4_2 = make_shared<CPS_4_2> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126));
    cps_4_2->setShouldComputeSubsets (true);
    cps_4_2->update();
    codegenWalkCPSTuningBase (cps_4_2, "", "");
#elif 0
    // this completes in 32gb ram
    auto cps_2_1 = make_shared<CPS_2_1> (CPS::A (123), CPS::B (124));
    cps_2_1->setShouldComputeSubsets (true);
    cps_2_1->update();
    codegenWalkCPSTuningBase (cps_2_1, "", "");
#elif 0
    // next level prize...canonical erv drawing
    auto eg4 = make_shared<EulerGenus_4> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126));
    eg4->setShouldComputeSubsets (true);
    codegenWalkCPSTuningBase (eg4, "", "");
#elif 0
    // testing
    auto eg5 = make_shared<EulerGenus_5> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126), CPS::E (127));
    eg5->setShouldComputeSubsets (true);
    codegenWalkCPSTuningBase (eg5, "", "");
#elif 1
    // ultimate prize...32k+ states (~13K w floor of 3 npo)
    auto eg6 = make_shared<EulerGenus_6> (CPS::A (123), CPS::B (124), CPS::C (125), CPS::D (126), CPS::E (127), CPS::F (128));
    eg6->setShouldComputeSubsets (true);
    codegenWalkCPSTuningBase (eg6, "", "");
#else
    // NOP
    jassertfalse;
#endif

    // close all the files
    __stream_daw_keys_cpp->close();
    __stream_tuning_constructor_map_cpp->close();
    __stream_tuning_selection_map_cpp->close();
    __stream_tuning_update_map_cpp->close();
    __stream_view_model_constructor_map_cpp->close();
#endif

}

// variant in print format: print one row per UI state including selection, and back index, modifying keys with prefix to be unambiguous root and selection state
void EulerGenusModel::codegenWalkCPSTuningBase (shared_ptr<CPSTuningBase> cpst, const string back_key, const string tuning_prefix)
{
    // const delimiters
    const string tuning_delim = "||";
    const string select_delim = "__";

    // no lazy loading, order is important
    cpst->setShouldComputeSubsets (true);
    cpst->update();

    // lambdas

    // daw keys are selection state
    // "CPS_6_3_A_B_C_D_E_F__CPS_6_3_A_B_C_D_E_F",
    auto codegen_daw_keys = [](string in_daw_key)
    {
        __stream_daw_keys_cpp->write (" _dawKeys->add(\"" + in_daw_key + "\");\n");
    };

    // tuning constructor
    auto codegen_tuning_constructor_map_cpp = [](string in_tuning_name, string in_tuning_create_lambda)
    {
        __stream_tuning_constructor_map_cpp->write ("{\"" + in_tuning_name + "\", " + in_tuning_create_lambda + "}," + "\n");
    };

    // tuning update
    //{"CPS_6_3(A,B,C,D,E,F)", [this](){auto cps = _getTuning (tuning_key); cps->set ({_A,_B,_C,_D,_E}, {_F});}}
    auto codegen_tuning_update_map_cpp = [](string in_tuning_key, string in_update_str)
    {
        __stream_tuning_update_map_cpp->write ("       {\"" + in_tuning_key + "\", [this](){auto cps = _getTuning (\"" + in_tuning_key + "\"); " + in_update_str + "}}," + "\n");
    };

    // tuning selection
    auto codegen_tuning_selection_map_cpp = [](string in_select_key, bool in_select_parent, bool in_select_s0, bool in_select_s1, int in_s01_index)
    {
        string subset_selection_string = "";
        if (in_select_parent)
        {
            subset_selection_string = "cps->selectParent();";
        }
        else if (in_select_s0)
        {
            switch (in_s01_index) {
                case 0: subset_selection_string = "cps->selectS0_0();"; break;
                case 1: subset_selection_string = "cps->selectS0_1();"; break;
                case 2: subset_selection_string = "cps->selectS0_2();"; break;
                case 3: subset_selection_string = "cps->selectS0_3();"; break;
                case 4: subset_selection_string = "cps->selectS0_4();"; break;
                case 5: subset_selection_string = "cps->selectS0_5();"; break;
                default: jassertfalse;
                    break;
            }
        }
        else if (in_select_s1)
        {
            switch (in_s01_index) {
                case 0: subset_selection_string = "cps->selectS1_0();"; break;
                case 1: subset_selection_string = "cps->selectS1_1();"; break;
                case 2: subset_selection_string = "cps->selectS1_2();"; break;
                case 3: subset_selection_string = "cps->selectS1_3();"; break;
                case 4: subset_selection_string = "cps->selectS1_4();"; break;
                case 5: subset_selection_string = "cps->selectS1_5();"; break;
                default: jassertfalse;
                    break;
            }
        }
        else
        {
            jassertfalse;
        }

        __stream_tuning_selection_map_cpp->write ("     {\"" + in_select_key + "\", " +
                                                  "[this]() { auto vm = _getViewModel (\"" + in_select_key + "\"); " +
                                                  "auto cps = vm->parentTuning; " + subset_selection_string + "}}," +
                                                  "\n");
    };

    // view model
    auto codegen_view_model_constructor_map_cpp = [](string in_daw_key, string in_tuning_key, string in_back_key, string in_select_key)
    {
        __stream_view_model_constructor_map_cpp->write ("       {\"" + in_daw_key + "\", [this](){return _create_view_model (\"" + in_daw_key + "\", \"" + in_tuning_key + "\", \"" + in_back_key + "\", \"" + in_select_key + "\");}}," +
                                                        "\n");
    };

    // many leaf-level subsets are duplicates: keys must be unique for every path in every branch of the tree
    // reminder: keys are unique for selection state, but tuning keys point to redundant tunings
    auto recursive_prefix = tuning_prefix + tuning_delim + cpst->getTuningNameAsUnderscores();
    auto tuning_key = recursive_prefix;

    // parent tuning daw_key
    auto create_daw_key = [&](shared_ptr<CPSTuningBase> cps_tuning_parent, shared_ptr<CPSTuningBase> cps_tuning_subset)
    {
        return tuning_prefix + tuning_delim + cps_tuning_parent->getTuningNameAsUnderscores() + select_delim + cps_tuning_subset->getTuningNameAsUnderscores();
    };

    // select daw_key
    auto create_select_key = [&](shared_ptr<CPSTuningBase> cps_tuning_parent, shared_ptr<CPSTuningBase> cps_tuning_subset)
    {
        return tuning_prefix + tuning_delim + cps_tuning_parent->getTuningNameAsUnderscores() + tuning_delim + cps_tuning_subset->getTuningNameAsUnderscores() + select_delim + cps_tuning_subset->getTuningNameAsUnderscores();
    };

    // subset TuningKeys, DAWKeys, select keys: parent, s0, s1 keys for tuning constructor
    vector<string> s0_daw_keys    = {};
    vector<string> s0_select_keys = {};
    for (auto cpsts0 : cpst->getSubsets0())
    {
        auto daw_key_s0    = create_daw_key (cpst, cpsts0);
        auto select_key_s0 = create_select_key (cpst, cpsts0);
        s0_daw_keys.push_back (daw_key_s0);
        s0_select_keys.push_back (select_key_s0);
    }

    vector<string> s1_daw_keys    = {};
    vector<string> s1_select_keys = {};
    for (auto cpsts1: cpst->getSubsets1())
    {
        auto daw_key_s1    = create_daw_key (cpst, cpsts1);
        auto select_key_s1 = create_select_key (cpst, cpsts1);
        s1_daw_keys.push_back (daw_key_s1);
        s1_select_keys.push_back (select_key_s1);
    }

    // Tuning constructor: every tuning and subset has a dawkey, limited by leaf-size
    // Technically there are cps base tuning duplicates, differentiated by selection state.
    // For example, [almost] every "parent tuning" is both a selected parent, and a selected subset; exceptions at the leaves
    // So you have a daw key for a selected subset of a parent, and then a daw key for that subset as the parent tuning one level down
    auto daw_key_parent = create_daw_key (cpst, cpst);
    auto create_str     = cpst->getTuningCreationCodegen (daw_key_parent, s0_daw_keys, s1_daw_keys);
    auto select_key     = daw_key_parent;
    auto update_str     = cpst->getTuningUpdateCodegen();

    // codegen parent tuning: EulerGenus type has a tuning, but it has no selected parent, only selected subsets
    if (!cpst->isEulerGenusTuningType())
    {
        codegen_daw_keys (daw_key_parent);
        codegen_view_model_constructor_map_cpp (daw_key_parent, tuning_key, back_key, select_key);
        codegen_tuning_selection_map_cpp (select_key, true, false, false, 0);
    }
    codegen_tuning_constructor_map_cpp (tuning_key, create_str); // only call on parent
    codegen_tuning_update_map_cpp (tuning_key, update_str); // only call on parent

    // print subsets and back
    // "back" equals selected subset's parent.  Only the parent has a "back" with a new parent
    // __daw_key_null = a leaf node.  select-able, but not drill-able.
    int index = 0;
    for (auto cpsts0 : cpst->getSubsets0())
    {
        auto daw_key_s0    = create_daw_key (cpst, cpsts0);
        auto select_key_s0 = create_select_key (cpst, cpsts0);
        codegen_daw_keys (daw_key_s0);
        // do not call codegen_daw_keys (select_key_s0); // will be a dup
        codegen_tuning_selection_map_cpp (daw_key_s0, false, true, false, index);

        auto big_enough_s0       = cpsts0->getProcessedArray().count() >= __cps_parent_as_leaf_min_size;
        auto select_key_s0_final = big_enough_s0 ? select_key_s0 : __daw_key_null;
        codegen_view_model_constructor_map_cpp (daw_key_s0, tuning_key, daw_key_parent, select_key_s0_final);

        // do not call codegen_tuning_constructor_map_cpp
        // do not call codegen_tuning_update_map_cpp

        index++;
    }

    index = 0;
    for (auto cpsts1 : cpst->getSubsets1())
    {
        auto daw_key_s1    = create_daw_key (cpst, cpsts1);
        auto select_key_s1 = create_select_key (cpst, cpsts1);
        codegen_daw_keys (daw_key_s1);
        // do not call codegen_daw_keys (select_key_s1); // will be a dup
        codegen_tuning_selection_map_cpp (daw_key_s1, false, false, true, index);

        auto big_enough_s1       = cpsts1->getProcessedArray().count() >= __cps_parent_as_leaf_min_size;
        auto select_key_s1_final = big_enough_s1 ? select_key_s1 : __daw_key_null;
        codegen_view_model_constructor_map_cpp (daw_key_s1, tuning_key, daw_key_parent, select_key_s1_final);

        // do not call codegen_tuning_constructor_map_cpp
        // do not call codegen_tuning_update_map_cpp

        index++;
    }

    // trivial terminal condition: no subsets...see below for others
    if (cpst->getSubsets0().size() == 0 && cpst->getSubsets1().size() == 0)
    {
        return;
    }

    // the recursive terminal conditions are the empty subsets
    // floor of __cps_parent_as_leaf_min_size compiles and links for EulerGenus_6
    for (auto cpsts0 : cpst->getSubsets0())
    {
        auto big_enough_s0 = cpsts0->getProcessedArray().count() >= __cps_parent_as_leaf_min_size;
        if (!big_enough_s0)
        {
            break;
        }
        auto s0_back_key = create_daw_key (cpst, cpsts0);
        codegenWalkCPSTuningBase (cpsts0, s0_back_key, recursive_prefix);
    }
    for (auto cpsts1 : cpst->getSubsets1())
    {
        auto big_enough_s1 = cpsts1->getProcessedArray().count() >= __cps_parent_as_leaf_min_size;
        if (!big_enough_s1)
        {
            break;
        }
        auto s1_back_key = create_daw_key (cpst, cpsts1);
        codegenWalkCPSTuningBase (cpsts1, s1_back_key, recursive_prefix);
    }
}
