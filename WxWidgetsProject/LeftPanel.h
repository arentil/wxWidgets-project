#pragma once

#include <wx/wx.h>
#include "RightPanel.h"

class LeftPanel : public wxPanel
{
public:
	LeftPanel(wxFrame * frameParent, wxPanel * parent, RightPanel * rightPanel, wxWindowID winid, wxPoint point, wxSize size, const wxString & sizertext);

	void onCreateGrid(wxCommandEvent & event);

private:
	wxFrame * m_frameParent;
	wxPanel * m_parent;
	RightPanel * m_rightPanel;

	wxStaticBoxSizer * m_staticsizer;

	wxButton * m_create;
	wxTextCtrl * m_rows;
	wxTextCtrl * m_cols;

	DECLARE_EVENT_TABLE()
};
