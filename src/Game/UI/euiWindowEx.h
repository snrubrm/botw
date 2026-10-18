#pragma once

#include <nn/ui2d/Window.h>

namespace eui {

// Both constructors delegate to the Window base. The full instance extent is
// not recovered; this declaration must not be used for allocation.
class WindowEx : public nn::ui2d::Window {
public:
    NN_RUNTIME_TYPEINFO(nn::ui2d::Window)

    // AdjustPaneSizeToTextSize reads the Window base's content margins and kind.
    using nn::ui2d::Window::mContentMargins;
    using nn::ui2d::Window::mWindowKind;

    WindowEx(const nn::ui2d::ResWindow*, const nn::ui2d::ResWindow*,
             const nn::ui2d::BuildArgSet&);
    WindowEx(const WindowEx&);
    ~WindowEx() override = default;
};

}  // namespace eui
