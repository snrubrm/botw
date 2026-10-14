#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class AnimalCounterFlagOn : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(AnimalCounterFlagOn, ksys::act::ai::Behavior)
public:
    explicit AnimalCounterFlagOn(const InitArg& arg);
    ~AnimalCounterFlagOn() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ bool* mAnimalEnableCounterFlag_a{};
};
KSYS_CHECK_SIZE_NX150(AnimalCounterFlagOn, 0x30);

}  // namespace uking::behavior
