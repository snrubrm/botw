#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace uking::ai {

class EnemyCutRope : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyCutRope, ksys::act::ai::Ai)
public:
    explicit EnemyCutRope(const InitArg& arg);
    ~EnemyCutRope() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    // 0x71003864f8 / 0x7100386610 / 0x7100386728 (placeholder names)
    void changeToCut();
    void changeToRotate();
    void changeToApproach();

protected:
    // static_param at offset 0x38
    const int* mWeaponIdx_s{};
    // static_param at offset 0x40
    const float* mCutDist_s{};
    // static_param at offset 0x48
    const float* mCutAngle_s{};
    // static_param at offset 0x50
    const bool* mCutFlyAttack_s{};
    // dynamic_param at offset 0x58
    ksys::act::BaseProcLink* mTargetActor_d{};
    // dynamic_param at offset 0x60
    ksys::MesTransceiverId* mCommanderID_d{};
    int _68 = 3;
};

}  // namespace uking::ai
