#include "Game/AI/Action/actionUnk_71023c8418.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007320F0.h"
#include "Game/Actor/actWeapon.h"
#include "Game/Damage/dmgDamageCallback.h"

Unk_71023c8418::Unk_71023c8418(ksys::act::ai::ActionBase* owner) : Unk_71025afc58(owner) {}

void Unk_71023c8418::enter_(ksys::act::ai::InlineParamPack* params) {
    _88 = false;
    if (*mIsIgnoreSmallHit_s)
        setDamageCallbackTiming(mOwner->getActor(), 4, &_60);
}

// NON_MATCHING: stack layout (the original places the query below the weapon request)
void Unk_71023c8418::calc_() {
    if (sub_71005DAFB0(mOwner->getActor())) {
        mFlags.set(Flag::Failed);
        mFlags.reset(Flag::Finished);
        return;
    }

    const f32 range = sub_71007322E8(mOwner->getActor(), *mWeaponIdx_s);
    sub_71005DAB2C(mOwner->getActor(), range + *mJustAvoidSideDist_s,
                   range + *mJustAvoidBackDist_s, *mJustAvoidAngle_s, m14());

    ksys::as::ASList::Unk4 query;
    if (m16(&query)) {
        m15(*mWeaponIdx_s, &query.name, _88, 1.0f);
        _88 = true;
    } else if (m17()) {
        sub_71005D79AC(mOwner->getActor(), *mWeaponIdx_s, uking::act::Unk_71002edaec(1));
    }
}

void Unk_71023c8418::leave_() {
    sub_71005D79AC(mOwner->getActor(), *mWeaponIdx_s, uking::act::Unk_71002edaec(1));
    sub_71005DA114(mOwner->getActor(), &_60);
}

void Unk_71023c8418::loadParams_() {
    getStaticParam(&mJustAvoidAngle_s, "JustAvoidAngle");
    getStaticParam(&mJustAvoidBackDist_s, "JustAvoidBackDist");
    getStaticParam(&mJustAvoidSideDist_s, "JustAvoidSideDist");
    getStaticParam(&mIsNoRodAttack_s, "IsNoRodAttack");
    getStaticParam(&mIsNoColRodAttack_s, "IsNoColRodAttack");
    getStaticParam(&mIsIgnoreSmallHit_s, "IsIgnoreSmallHit");
    getStaticParam(&mRodAttackDelayTime_s, "RodAttackDelayTime");
    m13();
}

void Unk_71023c8418::m13() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
}

// NON_MATCHING: the original branches around the `| 0x40` (tbz) instead of using csel
void Unk_71023c8418::m15(int weapon_idx, const sead::SafeString* name, bool a3, f32 a4) {
    sead::BitFlag8 flags;
    sub_71002A665C(mOwner->getActor(), weapon_idx, a3 ? _58 | 0x40 : _58, name, flags, 1, a4, 1.0f);
}

bool Unk_71023c8418::m16(ksys::as::ASList::Unk4* query) {
    return sub_71005DD66C(mOwner->getActor(), query, 0, 0);
}

bool Unk_71023c8418::m17() {
    return sub_71005DD74C(mOwner->getActor(), nullptr, 0, 0);
}

void Unk_71023c8418::sub_71002A665C(ksys::act::Actor* actor, int weapon_idx, u32 a3,
                                    const sead::SafeString* name, const sead::BitFlag8& flags,
                                    int a6, f32 a7, f32 a8) {
    sead::BitFlag8 flags_ = flags;
    if (_89)
        flags_.set(0x20);

    if (*mIsNoRodAttack_s) {
        sub_71005D7F4C(actor, weapon_idx, a3, name, &flags_, a6, a7, a8);
    } else if (*mIsNoColRodAttack_s) {
        sub_71005D7D90(actor, weapon_idx, a3, name, &flags_, a6, 1, *mRodAttackDelayTime_s, 1, a7,
                       a8);
    } else {
        sub_71005D7ADC(actor, weapon_idx, a3, name, &flags_, a6, 1, *mRodAttackDelayTime_s, 1, a7,
                       a8);
    }
}
