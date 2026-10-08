#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class InsectRoam : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(InsectRoam, ksys::act::ai::Ai)
public:
    explicit InsectRoam(const InitArg& arg);
    ~InsectRoam() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    void calc_() override;

    void changeToRoamWalk();
    void sub_710044ACE4(sead::Vector3f* pos, sead::Vector3f* dir);

protected:
    // static_param at offset 0x38
    const float* mTerritoryRadius_s{};
    // static_param at offset 0x40
    const float* mTerritoryRadiusRnd_s{};
    // static_param at offset 0x48
    const float* mMoveDist_s{};
    // static_param at offset 0x50
    const float* mMoveSpeed_s{};
    // dynamic_param at offset 0x58
    sead::Vector3f* mTargetPos_d{};
    u8 _60 = 0;
    f32 _64 = 0;
    sead::Vector3f _68;
    sead::Vector3f _74;
    sead::Vector3f _80;
    sead::Vector3f _8c;
    ksys::Timer _98;
    ksys::Timer _a4;
};
KSYS_CHECK_SIZE_NX150(InsectRoam, 0xb0);

}  // namespace uking::ai
