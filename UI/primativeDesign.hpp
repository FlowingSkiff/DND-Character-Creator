#pragma once
#include "baseProject.h"
#include <vector>
#include <memory>
#include "SQObject.hpp"
#include "StringTools.hpp"
namespace Creator::Entity{struct SQObject; }

static wxString ProcessHTMLDescription(const std::string& str)
{
    return "<!DOCTYPE html><html><body>" + ReplaceSpecialInString(str) + "</body></html>";
}

class TmpDisplay: public MyFrame1
{
    protected:
        virtual void ReloadHtmlDescription(wxCommandEvent& event) wxOVERRIDE
        {
            m_htmlWin1->SetPage(ProcessHTMLDescription(m_objects.at(m_choice1->GetStringSelection().ToStdString())->description));
            event.Skip();
        }
    public:
        TmpDisplay(): MyFrame1(nullptr) { }
        std::unordered_map<std::string, std::shared_ptr<Creator::Entity::SQObject>> m_objects;
};

