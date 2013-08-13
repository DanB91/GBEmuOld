/***************************************************************
 * Name:      GBEmuApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Dan ()
 * Created:   2013-08-10
 * Copyright: Dan ()
 * License:
 **************************************************************/

#include "GBEmuApp.h"

//(*AppHeaders
#include "GBEmuMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(GBEmuApp);

bool GBEmuApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	GBEmuFrame* Frame = new GBEmuFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
