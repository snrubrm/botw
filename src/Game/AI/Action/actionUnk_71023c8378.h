#pragma once

#include "Game/AI/Action/actionUnk_71023c8418.h"

// Attack helper variant (vtable 0x71023c8378, ctor 0x71002a5d50) embedded in AttackPartBind
// (+0xd8): takes the weapon index from the dynamic param "DynWeaponIdx" and an AS slot (_8c, set by
// the owner).
// TODO: the m16/m17 overrides (0x71002a5f50, 0x71002a5f90) call ASList::x directly (not declared
// yet), so this vtable is still incomplete.
class Unk_71023c8378 : public Unk_71023c8418 {
    SEAD_RTTI_OVERRIDE(Unk_71023c8378, Unk_71023c8418)
public:
    explicit Unk_71023c8378(ksys::act::ai::ActionBase* owner);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void m13() override;
    int m14() override { return _8c; }

    int _8c = 0;
};
KSYS_CHECK_SIZE_NX150(Unk_71023c8378, 0x90);
