/*
  ==============================================================================

    WilsonicIntervalMatrixComponent.cpp
    Created: 17 May 2021 9:28:26pm
    Author:  Marcus W. Hobbs

  ==============================================================================
*/

#include <JuceHeader.h>
#include "WilsonicIntervalMatrixComponent.h"
#include "AppTuningModel.h"
#include "Microtone.h"
#include "WilsonicProcessor.h"

#pragma mark - lifecycle

WilsonicIntervalMatrixComponent::WilsonicIntervalMatrixComponent (WilsonicProcessor& processor)
: _processor (processor)
{
    _tuning = make_shared<TuningImp> (TuningImp());
}

WilsonicIntervalMatrixComponent::~WilsonicIntervalMatrixComponent()
{

}

#pragma mark - drawing

/*
 (0,     0), (1,  0), ..., (npo+1,  0)
 (0,     1), (1,   0), ..., (npo,   0)
 ...
 (0, npo+1), (1, npo+1), ..., (npo+1, npo+1)
 i.e., row 0 and column 0 are headers with frequency,
 and inset from row/column 1-npo+1 is the interval of the column/row
 */
void WilsonicIntervalMatrixComponent::paint(Graphics& g)
{
    // BG
    g.fillAll(_processor.getAppSkin().getBgColor());

    if (AppExperiments::showDebugBoundingBox)
    {
        // DEBUG
        g.setColour (Colours::yellow);
        g.drawRect (getLocalBounds(), 1);
    }

    // Layout
    auto const area = getLocalBounds().reduced (2.f);

    // make a copy of processed array
    auto ma = MicrotoneArray(_tuning->getProcessedArrayNPO());
    unsigned long npo = ma.count();
    if (npo == 0) {
        
        jassertfalse;
        return;
    }
    auto const cellWidth = static_cast<int>(area.getWidth() / float(npo + 1));
    auto const cellHeight = static_cast<int>(area.getHeight() / float(npo + 1));
    constexpr float lineThin = 0.25f;
    const Colour lineThinColour = Colours::darkslategrey;
    constexpr float lineThick = 1.f;
    const Colour lineThickColour = Colours::lightgrey;
    Colour lineColor = lineThinColour;
    float lineThickness = lineThin;
    Colour cellTextColor = Colours::white;

    for (unsigned long i = 0; i < npo + 1; i++)
    {
        // cell-level text and color, overwritten depending on 0-row or 0-column
        string shortDesc = "";
        lineColor = lineThinColour;

        // cell-level pitch, including header row/column
        float iFrequency = 0;
        float jFrequency = 0;

        if (i == 0)
        {
            // (i,j) == (0,0) display a white 'x' (upper left cell)
            iFrequency = 0;
            shortDesc = "x";
            cellTextColor = Colours::white;
            lineColor = lineThinColour;
            lineThickness = lineThin;
        }
        else
        {
            // for j==0 iPitch and shortDesc are the pitch of header row cell
            // for j>0 iPitch and shortDesc are the interval of the cell
            auto const mti = ma.microtoneAtIndex(i - 1);
            iFrequency = mti->getFrequencyValue();
            jassert(iFrequency > 0);
            shortDesc = to_string(iFrequency);
            cellTextColor =_processor.getAppTuningModel()->colorForFrequency(iFrequency);     // DEPRECATED

            lineThickness = lineThin;
            lineColor = lineThinColour;
        }

        for (unsigned long j = 0; j < npo + 1; j++)
        {
            if (i == 0 && j == 0)
            {
                // leave colour and description set to column from outer loop
                // (i,j) == (0,0) display a white 'x' (upper left cell)
            }
            else if (j == 0)
            {
                // for j==0 iPitch and shortDesc are the pitch of header row cell
            }
            else if (i == 0)
            {
                // j > 0, i.e., header column displaying 1/pitch
                auto const mtj = ma.microtoneAtIndex(j - 1);
                jFrequency = mtj->getFrequencyValue();
                shortDesc = "1/" + to_string(jFrequency);
                cellTextColor =_processor.getAppTuningModel()->colorForFrequency(1.f / jFrequency);     // DEPRECATED

                lineThickness = lineThin;
                lineColor = lineThinColour;
            }
            else
            {
                // (i,j) = (1...npo+1, 1...npo+1) => interval
                auto const mtj = ma.microtoneAtIndex(j - 1);
                jFrequency = mtj->getFrequencyValue();
                jassert(jFrequency > 0);
                auto pFinal = iFrequency / jFrequency;
                jassert(pFinal > 0);

                // octave reduce
                while (pFinal < 1)
                    pFinal *= 2.f;

                shortDesc = to_string(pFinal);
                cellTextColor = _processor.getAppTuningModel()->colorForFrequency(pFinal);     // DEPRECATED

                lineThickness = lineThick;
                lineColor = lineThickColour;
            }

            // rect for this cell
            auto cellRect = Rectangle<int>();
            auto const x = static_cast<int>(area.getX() + cellWidth * float(i));
            auto const y = static_cast<int>(area.getY() + cellHeight * float(j));
            cellRect.setX(x);
            cellRect.setY(y);
            cellRect.setSize(cellWidth, cellHeight);

            // draw text for cell
            if (i == 0 || j == 0)
            {
                // row/column headers don't get filled in
                g.setColour(cellTextColor);
                g.drawFittedText(shortDesc, cellRect, Justification::centred, 1);
            }
            else
            {
                // cells get filled
                g.setColour(cellTextColor);
                g.fillRect(cellRect);
                g.setColour(Colours::black);
                g.drawFittedText(shortDesc, cellRect, Justification::centred, 1);
            }

            // stroke cell
            g.setColour(lineColor);
            g.drawRect(cellRect, static_cast<int>(lineThickness));
        }
    }
}

void WilsonicIntervalMatrixComponent::resized()
{

}

#pragma mark - tuning

void WilsonicIntervalMatrixComponent::setTuning(shared_ptr<Tuning> t)
{
    _tuning = t;
    repaint();
}
