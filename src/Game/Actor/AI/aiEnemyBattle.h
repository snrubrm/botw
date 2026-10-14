#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class EnemyBattle : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyBattle, ksys::act::ai::Ai)
public:
    explicit EnemyBattle(const InitArg& arg);

    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34(ksys::act::ai::InlineParamPack* params);
    virtual ksys::act::BaseProcLink& m35();
    virtual void m36(sead::Vector3f* pos);
    virtual void m37();
    virtual void m38();
    virtual bool m39();
    virtual bool m40();
    virtual bool m41() { return true; }
    virtual bool m42() { return !m41(); }
    virtual void m43(ksys::act::ai::InlineParamPack* params) {}

    // 0x7100381e58: Enemy::_e68 = Timer(time, time) (nothing for a negative time).
    void sub_7100381E58(s32 time);
    void sub_7100381ED4();
    // 0x7100381e7c: acc::PlayerBase::x_13() of the actor m35() points to.
    bool sub_7100381E7C();
    bool sub_7100382558();
    // 0x7100381d68: Actor::m140() of the Enemy's `_e08` link target, else of the m35() target.
    bool sub_7100381D68();

protected:
    // static_param at offset 0x38
    const int* mRetFrmGrdAtkTimer_s{};
    // static_param at offset 0x40
    const int* mRetFrmGrdAtkPrcTimer_s{};
    // static_param at offset 0x48
    const int* mRetFrmDmgAtkTimer_s{};
    // static_param at offset 0x50
    const int* mGlobalNoAtkTime_s{};
    // static_param at offset 0x58
    const int* mGlobalNoAtkTimeRnd_s{};
    // static_param at offset 0x60
    const float* mAttackAngle_s{};
    // static_param at offset 0x68
    const float* mAttackIntervalIntensity_s{};
    // static_param at offset 0x70
    const float* mDisplayCheckRadius_s{};
    // static_param at offset 0x78
    const bool* mIsUpdateNoticeState_s{};
    // static_param at offset 0x80
    const bool* mIsCheckLineReachable_s{};
    bool _88{};
};

}  // namespace uking::ai
