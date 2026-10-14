#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/uiScreens.h"
#include "Game/UI/uiManager.h"
#include "Game/UI/euiMessageString.h"
#include <container/seadSafeArray.h>

namespace uking::ui {

// 0x7100a030d8 (D0)
Unk_7102485670::~Unk_7102485670() = default;

// 0x7100a01730
void Unk_7102485670::m4(sead::Heap*) {
    _48 = _8->createAnimatorAuto("New", false);
    if (_48)
        _48->StopAtMin();
}

// 0x71010b6558 (placeholder; declared only)
bool sub_71010B6558();

namespace {
// 0x7102485040
const sead::SafeArray<s32, 8> sUnk_7102485040 = {{10, 1, 16, 14, 12, 13, 11, 18}};
}  // namespace

// 0x7100a01918
// NON_MATCHING: the original selects the table element pointer (csel on addresses) and reloads it after the call.
void Unk_7102485670::sub_7100A01918() {
    auto* screen = sead::DynamicCast<ScreenControllerWindow>(sub_7100939C5C());
    if (!screen)
        return;
    eui::MessageString message;
    s32 id = sUnk_7102485040[sub_7100939C78()];
    if (id == 18 && sub_71010B6558())
        id = 19;
    if (_48) {
        if (Manager::instance()->sub_7100A7F930(id))
            _48->StopAtMax();
        else
            _48->StopAtMin();
    }
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
