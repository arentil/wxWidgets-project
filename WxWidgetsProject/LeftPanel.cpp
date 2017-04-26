#include "LeftPanel.h"

LeftPanel::LeftPanel(wxFrame * frameParent, wxPanel * parent, wxWindowID winid, wxPoint point, wxSize size, const wxString & sizertext) : wxPanel(parent, winid, point, size)
{
	m_frameParent = frameParent;
	m_parent = parent;
	wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(new wxStaticBoxSizer(wxVERTICAL, this, sizertext), 1, wxEXPAND | wxALL, 0);
	this->SetSizer(sizer);
}