#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class EmitHalfLifeDamageSe : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(EmitHalfLifeDamageSe, ksys::act::ai::Behavior)
public:
    explicit EmitHalfLifeDamageSe(const InitArg& arg);
    ~EmitHalfLifeDamageSe() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

    /* 0x28 */ bool _28 = false;
};
KSYS_CHECK_SIZE_NX150(EmitHalfLifeDamageSe, 0x30);

}  // namespace uking::behavior
