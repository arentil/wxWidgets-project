#pragma once

#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "RightPanel.h"

enum class BUTTON_ID : short
{
	BUT_CREATE_ID = 100,
	BUT_RANDOMIZE_ID,
	BUT_GENERATEL_ID,
	BUT_SEARCH_ID,
	BUT_CLEARPATH_ID,
	BUT_CLEARWALLS_ID
};

class LeftPanel : public wxPanel
{
public:
	LeftPanel(wxFrame * frameParent, wxPanel * parent, RightPanel * rightPanel, wxWindowID winid, wxPoint point, wxSize size, const wxString & sizertext);
	int getScaleValue();

	void setSelection(int selection);
	void onCreateGrid(wxCommandEvent & event);
	void onRandPushed(wxCommandEvent & event);
	void onGenPushed(wxCommandEvent & event);
	void onSearchPushed(wxCommandEvent & event);
	void onClearPathPushed(wxCommandEvent & event);
	void onClearWallsPushed(wxCommandEvent & event);

private:
	wxFrame * m_frameParent;
	wxPanel * m_parent;
	RightPanel * m_rightPanel;

	//SIZE AND ZOOM INDICATORS
	wxSpinCtrlDouble * sizeSpin;
	wxSpinCtrlDouble * zoomSpin;
	//------

	//CREATE BUTTON AND LABELS
	wxButton * m_create;
	wxTextCtrl * m_rows;
	wxTextCtrl * m_cols;
	//------

	//COLOR CHOOSE
	wxRadioBox * color;
	//------

	//RANDOMIZE AND GENERATE LABYRINTH
	wxButton * randomize;
	wxButton * generateL;
	//------

	//A* BUTTONS
	wxButton * search;
	wxButton * clearPath;
	wxButton * clearWalls;
	//------

	DECLARE_EVENT_TABLE()
};
