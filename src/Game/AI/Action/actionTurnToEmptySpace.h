#pragma once

#include "Game/AI/Action/actionTurnAndLookToObjNotAnimDriven.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class TurnToEmptySpace : public TurnAndLookToObjNotAnimDriven {
    SEAD_RTTI_OVERRIDE(TurnToEmptySpace, TurnAndLookToObjNotAnimDriven)
public:
    explicit TurnToEmptySpace(const InitArg& arg);
    ~TurnToEmptySpace() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    sead::Vector3f* m39() override { return &_150; }
    // 0x71002a29cc (declared only, 1.8 KB): sphere casts around the actor to find the empty direction
    // (writes `_150`); called by enter_. Placeholder name.
    void sub_71002A29CC();

    // static_param at offset 0x128
    const float* mCheckDistance_s{};
    // static_param at offset 0x130
    const float* mCheckAngOffset_s{};
    // static_param at offset 0x138
    const float* mCheckShapeRadius_s{};
    // static_param at offset 0x140
    const float* mCastOffset_s{};
    // static_param at offset 0x148
    const float* mCheckAngOffsetX_s{};
    /* 0x150 */ sead::Vector3f _150;
};
KSYS_CHECK_SIZE_NX150(TurnToEmptySpace, 0x160);

}  // namespace uking::action
