#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>

namespace ksys::phys {
class StaticCompoundRigidBodyGroup;
}

namespace xlink2 {
class HandleSLink;
}

namespace uking::action {

class DungeonMove : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DungeonMove, ksys::act::ai::Action)
public:
    explicit DungeonMove(const InitArg& arg);
    ~DungeonMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m9() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAccel_s{};
    // dynamic_param at offset 0x28
    float* mDynMoveDis_d{};
    // map_unit_param at offset 0x30
    const int* mInitDgnPriority_m{};
    // map_unit_param at offset 0x38
    const int* mCameraPattern_m{};
    // map_unit_param at offset 0x40
    const float* mMoveSpeed_m{};
    // map_unit_param at offset 0x48
    const float* mCameraPower_m{};
    // map_unit_param at offset 0x50
    const float* mCameraRange_m{};
    sead::Vector3f _58 = sead::Vector3f::zero;
    sead::Vector3f _64 = sead::Vector3f::zero;
    f32 _70 = 0;
    f32 _74 = 0;
    int _78 = 0;
    ksys::phys::StaticCompoundRigidBodyGroup* _80 = nullptr;
    s32 _88 = -1;
    bool _8c = false;
    xlink2::HandleSLink* _90 = nullptr;
};

KSYS_CHECK_SIZE_NX150(DungeonMove, 0x98);

}  // namespace uking::action
