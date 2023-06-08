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
{
private:
	 DECLARE_EVENT_TABLE();	
public:
    MyPopupScreen(wxWindow *parent, const wxPoint &plaats, const wxSize &grootte);
	 void CreateLampControls(wxPoint plaats, wxString titel);
	 
	 void OnPaint(wxPaintEvent& WXUNUSED(event))
    {
        wxPaintDC dcPu(this);

        // this call is vital: it adjusts the dc to account for the current
        // scroll offset
        PrepareDC(dcPu);

        wxBLACK_DASHED_PEN; 
        dcPu.DrawLine(wxPoint(3, 40), wxPoint(147,40));
    }
};

//MyPopScreen constructor
MyPopupScreen::MyPopupScreen(wxWindow *parent, const wxPoint &plaats, const wxSize &grootte)
	//: wxPopupWindow(parent, wxBORDER_MASK )
{
		 SetBackgroundStyle(wxBG_STYLE_SYSTEM );
		 this->Create(parent, wxBORDER_MASK ); 
		 this->SetBackgroundColour(*wxWHITE);
		 this->Position(wxPoint((POINTMAINX + 700),(POINTMAINY+300)), wxSize(0,0));
		 this->SetSize(150,175); 
		 cout << "Plaats "<< plaats.x << ", " << plaats.y << "Grootte " << grootte.x << "," << grootte.y << endl; 
		 CreateLampControls(wxPoint(5,0), wxT("Randverlichting"));
		 
}


//Method to create buttons on MyPopupSccreen
void MyPopupScreen::CreateLampControls(wxPoint plaats, wxString titel)
{

	wxImage myBitmapKnopOnBlue = wxImage("./knop_on_off_on.gif",  wxBITMAP_TYPE_GIF);
	wxImage myBitmapKnopOffBlue = wxImage("./knop_on_off_off.gif",  wxBITMAP_TYPE_GIF);
	
	wxStaticText *popupTitel = new wxStaticText(this, wxID_ANY, titel, wxPoint((plaats.x + 20 ), (plaats.y+10)), wxSize(100,25));
	wxStaticLine *popupLine1 = new wxStaticLine(this, wxID_ANY, wxPoint((plaats.x), (plaats.y + 40)), wxSize(150, 0), wxLI_HORIZONTAL, wxT(" ")); 
	popupLine1->SetForegroundColour(wxColour(0,253,0));
	wxButton *lampen = new wxButton(this, 35, wxEmptyString, wxPoint((plaats.x + 20), (plaats.y+50)), wxSize(100,25), wxTRANSPARENT_WINDOW |wxBORDER_NONE);
	lampen->SetBitmap(myBitmapKnopOnBlue); 
	
}	


class MySimpleCanvas : public wxScrolled<wxWindow>
{
public:
	int x1, x2;
	wxImage myBitmap2 = wxImage("./Living.gif", wxBITMAP_TYPE_GIF);
	wxImage myBitmapDoorClosed = wxImage("./Door_Closed.gif",  wxBITMAP_TYPE_GIF);
	wxImage myBitmapDoorOpen = wxImage("./Door_Open.gif",  wxBITMAP_TYPE_GIF);
	wxButton *doorLuc = new wxButton(this, 31, wxEmptyString, wxPoint(425,55), wxSize(25,25), wxTRANSPARENT_WINDOW |wxBORDER_NONE);
	wxButton *doorGarage = new wxButton(this, 32, wxEmptyString, wxPoint(550,55), wxSize(25,25), wxTRANSPARENT_WINDOW |wxBORDER_NONE);
	wxButton *doorTerras = new wxButton(this, 33, wxEmptyString, wxPoint(245,147), wxSize(25,25), wxTRANSPARENT_WINDOW |wxBORDER_NONE);
	wxPopupWindow *popup = new MyPopupScreen(this, wxPoint((POINTMAINX + 50),(POINTMAINY + 50)), wxSize(50,150));  

    //Constructor - design van het volledige linker en rechter scherm 
    MySimpleCanvas(wxWindow *parent)
        : wxScrolled<wxWindow>(parent, wxID_ANY, wxPoint(0,0), wxDefaultSize, wxHSCROLL, wxT("scrolledWindow"))
    {
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
	
    }

private:
    DECLARE_EVENT_TABLE();
	 
	 void onMouseDown(wxMouseEvent & evt)
	 {
		 CaptureMouse();
		 x1= evt.GetX(); 
		 std::cout << "muis neer " << x1 << std::endl;  
	 }
    
	 void onMouseUp(wxMouseEvent & evt)
	 {
		x2= evt.GetX();  
		ReleaseMouse();  
		std::cout << "muis omhoog " << x2 << std::endl;
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
		  popup->Show(true); 
		  
    }
    
    void VorigScherm(wxCommandEvent & event)
    { 
        this->Scroll (0, 0); 
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
	 
};
BEGIN_EVENT_TABLE(MySimpleCanvas, wxScrolled)
	 EVT_PAINT(MySimpleCanvas::OnPaint)
    EVT_BUTTON(5, MySimpleCanvas::VolgendScherm)
    EVT_BUTTON(10, MySimpleCanvas::VorigScherm)
	 EVT_LEFT_DOWN(MySimpleCanvas::onMouseDown)
	 EVT_LEFT_UP(MySimpleCanvas::onMouseUp)
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
