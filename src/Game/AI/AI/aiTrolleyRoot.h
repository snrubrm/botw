#pragma once

#include <prim/seadDelegate.h>
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::phys {
class Constraint;
}

namespace uking::ai {

class TrolleyRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(TrolleyRoot, ksys::act::ai::Ai)
public:
    explicit TrolleyRoot(const InitArg& arg);
    ~TrolleyRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    // static_param at offset 0x38
    const float* mNearGoalDist_s{};
    // static_param at offset 0x40
    const float* mNearGoalLimitSpd_s{};
    // 0x71005d0cb4 (not decompiled): the DynamicActor _a70 callback.
    void sub_71005D0CB4(ksys::act::Unk_71006dc134* arg);

    // static_param at offset 0x48
    const float* mNearGoalReduceRate_s{};
    sead::Vector3f _50 = sead::Vector3f::zero;
    f32 _5c = 0.02f;
    ksys::act::BaseProcLink _60;
    Unk_7102450558 _70;
    sead::Vector3f _c0 = sead::Vector3f::zero;
    ksys::phys::Constraint* _d0 = nullptr;
    // Stored in DynamicActor::_a70 by init_ (handler 0x71005d0cb4, invoke 0x71005d21f0; same callback
    // shape as StoneBall_BRoot's).
    sead::Delegate1<TrolleyRoot, ksys::act::Unk_71006dc134*> _d8{this, &TrolleyRoot::sub_71005D0CB4};
};
KSYS_CHECK_SIZE_NX150(TrolleyRoot, 0xf8);

}  // namespace uking::ai
