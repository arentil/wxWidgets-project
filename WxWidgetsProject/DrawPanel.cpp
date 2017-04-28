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
	m_frameParent->SetStatusText("Point: " + wxString::Format(wxT("%i"), p.x) + ", " + wxString::Format(wxT("%i"), p.y), 0);
	if (event.Dragging())
	{
		square += p - dragStart;
		m_frameParent->SetStatusText(wxString::Format(wxT("Drag: %i, %i"), square.x, square.y), 2);
		paintNow();
		dragStart = p;
	}
}

void DrawPanel::MouseOnLeft(wxMouseEvent & event)
{
	dragStart = event.GetPosition();
}

void DrawPanel::PanelResize(wxSizeEvent & event)
{
	wxSize s = event.GetSize();
	m_panelSize = s;
	m_frameParent->SetStatusText("Size: " + wxString::Format(wxT("%i"), s.x) + ", " + wxString::Format(wxT("%i"), s.y), 1);
}

void DrawPanel::paintNow()
{
	wxClientDC dc(this);
	render(dc);
}

void DrawPanel::render(wxDC & dc)
{
	dc.SetBrush(*wxWHITE_BRUSH);
	dc.Clear();
	dc.DrawRectangle(square, wxSize(50, 50));
}