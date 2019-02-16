#pragma once

#include "pch.h"

class MainWindow : public wxFrame
{
public:
    MainWindow(const wxString& title);

private:

private:
    wxBoxSizer* m_MainSizer;
};