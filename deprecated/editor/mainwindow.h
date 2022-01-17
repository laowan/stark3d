#pragma once

#include "ui_mainwindow.h"

namespace SkEditor
{
    class RenderPanel;
    class MainWindow : public QMainWindow
    {
        Q_OBJECT
    public:
        MainWindow(QMainWindow* parent = 0);
        ~MainWindow();

    protected slots:
        void onLoadGLTF();

    private:
        Ui::mainWindow _ui;
        RenderPanel* _renderPanel;
        QDockWidget* _scenePanel;
        QDockWidget* _logPanel;
    };
}