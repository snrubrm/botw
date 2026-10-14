#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class GreatGoddesStatueLightEffect : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(GreatGoddesStatueLightEffect, ksys::act::ai::Behavior)
public:
    explicit GreatGoddesStatueLightEffect(const InitArg& arg);
    ~GreatGoddesStatueLightEffect() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ sead::SafeString mFlagName_s{};
};
KSYS_CHECK_SIZE_NX150(GreatGoddesStatueLightEffect, 0x38);

}  // namespace uking::behavior
