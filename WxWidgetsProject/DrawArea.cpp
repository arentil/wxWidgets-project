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
	x_res = div((x - x_min), m_size);
	y_res = div((y - y_min), m_size);
	if (x_res.quot < 0 || y_res.quot < 0 || x_res.quot >= m_width || y_res.quot >= m_height || x < x_min || y < y_min)
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
	if (m_size < 10 && scale < 0)
		return;
	if (scale > 0)
		m_size += 3;
	else if (scale < 0)
		m_size -= 3;

	float fmat[3][3] = {
		{ m_zoom + scale, 0, 0 },
		{ 0, m_zoom + scale, 0 },
		{ 0, 0, 1 }
	};
	Matrix2D mat(fmat);
	Vector2D vec(m_area[0][0]->getPos()[0], m_area[0][0]->getPos()[1]);
	vec = mat * vec;
	m_area[0][0]->setPos(vec);

	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			if (i == 0 && j == 0)
				continue;
			Vector2D vect(vec[0] + (i * m_size), vec[1] + (j * m_size));
			m_area[i][j]->setPos(vect);
		}
	}

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

void DrawArea::setPanelSize(wxSize * panelSize)
{
	m_panelSize = panelSize;
}

void DrawArea::computeAreaToDraw()
{
	int i_min = 0;
	int j_min = 0;
	int i_max = m_width;
	int j_max = m_height;
	Square * sqr_lup = getSquare(1, 1);	//left upper corner square
	Square * sqr_rdown = getSquare(m_panelSize->x - 1, m_panelSize->y - 1); //right lower corner square
	if (sqr_lup != nullptr && sqr_lup->getPos()[0] >= 0 && sqr_lup->getPos()[1] >= 0)
	{
		i_min = sqr_lup->getPos()[0];
		j_min = sqr_lup->getPos()[1];
	}
	if (sqr_rdown != nullptr && sqr_rdown->getPos()[0] <= i_max && sqr_rdown->getPos()[1] <= j_max)
	{
		i_max = sqr_rdown->getPos()[0];
		j_max = sqr_rdown->getPos()[1];
	}
	toDraw.clear();
	for (int i = i_min; i < i_max; i++)
	{
		for (int j = j_min; j < j_max; j++)
		{
			if (m_area[i][j]->getPos()[0] < 0 - m_size || m_area[i][j]->getPos()[1] < 0 - m_size ||
				m_area[i][j]->getPos()[0] > m_panelSize->x + m_size || m_area[i][j]->getPos()[1] > m_panelSize->y + m_size)
				continue;
			toDraw.push_back(m_area[i][j]);
		}
	}
}

void DrawArea::render(wxDC & dc)
{
	computeAreaToDraw(); 
	//dc.SetBrush(wxColor("green"));
	//dc.DrawRectangle(x_min, y_min, x_max - x_min, y_max - y_min);
	for (std::list<Square *>::iterator it = toDraw.begin(); it != toDraw.end(); ++it)
	{
		switch ((*it)->getColor())
		{
		case Color::white:
			dc.SetBrush(wxColor("white"));
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
		Vector2D vec =(*it)->getPos();
		dc.DrawRectangle(vec[0], vec[1], m_size, m_size);
		dc.SetBrush(wxColor("white"));
	}
}

void DrawArea::paintNow()
{
	wxClientDC cdc(m_parent);
	wxBufferedDC dc(&cdc);
	dc.Clear();
	render(dc);
}

void DrawArea::deleteArea()
{
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			delete m_area[i][j];
			m_area[i][j] = nullptr;
		}
	}
}