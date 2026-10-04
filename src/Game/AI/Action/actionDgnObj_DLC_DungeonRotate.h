#pragma once

#include "Game/AI/Action/actionDungeonRotateBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DgnObj_DLC_DungeonRotate : public DungeonRotateBase {
    SEAD_RTTI_OVERRIDE(DgnObj_DLC_DungeonRotate, DungeonRotateBase)
public:
    explicit DgnObj_DLC_DungeonRotate(const InitArg& arg);
    ~DgnObj_DLC_DungeonRotate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71000ee43c (declared only): out of line in the original.
    void sub_71000EE43C();
    void calc_() override;

    // map_unit_param at offset 0xc8
    const float* mGearRatio_m{};
    // map_unit_param at offset 0xd0
    const bool* mIsClockWiseRotation_m{};
    // aitree_variable at offset 0xd8
    float* mRotationOffset_a{};
    f32 _e0 = 0.0f;
    f32 _e4 = 1.0f;
    f32 _e8 = 0.0f;
};

KSYS_CHECK_SIZE_NX150(DgnObj_DLC_DungeonRotate, 0xf0);

}  // namespace uking::action
