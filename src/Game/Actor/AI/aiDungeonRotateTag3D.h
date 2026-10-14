#pragma once

#include <container/seadSafeArray.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <xlink2/xlink2Handle.h>
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class StaticCompoundRigidBodyGroup;
}

namespace uking::ai {

class DungeonRotateTag3D : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(DungeonRotateTag3D, ksys::act::ai::Ai)
public:
    explicit DungeonRotateTag3D(const InitArg& arg);
    ~DungeonRotateTag3D() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    virtual bool m34(s32* axis);
    virtual void m35();
    virtual void m36();

protected:
    // static_param at offset 0x38
    const float* mTargetRad_s{};
    // map_unit_param at offset 0x40
    const int* mCameraPattern_m{};
    // map_unit_param at offset 0x48
    const int* mRemainsPartType_m{};
    // map_unit_param at offset 0x50
    const float* mTiltAngularSpeed_m{};
    // map_unit_param at offset 0x58
    const float* mCameraPower_m{};
    // map_unit_param at offset 0x60
    const float* mCameraRange_m{};
    // Last seen state of the six axis signals (X, Y, Z, -X, -Y, -Z).
    sead::SafeArray<bool, 6> _68;
    ksys::phys::StaticCompoundRigidBodyGroup* _70 = nullptr;
    sead::Matrix34f _78 = sead::Matrix34f::ident;
    sead::Matrix34f _a8 = sead::Matrix34f::ident;
    sead::Vector3f _d8 = sead::Vector3f::zero;
    s32 _e4 = -1;
    u32 _e8 = 0;
    f32 _ec = 0;
    f32 _f0 = 0;
    bool _f4 = false;
    bool _f5 = false;
    f32 _f8 = 0;
    // xlink2 event handle (allocated in init_, faded in leave_)
    xlink2::HandleSLink* _100 = nullptr;
    u32 _108 = 0;
};
KSYS_CHECK_SIZE_NX150(DungeonRotateTag3D, 0x110);

}  // namespace uking::ai
