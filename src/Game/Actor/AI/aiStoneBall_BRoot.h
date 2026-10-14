#pragma once

#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class StoneBall_BRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(StoneBall_BRoot, ksys::act::ai::Ai)
public:
    explicit StoneBall_BRoot(const InitArg& arg);
    ~StoneBall_BRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    // Handler of the delegate `_50` (called by DynamicActor::m36 through the actor's `_a70` with the impulse about
    // to be applied): scales the impulse by the amplify powers depending on what hit the ball.
    void scaleReceivedImpulseMaybe(ksys::act::Unk_71006dc134* arg);

protected:
    // static_param at offset 0x38
    const float* mWeaponImpulseAmplifyPower_s{};
    // static_param at offset 0x40
    const float* mBombImpulseAmplifyPower_s{};
    // static_param at offset 0x48
    const float* mDoubleBombImpulseAmplifyPower_s{};
    sead::Delegate1<StoneBall_BRoot, ksys::act::Unk_71006dc134*> _50{
        this, &StoneBall_BRoot::scaleReceivedImpulseMaybe};
    f32 _70{};
};
KSYS_CHECK_SIZE_NX150(StoneBall_BRoot, 0x78);

}  // namespace uking::ai
