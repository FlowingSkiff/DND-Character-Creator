#include <UI/primativeDesign.hpp>

#include <Creator/Base/SQObject.hpp>
#include <Creator/Base/StringTools.hpp>
#include <Creator/DescriptionTools.hpp>

void TmpDisplay::ReloadHtmlDescription(wxCommandEvent& event) 
{
    //m_htmlWin1->SetPage(ProcessHTMLDescription(m_items.at(static_cast<size_t>(m_choice1->GetCurrentSelection()))->description));
    auto& item = m_items.at(static_cast<size_t>(m_choice1->GetCurrentSelection()));
    m_htmlWin1->SetPage(wxString::FromUTF8(Creator::FormatDescription(item->name, item->description, m_item_map)));
    this->GetSizer()->Layout();
    event.Skip();
}

TmpDisplay::TmpDisplay(): MyFrame1(nullptr) 
{ 
    this->Maximize(true);
}