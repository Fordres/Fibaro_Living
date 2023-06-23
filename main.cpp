// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "wx/defs.h"

#include "MainFrame.hpp"
#include <wx/app.h>
#include <wx/event.h>
#include <wx/image.h>
#include <wx/mdi.h>
#include <iostream> 
#include <wx/mousestate.h>
#include <wx/popupwin.h>
#include <wx/statline.h>

#include "wx/sizer.h"
#include "wx/log.h"
#include "wx/tglbtn.h"
#include "popupscherm.hpp"
#include <wx/slider.h>
#include "wx/panel.h"
#include <wx/time.h>




#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "sample.xpm"
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

enum
    {
		 POINTMAINX = 300, 
		 POINTMAINY = 350, 
		 SIZEMAINX = 960,
		 SIZEMAINY = 600,
		 // WIDTH is dubbel van het scherm - de randen 
        // Height is de hoogte min de randen 
        WIDTH = 1920,
        HEIGHT = 578,
        EENL = 5, // Beginwaarde x van eerste scherm
        EENR = 955, 
        TWEEL = 975, // Beginwaarde x van tweede scherm
        TWEER = 1925, 
        BODEM = 563 // Onderste y waarde
    };

using namespace std;

class MyPopupScreen : public wxPopupWindow
//class MyPopupScreen : public wxPanel

{
private:
	 DECLARE_EVENT_TABLE();
     
     wxImage myBitmapPopup1, myBitmapPopup2;  
    
public: 
    int itemPu;
    // Defeinitie methodes
	 // Def
     MyPopupScreen(wxWindow *parent, int item);
	 void CreateLampControls(int item);
	 // Schermen voor de popup vensters 
	 void OnPaint(wxPaintEvent& WXUNUSED(event))
    {
        wxPaintDC dcPu(this); 
        PrepareDC(dcPu);
        if (itemPu == 1) {  // Randverlichting
            myBitmapPopup1 = wxImage("./Popup1.gif",  wxBITMAP_TYPE_GIF);
            dcPu.DrawBitmap(myBitmapPopup1, 0, 0, true);
        }
        else if (itemPu == 2) { // Salon
            myBitmapPopup2 = wxImage("./Popup2.gif",  wxBITMAP_TYPE_GIF);
            dcPu.DrawBitmap(myBitmapPopup2, 0, 0, true);
        }
        
    }
};

//MyPopScreen constructor test
MyPopupScreen::MyPopupScreen(wxWindow *parent, int item )
{
         SetBackgroundStyle(wxBG_STYLE_SYSTEM );
		 //this->Create(parent, wxTRANSPARENT_WINDOW |wxBORDER_NONE); 
		   //this->SetBackgroundColour(*wxBLUE);
         // this->SetForegroundColour(*wxBLUE);
         //this->SetForegroundColour(wxTransparentColour);
         this->Create(parent, wxTRANSPARENT_WINDOW |wxBORDER_NONE); 
         this->SetBackgroundColour(wxTransparentColour); 
			
         if (item == 1) //Randverlichting
         {
             itemPu = item; 
             this->Position(wxPoint((POINTMAINX + 700),(POINTMAINY+300)), wxSize(0,0));
         }
         else if (item == 2) // Salon
         {
             itemPu = item;
             this->Position(wxPoint((POINTMAINX + 500),(POINTMAINY+200)), wxSize(0,0));
         }
		 this->SetSize(175,250); 
		 CreateLampControls(item);
		 
}

//Method to create buttons on MyPopupSccreen
void MyPopupScreen::CreateLampControls(int item)
{
    
	wxImage myBitmapKnopOnBlue = wxImage("./knop_on_off_on.gif",  wxBITMAP_TYPE_GIF);
	wxImage myBitmapKnopOffBlue = wxImage("./knop_on_off_off.gif",  wxBITMAP_TYPE_GIF);
    
	wxButton *lampen = new wxButton(this, 35, wxEmptyString, wxPoint(35, 100), wxSize(100,25), wxTRANSPARENT_WINDOW |wxBORDER_NONE);
	lampen->SetBitmap(myBitmapKnopOnBlue);
    wxSlider *dimmer = new wxSlider(this, wxID_ANY, 100, 0, 100, wxPoint(10, 200), wxSize(130,10), wxSL_HORIZONTAL,wxDefaultValidator,wxT("test")); 
	
}	


class MySimpleCanvas : public wxScrolled<wxWindow>
{
public:
	int x1, x2, y1, y2;
	bool statusLampTerras, statusLampSalon, statusLampRand = false; 
	wxLongLong klickTime, oldKlickTime; 
	wxImage myBitmap2 = wxImage("./Living.gif", wxBITMAP_TYPE_GIF);
	wxImage myBitmapDoorClosed = wxImage("./Door_Closed.gif",  wxBITMAP_TYPE_GIF);
	wxImage myBitmapDoorOpen = wxImage("./Door_Open.gif",  wxBITMAP_TYPE_GIF);
	wxImage myBitmapLampAan = wxImage("./lamp_aan.gif",  wxBITMAP_TYPE_GIF);
	wxImage myBitmapLampUit = wxImage("./lamp_uit.gif",  wxBITMAP_TYPE_GIF);
	wxButton *doorLuc = new wxButton(this, 31, wxEmptyString, wxPoint(425,55), wxSize(25,25), wxTRANSPARENT_WINDOW |wxBORDER_NONE);
	wxButton *doorGarage = new wxButton(this, 32, wxEmptyString, wxPoint(550,55), wxSize(25,25), wxTRANSPARENT_WINDOW |wxBORDER_NONE);
	wxButton *doorTerras = new wxButton(this, 33, wxEmptyString, wxPoint(245,147), wxSize(25,25), wxTRANSPARENT_WINDOW |wxBORDER_NONE);
	wxButton *lampTerras = new wxButton(this, 34, wxEmptyString, wxPoint(310,125), wxSize(50,53), wxTRANSPARENT_WINDOW |wxBORDER_NONE);
	wxButton *lampSalon = new wxButton(this, 35, wxEmptyString, wxPoint(480,225), wxSize(50,53), wxTRANSPARENT_WINDOW |wxBORDER_NONE);
	// wxButton *lampRandverlichting = new wxButton(this, 36, wxEmptyString, wxPoint(500,375), wxSize(50,53), wxTRANSPARENT_WINDOW |wxBORDER_NONE);
    wxPopupWindow *popup1 = new MyPopupScreen(this, 1);  
    wxPopupWindow *popup2 = new MyPopupScreen(this, 2);
    

    //Constructor - design van het volledige linker en rechter scherm 
    MySimpleCanvas(wxWindow *parent)
        : wxScrolled<wxWindow>(parent, wxID_ANY, wxPoint(0,0), wxDefaultSize, wxHSCROLL, wxT("scrolledWindow"))
    {
        oldKlickTime = wxGetUTCTimeMillis(); 
		 SetScrollRate( 1, 1 );
        SetVirtualSize( WIDTH, HEIGHT );
		  SetBackgroundColour( *wxBLUE );
        
        wxButton* nextKnop = new wxButton(this, 5, wxT("Next"), wxPoint((EENR - 105),(BODEM - 30)), wxSize(100,25), 0, 
            wxDefaultValidator, wxT("Next"));
        wxButton* backKnop = new wxButton(this, 10, wxT("Previous"), wxPoint((TWEER - 113),(BODEM - 30)), wxSize(100,25), 0, 
            wxDefaultValidator, wxT("Previous"));
		  
		  StatusDeur(doorLuc, false); 
		  StatusDeur(doorGarage, false);
		  StatusDeur(doorTerras, false); 
		  StatusLamp(lampTerras, false); 
		  StatusLamp(lampSalon, false); 
		  // StatusLamp(lampRandverlichting, true); 
    }

private:
    DECLARE_EVENT_TABLE();
	 
	 void onMouseDown(wxMouseEvent & evt)
	 {
		 // CaptureMouse();
			x1= evt.GetX();
			y1 = evt.GetY(); 
			klickTime = wxGetUTCTimeMillis();
			
		 if (evt.LeftDClick())
		 {
			 cout << " Dubbel klick" << endl;
		 }
		 else if (evt.LeftDown() and not evt.LeftDClick())
		 {
			 
			 cout << "Oldklicktime " << oldKlickTime << endl; 
			 if (klickTime >= (oldKlickTime + 500)) 
			 {
				cout << " één klik  met uitvoering " << " klicktime " << klickTime << endl;
				oldKlickTime = klickTime; 
			 }
			 else
			 {
				oldKlickTime = klickTime; 
				cout << "Doe niets" << endl;
			 } 
		 }
		 
		 
		 // ReleaseMouse();
	 }
    
	 void onMouseUp(wxMouseEvent & evt)
	 {
		 CaptureMouse(); 
		 x2= evt.GetX();
		 y2= evt.GetY();
		 ReleaseMouse(); 
		if (x1 > x2) 
			{
				this->Scroll(0,0); 
			}
		if (x1 < x2)
			{
				this->Scroll(1000,0); 
			}
	 }
	 
    void VolgendScherm(wxCommandEvent & event)
    {
        this->Scroll (1000, 0);
		  //popup->Position(wxPoint(200,200), wxSize(300,200));
		  //popup->SetBackgroundColour(*wxWHITE);
		  popup1->Show(true);
		  popup2->Show(false); 
		  
    }
    
    void VorigScherm(wxCommandEvent & event)
    { 
        this->Scroll (0, 0);
        popup1->Show(false);
        popup2->Show(true); 
    }
    
    void OnPaint(wxPaintEvent& WXUNUSED(event))
    {
        wxPaintDC dc(this);

        // this call is vital: it adjusts the dc to account for the current
        // scroll offset
        PrepareDC(dc);

        wxPen mijnPen = wxPen(wxColour(200,200,200), 10, wxPENSTYLE_SOLID);
        dc.SetPen( mijnPen);
        dc.SetBrush( *wxBLUE_BRUSH );
        dc.DrawRectangle( 0, 0, (WIDTH / 2), (HEIGHT-10));
        dc.DrawRectangle( (WIDTH/2), 0, (WIDTH /2 + 2), (HEIGHT-10));
        dc.DrawBitmap(myBitmap2, 0, 20, true);
		  dc.DrawBitmap(myBitmapLampUit, 500, 375, true); 
  
    }
	 void StatusDeur(wxButton *deur, bool open)
	 {
		if (open) 
		{
			deur->SetBitmap(myBitmapDoorOpen);
		}
		else 
		{
			deur->SetBitmap(myBitmapDoorClosed);
		}
	 }
	 
	 
	 void StatusLamp(wxButton *lamp, bool aan)
	 {
		if (aan) 
		{
			lamp->SetBitmap(myBitmapLampAan);
		}
		else 
		{
			lamp->SetBitmap(myBitmapLampUit);
		}
	 }
	 
	 void ToggleLampTerras(wxCommandEvent & event)
	 {
		 if (statusLampTerras) 
		 {
			 statusLampTerras = false;
		 }
		 else 
		 {
			 statusLampTerras = true; 
		 }
		 StatusLamp(lampTerras, statusLampTerras);
	 }
	 
	 void ToggleLampSalon(wxCommandEvent & event)
	 {
		 if (statusLampSalon) 
		 {
			 statusLampSalon = false;
		 }
		 else 
		 {
			 statusLampSalon = true; 
		 }
		 StatusLamp(lampSalon, statusLampSalon);
	 }
	 
	 void ToggleLampRand(wxCommandEvent & event)
	 {
		 if (statusLampRand) 
		 {
			 statusLampRand = false;
		 }
		 else 
		 {
			 statusLampRand = true; 
		 }
		 // StatusLamp(lampRandverlichting, statusLampRand);
	 }
	 
};
BEGIN_EVENT_TABLE(MySimpleCanvas, wxScrolled)
	 EVT_PAINT(MySimpleCanvas::OnPaint)
    EVT_BUTTON(5, MySimpleCanvas::VolgendScherm)
    EVT_BUTTON(10, MySimpleCanvas::VorigScherm)
	 EVT_MOUSE_EVENTS(MySimpleCanvas::onMouseDown)
	 EVT_LEFT_UP(MySimpleCanvas::onMouseUp)
	 EVT_BUTTON(34, MySimpleCanvas::ToggleLampTerras)
	 EVT_BUTTON(35, MySimpleCanvas::ToggleLampSalon)
	 // EVT_BUTTON(36, MySimpleCanvas::ToggleLampRand)
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(MyPopupScreen, wxPopupWindow)
	 EVT_PAINT(MyPopupScreen::OnPaint)
END_EVENT_TABLE()

// create the frame class

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
};

//MyFrame constructor
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
    : wxFrame(NULL, wxID_ANY, title, pos, size, wxMINIMIZE_BOX | 
                                                wxCLOSE_BOX |
                                                wxCLIP_CHILDREN) {
    
	 SetBackgroundColour(*wxBLUE);
	 SetMaxClientSize(size);
	 wxWindow *wxSC = new MySimpleCanvas(this);
	 // Show();
}
 

     
// start program
class MainApp : public wxApp
{
public:
    MainApp() {}
	 
    virtual ~MainApp() {}

    virtual bool OnInit()
    {
		wxInitAllImageHandlers();
		wxFrame *frame = new MyFrame("Living", wxPoint(POINTMAINX, POINTMAINY), wxSize(SIZEMAINX, SIZEMAINY)); 
		frame->Show(true);
		return true;
        
    }
};

DECLARE_APP(MainApp)
IMPLEMENT_APP(MainApp)
