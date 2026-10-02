#pragma once

#include "Game/AI/Action/actionFlyMoveBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class BeeAttack : public FlyMoveBase {
    SEAD_RTTI_OVERRIDE(BeeAttack, FlyMoveBase)
public:
    explicit BeeAttack(const InitArg& arg);
    ~BeeAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0xc0
    const float* mThroughDist_s{};
    sead::Vector3f _c8;
    void m32(sead::Vector3f* target) override;
};

KSYS_CHECK_SIZE_NX150(BeeAttack, 0xd8);

}  // namespace uking::action
