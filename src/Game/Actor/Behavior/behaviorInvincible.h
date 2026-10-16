#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class Invincible : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(Invincible, ksys::act::ai::Behavior)
public:
    explicit Invincible(const InitArg& arg);
    ~Invincible() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(Invincible, 0x28);

}  // namespace uking::behavior
