#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::action {

class GanonThrowFireBall : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GanonThrowFireBall, ksys::act::ai::Action)
public:
    explicit GanonThrowFireBall(const InitArg& arg);
    ~GanonThrowFireBall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    void calc_() override;
    // inline in the original (emitted out of line in this TU); signature is a guess
    virtual const sead::SafeString& m32(int idx);
    // 0x710017c0fc: `out->set(0, *mBallAppearOffset_s, 0)`; MultiIce / MultiTornado pass `idx` through.
    virtual void m33(sead::Vector3f* out, int idx);
    // 0x710017bba0 (declared only, 576 B): throws ball `idx` (parts actor / bone matrix + setProperties).
    void sub_710017BBA0(int idx);
    // 0x710017be48 (declared only, 352 B).
    void sub_710017BE48(int idx);

    // static_param at offset 0x20
    const float* mInitVelocity_s{};
    // static_param at offset 0x28
    const float* mFireBallScale_s{};
    // static_param at offset 0x30
    const float* mBallAppearOffset_s{};
    // static_param at offset 0x38
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x48
    sead::SafeString mThrowPartsName_d{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x60
    ksys::act::BaseProcLink* mTargetActor_d{};
    u8 _68[0x18];
    ksys::act::BaseProcLink _80;
    s32 _90 = 0;
    sead::FixedSafeString<32> _98;
};
KSYS_CHECK_SIZE_NX150(GanonThrowFireBall, 0xd0);

}  // namespace uking::action
