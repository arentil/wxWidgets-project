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

void RightPanel::setScale(float scale)
{
	if (canScale)
		m_drawpanel->setScale(scale);
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