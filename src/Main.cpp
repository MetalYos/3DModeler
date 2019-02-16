#include "Main.h"
#include "MainWindow.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    MainWindow* mainwindow = new MainWindow(wxT("3D Modeler - wxWidgets"));
    mainwindow->Show(true);

    return true;
}