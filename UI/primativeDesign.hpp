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
            m_htmlWin1->SetPage(ProcessHTMLDescription(m_items.at(static_cast<size_t>(m_choice1->GetCurrentSelection()))->description));
            event.Skip();
        }
    public:
        TmpDisplay(): MyFrame1(nullptr) { }
        std::unordered_map<std::string, std::shared_ptr<Creator::Entity::SQObject>> m_item_map;
        std::vector<std::shared_ptr<Creator::Entity::SQObject>> m_items;
};

