#include "DrawPanel.h"


BEGIN_EVENT_TABLE(DrawPanel, wxPanel)
	EVT_MOTION(DrawPanel::MouseMotion)
	EVT_LEFT_DOWN(DrawPanel::MouseOnLeft)
	EVT_SIZE(DrawPanel::PanelResize)
END_EVENT_TABLE()

DrawPanel::DrawPanel(wxFrame * frameParent, wxPanel * parent, wxWindowID winid, wxPoint point, wxSize size) : wxPanel(parent, winid, point, size)
{
	m_frameParent = frameParent;
}

void DrawPanel::MouseMotion(wxMouseEvent & event)
{
	wxPoint p = event.GetPosition();
	m_mouseXY = p;
	m_frameParent->SetStatusText("Point: " + wxString::Format(wxT("%i"), p.x) + ", " + wxString::Format(wxT("%i"), p.y), 0);
	event.Skip();
}

void DrawPanel::MouseOnLeft(wxMouseEvent & event)
{
	paintNow();
	event.Skip();
}

void DrawPanel::PanelResize(wxSizeEvent & event)
{
	wxSize s = event.GetSize();
	m_panelSize = s;
	m_frameParent->SetStatusText("Size: " + wxString::Format(wxT("%i"), s.x) + ", " + wxString::Format(wxT("%i"), s.y), 1);
	event.Skip();
}

void DrawPanel::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void DrawPanel::render(wxDC & dc)
{
	dc.DrawRectangle(m_mouseXY, wxSize(50, 50));
}