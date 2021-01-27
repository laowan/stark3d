#include "renderpanel.h"
#include "bgfx/bgfx.h"
#include "bgfx/platform.h"
#include <iostream>

namespace SkEditor
{
    RenderPanel::RenderPanel(QWidget* parent)
        : QDockWidget(parent)
    {
        setWindowTitle("Preview");
    }

    RenderPanel::~RenderPanel()
    {

    }

    void RenderPanel::init()
    {
        bgfx::PlatformData pd;
        pd.ndt = nullptr;
        pd.nwh = (HWND)winId();
        pd.context = nullptr;
        pd.backBuffer = nullptr;
        pd.backBufferDS = nullptr;
        bgfx::setPlatformData(pd);

        bgfx::renderFrame();

        bgfx::Init init;
        init.type = bgfx::RendererType::Enum::Count;
        init.vendorId = 0;
        init.resolution.width = 500;
        init.resolution.height = 500;
        bool ret = bgfx::init(init);
        std::cout << ret << std::endl;
    }

    void RenderPanel::render()
    {
        std::cout << "render" << std::endl;
        bgfx::setDebug(BGFX_DEBUG_TEXT /*| BGFX_DEBUG_STATS*/);
        bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x303030ff, 1.0f, 0);
        bgfx::frame();
    }
}