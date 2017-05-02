#pragma once

#include <wx/wx.h>
#include "DrawArea.h"

class DrawPanel : public wxPanel
{
public:
	wxFrame * m_frameParent;

	DrawPanel(wxFrame * frameParent, wxPanel * parent, wxWindowID winid, wxPoint point, wxSize sizer);
	void initialize(int width, int height, int size);

	void MouseMotion(wxMouseEvent & event);
	void MouseLeftDown(wxMouseEvent & event);
	void MouseLeftUp(wxMouseEvent & event);
	void PanelResize(wxSizeEvent & event);

private:
	wxSize m_panelSize;

	DrawArea * drawArea;

	wxPoint dragStart;

	bool colorChange;

	DECLARE_EVENT_TABLE()
};
