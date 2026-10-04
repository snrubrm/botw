#pragma once

#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "Game/AI/Action/actionForkEmitExpandField.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkEmitExpandFieldWithCreate : public ForkEmitExpandField {
    SEAD_RTTI_OVERRIDE(ForkEmitExpandFieldWithCreate, ForkEmitExpandField)
public:
    explicit ForkEmitExpandFieldWithCreate(const InitArg& arg);
    ~ForkEmitExpandFieldWithCreate() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    ksys::act::BaseProcLink& m32() override;

    // static_param at offset 0x90
    const float* mScaleTime_s{};
    // static_param at offset 0x98
    const bool* mIsReuseActor_s{};
    // static_param at offset 0xa0
    const bool* mIsSetPartsLink_s{};
    ksys::act::BaseProcLink _a8;
};
KSYS_CHECK_SIZE_NX150(ForkEmitExpandFieldWithCreate, 0xb8);

}  // namespace uking::action
