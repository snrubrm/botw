#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class GanonNearAttackOnFloorRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonNearAttackOnFloorRoot, ksys::act::ai::Ai)
public:
    explicit GanonNearAttackOnFloorRoot(const InitArg& arg);
    ~GanonNearAttackOnFloorRoot() override;
    void calc_() override;

    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    void sub_71003EC980();
    // 0x71003ecf34 (placeholder name)
    void changeToGreatswordAttack();
    // 0x71003ed028 (placeholder name)
    void changeToGreatswordSideAttack();
    // 0x71003ed11c (placeholder name)
    void changeToSwordAttack();

protected:
    // static_param at offset 0x38
    const float* mNearDist_s{};
    // dynamic_param at offset 0x40
    bool* mIsCounter_d{};
    // dynamic_param at offset 0x48
    bool* mIsPrevBeam_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mTargetPos_d{};
    int _58{};
};

}  // namespace uking::ai
