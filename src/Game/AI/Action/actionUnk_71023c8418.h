#pragma once

#include "KingSystem/ActorSystem/AS/ASList.h"
#include <prim/seadBitFlag.h>
#include <prim/seadSafeString.h>
#include "Game/AI/Action/actionUnk_7102451ba0.h"
#include "Game/AI/Action/actionUnk_71025afc58.h"

namespace ksys::act {
class Actor;
}

// Attack helper (vtable 0x71023c8418, ctor 0x71002a6238): embedded in Attack (+0x40), FollowAttack
// (+0x78) and returned by AttackBase::m32(). Loads the weapon / just-avoid / rod attack params and
// drives the weapon attack requests of the owner's actor.
class Unk_71023c8418 : public Unk_71025afc58 {
    SEAD_RTTI_OVERRIDE(Unk_71023c8418, Unk_71025afc58)
public:
    explicit Unk_71023c8418(ksys::act::ai::ActionBase* owner);

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    virtual void m13();
    virtual int m14() { return 0; }
    virtual void m15(int weapon_idx, const sead::SafeString* name, bool a3, f32 a4);
    virtual bool m16(ksys::as::ASList::Unk4* query);
    virtual bool m17();

    void sub_71002A665C(ksys::act::Actor* actor, int weapon_idx, u32 a3,
                        const sead::SafeString* name, const sead::BitFlag8& flags, int a6, f32 a7,
                        f32 a8);

    const int* mWeaponIdx_s{};
    const float* mJustAvoidAngle_s{};
    const float* mJustAvoidBackDist_s{};
    const float* mJustAvoidSideDist_s{};
    const bool* mIsNoRodAttack_s{};
    const bool* mIsNoColRodAttack_s{};
    const bool* mIsIgnoreSmallHit_s{};
    const int* mRodAttackDelayTime_s{};
    /// Set by the owner on enter (Attack::m35: 1, BlowOffAttack::m35: 4).
    u32 _58 = 1;
    Unk_7102451ba0 _60;
    bool _88 = false;
    bool _89 = false;
};
KSYS_CHECK_SIZE_NX150(Unk_71023c8418, 0x90);
