#pragma once

#include "Game/AI/AI/aiSimpleWildlifeRoot.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace ksys::phys {
class RayCastForRequest;
}

namespace uking::ai {

class FishRoot : public SimpleWildlifeRoot {
    SEAD_RTTI_OVERRIDE(FishRoot, SimpleWildlifeRoot)
public:
    explicit FishRoot(const InitArg& arg);
    ~FishRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

    bool m34() override;
    bool m35() override;
    bool m36() override;
    void m40() override;
    void m41() override;
    void m39() override;

protected:
    // Declaration only; original method names and void returns are inferred.
    void sub_71003CC878();
    void sub_71003CCA34();

    // static_param at offset 0xf8
    const float* mInWaterDepth_s{};
    // static_param at offset 0x100
    const float* mOnGroundDepth_s{};
    // static_param at offset 0x108
    const float* mNextJumpTimeBase_s{};
    // static_param at offset 0x110
    const float* mNextJumpTimeRand_s{};
    // static_param at offset 0x118
    const float* mAllowReturnThreatDist_s{};
    // static_param at offset 0x120
    const float* mFrameUntilOutOfWater_s{};
    // static_param at offset 0x128
    const float* mDistRunFromPlayerOnReturn_s{};
    // static_param at offset 0x130
    const float* mIgnoreFoodBase_s{};
    // static_param at offset 0x138
    const float* mIgnoreFoodRand_s{};
    // static_param at offset 0x140
    const float* mIgnoreFoodAfterSuccessBase_s{};
    // static_param at offset 0x148
    const float* mIgnoreFoodAfterSuccessRand_s{};
    // 0x150: BaseProcLink (ctor), 0x160 .. 0x1b4: vector / counters (not decompiled)
    u8 _150[0x184 - 0x150];
    sead::Vector3f _184;
    u8 _190[0x1a4 - 0x190];
    f32 _1a4;
    u8 _1a8[0x1b0 - 0x1a8];
    s32 _1b0{};
    u8 _1b4[0x1b8 - 0x1b4];
    ksys::phys::RayCastForRequest* _1b8{};
    ksys::phys::RayCastForRequest* _1c0{};
};

}  // namespace uking::ai
