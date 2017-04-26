#pragma once

#include <wx/wx.h>
#include "MainFrame.h"

class DrawPanel : public wxPanel
{
public:
	wxFrame * m_frameParent;

	DrawPanel(wxFrame * frameParent, wxPanel * parent, wxWindowID winid, wxPoint point, wxSize size);

	
	void paintNow();
	void render(wxDC & dc);


	void MouseMotion(wxMouseEvent & event);
	void MouseOnLeft(wxMouseEvent & event);
	void PanelResize(wxSizeEvent & event);

private:
	wxPoint m_mouseXY;
	wxSize m_panelSize;

	DECLARE_EVENT_TABLE()
};
