#pragma once

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
    u64 _a8 = 0;
    u64 _b0 = 0;
    u64 _b8 = 0;
    u64 _c0 = 0;
    u64 _c8 = 0;
    u64 _d0 = 0;
    u64 _d8 = 0;
};
KSYS_CHECK_SIZE_NX150(CreateActorInAreaBasic, 0xe0);

}  // namespace uking::action
