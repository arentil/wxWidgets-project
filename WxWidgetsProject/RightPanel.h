#pragma once

#include <wx/wx.h>
#include "DrawPanel.h"

class RightPanel : public wxPanel
{
public:
	wxFrame * m_frameParent;
	wxPanel * m_parent;
	DrawPanel * m_drawpanel;
	bool canScale;

	RightPanel(wxFrame * frameParent, wxPanel * parent, wxWindowID winid, const wxString & sizertext);
	void initialize(int width, int height, int size);
	void setScale(float scale);
	float getScale();
	void deleteArea();
};
