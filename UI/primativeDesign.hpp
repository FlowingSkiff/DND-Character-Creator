#pragma once
#include "baseProject.h"

class TmpDisplay: public MyFrame1
{
    protected:
        virtual void ReloadHtmlDescription(wxCommandEvent& event)
        {
            event.Skip();
        }
    public:
        TmpDisplay(): MyFrame1(nullptr) { }
};