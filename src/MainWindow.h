#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif


class MainWindow : public wxFrame{

    public:
        MainWindow();
        DECLARE_EVENT_TABLE();

    private:
        void OnExit(wxCommandEvent &e);
};




#endif /* MAINWINDOW_H */
