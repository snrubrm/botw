#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class PlayerEmitInterest : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(PlayerEmitInterest, ksys::act::ai::Behavior)
public:
    explicit PlayerEmitInterest(const InitArg& arg);
    ~PlayerEmitInterest() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const int* mLevelBase_s{};
    /* 0x30 */ const int* mLevelNaked_s{};
    /* 0x38 */ const bool* mIsTargetNPC_s{};
};
KSYS_CHECK_SIZE_NX150(PlayerEmitInterest, 0x40);

}  // namespace uking::behavior
