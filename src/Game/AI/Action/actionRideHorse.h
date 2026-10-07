#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"

namespace ksys::act {
class ActorLinkConstDataAccess;
}

namespace ksys::phys {
class CharacterController;
}

namespace uking::action {

class RideHorse : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(RideHorse, ksys::act::ai::Action)
public:
    explicit RideHorse(const InitArg& arg);
    ~RideHorse() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mJumpHeightOffset_s{};
    // static_param at offset 0x28
    const float* mMaxSpeed_s{};
    // static_param at offset 0x30
    const float* mFarRotSpeed_s{};
    // static_param at offset 0x38
    const float* mNearRotSpeed_s{};
    // static_param at offset 0x40
    const float* mRideRotSpeed_s{};
    // static_param at offset 0x48
    const float* mLoopASInterpolateTime_s{};
    // static_param at offset 0x50
    const sead::Vector3f* mPredictedRidePosOffset_s{};
    // static_param at offset 0x58
    const sead::Vector3f* mPreRideSklRootOffset_s{};
    // dynamic_param at offset 0x60
    ksys::act::BaseProcLink* mTargetActor_d{};
    s32 _68 = 0;
    sead::Matrix33f _6c;
    ksys::act::ModelBindInfo _90;
    // FIXME: fields not decompiled yet (written by calc_)
    u8 _130[0x16c - 0x130];
    f32 _16c = 1.0f;
    f32 _170 = 0;
    f32 _174 = 0;
    u64 _178 = 0;
    bool _180 = false;

    // 0x710023a4c8 (declaration only)
    void sub_710023A4C8();
    // 0x7100239f8c (placeholder name): starts the "HorseRideonMove" AS once and turns towards the target (the rotation
    // speed depends on the distance `_170` against `_174`).
    void sub_7100239F8C(ksys::phys::CharacterController* controller, ksys::act::ActorLinkConstDataAccess* accessor);
    // 0x710023a6b0 (placeholder name): turns the actor so that it faces the direction of the horse accessor.
    void sub_710023A6B0(f32 rate, ksys::phys::CharacterController* controller,
                        ksys::act::ActorLinkConstDataAccess* accessor);
    // 0x710023a050 (placeholder name): whether the linked actor is the one this actor is attached to.
    bool sub_710023A050(ksys::act::BaseProcLink* link);
};
KSYS_CHECK_SIZE_NX150(RideHorse, 0x188);

}  // namespace uking::action
