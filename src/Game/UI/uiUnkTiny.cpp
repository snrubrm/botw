#include "Game/UI/uiUnkTiny.h"
#include "Game/UI/euiAnimator.h"

// The "{ ; }" destructors keep the original's vtable store (upstream GameDataFlagSelector::~GameDataFlagSelector() { ; },
// commit 96101229; the original D1 is `str vptr; ret`).
namespace uking::ui {

// 0x7100934a6c
UiStringEntry::UiStringEntry() {}

// 0x7100932f6c
Unk_7102474b38::~Unk_7102474b38() = default;

// 0x71009332f0
Unk_7102474b78::Unk_7102474b78() = default;

// 0x71009333a4
void Unk_7102474b78::set30(eui::Animator* animator) {
    _30 = animator;
}

// 0x71009333c4
void Unk_7102474b78::set38(s32 value) {
    _38 = value;
}

// 0x7100933314
Unk_7102474b78::~Unk_7102474b78() = default;

// 0x71009336a4
Unk_7102474ba8::~Unk_7102474ba8() = default;

// 0x7100934b8c
// 0x7100934aec
Unk_7102474be8::Unk_7102474be8() {}

Unk_7102474be8::~Unk_7102474be8() = default;

// 0x7100935f90
Unk_7102474c08::~Unk_7102474c08() = default;

// 0x7100936990
Unk_7102474c28::~Unk_7102474c28() = default;

// 0x7100936b10
Unk_7102474c48::~Unk_7102474c48() = default;

// 0x7100947b7c
Unk_7102475158::~Unk_7102475158() = default;

// 0x7100949ce0

// 0x710094d8c4
Unk_7102475348::~Unk_7102475348() = default;

// 0x710095023c
Unk_7102475368::~Unk_7102475368() = default;

// 0x710096a890
Unk_7102475388::~Unk_7102475388() = default;

// 0x710095b124
Unk_71024753a8::~Unk_71024753a8() = default;

// 0x710095a3e4
Unk_7102476a80::~Unk_7102476a80() = default;

// 0x710096a89c
Unk_7102476b20::~Unk_7102476b20() = default;

// 0x7100968038
Unk_7102476b40::~Unk_7102476b40() = default;

// 0x7100968034
Unk_7102476b60::~Unk_7102476b60() = default;

// 0x7100987fb4
Unk_7102477468::~Unk_7102477468() = default;

// 0x71009880a4
Unk_7102477488::~Unk_7102477488() = default;

// 0x7100988ee8
Unk_71024774c8::~Unk_71024774c8() = default;

// 0x7100989a78
Unk_7102477508::~Unk_7102477508() = default;

// 0x71009a4d24
Unk_7102479bb0::~Unk_7102479bb0() = default;

// 0x71009a7fa0
Unk_7102479f90::~Unk_7102479f90() = default;

// 0x71009a8be4
Unk_7102479fb0::~Unk_7102479fb0() = default;

// 0x71009b14f0
Unk_710247aa30::~Unk_710247aa30() = default;

// 0x71009b2054
Unk_710247adc8::~Unk_710247adc8() = default;

// 0x71009b2ee0
Unk_710247ae08::~Unk_710247ae08() = default;

// 0x71009b2ee8
Unk_710247ae28::~Unk_710247ae28() = default;

// 0x71009c5098
Unk_710247d8d8::~Unk_710247d8d8() = default;

// 0x71009c66e4
Unk_710247dc50::~Unk_710247dc50() = default;

// 0x71009c6870
Unk_710247dc70::~Unk_710247dc70() = default;

// 0x71009dff74
Unk_71024810d8::~Unk_71024810d8() = default;

// 0x71009e7e00
Unk_71024810f8::~Unk_71024810f8() = default;

// 0x71009dff7c
Unk_7102481118::~Unk_7102481118() = default;

// 0x71009ec6c8
Unk_7102481e50::~Unk_7102481e50() = default;

// 0x7100a6cb6c
Unk_710249c3b0::~Unk_710249c3b0() = default;

// 0x7100a6cbb8
Unk_710249c3d0::~Unk_710249c3d0() = default;

// 0x7100a6cc44
Unk_710249c3f0::~Unk_710249c3f0() = default;

// 0x7100a6d2c8
Unk_710249c410::~Unk_710249c410() = default;

// 0x71009ec6c8
Unk_7102516880::~Unk_7102516880() = default;

// 0x7100933140
Unk_7102474b58::Unk_7102474b58(void* owner) : _8(owner) {}

// 0x7100933184
Unk_7102474b58::~Unk_7102474b58() { ; }

// 0x710093319c
void Unk_7102474b58::sub_71009319C(Index index, const sead::SafeString& a, const sead::SafeString& b) {
    Entry& entry = _10[index];
    entry.a = a;
    entry.b = b;
}

// 0x71009333ac
void Unk_7102474b78::sub_71009333AC() {
    if (_20)
        _20->StopAtMin();
}

// 0x7100959a84
Unk_7102476a40::~Unk_7102476a40() { ; }

// 0x7100959cfc
Unk_7102476a60::~Unk_7102476a60() { ; }

// 0x7100968020
Unk_7102476b00::~Unk_7102476b00() { ; }

// 0x7100988490
Unk_71024774a8::~Unk_71024774a8() { ; }

// 0x71009dfd4c
Unk_71024810b8::~Unk_71024810b8() { ; }

// NON_MATCHING: the original stores `_8` (the base class member) right after loading the vtable address, ours
// schedules it after the 64-bit constant of `_10`
// 0x7100a82fbc
Unk_710249d300::Unk_710249d300() = default;

// 0x7100a8331c
Unk_710249d300::~Unk_710249d300() { ; }

// 0x7100937f5c
Unk_7102474df8::~Unk_7102474df8() {
    _10.freeBuffer();
}

// 0x71009338a0
Unk_7102474bc8::Unk_7102474bc8() {}

// 0x7100933e50
bool Unk_7102474bc8::sub_7100933E50() const {
    for (s32 i = 0; i < _8; i++) {
        UiSlotTarget* target = _130[i].target;
        if (!target || target->_104 != 0)
            return false;
    }
    return true;
}

// 0x7100933fb8
void Unk_7102474bc8::sub_7100933FB8(u32 index, UiSlotTarget* target) {
    if (index < _8)
        _130[index].target = target;
}

// 0x7100933938
// 0x7100934308
void Unk_7102474bc8::sub_7100934308(s32 id, const sead::SafeString& text, s32 value) {
    UiStringEntry entry;
    entry._0 = id;
    entry._8.copy(text);
    entry._120 = value;
    sub_7100933FE0(entry);
}

Unk_7102474bc8::~Unk_7102474bc8() {
    _130.freeBuffer();
    _140.freeBuffer();
}

// 0x7100937d9c
Unk_7102474dd0::~Unk_7102474dd0() = default;

// 0x7100937e9c
void Unk_7102474dd0::m2(const sead::Vector2f& a, const sead::Vector2f& b) {
    _20 = _18;
    const sead::Vector2f pos = a + b + _20;
    _20 = pos;
    if (Unk_PaneTransform* pane = _10) {
        pane->_30.x = pos.x;
        pane->_30.y = pos.y;
        pane->_38 = 0;
        pane->_58 |= 0x10;
    }
}

// 0x71010a7bcc
Unk_7102509148::Unk_7102509148() = default;

// 0x71010a7bf8
Unk_7102509148::~Unk_7102509148() = default;

// Unk_7102475368 accessors (placeholder names after the offsets)
// 0x7100950244
u8* Unk_7102475368::get10() {
    return _10;
}

// 0x710095024c
void Unk_7102475368::set18(const Pair& value) {
    _18.a = value.a;
    _18.b = value.b;
}

// 0x7100950260
Unk_7102475368::Pair* Unk_7102475368::get18() {
    return &_18;
}

// 0x7100950268
void Unk_7102475368::set20(const Pair& value) {
    _20.a = value.a;
    _20.b = value.b;
}

// 0x710095027c
Unk_7102475368::Pair* Unk_7102475368::get20() {
    return &_20;
}

// 0x7100950284
void Unk_7102475368::set28(f32 value) {
    _28 = value;
}

// 0x710095028c
f32 Unk_7102475368::get28() const {
    return _28;
}

// 0x7100950294
void Unk_7102475368::set2c(f32 value) {
    _2c = value;
}

// 0x710095029c
f32 Unk_7102475368::get2c() const {
    return _2c;
}

// 0x71009502a4
u8* Unk_7102475368::get30() {
    return _30;
}

// 0x71009502ac
void Unk_7102475368::set38(f32 value) {
    _38 = value;
}

// 0x71009502b4
f32 Unk_7102475368::get38() const {
    return _38;
}

// 0x71009502bc
void Unk_7102475368::set3c(f32 value) {
    _3c = value;
}

// 0x71009502c4
f32 Unk_7102475368::get3c() const {
    return _3c;
}

// 0x71009502cc
void Unk_7102475368::set40(const Pair& value) {
    _40.a = value.a;
    _40.b = value.b;
}

// 0x71009502e0
Unk_7102475368::Pair* Unk_7102475368::get40() {
    return &_40;
}

// 0x71009502e8
s32 Unk_7102475368::get48() const {
    return _48;
}

// 0x71009502f0
u8* Unk_7102475368::get60() {
    return _60;
}

// Unk_7102474be8 methods (placeholder names after the offsets)
// 0x7100935930
void Unk_7102474be8::set940(s32 value) {
    _940 = value;
}

// 0x71009358c4
void Unk_7102474be8::set944(f32 value) {
    _944 = value;
}

// 0x7100935894
void Unk_7102474be8::set948(f32 value) {
    if (value >= 0.0f && value <= 100.0f)
        _948 = value;
}

// 0x71009358b4
void Unk_7102474be8::set958(f32 value) {
    if (value >= 0.0f)
        _958 = value;
}

// 0x7100935938
void Unk_7102474be8::playAnimator918() {
    _918->PlayAuto(1.0f);
}

// 0x710093594c
void Unk_7102474be8::stopAnimator918() {
    _918->StopAtMax();
}

// 0x710093595c
void Unk_7102474be8::playAnimator8e0() {
    _8e0->PlayAuto(1.0f);
}

// 0x7100935970
void Unk_7102474be8::stopAnimator8e0() {
    _8e0->StopAtMax();
}

// 0x7100935980
bool Unk_7102474be8::isAnimator8e0Playing() const {
    return _8e0->mRate != 0;
}

// 0x7100935994
f32 Unk_7102474be8::getAnimator8e0Frame() const {
    return _8e0->mFrame;
}

// 0x71009359a0
void Unk_7102474be8::playAnimator8e0FromFrame(f32 frame) {
    _8e0->PlayFromFrame(eui::Animator::PlayType(0), frame, 1.0f);
}

// 0x71009359b0
void Unk_7102474be8::playAnimator910() {
    _910->PlayAuto(1.0f);
}

// 0x71009359c4
bool Unk_7102474be8::isAnimator910Playing() const {
    return _910->mRate != 0;
}

// 0x71009359d8
void Unk_7102474be8::stopAnimator910(f32 frame) {
    _910->Stop(frame);
}

}  // namespace uking::ui
