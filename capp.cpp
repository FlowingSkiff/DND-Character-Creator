#include "capp.hpp"
#include "primativeDesign.hpp"
wxIMPLEMENT_APP(cApp);

cApp::cApp()
{

}

cApp::~cApp()
{

}

bool cApp::OnInit()
{
    auto* tmp = new TmpDisplay();
    tmp->Show(true);
    return true;
}