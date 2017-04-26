#pragma once

#include <wx/wx.h>
#include "MenuBar.h"
#include "StatusBar.h"

class MainFrame : public wxFrame
{
public:
	/// glowny panel dla calego okna
	wxPanel * m_mainpanel;

	///glowny wxBoxSizer dla lewego i prawego panelu
	wxBoxSizer * m_mainsizer;


	///menubar jak w kazdym programie, nic wiecej do dodania
	MenuBar * m_menubar;

	///statusbar - pasek na samym dole okienka wyswietlamy tam koordy prawego panelu i takie tam inne
	StatusBar * m_statusbar;

	
	MainFrame(const wxString & title);

private:
	DECLARE_EVENT_TABLE()
};
