#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class Invincible : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(Invincible, ksys::act::ai::Behavior)
public:
    explicit Invincible(const InitArg& arg);
    ~Invincible() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(Invincible, 0x28);

}  // namespace uking::behavior
