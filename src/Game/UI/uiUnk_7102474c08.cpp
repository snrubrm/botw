#include "Game/UI/uiUnkTiny.h"

namespace uking::ui {

// 0x7100935f90
Unk_7102474c08::~Unk_7102474c08() = default;

void Unk_7102474c08::sub_710093694C() {
    if (mGauge)
        mGauge->sub_71009359E8();
}

f32 Unk_7102474c08::sub_710093695C() const {
    return mGauge ? mGauge->getAnimator8e0Frame() : 0.0f;
}

}  // namespace uking::ui
