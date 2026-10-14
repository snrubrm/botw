#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyLiftShootItem : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyLiftShootItem, ksys::act::ai::Ai)
public:
    explicit EnemyLiftShootItem(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    void changeToLift();
    // 0x7100397db4 (placeholder name): the lift target position (the shoot item's previous position, else the
    // actor's forward point).
    sead::Vector3f sub_7100397DB4();
    // 0x7100397a64 (declared only): throws the lifted item (changes to the 投げつけ child).
    void sub_7100397A64();

protected:
    // static_param at offset 0x38
    const float* mShootAngle_s{};
    // static_param at offset 0x40
    const float* mShootDist_s{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0x50
    ksys::act::BaseProcLink* mShootItem_d{};
};

}  // namespace uking::ai
