#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication a(argc, argv);

    SkEditor::MainWindow mainWin;
    mainWin.show();
    return a.exec();
}