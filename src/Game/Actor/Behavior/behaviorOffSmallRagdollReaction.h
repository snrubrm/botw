#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class OffSmallRagdollReaction : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(OffSmallRagdollReaction, ksys::act::ai::Behavior)
public:
    explicit OffSmallRagdollReaction(const InitArg& arg);
    ~OffSmallRagdollReaction() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ bool _28 = true;
};
KSYS_CHECK_SIZE_NX150(OffSmallRagdollReaction, 0x30);

}  // namespace uking::behavior
