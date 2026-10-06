#include "Game/UI/euiWindowEx.h"

// A separate translation unit per out-of-line DynamicCast (the original has one copy per TU; identical copies would be
// merged by the compiler otherwise).
namespace eui {

// 0x7100bdf6a8
bool sub_7100BDF6A8(nn::ui2d::Pane* ptr) {
    return nn::font::DynamicCast<WindowEx>(ptr) != nullptr;
}

}  // namespace eui
