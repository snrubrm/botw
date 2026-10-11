#pragma once

#include "Game/UI/uiScreens.h"

namespace uking::ui {

// Native 9C2F58 owns vtable247D0C8 and an Animator at+130; distinct from button child24746D0.
class Unk_710247d0c8 : public ScreenChildEx {
public:
    NN_RUNTIME_TYPEINFO(ScreenChildEx)
    explicit Unk_710247d0c8(eui::LayoutEx* layout);
    ~Unk_710247d0c8() override;
    void m24(sead::Heap* heap) override;
    void sub_71009C3138(s32 value, u32 frame);
    void sub_71009C31D8();

    /* 0x130 */ eui::Animator* mAnimator = nullptr;
};
static_assert(sizeof(Unk_710247d0c8) == 0x138);

}  // namespace uking::ui
