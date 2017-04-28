#include "MainFrame.h"
#include "LeftPanel.h"
#include "RightPanel.h"


//³apiemy eventy
BEGIN_EVENT_TABLE(MainFrame, wxFrame)
END_EVENT_TABLE()



MainFrame::MainFrame(const wxString & title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
	m_mainpanel = new wxPanel(this, -1);
	m_mainsizer = new wxBoxSizer(wxHORIZONTAL);
	m_statusbar = new StatusBar(this);	//dodaje statusbar
	

	LeftPanel * leftpanel = new LeftPanel(this, m_mainpanel, wxID_ANY, wxPoint(0, 0), wxSize(200, 200), "LeftPanelStaticSizerBox");
	RightPanel * rightpanel = new RightPanel(this, m_mainpanel, -1, "RightPanelStaticSizerBox");
	m_mainsizer->Add(leftpanel, 0, wxEXPAND | wxALL, 5);
	m_mainsizer->Add(rightpanel, 1, wxEXPAND | wxALL, 5);
	m_mainpanel->SetSizer(m_mainsizer);



	/*
	mainpanel = new wxPanel(this, -1);
	wxBoxSizer * hbox = new wxBoxSizer(wxHORIZONTAL);
	wxPanel * leftpanel = new wxPanel(mainpanel, wxID_ANY, wxPoint(0, 0), wxSize(100, 400));
	leftpanel->SetBackgroundColour(wxColour("green"));
	wxPanel * rightpanel = new wxPanel(mainpanel);
	rightpanel->SetBackgroundColour(wxColour("blue"));

	hbox->Add(leftpanel, 0, wxEXPAND | wxALL, 5);
	hbox->Add(rightpanel, 1, wxEXPAND | wxALL, 5);
	mainpanel->SetSizer(hbox);
	*/

	m_menubar = new MenuBar(this);		//dodaje wlasny MenuBar

	Center();
}