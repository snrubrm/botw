#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class AnimalCounterFlagOn : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AnimalCounterFlagOn, ksys::act::ai::Behavior)
public:
    explicit AnimalCounterFlagOn(const InitArg& arg);
    ~AnimalCounterFlagOn() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ bool* mAnimalEnableCounterFlag_a{};
};
KSYS_CHECK_SIZE_NX150(AnimalCounterFlagOn, 0x30);

}  // namespace uking::behavior
