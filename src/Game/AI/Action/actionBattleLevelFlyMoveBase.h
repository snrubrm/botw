#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class BattleLevelFlyMoveBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(BattleLevelFlyMoveBase, ksys::act::ai::Action)
public:
    explicit BattleLevelFlyMoveBase(const InitArg& arg);
    ~BattleLevelFlyMoveBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSpeed_s{};
    // static_param at offset 0x28
    const float* mRotSpd_s{};
    // static_param at offset 0x30
    const float* mFinRotate_s{};
    // static_param at offset 0x38
    const float* mFinRadius_s{};
    // static_param at offset 0x40
    const float* mTargetHeightOffset_s{};
    // static_param at offset 0x48
    const float* mRotRatio_s{};
    // static_param at offset 0x50
    const float* mCheckStopSpeed_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    ksys::VFRVec3f _60;
    sead::Vector3f _84{0, 0, 0};
    sead::Vector3f _90{0, 0, 0};
    sead::Matrix33f _9c;
    ksys::VFRValue _c0;
    ksys::act::CCAccessor _cc;
};
KSYS_CHECK_SIZE_NX150(BattleLevelFlyMoveBase, 0xd8);

}  // namespace uking::action
