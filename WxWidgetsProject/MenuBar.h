#pragma once

#include <wx/wx.h>
#include "RightPanel.h"

class MenuBar : public wxMenuBar
{
public:
	wxFrame * m_parent;
	wxMenu * m_file;
	wxMenuItem * m_quit;
	RightPanel * m_rightpanel;

	MenuBar(wxFrame * parent, RightPanel * rightpanel);
	void OnQuit(wxCommandEvent & event);

private:
	DECLARE_EVENT_TABLE()
};