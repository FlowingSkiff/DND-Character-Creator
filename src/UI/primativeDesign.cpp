#include <UI/primativeDesign.hpp>

#include <Creator/Base/SQObject.hpp>
#include <Creator/Base/StringTools.hpp>

static wxString ProcessHTMLDescription(const std::string& str)
{
    return wxT("<!DOCTYPE html><html><body>") + wxString::FromUTF8(ReplaceSpecialInString(str)) + wxT("</body></html>");
}

void TmpDisplay::ReloadHtmlDescription(wxCommandEvent& event) 
{
    m_htmlWin1->SetPage(ProcessHTMLDescription(m_items.at(static_cast<size_t>(m_choice1->GetCurrentSelection()))->description));
    this->GetSizer()->Layout();
    event.Skip();
}

TmpDisplay::TmpDisplay(): MyFrame1(nullptr) 
{ 
    this->Maximize(true);
}