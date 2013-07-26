#include "GBEmuGUIMainWindow.h"

GBEmuGUIMainWindow::GBEmuGUIMainWindow( wxWindow* parent )
:
MainWindow( parent )
{

}

void GBEmuGUIMainWindow::OnExit( wxCommandEvent& event )
{
    Close(true);
}
