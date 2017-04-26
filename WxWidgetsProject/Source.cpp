#include "Source.h"
#include "MainFrame.h"
IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	MainFrame * mf = new MainFrame("Frame");
	mf->Show(true);

	return true;
}