#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiveCookResultForNpc : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(GiveCookResultForNpc, ksys::act::ai::Action)
public:
    explicit GiveCookResultForNpc(const InitArg& arg);
    ~GiveCookResultForNpc() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;

protected:
    bool oneShot_() override;
    s32 sub_710018B630();

    // dynamic_param at offset 0x20
    int* mCount_d{};
    // dynamic_param at offset 0x28
    sead::SafeString mPorchItemName_d{};
    // dynamic_param at offset 0x38
    sead::SafeString mCookEffectType_d{};
};

}  // namespace uking::action
