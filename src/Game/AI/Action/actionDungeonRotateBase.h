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

class DungeonRotateBase : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DungeonRotateBase, ksys::act::ai::Action)
public:
    explicit DungeonRotateBase(const InitArg& arg);
    ~DungeonRotateBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void m9() override;

protected:
    void calc_() override;
    virtual float m32();
    virtual void m33();
    virtual void m34(f32 x);
    virtual void m35();

    // static_param at offset 0x20
    const int* mRotateAxisIndex_s{};
    // map_unit_param at offset 0x28
    const int* mInitDgnPriority_m{};
    // map_unit_param at offset 0x30
    const int* mCameraPattern_m{};
    // map_unit_param at offset 0x38
    const int* mRemainsPartType_m{};
    // map_unit_param at offset 0x40
    const float* mTiltAngularSpeed_m{};
    // map_unit_param at offset 0x48
    const float* mInitDgnRotRad_m{};
    // map_unit_param at offset 0x50
    const float* mCameraPower_m{};
    // map_unit_param at offset 0x58
    const float* mCameraRange_m{};
    // map_unit_param at offset 0x60
    const float* mVelocityControlRate_m{};
    // map_unit_param at offset 0x68
    const float* mAngleVelocityControlAccelDeg_m{};
    sead::Vector3f _70 = sead::Vector3f::ey;
    int _7c = 0;
    f32 _80 = 0;
    f32 _84 = 0;
    f32 _88 = 0;
    f32 _8c = 0;
    ksys::phys::StaticCompoundRigidBodyGroup* _90 = nullptr;
    s32 _98 = -1;
    u32 _9c;
    xlink2::HandleSLink* _a0 = nullptr;
    xlink2::HandleSLink* _a8 = nullptr;
    u32 _b0 = 0;
    u8 _b4 = 0;
    bool _b5 = false;
    f32 _b8 = 1.0f;
    f32 _bc = 100.0f;
    f32 _c0 = 100.0f;
    bool _c4 = false;
};

KSYS_CHECK_SIZE_NX150(DungeonRotateBase, 0xc8);

}  // namespace uking::action
