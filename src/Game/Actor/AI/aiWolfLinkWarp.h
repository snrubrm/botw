#pragma once

#include <limits>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace ksys::phys {
class RayCastForRequest;
class Unk_7102372790;
}

namespace uking::act {
class WolfLink;
}

namespace uking::ai {

class WolfLinkWarp : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(WolfLinkWarp, ksys::act::ai::Ai)
public:
    // Bit indices of _c0 (names unknown).
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4, _5, _6, _7, _8)
    // inline-only in the original; name is a guess. Evidence: enter_ sets two bits back to back and
    // their enum temporaries share the InlineParamPack's stack slot (by-value parameter -> lifetime
    // markers); the WolfLinkNormalRoot flag setters (`_1b8 |= 1 << Flag`) have the same shape.
    void setFlag(Flag flag) { _c0 |= 1 << flag; }
    void clearFlag(Flag flag) { _c0 &= ~(1 << flag); }

    explicit WolfLinkWarp(const InitArg& arg);
    ~WolfLinkWarp() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void calc_() override;
    void loadParams_() override;

    // Declaration only.
    void sub_710060DDFC();
    void x();

protected:
    // 0x710060ece0: raycasts straight down (+-2.5) at _80 to find the warp height
    void sub_710060ECE0();
    // 0x710060ee14: takes the raycast result (hit position, flag 6 / 7) and releases the request
    void sub_710060EE14();

    // static_param at offset 0x38
    const int* mNumCalcPerFrame_s{};
    // static_param at offset 0x40
    const int* mFramesUntilFail_s{};
    // static_param at offset 0x48
    const float* mTransitFrames_s{};
    // static_param at offset 0x50
    const float* mWarpFromPlayerOffset_s{};
    // static_param at offset 0x58
    const float* mInitialAngle_s{};
    // static_param at offset 0x60
    const float* mAreaSearchRadius_s{};
    // static_param at offset 0x68
    const float* mAreaSearchCharacterRadius_s{};
    // static_param at offset 0x70
    const float* mAreaThreshold_s{};
    // dynamic_param at offset 0x78
    int* mWarpType_d{};
    sead::Vector3f _80{std::numeric_limits<f32>::quiet_NaN(), std::numeric_limits<f32>::quiet_NaN(),
                       std::numeric_limits<f32>::quiet_NaN()};
    ksys::Timer _8c;
    ksys::Timer _98;
    act::WolfLink* _a8{};
    ksys::phys::RayCastForRequest* _b0{};
    // Navigation query (HavokAI::destroyQuery in leave_ / the destructor).
    ksys::phys::Unk_7102372790* _b8{};
    u16 _c0 = 0;
};
KSYS_CHECK_SIZE_NX150(WolfLinkWarp, 0xc8);

}  // namespace uking::ai
