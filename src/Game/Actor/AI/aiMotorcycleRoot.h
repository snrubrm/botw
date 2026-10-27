#pragma once

#include <math/seadMatrix.h>
#include <prim/seadEnum.h>
#include "Game/Actor/AI/aiHorseRiddenStatusSelector.h"
#include "Game/Actor/aiFlagByte.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking {
class MotorcycleMgr;
}

namespace uking::act {
class Motorcycle;
class Unk_7100e8b2b8;
}  // namespace uking::act

namespace uking::ai {

class MotorcycleRoot : public HorseRiddenStatusSelector {
    SEAD_RTTI_OVERRIDE(MotorcycleRoot, HorseRiddenStatusSelector)
public:
    explicit MotorcycleRoot(const InitArg& arg);
    ~MotorcycleRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    // 0x71004ad5c8 (CSV AI_AI_MotorcycleRoot::x; placeholder name): updates the AS flags 0x2c (energy left),
    // 0x1a (no rider state) and 0x29 (energy empty) of the AS flag parameter 0x42.
    void updateASFlags();
    // 0x71004ae954 (CSV AI_AI_MotorcycleRoot::calc_x; placeholder name): picks one of the four noise
    // parameters (energy empty / no rider / throttle closed / throttle open) and sends it as actor noise.
    void sub_71004AE954(act::Motorcycle* motorcycle, act::Unk_7100e8b2b8* rideable,
                        MotorcycleMgr* motorcycle_mgr);
    // 0x71004aedac (CSV AI_AI_MotorcycleRoot::calcCookStuff; placeholder name): enables the "Cook"
    // attention client while the motorcycle is standing on the ground (or _f88 bit 32 is set), and
    // disables all of the actor's clients again once it moves.
    void sub_71004AEDAC(act::Motorcycle* motorcycle, act::Unk_7100e8b2b8* rideable);
    // 0x71004ae7e0 (CSV AI_AI_MotorcycleRoot::disappear; placeholder name): switches the child AI to
    // "消失" with the given disappear-effect name and marks the rideable as gone.
    void sub_71004AE7E0(act::Unk_7100e8b2b8* rideable, const sead::SafeString& effect_name);

    // Placeholder (bits of _81; the bit index goes through the stack like a SEAD_ENUM).
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5)

protected:
    // static_param at offset 0x38
    const float* mInWaterRateForDisappear_s{};
    // static_param at offset 0x40
    const float* mDistanceToPlayerForDisappear_s{};
    // static_param at offset 0x48
    const float* mNoiseEnergyEmpty_s{};
    // static_param at offset 0x50
    const float* mNoiseNotRidden_s{};
    // static_param at offset 0x58
    const float* mNoiseThrottleClose_s{};
    // static_param at offset 0x60
    const float* mNoiseThrottleOpen_s{};
    // static_param at offset 0x68
    const float* mForestFogRatioForDisappear_s{};
    void* _70{};
    sead::Matrix34f* _78{};  // set by message 0x380001d, applied by enter_
    u8 _80{};
    FlagByte<Flag> _81;
    u32 _84 = 0;
};

}  // namespace uking::ai
