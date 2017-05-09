#include "LeftPanel.h"

BEGIN_EVENT_TABLE(LeftPanel, wxPanel)
	EVT_BUTTON((short)BUTTON_ID::BUT_CREATE_ID, LeftPanel::onCreateGrid)
	EVT_BUTTON((short)BUTTON_ID::BUT_RANDOMIZE_ID, LeftPanel::onRandPushed)
	EVT_BUTTON((short)BUTTON_ID::BUT_GENERATEL_ID, LeftPanel::onGenPushed)
	EVT_BUTTON((short)BUTTON_ID::BUT_SEARCH_ID, LeftPanel::onSearchPushed)
	EVT_BUTTON((short)BUTTON_ID::BUT_CLEARPATH_ID, LeftPanel::onClearPathPushed)
	EVT_BUTTON((short)BUTTON_ID::BUT_CLEARWALLS_ID, LeftPanel::onClearWallsPushed)
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
	wxStaticBoxSizer * randGen = new wxStaticBoxSizer(wxVERTICAL, this, "Randomize or generate:");
	randomize = new wxButton(this, (short)BUTTON_ID::BUT_RANDOMIZE_ID, "Randomize");
	generateL = new wxButton(this, (short)BUTTON_ID::BUT_GENERATEL_ID, "Generate labyrinth");
	randGen->Add(randomize);
	randGen->Add(generateL);
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
	color = new wxRadioBox(this, wxID_ANY, "Selected color:", wxDefaultPosition, wxSize(200, 100), col_array, 3, wxRA_SPECIFY_ROWS);
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
	wxRadioBox * heuristic = new wxRadioBox(this, wxID_ANY, "Heuristic:", wxDefaultPosition, wxSize(200, 55), h_array, 1, wxRA_SPECIFY_ROWS);
	sbox1->Add(heuristic);
	//--------

	//OPTIONS
	wxStaticBoxSizer * options = new wxStaticBoxSizer(wxVERTICAL, this, "Options:");
	wxCheckBox * diagonal = new wxCheckBox(this, wxID_ANY, "Allow diagonal", wxDefaultPosition, wxSize(200, 30));
	options->Add(diagonal);
	sbox1->Add(options);
	//--------

	//A* BUTTONS
	wxStaticBoxSizer * aStarControl = new wxStaticBoxSizer(wxVERTICAL, this, "A* Algorithm control:");
	search = new wxButton(this, (short)BUTTON_ID::BUT_SEARCH_ID, "Search");
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
}

void LeftPanel::onRandPushed(wxCommandEvent & event)
{
	m_rightPanel->randomize();
}

void LeftPanel::onGenPushed(wxCommandEvent & event)
{

}

void LeftPanel::onSearchPushed(wxCommandEvent & event)
{
	m_rightPanel->search();
}

void LeftPanel::onClearPathPushed(wxCommandEvent & event)
{

}

void LeftPanel::onClearWallsPushed(wxCommandEvent & event)
{
	m_rightPanel->clearWalls();
}