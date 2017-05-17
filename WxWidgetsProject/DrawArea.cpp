#include "DrawArea.h"

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
	start = nullptr;
	goal = nullptr;
	m_heuristic = Heuristic::MANHATTAN;
	m_showFuncValues = false;
	m_allowDiagonal = false;

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
	if (x_res.quot < 0 || y_res.quot < 0 || x_res.quot >= m_width || y_res.quot >= m_height || x < x_min || y < y_min)
		return nullptr;
	else
		return m_area[x_res.quot][y_res.quot];
}

void DrawArea::setColor(Square * sqr, Color color)
{
	Color sqrCol = sqr->getColor();
	if (color == Color::green && sqrCol != Color::green)
	{
		if (start != nullptr)
			start->setColor(Color::white);
		start = sqr;
	}
	if (color == Color::red && sqrCol != Color::red)
	{
		if (goal != nullptr)
			goal->setColor(Color::white);
		goal = sqr;
	}
	
	switch (sqrCol)
	{
	case Color::white:
		sqr->setColor(color);
		break;
	case Color::grey:
		if (color == Color::grey)
			sqr->setColor(Color::white);
		else
			sqr->setColor(color);
		break;
	case Color::green:
		if (color == Color::green)
		{
			sqr->setColor(Color::white);
			start = nullptr;
		}
		else
			sqr->setColor(color);
		break;
	case Color::yellow:
		if (color == Color::yellow)
			sqr->setColor(Color::white);
		else
			sqr->setColor(color);
		break;
	case Color::red:
		if (color == Color::red)
		{
			goal = nullptr;
			sqr->setColor(Color::white);
		}
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

void DrawArea::scale(float scale, int scaleVal)
{
	if (m_size < 10 && scale < 0)
		return;
	if (scale > 0)
		m_size += scaleVal;
	else if (scale < 0)
		m_size -= scaleVal;

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

void DrawArea::setShowFuncValues(bool showVals)
{
	m_showFuncValues = showVals;
	paintNow();
}

void DrawArea::setHeuristic(Heuristic h)
{
	m_heuristic = h;
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

void DrawArea::randomize()
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist1((m_width + m_height) * 0.1, m_width + m_height - (m_width + m_height) * 0.1);

	std::vector<Square *> toRand;
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			toRand.push_back(m_area[i][j]);
		}
	}
	std::random_shuffle(toRand.begin(), toRand.end());

	for (int i = dist1(mt) - 1; i >= 0; i--)
	{
		if (toRand[i]->getColor() == Color::white)
			toRand[i]->setColor(Color::grey);
		toRand.pop_back();
	}
	toRand.clear();
	paintNow();
}

int DrawArea::getHeuristic(Square * from, Square * to)
{
	int h = 0;
	div_t fx_res, fy_res, tx_res, ty_res;
	fx_res = div((from->getPos()[0] + 1 - x_min), m_size);
	fy_res = div((from->getPos()[1] + 1 - y_min), m_size);
	tx_res = div((to->getPos()[0] + 1 - x_min), m_size);
	ty_res = div((to->getPos()[1] + 1 - y_min), m_size);
	int xd = abs(fx_res.quot - tx_res.quot);
	int yd = abs(fy_res.quot - ty_res.quot);
	switch (m_heuristic)
	{
	case Heuristic::MANHATTAN:
		h = (10 * (xd + yd));
		break;
	case Heuristic::DIAGONAL:
		if (xd > yd)
			h = ((14 * yd) + (10 * (xd - yd)));
		else
			h = ((14 * xd) + (10 * (yd - xd)));
		break;
	default:
		break;
	}
	from->setH(h);
	return h;
}

void DrawArea::search()
{
	if (start == nullptr || goal == nullptr)
	{
		wxMessageBox(wxT("Set start and goal point first!"));
		return;
	}
	clearPath();		//sprz¹tanie po ewentualnym poprzednim przejœciu

	PriorityQueue open;	
	goal->isGoal = true;
	start->onOpen = true;	//add to open set
	start->onClosed = false;
	start->setParent(nullptr);
	start->setG(0);
	start->setF(getHeuristic(start, goal));
	open.push(start);

	while (!open.empty())
	{
		Square * best = open.top();
		open.pop();
		best->onOpen = false;
		best->onClosed = true;
		best->setColor(Color::cyan);
		if (best->isGoal)
		{
			finalPath(start, goal);
			paintNow();
			return;
		}

		for (int i = 0; i < 8; i++)
		{
			if (!m_allowDiagonal && (i % 2))
				continue;
			Square * neighbor = getNeighbor(best, i);
			if (neighbor == nullptr || neighbor->getColor() == Color::grey || neighbor->onClosed == true)
				continue;

			int tentG = best->getG() + ((i % 2 == 0) ? 10 : 14);

			if (neighbor->onOpen == true && (tentG < neighbor->getG()))
			{
				neighbor->setParent(best);
				neighbor->setG(tentG);
				neighbor->setF(neighbor->getG() + getHeuristic(neighbor, goal));
				open.sortQ();
			}
			if (neighbor->onOpen == false)
			{
				neighbor->setParent(best);
				neighbor->setG(tentG);
				neighbor->setF(neighbor->getG() + getHeuristic(neighbor, goal));
				neighbor->onOpen = true;
				neighbor->setColor(Color::lightgreen);
				open.push(neighbor);
			}
		}
	}
	start->setColor(Color::green);
	paintNow();
	wxMessageBox(wxT("Path not found!"));
}

void DrawArea::finalPath(Square * from, Square * to)
{
	Square * temp = to;
	while ((*temp) != (*from))
	{
		temp = temp->getParent();
		temp->setColor(Color::yellow);
	}
	start->setColor(Color::green);
	goal->setColor(Color::red);
}

Square * DrawArea::getNeighbor(Square * from, int n)
{
	div_t x_res, y_res;
	x_res = div((from->getPos()[0] + 1 - x_min), m_size);
	y_res = div((from->getPos()[1] + 1 - y_min), m_size);
	int x = x_res.quot;
	int y = y_res.quot;
	Square * temp = nullptr;

	switch (n)
	{
	case 0:
		if (x - 1 >= 0)
			temp = m_area[x - 1][y];
		break;
	case 1:
		if (x - 1 >= 0 && y + 1 < m_width)
			temp = m_area[x - 1][y + 1];
		break;
	case 2:
		if (y + 1 < m_width)
			temp = m_area[x][y + 1];
		break;
	case 3:
		if (x + 1 < m_height && y + 1 < m_width)
			temp = m_area[x + 1][y + 1];
		break;
	case 4:
		if (x + 1 < m_height)
			temp = m_area[x + 1][y];
		break;
	case 5:
		if (x + 1 < m_height && y - 1 >= 0)
			temp = m_area[x + 1][y - 1];
		break;
	case 6:
		if (y - 1 >= 0)
			temp = m_area[x][y - 1];
		break;
	case 7:
		if (x - 1 >= 0 && y - 1 >= 0)
			temp = m_area[x - 1][y - 1];
		break;
	}

	return temp;
}

void DrawArea::clearPath()
{
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			Square * temp = m_area[i][j];
			if (temp->getColor() != Color::grey && temp->getColor() != Color::red && temp->getColor() != Color::green)
				temp->setColor(Color::white);
			temp->isGoal = false;
			temp->onClosed = false;
			temp->onOpen = false;
			temp->setF(0);
			temp->setG(0);
			temp->setH(0);
			temp->setParent(nullptr);
		}
	}
	paintNow();
}

void DrawArea::clearWalls()
{
	for (int i = 0; i < m_width; i++)
	{
		for (int j = 0; j < m_height; j++)
		{
			if (m_area[i][j]->getColor() == Color::grey)
				m_area[i][j]->setColor(Color::white);
		}
	}
	paintNow();
}

void DrawArea::render(wxDC & dc)
{
	computeAreaToDraw(); 
	for (std::list<Square *>::iterator it = toDraw.begin(); it != toDraw.end(); ++it)
	{
		switch ((*it)->getColor())
		{
		case Color::white:
			dc.SetBrush(wxColor("white"));
			break;
		case Color::grey:
			dc.SetBrush(wxColor("grey"));
			break;
		case Color::green:
			dc.SetBrush(wxColor("green"));
			break;
		case Color::yellow:
			dc.SetBrush(wxColor(255,255,100));
			break;
		case Color::red:
			dc.SetBrush(wxColor("red"));
			break;
		case Color::lightgreen:
			dc.SetBrush(wxColor(155, 255, 157));
			break;
		case Color::cyan:
			dc.SetBrush(wxColor(100,255,255));
		default:
			break;
		}
		Vector2D vec =(*it)->getPos();
		dc.DrawRectangle(vec[0], vec[1], m_size, m_size);
		if (m_showFuncValues && (*it)->getColor() != Color::grey && (*it)->getColor() != Color::white)
		{
			if (m_size > 35)
			{
				wxString gg = wxString::Format(wxT("%i"), (*it)->getG());
				wxString hh = wxString::Format(wxT("%i"), (*it)->getH());
				wxString ff = wxString::Format(wxT("%i"), (*it)->getF());
				int x = vec[0] + m_size / 2 - 5;
				int y = vec[1] + m_size / 2 - 5;
				dc.DrawText(gg, x, y - 10);
				dc.DrawText(hh, x, y);
				dc.DrawText(ff, x, y + 10);
			}
		}
		dc.SetBrush(wxColor("white"));
	}
}

void DrawArea::paintNow()
{
	wxClientDC cdc(m_parent);
	wxBufferedDC dc(&cdc);
	dc.Clear();
	dc.SetPen(wxColor("grey"));
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

void DrawArea::allowDiagonal(bool allow)
{
	m_allowDiagonal = allow;
}