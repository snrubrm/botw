#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class BreathAttackEnemyBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(BreathAttackEnemyBattle, ksys::act::ai::Ai)
public:
    explicit BreathAttackEnemyBattle(const InitArg& arg);
    ~BreathAttackEnemyBattle() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual ksys::act::BaseProcLink& m34();
    virtual const sead::Vector3f* m35();
    virtual const sead::SafeString& m36();
    virtual void m37();
    virtual bool m38();
    virtual bool m39();
    virtual bool m40();
    virtual void m41();
    virtual void m42();
    virtual void m43();
    virtual bool m44();

    void sub_710033E970();
    void sub_710033EA88();
    void sub_710033F27C(s32 time);
    // The position of the actor of m34().
    void sub_710033EDD0(sead::Vector3f* out);
protected:
    // static_param at offset 0x38
    const int* mEnlargeTime_s{};
    // static_param at offset 0x40
    const float* mAttackAngle_s{};
    // static_param at offset 0x48
    const float* mAttackRatio_s{};
    // static_param at offset 0x50
    const float* mBreathSize_s{};
    // static_param at offset 0x58
    const float* mAttackIntervalIntensity_s{};
    // static_param at offset 0x60
    const int* mGlobalNoAtkTime_s{};
    // static_param at offset 0x68
    const bool* mIsEndAfterAttack_s{};
    // static_param at offset 0x70
    const bool* mIsDeleteBreath_s{};
    // static_param at offset 0x78
    const bool* mIsUpdateNoticeState_s{};
    // static_param at offset 0x80
    sead::SafeString mBreathName_s{};
    ksys::act::BaseProcHandle _90;
    ksys::act::BaseProcLink _a0;
};

}  // namespace uking::ai
