#include "MainWindow.h"

BEGIN_EVENT_TABLE(MainWindow, wxFrame)
    EVT_MENU(wxID_EXIT,  MainWindow::OnExit)
END_EVENT_TABLE()

MainWindow::MainWindow()
    :wxFrame(NULL, wxID_ANY, wxT("GBEmu"), wxPoint(50, 50), wxSize(450, 340))
{
    wxMenuBar *menuBar = new wxMenuBar;
    wxMenu *fileMenu = new wxMenu;
    fileMenu->Append(wxID_EXIT);


    menuBar->Append(fileMenu, wxT("&File"));
    SetMenuBar(menuBar);
}

void MainWindow::OnExit(wxCommandEvent &e){
    Close(true);
}
