#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetRagdollBodyForceKeyframed : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetRagdollBodyForceKeyframed, ksys::act::ai::Behavior)
public:
    explicit SetRagdollBodyForceKeyframed(const InitArg& arg);
    ~SetRagdollBodyForceKeyframed() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void loadParams() override;
    void enter() override;
    void leave() override;

    /* 0x28 */ sead::SafeString mRagdollBodyName_s[2]{};
};
KSYS_CHECK_SIZE_NX150(SetRagdollBodyForceKeyframed, 0x48);

}  // namespace uking::behavior
