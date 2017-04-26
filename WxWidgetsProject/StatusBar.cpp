#include "StatusBar.h"

StatusBar::StatusBar(wxFrame * parent) : wxStatusBar(parent, -1)
{
	m_parent = parent;
	this->SetFieldsCount(3);
	int statusTab[] = { 100, 100, -1 };
	this->SetStatusWidths(3, statusTab);
	this->SetStatusText("Point:", 0);
	m_parent->SetStatusBar(this);
}


void StatusBar::SetText(const wxString & text, int field)
{
	this->SetStatusText(text, field);
}