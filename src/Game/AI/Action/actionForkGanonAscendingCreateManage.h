#pragma once

#include "Game/AI/aiUnk_71007444AC.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkGanonAscendingCreateManage : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ForkGanonAscendingCreateManage, ksys::act::ai::Action)
public:
    explicit ForkGanonAscendingCreateManage(const InitArg& arg);
    ~ForkGanonAscendingCreateManage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool updateForPreDelete() override;
    bool hasUpdateForPreDeleteCb() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    const int* mMaxNum_s{};
    // static_param at offset 0x28
    sead::SafeString mCreateGrudgeName_s{};
    Unk_71007444ac _38;
    Unk_7102450a38 _48;
};
KSYS_CHECK_SIZE_NX150(ForkGanonAscendingCreateManage, 0xb8);

}  // namespace uking::action
