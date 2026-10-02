#pragma once

#include <container/seadBuffer.h>
#include <gsys/gsysModelAccessKey.h>
#include <math/seadMatrix.h>
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DragonMoveTo : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(DragonMoveTo, ksys::act::ai::Action)
public:
    explicit DragonMoveTo(const InitArg& arg);
    ~DragonMoveTo() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const float* mRollMax_s{};
    // static_param at offset 0x28
    const float* mRollSpeed_s{};
    // static_param at offset 0x30
    const float* mRollMaxSpeed_s{};
    // static_param at offset 0x38
    const float* mRollAmount_s{};
    // static_param at offset 0x40
    const float* mRestoreUp_s{};
    // static_param at offset 0x48
    const float* mBackAdjustAngle_s{};
    // static_param at offset 0x50
    const float* mBackAdjustRestoreUp_s{};
    // static_param at offset 0x58
    const float* mFixAngle_s{};
    // static_param at offset 0x60
    sead::SafeString mASName_s{};
    // dynamic_param at offset 0x70
    sead::Vector3f* mFrontDir_d{};
    // dynamic_param at offset 0x78
    sead::Vector3f* mTargetPos_d{};
    // An xlink effect with a timer (layout from the ctor).
    struct Unk1 {
        Unk_71012419b4 handle{};
        f32 _20 = -1.0f;
        bool _24 = false;
    };

    Unk1 _80;
    Unk1 _a8;
    Unk1 _d0;
    // 18 bones (names in a table of the TU's static data), searched by init_.
    sead::Buffer<gsys::BoneAccessKeyEx> _f8;
    sead::Matrix34f _108 = sead::Matrix34f::ident;
    sead::Vector3f _138 = sead::Vector3f::ey;
    u32 _144 = 0;
    u32 _148 = 0;
};
KSYS_CHECK_SIZE_NX150(DragonMoveTo, 0x150);

}  // namespace uking::action
