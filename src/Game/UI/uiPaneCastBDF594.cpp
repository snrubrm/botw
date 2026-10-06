#include "Game/UI/euiPictureEx.h"

// A separate translation unit per out-of-line DynamicCast (the original has one copy per TU; identical copies would be
// merged by the compiler otherwise).
namespace eui {

// 0x7100bdf594
bool sub_7100BDF594(nn::ui2d::Pane* ptr) {
    return nn::font::DynamicCast<PictureEx>(ptr) != nullptr;
}

}  // namespace eui
