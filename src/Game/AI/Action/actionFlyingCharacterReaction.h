#pragma once

#include <math/seadMatrix.h>
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

class FlyingCharacterReaction : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(FlyingCharacterReaction, ksys::act::ai::Action)
public:
    explicit FlyingCharacterReaction(const InitArg& arg);
    ~FlyingCharacterReaction() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();
    virtual void m33();

    // static_param at offset 0x20
    const float* mPosReduceRatio_s{};
    // static_param at offset 0x28
    const float* mRotReduceRatio_s{};
    // static_param at offset 0x30
    const bool* mIsControlRotation_s{};
    // static_param at offset 0x38
    const bool* mIsSetBackLastState_s{};
    sead::Matrix33f _40;
    bool _64 = false;
    ksys::act::CCAccessor mCCAccessor;
};

KSYS_CHECK_SIZE_NX150(FlyingCharacterReaction, 0x70);

}  // namespace uking::action
