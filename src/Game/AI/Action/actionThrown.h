#pragma once

#include "Game/AI/Action/actionActionEx.h"
#include "Game/AI/aiUnkDamageCallbacks.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class Thrown : public ActionEx {
    SEAD_RTTI_OVERRIDE(Thrown, ActionEx)
public:
    explicit Thrown(const InitArg& arg);
    ~Thrown() override = default;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool isFinished() const override;

protected:
    void calc_() override;

    virtual void m32(ksys::act::Actor* actor, const sead::Vector3f& vel,
                     const sead::Vector3f& ang_vel);

    // 0x71002974ec (CSV name; not decompiled: needs a ContactPointInfo::Iterator end test that
    // the header lacks)
    bool thrownStalfosPartsStuff() const;

    struct Params {
        // static_param at offset 0x20
        const int* mReactionLevel_s{};
        // static_param at offset 0x28
        const bool* mIsForceOnly_s{};
        // static_param at offset 0x30
        const bool* mIsOnImpact_s{};
        // static_param at offset 0x38
        sead::SafeString mAS_s{};
        // static_param at offset 0x48
        sead::SafeString mThrownKey_s{};
        // static_param at offset 0x58
        const sead::Vector3f* mRotSpd_s{};
        // dynamic_param at offset 0x60
        float* mPower_d{};
        // dynamic_param at offset 0x68
        bool* mIsShootByPlayer_d{};
        // dynamic_param at offset 0x70
        sead::Vector3f* mTargetDir_d{};
    };
    Params mParams;
    Unk_7102451970 _78;
    s32 _a0 = -1;
    bool _a4 = false;
    bool _a5 = false;
    bool _a6 = false;
    bool _a7 = false;
    f32 _a8 = 0;  // linear damping of the main body before enter_
    f32 _ac = 0;  // angular damping of the main body before enter_

};
KSYS_CHECK_SIZE_NX150(Thrown, 0xb0);

}  // namespace uking::action
