#include "DrawArea.h"
#include <wx/dcbuffer.h>

DrawArea::DrawArea(wxPanel * parent, int width, int height, int size)
{
	m_parent = parent;
	m_size = size;
	m_width = width;
	m_height = height;
	x_min = 0;
	y_min = 0;
	x_max = width * size;
	y_max = height * size;


	m_area = new Square**[m_width];
	for (int i = 0; i < m_width; i++)
	{
		m_area[i] = new Square*[m_height];
	}

	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			m_area[i][j] = new Square(i * size, j * size);
			m_area[i][j]->setColor(Color::white);
		}
	}
}

Square * DrawArea::getSquare(int x, int y)
{
	div_t x_res, y_res;
	x_res = div((x - x_min), m_size);
	y_res = div((y - y_min), m_size);
	return m_area[x_res.quot][y_res.quot];
}

void DrawArea::setColor(Square * sqr, Color color)
{
	Color sqrCol = sqr->getColor();
	switch (sqrCol)
	{
	case Color::white:
		sqr->setColor(color);
		break;
	case Color::blue:
		if (color == Color::blue)
			sqr->setColor(Color::white);
		else
			sqr->setColor(color);
		break;
	case Color::green:
		if (color == Color::green)
			sqr->setColor(Color::white);
		else
			sqr->setColor(color);
		break;
	case Color::path:
		if (color == Color::path)
			sqr->setColor(Color::white);
		else
			sqr->setColor(color);
		break;
	case Color::red:
		if (color == Color::red)
			sqr->setColor(Color::white);
		else
			sqr->setColor(color);
		break;
	default:
		break;
	}
}

void DrawArea::changePos(int x, int y)
{
	x_min += x;
	y_min += y;
	x_max += x;
	y_max += y;
}

void DrawArea::render(wxDC & dc)
{
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			switch (m_area[i][j]->getColor())
			{
			case Color::white:
				break;
			case Color::blue:
				dc.SetBrush(wxColor("blue"));
				break;
			case Color::green:
				dc.SetBrush(wxColor("green"));
				break;
			case Color::path:
				dc.SetBrush(wxColor("yellow"));
				break;
			case Color::red:
				dc.SetBrush(wxColor("red"));
				break;
			default:
				break;
			}

			dc.DrawRectangle(i * m_size + x_min, j * m_size + y_min, m_size, m_size);
			dc.SetBrush(wxColor("white"));
		}
	}

}

void DrawArea::paintNow()
{
	wxClientDC cdc(m_parent);
	wxBufferedDC dc(&cdc);
	dc.Clear();
	render(dc);
}