#pragma once

#include "Game/AI/aiUnk_7102450058.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AddCarriedBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AddCarriedBase, ksys::act::ai::Ai)
public:
    explicit AddCarriedBase(const InitArg& arg);
    ~AddCarriedBase() override;

    bool hasUpdateForPreDeleteCb() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const float* mFailDistance_s{};
    // static_param at offset 0x40
    const bool* mIsRecoverCharCtrlAxis_s{};
    // static_param at offset 0x48
    const bool* mIsUseConstraint_s{};
    // static_param at offset 0x50
    sead::SafeString mHoldOnXLinkKey_s{};
    u32 _60 = 0;
    Unk_7102450298 _68{mActor};
};
KSYS_CHECK_SIZE_NX150(AddCarriedBase, 0xc0);

}  // namespace uking::ai
