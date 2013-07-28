///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jul 25 2013)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MainWindow.h"

///////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	m_menubar1 = new wxMenuBar( 0 );
	m_menu1 = new wxMenu();
	wxMenuItem* m_menuItem21;
	m_menuItem21 = new wxMenuItem( m_menu1, wxID_ANY, wxString( wxT("Open ROM") ) + wxT('\t') + wxT("Ctrl + O"), wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem21 );
	
	wxMenuItem* m_menuItem2;
	m_menuItem2 = new wxMenuItem( m_menu1, wxID_EXIT, wxString( wxT("Quit") ) , wxEmptyString, wxITEM_NORMAL );
	m_menu1->Append( m_menuItem2 );
	
	m_menubar1->Append( m_menu1, wxT("File") ); 
	
	this->SetMenuBar( m_menubar1 );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	cpuStatus = new wxStaticText( this, wxID_ANY, wxT("CPU Status goes here"), wxDefaultPosition, wxDefaultSize, 0 );
	cpuStatus->Wrap( -1 );
	bSizer1->Add( cpuStatus, 0, wxALL, 5 );
	
	this->SetSizer( bSizer1 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( m_menuItem21->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow::OpenROM ) );
	this->Connect( m_menuItem2->GetId(), wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow::OnExit ) );
	cpuStatus->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainWindow::UpdateCPUStatus ), NULL, this );
}

MainWindow::~MainWindow()
{
	// Disconnect Events
	this->Disconnect( wxID_ANY, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow::OpenROM ) );
	this->Disconnect( wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( MainWindow::OnExit ) );
	cpuStatus->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( MainWindow::UpdateCPUStatus ), NULL, this );
	
}
