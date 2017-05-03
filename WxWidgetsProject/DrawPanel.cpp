#include "DrawPanel.h"


BEGIN_EVENT_TABLE(DrawPanel, wxPanel)
	EVT_MOTION(DrawPanel::MouseMotion)
	EVT_LEFT_DOWN(DrawPanel::MouseLeftDown)
	EVT_LEFT_UP(DrawPanel::MouseLeftUp)
	EVT_SIZE(DrawPanel::PanelResize)
END_EVENT_TABLE()

DrawPanel::DrawPanel(wxFrame * frameParent, wxPanel * parent, wxWindowID winid, wxPoint point, wxSize sizer)
	: wxPanel(parent, winid, point, sizer)
{
	SetEvtHandlerEnabled(false);
	m_frameParent = frameParent;
}

void DrawPanel::initialize(int width, int height, int size)
{
	drawArea = new DrawArea(this, width, height, size);
	colorChange = true;
	drawArea->paintNow();
	SetEvtHandlerEnabled(true);
}

void DrawPanel::setScale(float scale)
{
	drawArea->setScale(scale);
}

float DrawPanel::getScale()
{
	return drawArea->getScale();
}

void DrawPanel::MouseMotion(wxMouseEvent & event)
{
	wxPoint p = event.GetPosition();
	m_frameParent->SetStatusText("Point: " + wxString::Format(wxT("%i"), p.x) + ", " + wxString::Format(wxT("%i"), p.y), 0);
	if (event.Dragging())
	{
		wxPoint pt = p - dragStart;
		drawArea->changePos(pt.x, pt.y);
		drawArea->paintNow();
		m_frameParent->SetStatusText(wxString::Format(wxT("Drag: %i, %i"), pt.x, pt.y), 2);
		dragStart = p;
		colorChange = false;
	}
}

void DrawPanel::MouseLeftDown(wxMouseEvent & event)
{
	dragStart = event.GetPosition();
}

void DrawPanel::MouseLeftUp(wxMouseEvent & event)
{
	wxPoint p = event.GetPosition();
	if (colorChange)
	{
		Square * sqr = drawArea->getSquare(p.x, p.y);
		if (sqr == nullptr)
		{
			colorChange = true;
			return;
		}
		drawArea->setColor(sqr, Color::red);
		drawArea->paintNow();
	}
	colorChange = true;
}

void DrawPanel::PanelResize(wxSizeEvent & event)
{
	wxSize s = event.GetSize();
	m_panelSize = s;
	m_frameParent->SetStatusText("Size: " + wxString::Format(wxT("%i"), s.x) + ", " + wxString::Format(wxT("%i"), s.y), 1);
	drawArea->paintNow();
}