#pragma once

#include <QDockWidget>

namespace SkEditor
{
    class RenderPanel : public QDockWidget
    {
        Q_OBJECT
    public:
        RenderPanel(QWidget* parent = 0);
        ~RenderPanel();
        void init();

    public slots:
        void render();
    };
}