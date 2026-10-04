#pragma once

#include <limits>
#include <math/seadVector.h>
#include "Game/AI/aiFlagByte.h"
#include <prim/seadEnum.h>
#include "Game/AI/AI/aiDomesticNormal.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class DogNormal : public DomesticNormal {
    SEAD_RTTI_OVERRIDE(DogNormal, DomesticNormal)
public:
    SEAD_ENUM(Flag, _0, _1, _2, _3, _4)

    explicit DogNormal(const InitArg& arg);
    ~DogNormal() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool m40() override;
    bool m41() override;
    bool m44() override;
    // 0x7100364460 (CSV: AI_AI_DogNormal::x): friend / follow update (per-frame helper of m41).
    void sub_7100364460();

protected:
    // static_param at offset 0x3a0
    const int* mNumFriendlyFoodForLeadTreasure_s{};
    // static_param at offset 0x3a8
    const float* mMaxFollowDist_s{};
    // static_param at offset 0x3b0
    const float* mMaxFollowFriendDecayRate_s{};
    // static_param at offset 0x3b8
    const float* mFoodFriendRate_s{};
    // static_param at offset 0x3c0
    const float* mFoodFriendDist_s{};
    // static_param at offset 0x3c8
    const float* mNearFriendRate_s{};
    // static_param at offset 0x3d0
    const float* mNearFriendDist_s{};
    // static_param at offset 0x3d8
    const float* mFarFriendDecayRate_s{};
    // static_param at offset 0x3e0
    const float* mFarFriendDist_s{};
    // static_param at offset 0x3e8
    const float* mFarFriendFriendlyDist_s{};
    // static_param at offset 0x3f0
    const float* mAttackFriendDecayRate_s{};
    // static_param at offset 0x3f8
    const float* mFriendTickRate_s{};
    // static_param at offset 0x400
    const float* mNoMoveFriendDecayRate_s{};
    // static_param at offset 0x408
    const float* mNoMoveThreshold_s{};
    // static_param at offset 0x410
    const float* mFramesKeepMaxFriendly_s{};
    // static_param at offset 0x418
    const float* mFramesStayAfterLead_s{};
    // static_param at offset 0x420
    const float* mAngleTurnToPlayer_s{};
    ksys::Timer _428{0, 0};  // enter_: value = previous value = FriendTickRate
    u32 _434 = 0;
    u32 _438 = 0;
    u32 _43c = 0;
    sead::Vector3f _440{0, 0, 0};
    // init_: translate and rotate (y) of the map object
    sead::Vector3f _44c{std::numeric_limits<f32>::quiet_NaN(),
                        std::numeric_limits<f32>::quiet_NaN(),
                        std::numeric_limits<f32>::quiet_NaN()};
    f32 _458 = std::numeric_limits<f32>::quiet_NaN();
    f32 _45c = 0;
    u32 _460 = 0;
    FlagBits<Flag, u16> _464;
};
KSYS_CHECK_SIZE_NX150(DogNormal, 0x468);

}  // namespace uking::ai
