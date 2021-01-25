#include "mainwindow.h"

namespace SkEditor
{
    MainWindow::MainWindow(QMainWindow* parent)
        : QMainWindow(parent)
    {
        _ui.setupUi(this);
    }

    MainWindow::~MainWindow()
    {

    }
}