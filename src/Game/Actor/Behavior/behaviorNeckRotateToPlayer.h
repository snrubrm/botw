#pragma once

#include "Game/Actor/Behavior/behaviorNeckControl.h"

namespace uking::behavior {

class NeckRotateToPlayer : public NeckControl {
    SEAD_RTTI_OVERRIDE(NeckRotateToPlayer, NeckControl)
public:
    explicit NeckRotateToPlayer(const InitArg& arg);
    ~NeckRotateToPlayer() override;
    bool init_(sead::Heap* heap) override;
    void calc() override;
    void enter() override;
    void leave() override;
    void loadParams() override;
    void m15(sead::Vector3f* out) override;

};
KSYS_CHECK_SIZE_NX150(NeckRotateToPlayer, 0x38);

}  // namespace uking::behavior
