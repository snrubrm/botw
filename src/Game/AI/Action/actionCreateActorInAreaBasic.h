#pragma once

#include "KingSystem/System/Timer.h"
#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CreateActorInAreaBasic : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(CreateActorInAreaBasic, ksys::act::ai::Action)
public:
    explicit CreateActorInAreaBasic(const InitArg& arg);
    ~CreateActorInAreaBasic() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    virtual void m33(sead::Vector3f* pos);
    virtual bool m34();

    // static_param at offset 0x20
    const int* mCreateBasePosNum_s{};
    // static_param at offset 0x28
    const float* mCreateNewActorIntervalFirst_s{};
    // static_param at offset 0x30
    const float* mCreateNewActorInterval_s{};
    // static_param at offset 0x38
    const float* mCreateContinueTime_s{};
    // static_param at offset 0x40
    const float* mAfterWaitTime_s{};
    // static_param at offset 0x48
    const bool* mIsAllowCreateNoSafeArea_s{};
    // static_param at offset 0x50
    sead::SafeString mCreateActorName_s{};
    // static_param at offset 0x60
    const sead::Vector3f* mBaseOffset_s{};
    // static_param at offset 0x68
    const sead::Vector3f* mCreateRandArea_s{};
    // static_param at offset 0x70
    const sead::Vector3f* mProhibitedCreateArea_s{};
    ksys::act::BaseProcHandle _78;
    ksys::act::BaseProcHandle _88;
    ksys::act::BaseProcHandle _98;
    ksys::Timer _a8;
    ksys::Timer _b4;
    ksys::Timer _c0;
    ksys::Timer _cc;
    f32 _d8 = 0.0f;
    f32 _dc = 0.0f;
};
KSYS_CHECK_SIZE_NX150(CreateActorInAreaBasic, 0xe0);

}  // namespace uking::action
