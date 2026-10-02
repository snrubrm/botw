#pragma once

#include "KingSystem/ActorSystem/AS/ASList.h"
#include "Game/AI/Action/actionForkAttackWithWeaponOrWithout.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkWeaponAttackBase : public ForkAttackWithWeaponOrWithout {
    SEAD_RTTI_OVERRIDE(ForkWeaponAttackBase, ForkAttackWithWeaponOrWithout)
public:
    explicit ForkWeaponAttackBase(const InitArg& arg);
    ~ForkWeaponAttackBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32(int weapon_idx, const sead::SafeString& name, bool x, f32 y);
    virtual void m33();
    virtual bool m34(ksys::as::ASList::Unk4* query);
    virtual bool m35();
    virtual int m36();

    // static_param at offset 0x50
    const int* mSeqBank_s{};
    // static_param at offset 0x58
    const int* mTargetBone_s{};
    // static_param at offset 0x60
    const bool* mIsNoRod_s{};
    bool _68 = false;
};

KSYS_CHECK_SIZE_NX150(ForkWeaponAttackBase, 0x70);

}  // namespace uking::action
