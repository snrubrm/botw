#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class EmitCreateDeleteEffect : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(EmitCreateDeleteEffect, ksys::act::ai::Behavior)
public:
    explicit EmitCreateDeleteEffect(const InitArg& arg);
    ~EmitCreateDeleteEffect() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ sead::SafeString mEffectName_s{};
};
KSYS_CHECK_SIZE_NX150(EmitCreateDeleteEffect, 0x38);

}  // namespace uking::behavior
