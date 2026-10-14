#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class ElevatorBaseEmitPassingSe : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(ElevatorBaseEmitPassingSe, ksys::act::ai::Behavior)
public:
    explicit ElevatorBaseEmitPassingSe(const InitArg& arg);
    ~ElevatorBaseEmitPassingSe() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ bool _28 = false;
};
KSYS_CHECK_SIZE_NX150(ElevatorBaseEmitPassingSe, 0x30);

}  // namespace uking::behavior
