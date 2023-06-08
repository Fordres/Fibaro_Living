// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"
#include "wx/defs.h"
#include "MainFrame.hpp"
#include <wx/app.h>
#include <wx/event.h>
#include <wx/image.h>
#include <wx/mdi.h>
#include <iostream>  

#include "wx/sizer.h"
#include "wx/log.h"
#include "wx/tglbtn.h"

#ifndef wxHAS_IMAGES_IN_RESOURCES
    #include "sample.xpm"
#endif

// for all others, include the necessary headers (this file is usually all you
// need because it includes almost all "standard" wxWidgets headers)
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

class MySimpleCanvas : public wxScrolled<wxWindow>
{
public:
    enum
    {
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
    
    //Constructor - design van het volledige linker en rechter scherm 
    MySimpleCanvas(wxWindow *parent)
        : wxScrolled<wxWindow>(parent, wxID_ANY, wxPoint(0,0), wxDefaultSize, wxHSCROLL, wxT("scrolledWindow"))
    {
        SetScrollRate( 1, 1 );
        SetVirtualSize( WIDTH, HEIGHT );
        SetBackgroundColour(*wxBLUE);

        Bind(wxEVT_PAINT, &MySimpleCanvas::OnPaint, this);
        
        wxButton* nextKnop = new wxButton(this, 5, wxT("Next"), wxPoint((EENR - 105),(BODEM - 30)), wxSize(100,25), 0, 
            wxDefaultValidator, wxT("Next"));
        wxButton* backKnop = new wxButton(this, 10, wxT("Previous"), wxPoint((TWEER - 113),(BODEM - 30)), wxSize(100,25), 0, 
            wxDefaultValidator, wxT("Previous"));
        this->Bind(wxEVT_MOTION, &MySimpleCanvas::MuisBeweging, this);
    }

private:
    DECLARE_EVENT_TABLE();
    
    void VolgendScherm(wxCommandEvent & event)
    {
        this->Scroll (1000, 0);
    }
    
    void VorigScherm(wxCommandEvent & event)
    { 
        
        this->Scroll (0, 0); 
    }
    void MuisBeweging(wxMouseEvent & event)
    {
        if (event.Dragging()) {
            if (event.LeftIsDown()) {
                std::cout << "Muis bewoog" << std::endl;
                this->Scroll (1000, 0);
            }
        }
        
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
    }
};
BEGIN_EVENT_TABLE(MySimpleCanvas, wxScrolled)
    EVT_BUTTON(5, MySimpleCanvas::VolgendScherm)
    EVT_BUTTON(10, MySimpleCanvas::VorigScherm)
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
    // SetMaxClientSize(size); 
    new MySimpleCanvas(this);
    Show();
}
 

     
// start program
class MainApp : public wxApp
{
public:
    MainApp() {}
    virtual ~MainApp() {}

    virtual bool OnInit()
    {
         
            wxFrame *frame = new MyFrame("Living", wxPoint(300, 350), wxSize(960, 600)); 
            frame->Show(true);
        return true;
        
    }
};

DECLARE_APP(MainApp)
IMPLEMENT_APP(MainApp)
