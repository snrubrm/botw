#pragma once

#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class StaticCompoundRigidBodyGroup;
}

namespace uking::action {

class DungeonMoveReset : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DungeonMoveReset, ksys::act::ai::Action)
public:
    explicit DungeonMoveReset(const InitArg& arg);
    ~DungeonMoveReset() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mAccel_s{};
    // dynamic_param at offset 0x28
    float* mDynMoveDis_d{};
    // dynamic_param at offset 0x30
    float* mDynMoveSpeed_d{};
    // map_unit_param at offset 0x38
    const int* mInitDgnPriority_m{};
    sead::Vector3f _40 = sead::Vector3f::zero;
    sead::Vector3f _4c = sead::Vector3f::zero;
    f32 _58 = 0;
    f32 _5c = 0;
    int _60 = 0;
    ksys::phys::StaticCompoundRigidBodyGroup* _68 = nullptr;
    s32 _70 = -1;
    bool _74 = false;
};
KSYS_CHECK_SIZE_NX150(DungeonMoveReset, 0x78);

}  // namespace uking::action
