#include "Game/UI/euiPartsEx.h"

// A separate translation unit per out-of-line DynamicCast (the original has one copy per TU; identical copies would be
// merged by the compiler otherwise).
namespace eui {

// 0x7100bdd310
PartsEx* sub_7100BDD310(nn::ui2d::Pane* ptr) {
    return nn::font::DynamicCast<PartsEx>(ptr);
}

}  // namespace eui
