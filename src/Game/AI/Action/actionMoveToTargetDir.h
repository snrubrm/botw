#pragma once

#include "Game/AI/Action/actionMoveToTargetBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class MoveToTargetDir : public MoveToTargetBase {
    SEAD_RTTI_OVERRIDE(MoveToTargetDir, MoveToTargetBase)
public:
    explicit MoveToTargetDir(const InitArg& arg);
    ~MoveToTargetDir() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m32(sead::Vector3f* pos, const sead::Vector3f* target) override;
    f32 m33() override;

    // dynamic_param at offset 0x40
    sead::Vector3f* mFrontDir_d{};
    // dynamic_param at offset 0x48
    sead::Vector3f* mDynTargetPos_d{};
    // dynamic_param at offset 0x50
    sead::Vector3f* mDynStartPos_d{};
    // map_unit_param at offset 0x58
    const float* mRailMoveSpeed_m{};
    sead::Vector3f _60 = sead::Vector3f::zero;
};

KSYS_CHECK_SIZE_NX150(MoveToTargetDir, 0x70);

}  // namespace uking::action
