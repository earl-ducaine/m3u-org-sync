// wxWidgets "Hello world" Program
// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#include "wx/image.h"
#include "wx/xrc/xmlres.h"
#endif

// the application icon
#if defined(__WXGTK__) || defined(__WXMOTIF__) || defined(__WXMAC__)
    #include "appicon.xpm"
#endif


class MyApp: public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
  void OnQuit(wxCommandEvent& event);
    void OnHello(wxCommandEvent& event);
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
  private:
  DECLARE_EVENT_TABLE()
};

// Define a new frame type: this is going to be our main frame
class MyFrame2 : public wxFrame
{
public:
    // ctor(s)
    MyFrame2(const wxString& title, const wxPoint& pos, const wxSize& size);

    // event handlers (these functions should _not_ be virtual)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnDlg1(wxCommandEvent& event);
    void OnDlg2(wxCommandEvent& event);

private:
    // any class wishing to process wxWidgets events must use this macro
  //DECLARE_EVENT_TABLE()
};



enum
{
    ID_Quit = 1,
    ID_About,
    ID_Hello,
};

// EGIN_EVENT_TABLE(MyFrame2, wxFrame)
//     EVT_MENU(XRCID("menu_quit"),  MyFrame::OnQuit)
//     EVT_MENU(XRCID("menu_about"), MyFrame::OnAbout)
//     EVT_MENU(XRCID("menu_dlg1"), MyFrame::OnDlg1)
//     EVT_MENU(XRCID("menu_dlg2"), MyFrame::OnDlg2)
// END_EVENT_TABLE()


BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_MENU(ID_Quit,  MyFrame::OnQuit)
  EVT_MENU(ID_About, MyFrame::OnAbout)
END_EVENT_TABLE()

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit() {
  // MyFrame *frame = new MyFrame();
    MyFrame *frame = new MyFrame( L"Hello World", wxPoint(50,50), wxSize(450,340) );

    wxImage::AddHandler(new wxGIFHandler);
    wxImage::AddHandler(new wxPNGHandler);
    wxXmlResource::Get()->InitAllHandlers();
    wxXmlResource::Get()->Load(L"resource.xrc");

    MyFrame2 *frame2 = new MyFrame2(L"XML resources demo",
				    wxPoint(50, 50), wxSize(450, 340));

    frame->Show( true );
    return true;
}

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(ID_Hello, L"&Hello...\tCtrl-H",
                     L"Help string shown in status bar for this menu item");
    menuFile->AppendSeparator();
    menuFile->Append( ID_Quit, L"E&xit" );
    
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(ID_About, L"&About..." );
    //menuHelp->Append(wxID_ABOUT);
    
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append( menuFile, L"&File" );
    menuBar->Append( menuHelp, L"&Help" );
    SetMenuBar( menuBar );
    CreateStatusBar();
    SetStatusText(L"Welcome to wxWidgets!" );
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close( true );
}
void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( L"This is a wxWidgets' Hello world sample",
                  L"About Hello World", wxOK | wxICON_INFORMATION );
}
void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage(L"Hello world from wxWidgets!");
}

void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    Close( true );
}



/////////////////////////////////////////////////


// ----------------------------------------------------------------------------
// main frame
// ----------------------------------------------------------------------------

// frame constructor
MyFrame2::MyFrame2(const wxString& title, const wxPoint& pos, const wxSize& size)
       : wxFrame((wxFrame *)NULL, -1, title, pos, size)
{
    SetIcon(wxICON(appicon));

    SetMenuBar(wxXmlResource::Get()->LoadMenuBar(L"mainmenu"));
    SetToolBar(wxXmlResource::Get()->LoadToolBar(this, L"toolbar"));
}

// event handlers
void MyFrame2::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    // true is to force the frame to close
    Close(true);
}

void MyFrame2::OnAbout(wxCommandEvent& WXUNUSED(event))
{
    wxString msg;
    msg.Printf( _T("This is the about dialog of XML resources demo.\n")
                _T("Welcome to %s"), wxVERSION_STRING);

    wxMessageBox(msg, L"About XML resources demo", wxOK | wxICON_INFORMATION, this);
}

void MyFrame2::OnDlg1(wxCommandEvent& WXUNUSED(event))
{
    wxDialog dlg;
    wxXmlResource::Get()->LoadDialog(&dlg, this, L"dlg1");
    dlg.ShowModal();
}

void MyFrame2::OnDlg2(wxCommandEvent& WXUNUSED(event))
{
    wxDialog dlg;
    wxXmlResource::Get()->LoadDialog(&dlg, this, L"dlg2");
    dlg.ShowModal();
}
