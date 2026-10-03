#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class GuardianMiniBeamAttackMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GuardianMiniBeamAttackMove, ksys::act::ai::Ai)
public:
    explicit GuardianMiniBeamAttackMove(const InitArg& arg);
    ~GuardianMiniBeamAttackMove() override;
    bool isChangeable() const override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void changeToMove();
    void sub_7100418694();
    bool sub_710041889C();
    void sub_710041896C();
    void sub_7100418D7C();

protected:
    // static_param at offset 0x38
    const int* mMoveTime_s{};
    // static_param at offset 0x40
    const int* mAttackInterval_s{};
    // static_param at offset 0x48
    const float* mBeamSpeed_s{};
    // static_param at offset 0x50
    sead::SafeString mBaseNode_s{};
    // dynamic_param at offset 0x60
    sead::Vector3f* mTargetPos_d{};
    // static_param at offset 0x68
    const float* mTargetDistOffset_s{};
    ksys::Timer _70{0, 0};
    ksys::Timer _7c{0, 0};
    ksys::act::BaseProcHandle _88;
    f32 _98 = 0;
};

}  // namespace uking::ai
