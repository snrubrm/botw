#pragma once

#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/System/Timer.h"
#include "KingSystem/System/VFRValue.h"

namespace uking::action {

class Tumble : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(Tumble, ksys::act::ai::Action)
public:
    explicit Tumble(const InitArg& arg);
    ~Tumble() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool isChangeable() const override;

protected:
    void calc_() override;

    // 0x710029d098 / 0x710029d1bc (placeholder names): the switch to the get-up phase ("DownBackWait") and the
    // per-frame update of the controller's target matrix (the Spine_1 bone of the ragdoll).
    void sub_710029D098();
    void sub_710029D1BC();

    /* 0x1c */ ksys::VFRValue _1c{0.0f};
    /* 0x28 */ ksys::VFRVec3f _28;
    /* 0x4c */ f32 _4c = 0;
    /* 0x50 */ f32 _50 = 0;
    /* 0x54 */ f32 _54 = -1.0f;
    /* 0x58 */ ksys::Timer _58{0.0f, 0.0f};
    /* 0x64 */ u8 _64[4];
    /* 0x68 */ Unk_7102451970 _68;  // 0x28 bytes
    /* 0x90 */ sead::Vector3f _90{0, 0, 0};
    /* 0x9c */ sead::Matrix33f _9c{0, 0, 0, 0, 0, 0, 0, 0, 0};
    /* 0xc0 */ sead::Vector3f _c0{0, 0, 0};
    /* 0xcc */ sead::Vector3f _cc{0, 0, 0};
    /* 0xd8 */ s32 _d8 = 0;
    /* 0xdc */ u8 _dc[4];
    // static_param at offset 0xe0
    const float* mTumblingTime_s{};
    // static_param at offset 0xe8
    const float* mGetUpTime_s{};
    // static_param at offset 0xf0
    const char* mLandCheckNode_s{};
    // static_param at offset 0xf8
    const float* mTumbleAngle_s{};
    // static_param at offset 0x100
    const float* mTumbleSpeed_s{};
    /* 0x108 */ s32 _108 = -1;
    /* 0x10c */ sead::Vector3f _10c{0, 0, 0};
};

}  // namespace uking::action
