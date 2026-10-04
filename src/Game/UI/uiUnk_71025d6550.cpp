#include <prim/seadMemUtil.h>
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

}  // namespace uking::ui
