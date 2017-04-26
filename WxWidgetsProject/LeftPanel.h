#pragma once

#include <wx/wx.h>

class LeftPanel : public wxPanel
{
public:
	wxFrame * m_frameParent;
	wxPanel * m_parent;
	wxStaticBoxSizer * m_staticsizer;

	LeftPanel(wxFrame * frameParent, wxPanel * parent, wxWindowID winid, wxPoint point, wxSize size, const wxString & sizertext);
};
