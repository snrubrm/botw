#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ElevatorBaseEmitPassingSe : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ElevatorBaseEmitPassingSe, ksys::act::ai::Behavior)
public:
    explicit ElevatorBaseEmitPassingSe(const InitArg& arg);
    ~ElevatorBaseEmitPassingSe() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ bool _28 = false;
};
KSYS_CHECK_SIZE_NX150(ElevatorBaseEmitPassingSe, 0x30);

}  // namespace uking::behavior
