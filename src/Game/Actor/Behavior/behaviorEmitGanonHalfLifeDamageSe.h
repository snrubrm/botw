#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class EmitGanonHalfLifeDamageSe : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(EmitGanonHalfLifeDamageSe, ksys::act::ai::Behavior)
public:
    explicit EmitGanonHalfLifeDamageSe(const InitArg& arg);
    ~EmitGanonHalfLifeDamageSe() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ bool _28 = false;
};
KSYS_CHECK_SIZE_NX150(EmitGanonHalfLifeDamageSe, 0x30);

}  // namespace uking::behavior
