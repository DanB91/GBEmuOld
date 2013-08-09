#include "GBEmuGUIMainWindow.h"
#include "../GBEmuExceptions.h"
#include <wx/msgdlg.h>

GBEmuGUIMainWindow::GBEmuGUIMainWindow( wxWindow* parent )
    :
        MainWindow( parent )
{

}

static void showError(wxFrame *parent, const char* error);

void GBEmuGUIMainWindow::OpenROM( wxCommandEvent& event){
    wxString fn = wxFileSelector(wxT("Choose ROM"));

    if(!fn.IsEmpty()){

        try{
            gb = GBEmu::GameBoyPtr(new GBEmu::GameBoy((const char *)fn.ToAscii()));
        } 
        catch(GBEmu::GBEmuException &e){
            showError(this,e.what()); 
        }
    }
}

void GBEmuGUIMainWindow::OnExit( wxCommandEvent& event )
{
    Close(true);
}

void GBEmuGUIMainWindow::UpdateCPUStatus( wxUpdateUIEvent& event )
{
    try{
        if(gb){
            wxString output = wxT("Registers: \n");
            output << wxT("A: ") << wxString::Format(_T("%x"),gb->getCPUState().registers.A) << wxT("\t\t");
            output << wxT(" B: ") << wxString::Format(_T("%x"),gb->getCPUState().registers.B) << wxT("\t\t");
            output << wxT(" C: ") << wxString::Format(_T("%x"),gb->getCPUState().registers.C) << wxT("\t\t");
            output << wxT(" D: ") << wxString::Format(_T("%x"),gb->getCPUState().registers.D) << wxT("\t\t");
            output << wxT(" F: ") << wxString::Format(_T("%x"),gb->getCPUState().registers.F) << wxT("\t\t");
            output << wxT(" H: ") << wxString::Format(_T("%x"),gb->getCPUState().registers.H) << wxT("\t\t\n");
            output << wxT("L: ") << wxString::Format(_T("%x"),gb->getCPUState().registers.L) << wxT("\t\t");
            output << wxT(" PC: ") << wxString::Format(_T("%x"),gb->getCPUState().registers.PC) << wxT("\t\t");
            output << wxT(" SP: ") << wxString::Format(_T("%x"),gb->getCPUState().registers.SP) << wxT("\t\t");

            cpuStatus->SetLabel(output);

            gb->step();
        }
    }
    catch(std::exception &e){
        showError(this, e.what());
    }



}


static void showError(wxFrame *parent, const char *msg){

    wxMessageDialog(parent, 
            wxString::FromAscii(msg),
            wxT("Error"),
            wxOK | wxCENTRE | wxICON_ERROR,
            wxDefaultPosition
            ).ShowModal();
}
