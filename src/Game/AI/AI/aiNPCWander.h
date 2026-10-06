#pragma once

#include "Game/AI/AI/aiNPCTravelBase.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCWander : public NPCTravelBase {
    SEAD_RTTI_OVERRIDE(NPCWander, NPCTravelBase)
public:
    explicit NPCWander(const InitArg& arg);
    ~NPCWander() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // 0x71004e9ff8: advances the rail follower by the actor's speed; true when it turned around at a rail end
    bool sub_71004E9FF8();
    // 0x71004ea4b0: changes to the "レール点に移動" child
    void sub_71004EA4B0();
    // 0x71004ea108: changes to the "振り向く" child
    void sub_71004EA108();
    // static_param at offset 0x78
    const float* mRainWaitTime_s{};
    // static_param at offset 0x80
    const float* mGoalDistance_s{};
    // static_param at offset 0x88
    const float* mRailUpdateDistRate_s{};
    // static_param at offset 0x90
    sead::SafeString mRainDestination_s{};
    // static_param at offset 0xa0
    sead::SafeString mNormalASKeyName_s{};
    // static_param at offset 0xb0
    sead::SafeString mRainASKeyName_s{};
    // static_param at offset 0xc0
    sead::SafeString mRailUniqueName_s{};
    // dynamic_param at offset 0xd0
    bool* mIsPathRest_d{};
    act::NPC* _d8{};
    u32 _e0 = 0;
    Unk_71024f15c0* _e8{};  // NPC::_848
    sead::SafeString _f0{};
    sead::SafeString _100{};
    f32 _110 = -1.0f;
    sead::Vector3f _114;
    sead::Vector3f _120;
    u32 _12c;
};
KSYS_CHECK_SIZE_NX150(NPCWander, 0x130);

}  // namespace uking::ai
