#include "LeftPanel.h"

BEGIN_EVENT_TABLE(LeftPanel, wxPanel)
	EVT_BUTTON((short)BUTTON_ID::BUT_CREATE_ID, LeftPanel::onCreateGrid)
	EVT_BUTTON((short)BUTTON_ID::BUT_RANDOMIZE_ID, LeftPanel::onRandPushed)
	EVT_BUTTON((short)BUTTON_ID::BUT_SEARCH_ID, LeftPanel::onSearchPushed)
	EVT_BUTTON((short)BUTTON_ID::BUT_CLEARPATH_ID, LeftPanel::onClearPathPushed)
	EVT_BUTTON((short)BUTTON_ID::BUT_CLEARWALLS_ID, LeftPanel::onClearWallsPushed)
	EVT_CHECKBOX((short)CHECKBOX_ID::CBOX_SHOWFUNCVAL, LeftPanel::onShowFuncValMarked)
	EVT_CHECKBOX((short)CHECKBOX_ID::CBOX_ALLOWDIAG, LeftPanel::onAllowDiagMarked)
	EVT_CHECKBOX((short)CHECKBOX_ID::CBOX_COMPAREWITHDIJKSTA, LeftPanel::onCompareWithDijkstra)
	EVT_CHECKBOX((short)CHECKBOX_ID::CBOX_COMPAREWITHBELLMANFORD, LeftPanel::onCompareWithBellmanFord)
	EVT_RADIOBOX(250, LeftPanel::onHeuristicChange)
	EVT_RADIOBOX(249, LeftPanel::onColorChange)
END_EVENT_TABLE()


LeftPanel::LeftPanel(wxFrame * frameParent, wxPanel * parent, RightPanel * rightPanel, wxWindowID winid, wxPoint point, wxSize size, const wxString & sizertext) : wxPanel(parent, winid, point, size)
{
	m_rightPanel = rightPanel;
	m_frameParent = frameParent;
	m_parent = parent;
	wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer * sbox1 = new wxStaticBoxSizer(wxVERTICAL, this, sizertext);


	wxStaticBoxSizer * sizerCreate1 = new wxStaticBoxSizer(wxVERTICAL, this, "Create grid:");
	wxBoxSizer * sizerCreate2 = new wxBoxSizer(wxHORIZONTAL);
	m_create = new wxButton(this, (short)BUTTON_ID::BUT_CREATE_ID, "Create");
	sizerCreate1->Add(sizerCreate2);
	sbox1->Add(sizerCreate1);

	//RANDOMIZE AND GENERATE LABYRINTH
	wxStaticBoxSizer * randGen = new wxStaticBoxSizer(wxVERTICAL, this, "Randomize:");
	randomize = new wxButton(this, (short)BUTTON_ID::BUT_RANDOMIZE_ID, "Randomize");
	randGen->Add(randomize);
	sbox1->Add(randGen, 0, wxEXPAND | wxLEFT);
	//--------

	//SQUARE SIZE AND ZOOM PERCENTAGE
	wxStaticBoxSizer * sizeAndZoom = new wxStaticBoxSizer(wxVERTICAL, this);
	wxStaticText * sizeText = new wxStaticText(this, wxID_ANY, "Square size:");
	sizeSpin = new wxSpinCtrlDouble(this);
	wxStaticText * zoom = new wxStaticText(this, wxID_ANY, "Zoom:");
	zoomSpin = new wxSpinCtrlDouble(this);
	sizeSpin->SetRange(10, 50);
	zoomSpin->SetRange(1, 20);
	zoomSpin->SetValue(3);
	sizeAndZoom->Add(sizeText);
	sizeAndZoom->Add(sizeSpin);
	sizeAndZoom->Add(zoom);
	sizeAndZoom->Add(zoomSpin);
	sbox1->Add(sizeAndZoom, 0, wxEXPAND | wxLEFT);
	//--------

	//SELECTED COLOR
	wxArrayString col_array;
	col_array.Add(wxT("Walls( F1 )"));
	col_array.Add(wxT("Start ( F2 )"));
	col_array.Add(wxT("Goal ( F3 )"));
	color = new wxRadioBox(this, 249, "Selected color:", wxDefaultPosition, wxSize(200, 100), col_array, 3, wxRA_SPECIFY_ROWS);
	sbox1->Add(color);
	//--------

	//CREATE GRID
	m_rows = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(0, 0), wxSize(87, 25));
	m_cols = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(0, 0), wxSize(87, 25));
	sizerCreate2->Add(m_rows);
	sizerCreate2->Add(new wxStaticText(this, wxID_ANY, "x"));
	sizerCreate2->Add(m_cols);
	sizerCreate1->Add(m_create, 1, wxALIGN_CENTER, 4);
	//--------

	//HEURISTIC CHOISE
	wxArrayString h_array;
	h_array.Add(wxT("Manhattan"));
	h_array.Add(wxT("Diagonal"));
	h_array.Add(wxT("Euclidean"));
	heuristic = new wxRadioBox(this, 250, "Heuristic:", wxDefaultPosition, wxSize(200, 100), h_array, 1, wxRA_SPECIFY_COLS);
	sbox1->Add(heuristic);
	//--------

	//OPTIONS
	wxStaticBoxSizer * options = new wxStaticBoxSizer(wxVERTICAL, this, "Options:");
	diagonal = new wxCheckBox(this, (short)CHECKBOX_ID::CBOX_ALLOWDIAG, "Allow diagonal", wxDefaultPosition, wxSize(200, 20));
	showFuncs = new wxCheckBox(this, (short)CHECKBOX_ID::CBOX_SHOWFUNCVAL, "Show function values", wxDefaultPosition, wxSize(200, 20));
	compareWithDijkstra = new wxCheckBox(this, (short)CHECKBOX_ID::CBOX_COMPAREWITHDIJKSTA, "Compare with Dijkstra", wxDefaultPosition, wxSize(200, 20));
	compareWithBellmanFord = new wxCheckBox(this, (short)CHECKBOX_ID::CBOX_COMPAREWITHBELLMANFORD, "Compare with Bellman-Ford", wxDefaultPosition, wxSize(200, 20));
	options->Add(diagonal);
	options->Add(showFuncs);
	options->Add(compareWithDijkstra);
	options->Add(compareWithBellmanFord);
	sbox1->Add(options);
	//--------

	//A* BUTTONS
	wxStaticBoxSizer * aStarControl = new wxStaticBoxSizer(wxVERTICAL, this, "A* Algorithm control:");
	search = new wxButton(this, (short)BUTTON_ID::BUT_SEARCH_ID, "Search ( F5 )");
	clearPath = new wxButton(this, (short)BUTTON_ID::BUT_CLEARPATH_ID, "Clear Path");
	clearWalls = new wxButton(this, (short)BUTTON_ID::BUT_CLEARWALLS_ID, "Clear walls");
	aStarControl->Add(search);
	aStarControl->Add(clearPath);
	aStarControl->Add(clearWalls);
	sbox1->Add(aStarControl, 0, wxEXPAND | wxLEFT);
	//--------

	sizer->Add(sbox1, 1, wxEXPAND | wxALL, 0);
	this->SetSizer(sizer);
}

int LeftPanel::getScaleValue()
{
	return zoomSpin->GetValue();
}

void LeftPanel::setSelection(int selection)
{
	color->SetSelection(selection);
	switch (selection)
	{
	case 0:
		m_rightPanel->setColor(Color::grey);
		break;
	case 1:
		m_rightPanel->setColor(Color::green);
		break;
	case 2:
		m_rightPanel->setColor(Color::red);
		break;
	default:
		break;
	}
}

void LeftPanel::execSearch()
{
	m_rightPanel->search();
}

void LeftPanel::onCreateGrid(wxCommandEvent & event)
{
	if (m_rows->GetValue() == wxEmptyString || m_cols->GetValue() == wxEmptyString)
		return;
	int width = wxAtoi(m_rows->GetValue());
	int height = wxAtoi(m_cols->GetValue());
	int size = 10;
	if (sizeSpin->GetValue() != NULL)
		size = sizeSpin->GetValue();
	if (width > 0 && height > 0)
		m_rightPanel->initialize(width, height, sizeSpin->GetValue());

	onAllowDiagMarked(event);
	onShowFuncValMarked(event);
	onHeuristicChange(event);
	onColorChange(event);
	onCompareWithDijkstra(event);
	onCompareWithBellmanFord(event);
}

void LeftPanel::onRandPushed(wxCommandEvent & event)
{
	m_rightPanel->randomize();
}

void LeftPanel::onSearchPushed(wxCommandEvent & event)
{
	m_rightPanel->search();
}

void LeftPanel::onClearPathPushed(wxCommandEvent & event)
{
	m_rightPanel->clearPath();
}

void LeftPanel::onClearWallsPushed(wxCommandEvent & event)
{
	m_rightPanel->clearWalls();
}

void LeftPanel::onAllowDiagMarked(wxCommandEvent & event)
{
	if (diagonal->IsChecked())
	{
		m_rightPanel->allowDiagonal(true);
	}
	else
		m_rightPanel->allowDiagonal(false);
}

void LeftPanel::onShowFuncValMarked(wxCommandEvent & event)
{
	if (showFuncs->IsChecked())
		m_rightPanel->setShowFuncValues(true);
	else
		m_rightPanel->setShowFuncValues(false);
}

void LeftPanel::onHeuristicChange(wxCommandEvent & event)
{
	switch (heuristic->GetSelection())
	{
	case 0:
		m_rightPanel->setHeuristic(Heuristic::MANHATTAN);
		break;
	case 1:
		m_rightPanel->setHeuristic(Heuristic::DIAGONAL);
		break;
	case 2:
		m_rightPanel->setHeuristic(Heuristic::EUCLIDEAN);
		break;
	default:
		break;
	}
}

void LeftPanel::onColorChange(wxCommandEvent & event)
{
	switch (color->GetSelection())
	{
	case 0:
		m_rightPanel->setColor(Color::grey);
		break;
	case 1:
		m_rightPanel->setColor(Color::green);
		break;
	case 2:
		m_rightPanel->setColor(Color::red);
		break;
	default:
		break;
	}
}

void LeftPanel::onCompareWithDijkstra(wxCommandEvent & event)
{
	if (compareWithDijkstra->IsChecked())
		m_rightPanel->setCompareWithDijkstra(true);
	else
		m_rightPanel->setCompareWithDijkstra(false);
}

void LeftPanel::onCompareWithBellmanFord(wxCommandEvent & event)
{
	if (compareWithBellmanFord->IsChecked())
		m_rightPanel->setCompareWithBellmanFord(true);
	else
		m_rightPanel->setCompareWithBellmanFord(false);
}