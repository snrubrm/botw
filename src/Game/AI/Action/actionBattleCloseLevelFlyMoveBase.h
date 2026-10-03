#pragma once

#include <math/seadMatrix.h>
#include "Game/AI/aiUnk_71006F3CC4.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class BattleCloseLevelFlyMoveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BattleCloseLevelFlyMoveBase, ksys::act::ai::Action)
public:
    explicit BattleCloseLevelFlyMoveBase(const InitArg& arg);
    ~BattleCloseLevelFlyMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mXZSpeed_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // static_param at offset 0x30
    const float* mFinRotate_s{};
    // static_param at offset 0x38
    const float* mHorizontalFinRadius_s{};
    // static_param at offset 0x40
    const float* mVerticalFinLength_s{};
    // static_param at offset 0x48
    const float* mTargetHeightOffset_s{};
    // static_param at offset 0x50
    const float* mRotRatio_s{};
    // static_param at offset 0x58
    const float* mRiseSpeed_s{};
    // static_param at offset 0x60
    const float* mDownSpeed_s{};
    // dynamic_param at offset 0x68
    sead::Vector3f* mTargetPos_d{};
    /* 0x70 */ ksys::VFRValue _70;
    /* 0x7c */ ksys::VFRValue _7c;
    /* 0x88 */ sead::Matrix33f _88;
    /* 0xac */ ksys::VFRValue _ac;
    /* 0xb8 */ sead::Vector3f _b8;
    /* 0xc4 */ ksys::act::CCAccessor _c4;
    /* 0xd0 */ Unk_7102450038 _d0{this};
};
KSYS_CHECK_SIZE_NX150(BattleCloseLevelFlyMoveBase, 0xf0);

}  // namespace uking::action
