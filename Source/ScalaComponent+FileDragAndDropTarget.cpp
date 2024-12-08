/*
  ==============================================================================

    ScalaComponent+FileDragAndDropTarget.cpp
    Created: 14 Nov 2022 2:01:42pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include "ScalaComponent.h"
#include "ScalaModel.h"

// at least one .scl file exists on disk
bool ScalaComponent::isInterestedInFileDrag(const StringArray& files)
{
    if(_processor.getScalaModel()->uiGetLibrary() == ScalaModel::Library::Bundled)
    {
        return false;
    }

    for(auto s : files)
    {
        auto f = File(s);
        if(f.existsAsFile())
        {
            auto fn = f.getFileName();
            if(fn.endsWith(".scl"))
            {
                return true;
            }
        }
    }

    return false;
}

void ScalaComponent::fileDragEnter(const StringArray& /*files*/, int /*x*/, int /*y*/)
{
    _filesAreBeingDragged = ! (_processor.getScalaModel()->uiGetLibrary() == ScalaModel::Library::Bundled);
    repaint();
}

void ScalaComponent::fileDragMove(const StringArray& /*files*/, int /*x*/, int /*y*/)
{
    _filesAreBeingDragged = ! (_processor.getScalaModel()->uiGetLibrary() == ScalaModel::Library::Bundled);
    repaint();
}

void ScalaComponent::fileDragExit(const StringArray& /*files*/)
{
    _filesAreBeingDragged = false;
    repaint();
}

void ScalaComponent::filesDropped(const StringArray& files, int /*x*/, int /*y*/)
{
    // update view
    _filesAreBeingDragged = false;
    repaint();

    // only import for user scala files

    if(_processor.getScalaModel()->uiGetLibrary() == ScalaModel::Library::Bundled)
    {
        return;
    }

    // convert array of paths to file array
    auto file_array = Array<File>();
    for(auto s : files)
    {
        auto f = File(s);
        if(f.existsAsFile())
        {
            auto fn = f.getFileName();
            if(fn.endsWith(".scl"))
            {
                file_array.add(f);
            }
        }
    }

    // tell model to import file array
    auto const sm = _processor.getScalaModel();
    sm->importUserScalaFiles(file_array);
}
