#include <prim/seadMemUtil.h>
#include "Game/UI/uiManager.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameGearMgr.h"
#include "Game/UI/uiUnkSingletons.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

// 0x71009482fc: resets the map / compass state
void Unk_71025d6550::sub_71009482FC() {
    _b64 = 0;
    _b68 = 0;
    _b6c = 1;
    _b70 = 0;
    _b74 = -1;
    _d38 = 0;
    _d3a = 0;
    _d3c = 0;
    _d40 = 0;
    _d44 = 0;
    _d48 = -1;
    _d4c = -1;
    _d50 = -1;
    _d54[0] = -1;
    _d54[1] = -1;
    _d54[2] = -1;
    bool final_trial = ksys::gdt::getFlag_Used_App_FinalTrial(false);
    s32 a = final_trial ? 2 : 1;
    s32 b = final_trial ? 1 : -1;
    _d60 = a;
    _d64 = b;
}

// 0x7100948cc4
void Unk_71025d6550::sub_7100948CC4(const void* a1) {
    const auto* arg = static_cast<const UiSubsys1PinArg*>(a1);
    switch (_b3c) {
    case 0:
    case 1: {
        auto* manager = instance();
        manager->_b54 = arg->value;
        break;
    }
    case 3: {
        const s32 index = u32(arg->index) - 0x193;
        if (u32(index) <= 2) {
            auto& pin = instance()->_b80[index];
            pin.value = arg->value;
            pin.pos = arg->pos;
            pin.valid = true;
        }
        break;
    }
    }
}

// 0x7100948ee4
bool Unk_71025d6550::isD78Zero() const {
    return _d78 == 0;
}

// 0x7100948ef4
bool Unk_71025d6550::isD78One() const {
    return _d78 == 1;
}

// 0x7100948f04
void Unk_71025d6550::setD78(s32 value) {
    _d78 = value;
}

// 0x7100948f0c
void Unk_71025d6550::sub_7100948F0C(const f32* values) {
    sead::MemUtil::copy(&_d80, values, sizeof(_d80));
}

// 0x7100948f18
f32 Unk_71025d6550::getD80(s32 index) const {
    return _d80[index];
}

// 0x7100948f30
void Unk_71025d6550::clearD80() {
    for (s32 i = 0; i < 10; ++i)
        _d80[i] = 0;
}

// 0x7100948f48
void Unk_71025d6550::sub_7100948F48(f32 value) {
    _da8 = value;
}

// 0x7100948f50
f32 Unk_71025d6550::getDA8() const {
    return _da8;
}

// 0x7100948fb8
bool Unk_71025d6550::getDAC() const {
    return _dac;
}

// 0x7100948fc0
void Unk_71025d6550::setDAC(bool value) {
    _dac = value;
}

// 0x7100948eb4
Unk_71025d6550Entry* Unk_71025d6550::sub_7100948EB4(s32 i, s32 j) {
    return &_e8[i][j];
}

// 0x7100948f58
s32 Unk_71025d6550::sub_7100948F58() {
    switch (Manager::instance()->_64c38) {
    case 0:
        return _b64 + 1;
    case 1:
        return _b6c;
    case 2:
        return _b74;
    case 4:
        return _d64;
    default:
        return -1;
    }
}

// 0x7100948d40
bool Unk_71025d6550::sub_7100948D40() {
    for (s32 i = 0; i < _b38; ++i) {
        const auto& entry = _e8[0][i];
        if (static_cast<u32>(entry._8 - 2) > 2 || entry._28 == -1 || !entry._48)
            return false;
    }
    return true;
}

// 0x71009485ec
void Unk_71025d6550::sub_71009485EC() {
    switch (_b3c) {
    case 0:
        _b58[0] = _b64;
        break;
    case 1:
        _b58[0] = _b6c;
        break;
    case 2:
        _b58[0] = _b74;
        break;
    case 3:
        _b58[0] = _d54[0];
        _b58[1] = _d54[1];
        _b58[2] = _d54[2];
        break;
    case 4:
        _b58[0] = _d64;
        break;
    }
}

// 0x7100948db0
// NON_MATCHING: same code; the original shares one `return true` block between the two early exits of the three-value
// compare, ours emits a second copy (`||` chain, early returns and a `bool` local give the same)
bool Unk_71025d6550::sub_7100948DB0() {
    const s32* value;
    switch (_b3c) {
    case 0:
        value = &_b64;
        break;
    case 1:
        value = &_b6c;
        break;
    case 2:
        value = &_b74;
        break;
    case 3:
        if (_b58[0] != _d54[0])
            return true;
        if (_b58[1] != _d54[1])
            return true;
        return _b58[2] != _d54[2];
    case 4:
        value = &_d64;
        break;
    default:
        return false;
    }
    return _b58[0] != *value;
}

// 0x710094852c
// NON_MATCHING: same unrolled search; for the first entry the original stores the already loaded null pointer (w8) as the
// index 0 into the shared `_b38` store block, ours materialises the constant in its own block like the other indices
void Unk_71025d6550::sub_710094852C() {
    for (s32 i = 0; i < 10; ++i) {
        if (!_e8[0][i]._50) {
            _b38 = i;
            return;
        }
    }
    _b38 = 10;
}

// 0x71009486f0
void Unk_71025d6550::sub_71009486F0() {
    for (s32 row = 0; row < 3; ++row) {
        for (s32 i = 0; i < 10; ++i) {
            auto& entry = _e8[row][i];
            if (static_cast<u32>(entry._8 - 2) <= 2 && entry._28 != -1)
                entry._c = entry._3c;
        }
    }
}

// 0x7100948914
// NON_MATCHING: same state machine; the original merges the four `sub_710066990C(true / false)` calls into two shared tails
// (the true / false paths of the three states jump into them) and reloads the manager only once in state 1; ours keeps
// separate copies
void Unk_71025d6550::sub_7100948914() {
    if (!sub_7100A9BAEC(27))
        return;
    switch (_d60) {
    case 0:
        if (_d64 == 1) {
            GearMgr::instance()->sub_710066990C(true);
            _d60 = 2;
        }
        break;
    case 1:
        GearMgr::instance()->sub_7100669B38();
        if (_d64 != 0) {
            GearMgr::instance()->sub_710066990C(true);
            _d60 = 2;
        } else {
            GearMgr::instance()->sub_710066990C(false);
            _d60 = 0;
        }
        break;
    case 2:
        if (_d64 == 0) {
            GearMgr::instance()->sub_710066990C(false);
            _d60 = 0;
        }
        break;
    }
}

}  // namespace uking::ui
