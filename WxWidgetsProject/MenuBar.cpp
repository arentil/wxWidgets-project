#include "MenuBar.h"


BEGIN_EVENT_TABLE(MenuBar, wxMenuBar)
	EVT_MENU(wxID_EXIT, MenuBar::OnQuit)
END_EVENT_TABLE()


MenuBar::MenuBar(wxFrame * parent) : wxMenuBar()
{
	m_parent = parent;
	m_file = new wxMenu;
	m_quit = new wxMenuItem(m_file, wxID_EXIT, "&Quit\tCtrl+W");
	m_file->Append(m_quit);
	this->Append(m_file, "&File");
	m_parent->SetMenuBar(this);
}


void MenuBar::OnQuit(wxCommandEvent & event)
{
	m_parent->Close(true);
}