#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class AwarenessScaleByASEvent : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AwarenessScaleByASEvent, ksys::act::ai::Behavior)
public:
    explicit AwarenessScaleByASEvent(const InitArg& arg);
    ~AwarenessScaleByASEvent() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(AwarenessScaleByASEvent, 0x28);

}  // namespace uking::behavior
