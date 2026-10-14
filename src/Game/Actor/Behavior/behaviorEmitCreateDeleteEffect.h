#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class EmitCreateDeleteEffect : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(EmitCreateDeleteEffect, ksys::act::ai::Behavior)
public:
    explicit EmitCreateDeleteEffect(const InitArg& arg);
    ~EmitCreateDeleteEffect() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ sead::SafeString mEffectName_s{};
};
KSYS_CHECK_SIZE_NX150(EmitCreateDeleteEffect, 0x38);

}  // namespace uking::behavior
