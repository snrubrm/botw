#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetRagdollBodyForceKeyframed : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetRagdollBodyForceKeyframed, ksys::act::ai::Behavior)
public:
    explicit SetRagdollBodyForceKeyframed(const InitArg& arg);
    ~SetRagdollBodyForceKeyframed() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void loadParams() override;
    void m8() override;  // not decompiled yet (0x710063e16c)
    void m9() override;  // not decompiled yet (0x710063e1e0)

    /* 0x28 */ sead::SafeString _28{};
    /* 0x38 */ sead::SafeString _38{};
};
KSYS_CHECK_SIZE_NX150(SetRagdollBodyForceKeyframed, 0x48);

}  // namespace uking::behavior
