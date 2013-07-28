#ifndef __GBEmuGUIMainWindow__
#define __GBEmuGUIMainWindow__

/**
@file
Subclass of MainWindow, which is generated by wxFormBuilder.
*/

#include "../GB/GameBoy.h"
#include "MainWindow.h"
#include <wx/filedlg.h> 

using namespace GBEmu;

//// end generated include

/** Implementing MainWindow */
class GBEmuGUIMainWindow : public MainWindow
{
	protected:
		// Handlers for MainWindow events.
		void OnExit( wxCommandEvent& event );
		void UpdateCPUStatus( wxUpdateUIEvent& event );
        void OpenROM( wxCommandEvent& event );
    public:
		/** Constructor */
		GBEmuGUIMainWindow( wxWindow* parent );
	//// end generated class members
    
    private:
         GameBoyPtr gb;
};

#endif // __GBEmuGUIMainWindow__
