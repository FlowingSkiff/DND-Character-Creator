#pragma once
#include "baseProject.h"
#include <vector>
#include <memory>
namespace Creator::Entity{struct SQObject; }

class TmpDisplay: public MyFrame1
{
    protected:
        virtual void ReloadHtmlDescription(wxCommandEvent& event) override;
    public:
        TmpDisplay();
        std::unordered_map<std::string, std::shared_ptr<Creator::Entity::SQObject>> m_item_map;
        std::vector<std::shared_ptr<Creator::Entity::SQObject>> m_items;
};

