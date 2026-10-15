#pragma once

#include "Game/Actor/Action/actionGuardianActionBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GuardianMoveToPosition : public GuardianActionBase {
    SEAD_RTTI_OVERRIDE(GuardianMoveToPosition, GuardianActionBase)
public:
    explicit GuardianMoveToPosition(const InitArg& arg);
    ~GuardianMoveToPosition() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m0(Data* data, ksys::act::Actor* actor) override;

protected:
    void calc_() override;

    // 0x710019992c: movement data towards DynTargetPos in a straight line (the actor's own parameters select it).
    void sub_710019992C(Data* data);
    // Movement data from the guardian's path state.
    void sub_7100199AD4(Data* data, ksys::act::Actor* actor);

    // static_param at offset 0x28
    const float* mSpeed_s{};
    // static_param at offset 0x30
    const bool* mDecelerate_s{};
    // dynamic_param at offset 0x38
    sead::Vector3f* mDynTargetPos_d{};
    // dynamic_param at offset 0x40
    sead::Vector3f* mDynStartPos_d{};
    // Timer (seconds) between navmesh queries in calc_
    f32 _48 = 0.0f;
};

}  // namespace uking::action
