#pragma once

#include "Game/AI/aiUnk_7102357210.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace uking::ai {

class NPCMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCMove, ksys::act::ai::Ai)
public:
    explicit NPCMove(const InitArg& arg);
    ~NPCMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;
    bool handleAck_(const ksys::MessageAck* ack) override;

    // 0x71004d36a0: changes to the "振り返る" child (target rotation `rot`, the current position and the AS name
    // `_120[11]` when `_61` / `_62` is set, "Turn" otherwise).
    void changeToTurnAround(const sead::Vector3f& rot);

protected:
    // static_param at offset 0x38
    const float* mTerritoryRange_s{};
    // static_param at offset 0x40
    sead::SafeString mDestination_s{};
    // static_param at offset 0x50
    sead::SafeString mMoveEndASName_s{};
    bool _60 = false;
    bool _61 = false;
    bool _62 = false;
    bool _63 = false;
    bool _64 = false;
    bool _65 = false;
    bool _66 = false;
    bool _67 = false;
    s32 _68 = 0;
    s32 _6c = 0;
    f32 _70 = 0;
    f32 _74 = -1.0f;
    f32 _78 = 0;
    f32 _7c = 0;
    f32 _80 = -1.0f;
    sead::SafeString _88[6]{};
    u64 _e8 = 0;
    u64 _f0 = 0;
    u64 _f8 = 0;
    u64 _100 = 0;
    u64 _108 = 0;
    s32 _110 = 60;
    s32 _114 = -1;
    s32 _118 = -1;
    s32 _11c = 5;
    sead::SafeString _120[22]{};
    u8 _280[0x2a8 - 0x280];
    act::NPC* _2a8 = nullptr;
    ksys::act::BaseProcLink _2b0;
    Unk_710240bc48 _2c0{mActor, 0x8000009};
    Unk_710240bc70 _2f0{0x1800003};
};
KSYS_CHECK_SIZE_NX150(NPCMove, 0x330);

}  // namespace uking::ai
