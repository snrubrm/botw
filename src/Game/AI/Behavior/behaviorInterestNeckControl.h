#pragma once

#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/System/Timer.h"

namespace uking::behavior {

class InterestNeckControl : public ksys::act::ai::Behavior {
    SEAD_RTTI_OVERRIDE(InterestNeckControl, ksys::act::ai::Behavior)
public:
    explicit InterestNeckControl(const InitArg& arg);
    ~InterestNeckControl() override;
    bool m6(sead::Heap* heap) override;
    void m7() override;
    void m8() override;
    void m9() override;
    void loadParams() override;

    /* 0x28 */ const bool* mIgnorePlayerByTimePass_s{};
    /* 0x30 */ f32 _30 = 0;  // NPCIgnorePlayerTime (global parameter)
    /* 0x34 */ f32 _34 = 0;  // NPCCancelIgnorePlayerTime
    /* 0x38 */ f32 _38 = -1.0f;
    /* 0x3c */ s32 _3c = 0;
    /* 0x40 */ ksys::Timer _40;
    /* 0x4c */ ksys::Timer _4c;
};
KSYS_CHECK_SIZE_NX150(InterestNeckControl, 0x58);

}  // namespace uking::behavior
