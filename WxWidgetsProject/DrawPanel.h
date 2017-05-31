#pragma once

#include <wx/wx.h>
#include "DrawArea.h"
#include <chrono>

class DrawPanel : public wxPanel
{
public:
	wxFrame * m_frameParent;

	DrawPanel(wxFrame * frameParent, wxPanel * parent, wxWindowID winid, wxPoint point, wxSize sizer);
	void initialize(int width, int height, int size);
	void scale(float scale, int scaleVal);
	float getScale();
	void deleteArea();
	void setColor(Color color);
	void randomize();
	void search();
	void clearWalls();
	void setShowFuncValues(bool showVals);
	void clearPath();
	void setHeuristic(Heuristic h);
	void allowDiagonal(bool allow);
	void setCompareWithDijkstra(bool ifCompare);
	void setCompareWithBellmanFord(bool ifCompare);

	void MouseMotion(wxMouseEvent & event);
	void MouseLeftDown(wxMouseEvent & event);
	void MouseLeftUp(wxMouseEvent & event);
	void PanelResize(wxSizeEvent & event);

private:
	wxSize m_panelSize;

	DrawArea * drawArea;

	wxPoint dragStart;

	Color m_color;
	bool colorChange;
	bool isInitialized;

	bool m_compareWithDijkstra;
	bool m_compareWithBellmanFord;
	float timeOfAStar;
	float timeOfDijkstra;
	float timeOfBellmanFord;

	DECLARE_EVENT_TABLE()
};