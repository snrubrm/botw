#pragma once

#include <prim/seadEnum.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class EnemyTargetGearSelect : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(EnemyTargetGearSelect, ksys::act::ai::Ai)
public:
    explicit EnemyTargetGearSelect(const InitArg& arg);
    ~EnemyTargetGearSelect() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // The gear is an enum passed through the stack in the original (named local, compared with the parameter).
    SEAD_ENUM(Gear, _0, _1, _2, _3, _4, _5, _6, _7)

    // static_param at offset 0x38
    const int* mGearThreashold_s{};
    // static_param at offset 0x40
    const bool* mIsSelectEveryFrame_s{};
};

}  // namespace uking::ai
