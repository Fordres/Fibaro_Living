/*class MyPopupScreen : public wxPopupWindow
{
public:
    MyPopupScreen(wxWindow *parent, const wxPoint &plaats, const wxSize &grootte);
};

//MyFrame constructor
MyPopupScreen::MyPopupScreen(wxWindow *parent, const wxPoint &plaats, const wxSize &grootte)
    : wxPopupWindow(parent, wxBORDER_DEFAULT)
	 {
		 wxImage myBitmapKnopOpenBlue = wxImage("./knop_on_blue.gif",  wxBITMAP_TYPE_GIF);
		 this->SetBackgroundColour(*wxWHITE);
		 this->Position(wxPoint(200,200), wxSize(300,200));
		 wxButton *lampen = new wxButton(this, 35, wxEmptyString, wxPoint(10,10), wxSize(80,25), wxTRANSPARENT_WINDOW |wxBORDER_NONE);
		 lampen->SetBitmap(myBitmapKnopOpenBlue); 
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
	wxPopupWindow *popup = new MyPopupScreen(this, wxPoint(100,100), wxSize(200,200));  

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
*/ 