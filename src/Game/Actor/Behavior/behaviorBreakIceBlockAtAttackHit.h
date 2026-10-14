#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class BreakIceBlockAtAttackHit : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(BreakIceBlockAtAttackHit, ksys::act::ai::Behavior)
public:
    explicit BreakIceBlockAtAttackHit(const InitArg& arg);
    ~BreakIceBlockAtAttackHit() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(BreakIceBlockAtAttackHit, 0x28);

}  // namespace uking::behavior
