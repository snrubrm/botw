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
    // 0x710017be48: sends the target (message 0x800003a with the payload at 0x68) to the parts actor of ball `idx`.
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
    // 0x68-0xc8: payload of message 0x800003a (sub_710017BE48).
    sead::Vector3f _68;
    u8 _74[0x80 - 0x74];
    ksys::act::BaseProcLink _80;
    f32 _90 = 0;
    sead::FixedSafeString<32> _98;
};
KSYS_CHECK_SIZE_NX150(GanonThrowFireBall, 0xd0);

}  // namespace uking::action
