#include "RightPanel.h"

RightPanel::RightPanel(wxFrame * frameParent, wxPanel * parent, wxWindowID winid, const wxString & sizertext) : wxPanel(parent, winid)
{
	m_frameParent = frameParent;
	m_parent = parent;

	wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer * staticbox = new wxStaticBoxSizer(wxVERTICAL, this, sizertext);
	m_drawpanel = new DrawPanel(frameParent, this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	staticbox->Add(m_drawpanel, 1, wxEXPAND | wxALL, 0);
	sizer->Add(staticbox, 1, wxEXPAND | wxALL, 0);
	this->SetSizer(sizer);
}