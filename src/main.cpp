#include "GUI/GBEmuGUIMainWindow.h"
#include <wx/wx.h>

class MainApp : public wxApp{
    public:
        virtual bool OnInit();
};



bool MainApp::OnInit(){
    GBEmuGUIMainWindow *mw = new GBEmuGUIMainWindow(NULL);
    mw->Show();
    return true;
}
IMPLEMENT_APP(MainApp)

