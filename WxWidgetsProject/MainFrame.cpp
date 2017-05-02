#include "MainFrame.h"


MainFrame::MainFrame(const wxString & title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
	m_mainpanel = new wxPanel(this, -1);
	m_mainsizer = new wxBoxSizer(wxHORIZONTAL);
	m_statusbar = new StatusBar(this);	//dodaje statusbar
	
	rightpanel = new RightPanel(this, m_mainpanel, -1, "");
	LeftPanel * leftpanel = new LeftPanel(this, m_mainpanel, rightpanel, wxID_ANY, wxPoint(0, 0), wxSize(200, 200), "");
	m_mainsizer->Add(leftpanel, 0, wxEXPAND | wxALL, 5);
	m_mainsizer->Add(rightpanel, 1, wxEXPAND | wxALL, 5);
	m_mainpanel->SetSizer(m_mainsizer);


	m_menubar = new MenuBar(this);		//dodaje wlasny MenuBar

	Center();
}