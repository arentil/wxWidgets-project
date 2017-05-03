#include "DrawArea.h"
#include <wx/dcbuffer.h>
#include <cmath>

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
	m_zoom = 1;

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
	if (x_res.quot < 0 || y_res.quot < 0 || x_res.quot >= m_width || y_res.quot >= m_height)
		return nullptr;
	else
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


	float fmat[3][3] = {
		{ 1, 0, x },
		{ 0, 1, y },
		{ 0, 0, 1 }
	};
	Matrix2D mat(fmat);
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			Vector2D vec(m_area[i][j]->getPos()[0], m_area[i][j]->getPos()[1]);
			vec = mat * vec;
			m_area[i][j]->setPos(vec);
		}
	}
}

void DrawArea::setScale(float scale)
{
	float fmat[3][3] = {
		{ m_zoom + scale, 0, 0 },
		{ 0, m_zoom + scale, 0 },
		{ 0, 0, 1 }
	};
	Matrix2D mat(fmat);

	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			Vector2D vec(m_area[i][j]->getPos()[0], m_area[i][j]->getPos()[1]);
			vec = mat * vec;
			m_area[i][j]->setPos(vec);
		}
	}

	m_size = m_area[1][1]->getPos()[1] - m_area[0][0]->getPos()[1];
	x_min = m_area[0][0]->getPos()[0];
	y_min = m_area[0][0]->getPos()[1];
	x_max = m_area[m_width - 1][m_height - 1]->getPos()[0] + m_size;
	y_max = m_area[m_width - 1][m_height - 1]->getPos()[1] + m_size;
	
	paintNow();
}

float DrawArea::getScale()
{
	return m_zoom;
}

void DrawArea::render(wxDC & dc)
{
	//dc.DrawRectangle(x_min, y_min, x_max - x_min, y_max - y_min);
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
			Vector2D vec = m_area[i][j]->getPos();
			dc.DrawRectangle(vec[0], vec[1], m_size, m_size);
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