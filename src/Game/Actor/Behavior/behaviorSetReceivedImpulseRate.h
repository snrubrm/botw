#pragma once

#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"

namespace uking::behavior {

class SetReceivedImpulseRate : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(SetReceivedImpulseRate, ksys::act::ai::Behavior)
public:
    explicit SetReceivedImpulseRate(const InitArg& arg);
    ~SetReceivedImpulseRate() override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;
    bool m6(sead::Heap* heap) override;
    void sub_710063E528(ksys::act::Unk_71006dc134* arg);

    /* 0x28 */ const float* mImpulseRate_s{};
    /* 0x30 */ sead::Delegate1<SetReceivedImpulseRate, ksys::act::Unk_71006dc134*> _30{
        this, &SetReceivedImpulseRate::sub_710063E528};
};
KSYS_CHECK_SIZE_NX150(SetReceivedImpulseRate, 0x50);

}  // namespace uking::behavior
