#include "MainWindow.h"

MainWindow::MainWindow(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 720))
{
    // Initialize Log
    Log::Init();

    m_MainSizer = new wxBoxSizer(wxVERTICAL);

    createMenu();
    createTopToolbar();
    CreateStatusBar();
    SetStatusText(wxT("Ready"), 0);

    Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MainWindow::OnClose));

    SetSizer(m_MainSizer);
    Centre();

    Maximize(true);
}

// Event Handlers
void MainWindow::OnQuit(wxCommandEvent& WXUNUSED(event))
{
    if (closeWindow())
    {
        Close();
        Destroy();
    }
}

void MainWindow::OnClose(wxCloseEvent& event)
{
    if (closeWindow())
        Destroy();
}

// Private Methods
bool MainWindow::closeWindow()
{
    wxMessageDialog dialog(NULL, wxT("Are you sure you want to quit?"),
    wxT("Quit application?"), wxYES_NO | wxICON_QUESTION | wxCENTRE);
    if (dialog.ShowModal() != wxID_YES)
        return false;
    
    return true;
}

void MainWindow::createMenu()
{
    wxMenuBar* menuBar = new wxMenuBar();

    createFileMenu(menuBar);
    createEditMenu(menuBar);
    createCreateMenu(menuBar);

    SetMenuBar(menuBar);
}

void MainWindow::createFileMenu(wxMenuBar* menuBar)
{
    wxMenu* file = new wxMenu();
    
    file->Append(wxID_EXIT, wxT("&Quit"));
    file->Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(MainWindow::OnQuit));
    
    menuBar->Append(file, wxT("&File"));
}

void MainWindow::createEditMenu(wxMenuBar* menuBar)
{

}

void MainWindow::createCreateMenu(wxMenuBar* menuBar)
{

}

void MainWindow::createTopToolbar()
{
    wxImage::AddHandler(new wxPNGHandler());

    // Create Bitmaps
    wxBitmap quit(wxT("icons/exit.png"), wxBITMAP_TYPE_PNG);

    // Create Toolbar
    wxToolBar* toolbar = new wxToolBar(this, wxID_ANY);
    toolbar->AddTool(wxID_EXIT, wxT("Quit Application"), quit);

    toolbar->Realize();

    m_MainSizer->Add(toolbar, 0, wxEXPAND);
    m_MainSizer->Layout();
}

void MainWindow::createSideToolbar()
{

}

void MainWindow::createViewportPanel()
{

}

void MainWindow::createSceneGraphPanel()
{

}

void MainWindow::createPropertiesPanel()
{

}
