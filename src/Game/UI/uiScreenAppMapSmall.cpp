#include "Game/UI/uiScreens.h"
#include "Game/UI/uiUnkSingletons.h"
#include "Game/UI/euiAnimator.h"

namespace uking::ui {

// 0x71009ef488
// NON_MATCHING: position load and negation order.
void ScreenAppMap::sub_71009EF488(const sead::Vector3f* pos, s32 scale_level) {
    if (_3610) {
        UiSubsys1::instance()->sub_7100968AF8(0);
        _3ad4 = pos->x;
        _3ad8 = -pos->z;
        _3adc = scale_level;
    }
}

// 0x71009ef57c: the input speed is unused; the controller is always started at speed 1.
void ScreenAppMap::sub_71009EF57C(f32, s32 type) {
    if (_3c90) {
        switch (type) {
        case 0:
            _3c90->sub_71009C1474(1.0f, 0);
            break;
        case 1:
            _3c90->sub_71009C1474(1.0f, 1);
            break;
        }
    }
}

// 0x71009ef5a8
bool ScreenAppMap::sub_71009EF5A8(s32 type) {
    if (_3c90) {
        switch (type) {
        case 0:
            return _3c90->sub_71009C1814(0);
        case 1:
            return _3c90->sub_71009C1814(1);
        }
    }
    return true;
}

// 0x71009ef4ec (CSV unnamed)
void ScreenAppMap::sub_71009EF4EC(s32 a1, s32 a2) {
    if (u32(a1 - 3) > 1)
        return;
    _3ad2 = !(a2 & 1);
    UiSubsys1::instance()->sub_7100968AF8(a1);
}

// 0x71009ef51c (CSV unnamed)
void ScreenAppMap::sub_71009EF51C(s32 a1) {
    if (u32(a1) <= 0xe) {
        UiSubsys1::instance()->set128(a1);
        bool ready = UiSubsys1::instance()->sub_7100968BD8();
        if (ready)
            UiSubsys1::instance()->sub_7100968AF8(2);
        else
            UiSubsys1::instance()->sub_7100968AF8(1);
        _3ad2 = 0;
    }
}

// 0x71009eecd0
bool ScreenAppMap::sub_71009EECD0() const {
    if (!_3610 || !_3610->sub_71009AEF7C())
        return false;
    return isOpened();
}

// 0x71009eed10
s32 ScreenAppMap::sub_71009EED10() const {
    return _3610->sub_71009AEF7C();
}

}  // namespace uking::ui
