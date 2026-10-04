#include "Game/UI/euiWindowEx.h"
#include <gfx/nin/seadGraphicsNvn.h>

namespace eui {

// 0x7100be30cc
WindowEx::WindowEx(const nn::ui2d::ResWindow* resource,
                   const nn::ui2d::ResWindow* replacement, const nn::ui2d::BuildArgSet& args)
    : Window(nullptr, sead::GraphicsNvn::instance()->getNnDevice(), resource, replacement, args) {}

// 0x7100be3128
WindowEx::WindowEx(const WindowEx& other)
    : Window(other, sead::GraphicsNvn::instance()->getNnDevice()) {}

}  // namespace eui
