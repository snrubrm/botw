#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actUnk_7100d3bc4c.h"
#include "KingSystem/Event/evtResidentEvent.h"

namespace uking::ai {

class RemainsWaterBattleRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsWaterBattleRoot, ksys::act::ai::Ai)
public:
    explicit RemainsWaterBattleRoot(const InitArg& arg);
    ~RemainsWaterBattleRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    void sub_7100545B8C();

protected:
    // 0x710054623c: tracks the player state (height, ground contact, the m204 action) in the _b4-_b8 flags
    void sub_710054623C();
    // 0x71005464ec: resets the timers and flags, marks the battle info, then the "パオーン" child
    void sub_71005464EC();
    // static_param at offset 0x38
    const float* mCallClearDemoTimer_s{};
    // static_param at offset 0x40
    const float* mAfterDamageTimer_s{};
    // static_param at offset 0x48
    const float* mAfterPaooonTimer_s{};
    // static_param at offset 0x50
    const float* mAfterHellTimer_s{};
    // static_param at offset 0x58
    const float* mFirstBulletTimer_s{};
    // aitree_variable at offset 0x60
    void* mRemainsWaterBattleInfo_a{};
    ksys::act::Unk_7100d3bce4 _68{mActor};
    ksys::act::Unk_7100d3bce4 _80{mActor};
    ksys::act::Unk_7100d3bce4 _98{mActor};
    f32 _b0 = 0;
    bool _b4 = false;
    bool _b5 = false;
    bool _b6 = false;
    bool _b7 = false;
    bool _b8 = false;
    bool _b9 = false;
    bool _ba = false;
    ksys::evt::ResidentEvent _c0;
};
KSYS_CHECK_SIZE_NX150(RemainsWaterBattleRoot, 0x290);

}  // namespace uking::ai
