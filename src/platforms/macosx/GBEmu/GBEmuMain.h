/***************************************************************
 * Name:      GBEmuMain.h
 * Purpose:   Defines Application Frame
 * Author:    Dan ()
 * Created:   2013-08-10
 * Copyright: Dan ()
 * License:
 **************************************************************/

#ifndef GBEMUMAIN_H
#define GBEMUMAIN_H

//(*Headers(GBEmuFrame)
#include <wx/menu.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class GBEmuFrame: public wxFrame
{
    public:

        GBEmuFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~GBEmuFrame();

    private:

        //(*Handlers(GBEmuFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        //*)

        //(*Identifiers(GBEmuFrame)
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(GBEmuFrame)
        wxStatusBar* StatusBar1;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // GBEMUMAIN_H
