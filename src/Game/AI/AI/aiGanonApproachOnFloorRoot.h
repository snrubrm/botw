#pragma once

#include <gsys/gsysModelAccessKey.h>
#include <math/seadVector.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace ksys::phys {
class RayCastForRequest;
}

namespace uking::ai {

class GanonApproachOnFloorRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(GanonApproachOnFloorRoot, ksys::act::ai::Ai)
public:
    explicit GanonApproachOnFloorRoot(const InitArg& arg);
    ~GanonApproachOnFloorRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    // 0x71003df5c4 (placeholder name)
    void sub_71003DF5C4(const sead::Vector3f& pos, const sead::Vector3f& dst_pos);

protected:
    // static_param at offset 0x38
    const float* mFinDist_s{};
    // static_param at offset 0x40
    const float* mApproachTime_s{};
    // static_param at offset 0x48
    const float* mFinFarDist_s{};
    // static_param at offset 0x50
    const float* mMoveFrontRate_s{};
    // static_param at offset 0x58
    const float* mMoveFrontLRRate_s{};
    // static_param at offset 0x60
    const float* mMoveBackLRRate_s{};
    // static_param at offset 0x68
    const float* mCloseDist_s{};
    // static_param at offset 0x70
    const float* mForbitAngMin_s{};
    // static_param at offset 0x78
    const float* mForbitAngMax_s{};
    // static_param at offset 0x80
    const float* mCheckPosAng0_s{};
    // static_param at offset 0x88
    const float* mCheckPosAng1_s{};
    // static_param at offset 0x90
    const float* mCheckPosAng2_s{};
    // static_param at offset 0x98
    const float* mCheckPosAng3_s{};
    // static_param at offset 0xa0
    const float* mCheckPosAng4_s{};
    // dynamic_param at offset 0xa8
    bool* mIsMoveSide_d{};
    // dynamic_param at offset 0xb0
    bool* mIsChangeable_d{};
    // dynamic_param at offset 0xb8
    sead::Vector3f* mTargetPos_d{};
    // dynamic_param at offset 0xc0
    sead::Vector3f* mMoveDstPos_d{};
    bool _c8{};
    ksys::Timer _cc;
    ksys::Timer _d8;
    ksys::Timer _e4;
    s32 _f0{};
    ksys::phys::RayCastForRequest* _f8[5];
    sead::Vector3f _120[5];
    sead::Vector3f _15c[15];
    f32 _210[15];
    sead::Vector3f _24c;
    gsys::BoneAccessKeyEx _258;
    s32 _290 = 5;
};
KSYS_CHECK_SIZE_NX150(GanonApproachOnFloorRoot, 0x298);

}  // namespace uking::ai
