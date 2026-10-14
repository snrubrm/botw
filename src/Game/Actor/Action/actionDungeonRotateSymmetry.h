#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace xlink2 {
class HandleSLink;
}

namespace ksys::phys {
class StaticCompoundRigidBodyGroup;
}

namespace uking::action {

class DungeonRotateSymmetry : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DungeonRotateSymmetry, ksys::act::ai::Action)
public:
    explicit DungeonRotateSymmetry(const InitArg& arg);
    ~DungeonRotateSymmetry() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m9() override;

    // map_unit_param at offset 0x20
    const int* mInitDgnPriority_m{};
    // map_unit_param at offset 0x28
    const int* mCameraPattern_m{};
    // map_unit_param at offset 0x30
    const int* mRemainsPartType_m{};
    // map_unit_param at offset 0x38
    const float* mTiltAngle_m{};
    // map_unit_param at offset 0x40
    const float* mTiltAngularSpeed_m{};
    // map_unit_param at offset 0x48
    const float* mInitDgnRotRad_m{};
    // map_unit_param at offset 0x50
    const float* mCameraPower_m{};
    // map_unit_param at offset 0x58
    const float* mCameraRange_m{};
    sead::Vector3f _60 = sead::Vector3f::zero;
    f32 _6c = 0;
    f32 _70 = 0;
    f32 _74 = 0;
    ksys::phys::StaticCompoundRigidBodyGroup* _78 = nullptr;
    s32 _80 = -1;
    bool _84 = false;
    bool _85 = false;
    bool _86 = false;
    xlink2::HandleSLink* _88 = nullptr;
    u32 _90 = 0;
};
KSYS_CHECK_SIZE_NX150(DungeonRotateSymmetry, 0x98);

}  // namespace uking::action
