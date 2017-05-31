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

enum class CHECKBOX_ID : short
{
	CBOX_ALLOWDIAG = 200,
	CBOX_SHOWFUNCVAL,
	CBOX_COMPAREWITHDIJKSTA,
	CBOX_COMPAREWITHBELLMANFORD
};

class LeftPanel : public wxPanel
{
public:
	LeftPanel(wxFrame * frameParent, wxPanel * parent, RightPanel * rightPanel, wxWindowID winid, wxPoint point, wxSize size, const wxString & sizertext);
	int getScaleValue();
	void setSelection(int selection);
	void execSearch();

	void onCreateGrid(wxCommandEvent & event);
	void onRandPushed(wxCommandEvent & event);
	void onGenPushed(wxCommandEvent & event);
	void onSearchPushed(wxCommandEvent & event);
	void onClearPathPushed(wxCommandEvent & event);
	void onClearWallsPushed(wxCommandEvent & event);
	void onAllowDiagMarked(wxCommandEvent & event);
	void onShowFuncValMarked(wxCommandEvent & event);
	void onHeuristicChange(wxCommandEvent & event);
	void onColorChange(wxCommandEvent & event);
	void onCompareWithDijkstra(wxCommandEvent & event);
	void onCompareWithBellmanFord(wxCommandEvent & event);

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
	//------

	//HEURISTIC
	wxRadioBox * heuristic;
	//------

	//OPTIONS
	wxCheckBox * diagonal;
	wxCheckBox * showFuncs;
	wxCheckBox * compareWithDijkstra;
	wxCheckBox * compareWithBellmanFord;
	//------

	//A* BUTTONS
	wxButton * search;
	wxButton * clearPath;
	wxButton * clearWalls;
	//------

	DECLARE_EVENT_TABLE()
};