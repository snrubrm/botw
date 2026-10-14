#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class CreateActorWithTarget : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(CreateActorWithTarget, ksys::act::ai::Ai)
public:
    explicit CreateActorWithTarget(const InitArg& arg);
    ~CreateActorWithTarget() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    virtual void m34();
    virtual sead::Vector3f m35();
    virtual bool m36();
    virtual void m37(ksys::act::BaseProcHandle* handle);
    void sub_710035A00C(ksys::act::InstParamPack* pack, const sead::Vector3f* pos);

protected:
    // static_param at offset 0x38
    const int* mCreateNewActorInterval_s{};
    // static_param at offset 0x40
    const int* mCreateBasePosNum_s{};
    // static_param at offset 0x48
    const float* mCreateContinueTime_s{};
    // static_param at offset 0x50
    const float* mAfterWaitTime_s{};
    // static_param at offset 0x58
    const bool* mIsAllowCreateNoSafeArea_s{};
    // static_param at offset 0x60
    const bool* mIsRotateTargetDir_s{};
    // static_param at offset 0x68
    sead::SafeString mCreateActorName_s{};
    // static_param at offset 0x78
    const sead::Vector3f* mBaseOffset_s{};
    // static_param at offset 0x80
    const sead::Vector3f* mCreateRandArea_s{};
    // static_param at offset 0x88
    const sead::Vector3f* mProhibitedCreateArea_s{};
    // dynamic_param at offset 0x90
    sead::Vector3f* mTargetPos_d{};
    ksys::Timer _98;
    ksys::Timer _a4;
    ksys::Timer _b0;
    ksys::act::BaseProcHandle _c0[3];
    s32 _f0 = 0;
    f32 _f4 = 0;
    ksys::Timer _f8;
};

}  // namespace uking::ai
