#include "Game/gameUnkRttiClasses.h"
#include <nn/font/font_Util.h>
#include <nn/ui2d/Pane.h>
#include "Game/UI/euiAlignPane.h"
#include "Game/UI/euiTextBoxEx.h"
#include "Game/Actor/aiUnk_71025b27b8.h"
#include "Game/Actor/aiUnk_71025b2aa8.h"
#include "Game/Actor/aiUnk_71025b2d88.h"
#include "Game/Actor/aiUnk_710070F974.h"
#include <driver/aglNVNsampler.h>
#include <driver/aglNVNtexture.h>
#include "Game/gameUnkRttiPlaceholders.h"

// Existing placeholder AI tree variable classes whose vtables had no key function so far (the original keeps one
// out-of-line empty destructor per class).
Unk_71025b2aa8::~Unk_71025b2aa8() = default;
Unk_71025b2d88::~Unk_71025b2d88() = default;
Unk_71025b27b8::~Unk_71025b27b8() = default;
Unk_71025c89e8::~Unk_71025c89e8() = default;

// (Unk_71023f3710's destructor is defaulted inline in the header: virtual but trivial,
// so its subclasses keep no D1 of their own. Its RTTI virtuals are defined here so the
// vtable keeps an out-of-line key function.)
bool Unk_71023f3710::checkDerivedRuntimeTypeInfo(
    const sead::RuntimeTypeInfo::Interface* typeInfo) const {
    return checkDerivedRuntimeTypeInfoStatic(typeInfo);
}

const sead::RuntimeTypeInfo::Interface* Unk_71023f3710::getRuntimeTypeInfo() const {
    return getRuntimeTypeInfoStatic();
}

Unk_710245a498::~Unk_710245a498() = default;

Unk_710245a4c8::~Unk_710245a4c8() = default;

Unk_710245a4f8::~Unk_710245a4f8() = default;

Unk_710245a578::~Unk_710245a578() = default;

Unk_710245bee0::~Unk_710245bee0() = default;

Unk_710245c6b8::~Unk_710245c6b8() = default;

Unk_710245c858::~Unk_710245c858() = default;

Unk_710246c330::~Unk_710246c330() = default;

Unk_710246c360::~Unk_710246c360() = default;

Unk_710246cec8::~Unk_710246cec8() = default;

// The body keeps the vtable store of the original, as in upstream's GameDataFlagSelector::~GameDataFlagSelector() { ; }
// (commit 96101229).
Unk_71024dcf80::~Unk_71024dcf80() {
    ;
}


Unk_710250dcd8::~Unk_710250dcd8() = default;

struct Unk_710250dcd8::Unk1 {
    agl::driver::NVNsampler_ _0;
    u8 _pad[0x68 - sizeof(agl::driver::NVNsampler_)];
    agl::driver::NVNtexture_ _68;
};

void Unk_710250dcd8::sub_710110DD20(bool on) {
    _8 = on ? _8 | 4 : _8 & ~4;
}

void Unk_710250dcd8::sub_710110DD3C() {
    _8 &= ~8;
    _10->~Unk1();
    _10 = nullptr;
}

Unk_710251b678::~Unk_710251b678() = default;

Unk_7102457a80::~Unk_7102457a80() = default;

Unk_7102457ac0::~Unk_7102457ac0() = default;

Unk_7102499a68::~Unk_7102499a68() = default;

eui::AlignPane* Unk_7102499a68::findAlignPane(const sead::SafeString& name) {
    return nn::font::DynamicCast<eui::AlignPane>(_8->FindPaneByName(name.cstr(), true));
}

void Unk_7102499a68::m4(nn::ui2d::Pane* pane) {
    _8 = pane;
    if (_8)
        _8->SetVisible(false);
    if (_8)
        _8->SetPosition(nn::util::Float3{0.0f, 2000.0f, 0.0f});
}

void Unk_7102499968::m4(nn::ui2d::Pane* pane) {
    Unk_7102499a68::m4(pane);
    if (!_8)
        return;
    _18 = eui::sub_7100933580(_8->FindPaneByName("T_PostOne_00", true));
    _10 = findAlignPane("N_AlignEdge_00");
}

void Unk_7102499968::m5(const sead::SafeString& label, s32 idx) {
    if (_18)
        setMessage(_18, label);
}

void Unk_71024999a8::m4(nn::ui2d::Pane* pane) {
    Unk_7102499a68::m4(pane);
    if (!_8)
        return;
    _18 = eui::sub_7100933580(_8->FindPaneByName("T_NameOne_00", true));
}

void Unk_71024999a8::m5(const sead::SafeString& label, s32 idx) {
    if (_18)
        setMessage(_18, label);
}

void Unk_71024999e8::m4(nn::ui2d::Pane* pane) {
    Unk_7102499a68::m4(pane);
    if (!_8)
        return;
    _18[0] = eui::sub_7100933580(_8->FindPaneByName("T_NameTriple_00", true));
    _18[1] = eui::sub_7100933580(_8->FindPaneByName("T_NameTriple_01", true));
    _18[2] = eui::sub_7100933580(_8->FindPaneByName("T_NameTriple_02", true));
    _10 = findAlignPane("N_Align_00");
}

void Unk_71024999e8::m5(const sead::SafeString& label, s32 idx) {
    if (u32(idx) <= 2 && _18[idx])
        setMessage(_18[idx], label);
}

Unk_7102499968::~Unk_7102499968() = default;

Unk_71024999a8::~Unk_71024999a8() = default;

Unk_71024999e8::~Unk_71024999e8() = default;

Unk_710249a1a0::~Unk_710249a1a0() = default;

eui::AlignPane* Unk_710249a1a0::findAlignPane(const sead::SafeString& name) {
    return nn::font::DynamicCast<eui::AlignPane>(_8->FindPaneByName(name.cstr(), true));
}

void Unk_710249a1a0::m4(nn::ui2d::Pane* pane) {
    _8 = pane;
    if (_8)
        _8->SetVisible(false);
    if (_8)
        _8->SetPosition(nn::util::Float3{0.0f, 2000.0f, 0.0f});
}

void Unk_710249a0a0::m4(nn::ui2d::Pane* pane) {
    Unk_710249a1a0::m4(pane);
    if (!_8)
        return;
    _18 = eui::sub_7100933580(_8->FindPaneByName("T_PostOne_00", true));
    _10 = findAlignPane("N_AlignEdge_00");
}

void Unk_710249a0a0::m5(const sead::SafeString& label, s32 idx) {
    if (_18)
        setMessage(_18, label);
}

void Unk_710249a0e0::m4(nn::ui2d::Pane* pane) {
    Unk_710249a1a0::m4(pane);
    if (!_8)
        return;
    _18 = eui::sub_7100933580(_8->FindPaneByName("T_NameOne_00", true));
}

void Unk_710249a0e0::m5(const sead::SafeString& label, s32 idx) {
    if (_18)
        setMessage(_18, label);
}

void Unk_710249a120::m4(nn::ui2d::Pane* pane) {
    Unk_710249a1a0::m4(pane);
    if (!_8)
        return;
    _18[0] = eui::sub_7100933580(_8->FindPaneByName("T_NameTriple_00", true));
    _18[1] = eui::sub_7100933580(_8->FindPaneByName("T_NameTriple_01", true));
    _18[2] = eui::sub_7100933580(_8->FindPaneByName("T_NameTriple_02", true));
    _10 = findAlignPane("N_Align_00");
}

void Unk_710249a120::m5(const sead::SafeString& label, s32 idx) {
    if (u32(idx) <= 2 && _18[idx])
        setMessage(_18[idx], label);
}

Unk_710249a0a0::~Unk_710249a0a0() = default;

Unk_710249a0e0::~Unk_710249a0e0() = default;

Unk_710249a120::~Unk_710249a120() = default;

Unk_710251d230::~Unk_710251d230() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100155198) also destroys members or bases
// this class does not declare yet.
Unk_710238b148::~Unk_710238b148() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100a57d80) also destroys members or bases
// this class does not declare yet.
Unk_71024993a0::~Unk_71024993a0() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100a5ac3c) also destroys members or bases
// this class does not declare yet.
Unk_71024993e0::~Unk_71024993e0() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100a5aa08) also destroys members or bases
// this class does not declare yet.
Unk_7102499a28::~Unk_7102499a28() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100a5d4c0) also destroys members or bases
// this class does not declare yet.
Unk_7102499ad8::~Unk_7102499ad8() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100a5fef0) also destroys members or bases
// this class does not declare yet.
Unk_7102499b18::~Unk_7102499b18() = default;

// NON_MATCHING: placeholder destructor; the original (0x7100a5fcbc) also destroys members or bases
// this class does not declare yet.
Unk_710249a160::~Unk_710249a160() = default;

// NON_MATCHING: placeholder destructor; the original (0x710110e12c) also destroys members or bases
// this class does not declare yet.
Unk_710250dd60::~Unk_710250dd60() = default;

// NON_MATCHING: placeholder destructor; the original (0x710112ed24) also destroys members or bases
// this class does not declare yet.
Unk_710250e490::~Unk_710250e490() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101148888) also destroys members or bases
// this class does not declare yet.
Unk_710250f758::~Unk_710250f758() = default;

// NON_MATCHING: placeholder destructor; the original (0x7101148e08) also destroys members or bases
// this class does not declare yet.
Unk_710250f7d8::~Unk_710250f7d8() = default;
