#include "mainwindow.h"
#include "renderpanel.h"
#include <QTimer>

#include <windows.h>
#include <QDebug>

namespace SkEditor
{
    MainWindow::MainWindow(QMainWindow* parent)
        : QMainWindow(parent)
    {
        _ui.setupUi(this);

        centralWidget()->setMaximumHeight(0);

        _renderPanel = new RenderPanel(this);
        _renderPanel->setupGL();
        _renderPanel->init();

        _scenePanel = new QDockWidget(this);
        _scenePanel->setWindowTitle("Scene");
        _scenePanel->hide();

        _logPanel = new QDockWidget(this);
        _logPanel->setWindowTitle("Log");
        _logPanel->hide();

        setCorner(Qt::TopLeftCorner, Qt::LeftDockWidgetArea);
        setCorner(Qt::TopRightCorner, Qt::RightDockWidgetArea);
        setCorner(Qt::BottomLeftCorner, Qt::LeftDockWidgetArea);
        setCorner(Qt::BottomRightCorner, Qt::RightDockWidgetArea);

        addDockWidget(Qt::TopDockWidgetArea, _renderPanel);
        addDockWidget(Qt::LeftDockWidgetArea, _scenePanel);
        addDockWidget(Qt::BottomDockWidgetArea, _logPanel);

        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, _renderPanel, &RenderPanel::render);
        timer->start(100);
    }

    MainWindow::~MainWindow()
    {

    }

    void MainWindow::onLoadGLTF()
    {
        qDebug() << "onLoadGLTF()";
    }
}