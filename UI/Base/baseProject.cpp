///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "baseProject.h"

///////////////////////////////////////////////////////////////////////////

MyFrame1::MyFrame1( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->AddGrowableRow( 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_panel1 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel1->SetBackgroundColour( wxColour( 11, 151, 204 ) );

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxHORIZONTAL );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_staticText1 = new wxStaticText( m_panel1, wxID_ANY, wxT("Element Name"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer2->Add( m_staticText1, 0, wxALL, 5 );

	wxArrayString m_choice1Choices;
	m_choice1 = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_choice1Choices, 0 );
	m_choice1->SetSelection( 0 );
	fgSizer2->Add( m_choice1, 1, wxALL, 5 );


	m_panel1->SetSizer( fgSizer2 );
	m_panel1->Layout();
	fgSizer2->Fit( m_panel1 );
	fgSizer1->Add( m_panel1, 1, wxALL, 5 );

	m_panel2 = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_panel2->SetBackgroundColour( wxColour( 37, 100, 122 ) );

	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 1, 0, 0, 0 );
	fgSizer4->AddGrowableCol( 0 );
	fgSizer4->AddGrowableRow( 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

	m_htmlWin1 = new wxHtmlWindow( m_panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_NO_SELECTION|wxHW_SCROLLBAR_AUTO );
	m_htmlWin1->SetMinSize( wxSize( 300,200 ) );

	fgSizer4->Add( m_htmlWin1, 1, wxALL|wxEXPAND, 5 );


	m_panel2->SetSizer( fgSizer4 );
	m_panel2->Layout();
	fgSizer4->Fit( m_panel2 );
	fgSizer1->Add( m_panel2, 2, wxEXPAND | wxALL, 5 );


	this->SetSizer( fgSizer1 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	m_choice1->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame1::ReloadHtmlDescription ), NULL, this );
}

MyFrame1::~MyFrame1()
{
	// Disconnect Events
	m_choice1->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( MyFrame1::ReloadHtmlDescription ), NULL, this );

}
