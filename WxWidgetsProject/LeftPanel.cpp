#include "LeftPanel.h"

BEGIN_EVENT_TABLE(LeftPanel, wxPanel)
	EVT_BUTTON(wxID_ANY, LeftPanel::onCreateGrid)
END_EVENT_TABLE()


LeftPanel::LeftPanel(wxFrame * frameParent, wxPanel * parent, RightPanel * rightPanel, wxWindowID winid, wxPoint point, wxSize size, const wxString & sizertext) : wxPanel(parent, winid, point, size)
{
	m_rightPanel = rightPanel;
	m_frameParent = frameParent;
	m_parent = parent;
	wxBoxSizer * sizer = new wxBoxSizer(wxVERTICAL);
	wxStaticBoxSizer * sbox1 = new wxStaticBoxSizer(wxVERTICAL, this, sizertext);


	wxStaticBoxSizer * sizerCreate1 = new wxStaticBoxSizer(wxVERTICAL, this, "Create grid");
	wxBoxSizer * sizerCreate2 = new wxBoxSizer(wxHORIZONTAL);
	m_create = new wxButton(this, wxID_ANY, "Create");
	sizerCreate1->Add(sizerCreate2);
	sbox1->Add(sizerCreate1);

	m_rows = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(0, 0), wxSize(87, 20));
	m_cols = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxPoint(0, 0), wxSize(87, 20));
	sizerCreate2->Add(m_rows);
	sizerCreate2->Add(new wxStaticText(this, wxID_ANY, "x"));
	sizerCreate2->Add(m_cols);
	sizerCreate1->Add(m_create, 1, wxALIGN_CENTER);


	sizer->Add(sbox1, 1, wxEXPAND | wxALL, 0);
	this->SetSizer(sizer);
}

void LeftPanel::onCreateGrid(wxCommandEvent & event)
{
	if (m_rows->GetValue() == wxEmptyString || m_cols->GetValue() == wxEmptyString)
		return;
	int width = wxAtoi(m_rows->GetValue());
	int height = wxAtoi(m_cols->GetValue());
	if (width > 0 && height > 0)
		m_rightPanel->initialize(width, height, 20);
}