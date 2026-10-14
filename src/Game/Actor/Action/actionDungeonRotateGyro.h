#pragma once

#include <math/seadMatrix.h>

#include "KingSystem/ActorSystem/actAiAction.h"

namespace ksys::phys {
class StaticCompoundRigidBodyGroup;
}

namespace xlink2 {
class HandleSLink;
}

namespace uking::action {

class DungeonRotateGyro : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DungeonRotateGyro, ksys::act::ai::Action)
public:
    explicit DungeonRotateGyro(const InitArg& arg);
    ~DungeonRotateGyro() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mSlerpRatio_s{};
    // static_param at offset 0x28
    const bool* mIsUseInstParamSlerpRatio_s{};
    // map_unit_param at offset 0x30
    const int* mInitDgnPriority_m{};
    // map_unit_param at offset 0x38
    const float* mGyroSlerpRatio_m{};
    s32 _40 = -1;
    ksys::phys::StaticCompoundRigidBodyGroup* _48 = nullptr;
    sead::Matrix33f _50;
    sead::Matrix33f _74 = sead::Matrix33f::ident;
    sead::Matrix33f _98 = sead::Matrix33f::ident;
    sead::Matrix33f _bc = sead::Matrix33f::ident;
    sead::Matrix33f _e0 = sead::Matrix33f::ident;
    f32 _104;
    xlink2::HandleSLink* _108 = nullptr;
    u8 _110[0x128 - 0x110];
    u32 _128 = 0;
};
KSYS_CHECK_SIZE_NX150(DungeonRotateGyro, 0x130);

}  // namespace uking::action
