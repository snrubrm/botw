#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SealNoPlayerNotice : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SealNoPlayerNotice, ksys::act::ai::Behavior)
public:
    explicit SealNoPlayerNotice(const InitArg& arg);
    ~SealNoPlayerNotice() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ int* mSealNoPlayerAwnRequestCount_a{};
};
KSYS_CHECK_SIZE_NX150(SealNoPlayerNotice, 0x30);

}  // namespace uking::behavior
