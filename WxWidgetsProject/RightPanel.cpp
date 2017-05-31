#include "RightPanel.h"

RightPanel::RightPanel(wxFrame * frameParent, wxPanel * parent, wxWindowID winid, const wxString & sizertext) : wxPanel(parent, winid)
{
	canScale = false;
	m_frameParent = frameParent;
	m_parent = parent;
	wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer * staticbox = new wxStaticBoxSizer(wxVERTICAL, this, "");
	m_drawpanel = new DrawPanel(m_frameParent, this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	staticbox->Add(m_drawpanel, 1, wxEXPAND | wxALL, 0);
	sizer->Add(staticbox, 1, wxEXPAND | wxALL, 0);
	this->SetSizer(sizer);
}

void RightPanel::initialize(int width, int height, int size)
{
	m_drawpanel->initialize(width, height, size);
	canScale = true;
}

void RightPanel::scale(float scale, int scaleVal)
{
	if (canScale)
		m_drawpanel->scale(scale, scaleVal);
}

float RightPanel::getScale()
{
	if (canScale)
		return m_drawpanel->getScale();
	return 0.0;
}

void RightPanel::deleteArea()
{
	m_drawpanel->deleteArea();
}

void RightPanel::setColor(Color color)
{
	m_drawpanel->setColor(color);
}

void RightPanel::randomize()
{
	m_drawpanel->randomize();
}

void RightPanel::search()
{
	m_drawpanel->search();
}

void RightPanel::clearWalls()
{
	m_drawpanel->clearWalls();
}

void RightPanel::setShowFuncValues(bool showVals)
{
	m_drawpanel->setShowFuncValues(showVals);
}

void RightPanel::clearPath()
{
	m_drawpanel->clearPath();
}

void RightPanel::setHeuristic(Heuristic h)
{
	m_drawpanel->setHeuristic(h);
}

void RightPanel::allowDiagonal(bool allow)
{
	m_drawpanel->allowDiagonal(allow);
}

void RightPanel::setCompareWithDijkstra(bool ifCompare)
{
	m_drawpanel->setCompareWithDijkstra(ifCompare);
}

void RightPanel::setCompareWithBellmanFord(bool ifCompare)
{
	m_drawpanel->setCompareWithBellmanFord(ifCompare);
}