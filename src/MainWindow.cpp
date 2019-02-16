#include "MainWindow.h"

MainWindow::MainWindow(const wxString& title)
    : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(1280, 720))
{
    // Initialize Log
    Log::Init();

    m_MainSizer = new wxBoxSizer(wxVERTICAL);

    CreateStatusBar();
    SetStatusText(wxT("Ready"), 0);

    SetSizer(m_MainSizer);
    Centre();
}
