#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetForceSmallRagdoll : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetForceSmallRagdoll, ksys::act::ai::Behavior)
public:
    explicit SetForceSmallRagdoll(const InitArg& arg);
    ~SetForceSmallRagdoll() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(SetForceSmallRagdoll, 0x28);

}  // namespace uking::behavior
