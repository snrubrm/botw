#pragma once

#include "Game/AI/AI/aiSeqTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqPursuit : public SeqTwoAction {
    SEAD_RTTI_OVERRIDE(SeqPursuit, SeqTwoAction)
public:
    explicit SeqPursuit(const InitArg& arg);
    ~SeqPursuit() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

    bool m34() const override;

protected:
    // static_param at offset 0x50
    const int* mPursuitPer_s{};
    // static_param at offset 0x58
    const int* mWeaponIdx_s{};
    // static_param at offset 0x60
    const float* mPursuitDist_s{};
    // static_param at offset 0x68
    const bool* mIsEndPursuit_s{};
    // static_param at offset 0x70
    const bool* mIsGuardNoPursuit_s{};
    bool _78 = false;
    bool _79 = false;
};
KSYS_CHECK_SIZE_NX150(SeqPursuit, 0x80);

}  // namespace uking::ai
