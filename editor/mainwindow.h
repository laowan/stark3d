#pragma once

#include "ui_mainwindow.h"

namespace SkEditor
{
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        MainWindow(QMainWindow* parent = 0);
        ~MainWindow();
    private:
        Ui::mainWindow _ui;
    };
}