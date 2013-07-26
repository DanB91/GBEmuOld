#include "MainWindow.h"

class MainApp : public wxApp{
    public:
        virtual bool OnInit();
};



bool MainApp::OnInit(){
    MainWindow *mw = new MainWindow;
    mw->Show();
    return true;
}
IMPLEMENT_APP(MainApp)

