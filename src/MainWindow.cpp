#include "MainWindow.h"

MainWindow::MainWindow(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 720))
{
    // Initialize Log
    Log::Init();

    m_MainSizer = new wxBoxSizer(wxHORIZONTAL);
    m_LeftVerticalSizer = new wxBoxSizer(wxVERTICAL);
    m_LeftViewportSizer = new wxBoxSizer(wxHORIZONTAL);
    m_RightVerticalSizer = new wxBoxSizer(wxVERTICAL);

    wxImage::AddHandler(new wxPNGHandler());
    createMenu();
    createTopToolbar();
    createLeftViewport();
    createSceneGraphPanel();
    createPropertiesPanel();

    CreateStatusBar();
    SetStatusText(wxT("Ready"), 0);

    m_MainSizer->Add(m_LeftVerticalSizer, 5, wxEXPAND);
    m_MainSizer->Add(m_RightVerticalSizer, 2, wxEXPAND);

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
    // Create Bitmaps
    wxBitmap quit(wxT("icons/exit.png"), wxBITMAP_TYPE_PNG);

    // Create Toolbar
    wxToolBar* toolbar = new wxToolBar(this, wxID_ANY);
    toolbar->AddTool(wxID_EXIT, wxT("Quit Application"), quit);

    toolbar->Realize();

    m_LeftVerticalSizer->Add(toolbar, 0, wxEXPAND);
    m_LeftVerticalSizer->Layout();
}

void MainWindow::createLeftViewport()
{
    createSideToolbar();
    createDrawingPanel();

    m_LeftVerticalSizer->Add(m_LeftViewportSizer, 1, wxEXPAND);
    m_LeftVerticalSizer->Layout();
}

void MainWindow::createSideToolbar()
{
    // Create Bitmaps
    wxBitmap quit(wxT("icons/exit.png"), wxBITMAP_TYPE_PNG);

    // Create Toolbar
    wxToolBar* toolbar = new wxToolBar(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_VERTICAL);
    toolbar->AddTool(wxID_EXIT, wxT("Quit Application"), quit);

    toolbar->Realize();

    m_LeftViewportSizer->Add(toolbar, 0, wxEXPAND);
}

void MainWindow::createDrawingPanel()
{
    m_DrawingPanel = new DrawPanel(this);

    m_LeftViewportSizer->Add(m_DrawingPanel, 1, wxEXPAND | wxALL, 5);
}

void MainWindow::createSceneGraphPanel()
{
    m_SceneGraphPanel = new SceneGraphPanel(this);

    m_RightVerticalSizer->Add(m_SceneGraphPanel, 1, wxEXPAND | wxALL, 3);
}

void MainWindow::createPropertiesPanel()
{
    m_PropertiesPanel = new PropertiesPanel(this);

    m_RightVerticalSizer->Add(m_PropertiesPanel, 1, wxEXPAND | wxALL, 3);
    m_RightVerticalSizer->Layout();
}
