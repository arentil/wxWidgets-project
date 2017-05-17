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
	m_color = Color::grey;
	isInitialized = false;
	drawArea = nullptr;
	SetEvtHandlerEnabled(false);
	m_frameParent = frameParent;
	m_panelSize = sizer;
}

void DrawPanel::initialize(int width, int height, int size)
{
	deleteArea();
	m_panelSize = GetSize();
	drawArea = new DrawArea(this, width, height, size);
	drawArea->setPanelSize(&m_panelSize);
	isInitialized = true;
	colorChange = true;
	drawArea->paintNow();
	SetEvtHandlerEnabled(true);

}

void DrawPanel::scale(float scale, int scaleVal)
{
	if (!isInitialized)
		return;
	drawArea->scale(scale, scaleVal);
}

float DrawPanel::getScale()
{
	if (!isInitialized)
		return 0.0;
	return drawArea->getScale();
}

void DrawPanel::deleteArea()
{
	if (drawArea != nullptr)
	{
		drawArea->deleteArea();
		delete drawArea;
	}
}

void DrawPanel::setColor(Color color)
{
	m_color = color;
}

void DrawPanel::randomize()
{
	if (isInitialized)
		drawArea->randomize();
}

void DrawPanel::search()
{
	if (isInitialized)
		drawArea->search();
}

void DrawPanel::clearWalls()
{
	if (isInitialized)
		drawArea->clearWalls();
}

void DrawPanel::setShowFuncValues(bool showVals)
{
	if (isInitialized)
		drawArea->setShowFuncValues(showVals);
}

void DrawPanel::clearPath()
{
	if (isInitialized)
		drawArea->clearPath();
}

void DrawPanel::setHeuristic(Heuristic h)
{
	if (isInitialized)
		drawArea->setHeuristic(h);
}

void DrawPanel::allowDiagonal(bool allow)
{
	if (isInitialized)
		drawArea->allowDiagonal(allow);
}

void DrawPanel::MouseMotion(wxMouseEvent & event)
{
	if (!isInitialized)
		return;
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
	if (!isInitialized)
		return;
	dragStart = event.GetPosition();
}

void DrawPanel::MouseLeftUp(wxMouseEvent & event)
{
	if (!isInitialized)
		return;
	wxPoint p = event.GetPosition();
	if (colorChange)
	{
		Square * sqr = drawArea->getSquare(p.x, p.y);
		if (sqr == nullptr)
		{
			colorChange = true;
			return;
		}
		drawArea->setColor(sqr, m_color);
		drawArea->paintNow();
	}
	colorChange = true;
}

void DrawPanel::PanelResize(wxSizeEvent & event)
{
	wxSize s = event.GetSize();
	m_panelSize = s;
	m_frameParent->SetStatusText("Size: " + wxString::Format(wxT("%i"), s.x) + ", " + wxString::Format(wxT("%i"), s.y), 1);
	if (!isInitialized)
		return;	
	drawArea->setPanelSize(&m_panelSize);
	drawArea->paintNow();
}