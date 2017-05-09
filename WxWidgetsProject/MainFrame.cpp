#include "MainFrame.h"

BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MOUSEWHEEL(MainFrame::onMouseScroll)
	EVT_CHAR_HOOK(MainFrame::onFKeyPressed)
END_EVENT_TABLE()

MainFrame::MainFrame(const wxString & title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 675))
{
	m_mainpanel = new wxPanel(this, -1);
	m_mainsizer = new wxBoxSizer(wxHORIZONTAL);
	m_statusbar = new StatusBar(this);	//dodaje statusbar
	
	rightpanel = new RightPanel(this, m_mainpanel, -1, "");
	leftpanel = new LeftPanel(this, m_mainpanel, rightpanel, wxID_ANY, wxPoint(0, 0), wxSize(200, 200), "");
	m_mainsizer->Add(leftpanel, 0, wxEXPAND | wxALL, 5);
	m_mainsizer->Add(rightpanel, 1, wxEXPAND | wxALL, 5);
	m_mainpanel->SetSizer(m_mainsizer);

	m_menubar = new MenuBar(this, rightpanel);		//dodaje wlasny MenuBar
	
	Center();
}

void MainFrame::scale(float scale, int scaleVal)
{
	rightpanel->scale(scale, scaleVal);
}

void MainFrame::onMouseScroll(wxMouseEvent & event)
{
	if (event.GetWheelRotation() == 120)
		scale(0.1, leftpanel->getScaleValue());
	else if (event.GetWheelRotation() == -120)
		scale(-0.1, leftpanel->getScaleValue());
}

void MainFrame::onFKeyPressed(wxKeyEvent & event)
{
	switch (event.GetKeyCode())
	{
	case 340:
		leftpanel->setSelection(0);
		break;
	case 341:
		leftpanel->setSelection(1);
		break;
	case 342:
		leftpanel->setSelection(2);
		break;
	default:
		event.Skip();
		break;
	}
}