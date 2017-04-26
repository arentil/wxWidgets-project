#pragma once

#include <wx/wx.h>

class StatusBar : public wxStatusBar
{
public:
	wxFrame * m_parent;

	StatusBar(wxFrame * parent);
	void SetText(const wxString & text, int field = 0);
};