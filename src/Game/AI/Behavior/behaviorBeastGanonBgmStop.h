#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class BeastGanonBgmStop : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(BeastGanonBgmStop, ksys::act::ai::Behavior)
public:
    explicit BeastGanonBgmStop(const InitArg& arg);
    ~BeastGanonBgmStop() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

};
KSYS_CHECK_SIZE_NX150(BeastGanonBgmStop, 0x28);

}  // namespace uking::behavior
