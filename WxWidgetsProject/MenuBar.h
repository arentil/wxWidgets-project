#pragma once

#include <wx/wx.h>

class MenuBar : public wxMenuBar
{
public:
	wxFrame * m_parent;
	wxMenu * m_file;
	wxMenuItem * m_quit;

	MenuBar(wxFrame * parent);
	void OnQuit(wxCommandEvent & event);

private:
	DECLARE_EVENT_TABLE()
};