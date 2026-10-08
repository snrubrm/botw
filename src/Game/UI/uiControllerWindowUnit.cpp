#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"

namespace uking::ui {

// 0x7100a030d8 (D0)
Unk_7102485670::~Unk_7102485670() = default;

// 0x7100a01730
void Unk_7102485670::m4(sead::Heap*) {
    _48 = _8->createAnimatorAuto("New", false);
    if (_48)
        _48->StopAtMin();
}

// 0x7100a01a2c
void Unk_7102485670::m6() {
    if (_50) {
        _50 = false;
        return;
    }
    const s32 flags = _30;
    _50 = flags & 1;
    if (flags & 1)
        sub_7100A01918();
}

// 0x7100a065c8 (D0)
Unk_71024872a0::~Unk_71024872a0() = default;

// 0x7100a05314
void Unk_71024872a0::m4(sead::Heap*) {
    _48 = _8->findPartsLayout("Pa_DLCTips_00");
}

// 0x7100a065ec
void Unk_71024872a0::m6() {}

}  // namespace uking::ui
