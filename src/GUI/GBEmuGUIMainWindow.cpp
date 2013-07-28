#include "GBEmuGUIMainWindow.h"
#include "../GBEmuExceptions.h"
#include <wx/msgdlg.h>

GBEmuGUIMainWindow::GBEmuGUIMainWindow( wxWindow* parent )
:
MainWindow( parent )
{

}

void GBEmuGUIMainWindow::OpenROM( wxCommandEvent& event){
    wxString fn = wxFileSelector(wxT("Choose ROM"));

    if(!fn.IsEmpty()){
        
        try{
            gb = GBEmu::GameBoyPtr(new GBEmu::GameBoy((const char *)fn.ToAscii()));
        } 
        catch(GBEmu::GBEmuException &e){
            wxMessageDialog(this, 
                    wxString::FromAscii(e.what()),
                    wxT("Error"),
                    wxOK | wxCENTRE | wxICON_ERROR,
                    wxDefaultPosition
                    ).ShowModal();
            
        }
    }
}

void GBEmuGUIMainWindow::OnExit( wxCommandEvent& event )
{
    Close(true);
}

void GBEmuGUIMainWindow::UpdateCPUStatus( wxUpdateUIEvent& event )
{
    if(gb){
        wxString output = wxT("Registers: ");
        output << wxT("A: ") << gb->getCPUState().registers.A;
        output << wxT(" B: ") << gb->getCPUState().registers.B;
        output << wxT(" C: ") << gb->getCPUState().registers.C;
        output << wxT(" D: ") << gb->getCPUState().registers.D;
        output << wxT(" F: ") << gb->getCPUState().registers.F;
        output << wxT(" H: ") << gb->getCPUState().registers.H;
        output << wxT(" L: ") << gb->getCPUState().registers.L;

        cpuStatus->SetLabel(output);
    }


}
