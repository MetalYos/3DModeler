#pragma once

#include "pch.h"
#include "DrawPanel.h"
#include "SceneGraphPanel.h"
#include "PropertiesPanel.h"

class MainWindow : public wxFrame
{
public:
    MainWindow(const wxString& title);

    void OnClose(wxCloseEvent& event);

    // File Menu Event Handlers
    void OnQuit(wxCommandEvent& WXUNUSED(event));

private:
    bool closeWindow();

    void createMenu();
    void createFileMenu(wxMenuBar* menuBar);
    void createEditMenu(wxMenuBar* menuBar);
    void createCreateMenu(wxMenuBar* menuBar);

    void createTopToolbar();
    void createLeftViewport();
    void createSideToolbar();
    void createDrawingPanel();
    void createSceneGraphPanel();
    void createPropertiesPanel();

private:
    wxBoxSizer* m_MainSizer;
    wxBoxSizer* m_LeftVerticalSizer;
    wxBoxSizer* m_LeftViewportSizer;
    wxBoxSizer* m_RightVerticalSizer;

    DrawPanel* m_DrawingPanel;
    SceneGraphPanel* m_SceneGraphPanel;
    PropertiesPanel* m_PropertiesPanel;
};