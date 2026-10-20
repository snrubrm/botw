#pragma once

#include "Game/Actor/aiUnk_7102357210.h"
#include "Game/Actor/aiUnk_7102357d20.h"
#include "Game/Actor/actNPC.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"

namespace ksys::act {
struct Unk_7100d78e50;
}

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
    // 0x71004d0fb0: checks the ground direction and the angle to the stored rotation.
    bool sub_71004D0FB0();
    // 0x71004d4ca4: shelter from the rain: starts the "うろつく" child with the wait AS name (_120[19] / _120[20]) and the base position _28c
    void sub_71004D4CA4();
    // 0x71004d44b0: starts the "meeting" state: sets the NPC flags and updates them from the selected state value (_e8 / _ec / _f0 / _f4)
    void sub_71004D44B0(bool a1, bool a2);
    // 0x71004d4b98 (placeholder name): the awareness entry of a door to open (same code as
    // NPCScheduleMove::sub_71004DFA90); sets actor flag 0x34 when one is close
    ksys::act::Unk_7100d78e50* sub_71004D4B98();
    // 0x71004cfc88 (placeholder name): plays the move AS _120[7] (_120[8] when it rains and _60 is set) on AS slots
    // 55 and 56; true when slot 55 was playing another AS
    bool sub_71004CFC88();
    // 0x71004d11f4: stands up: "Standing" physics preset, then "ベッドから起きる" (hover motion) or "起きる"
    void sub_71004D11F4();
    // 0x71004d33e8 (placeholder name): applies the equipped-item AS state (Hold / Equip / Invisible) from the
    // selected _120 entry; a1 selects the entry used while the NPC's _1028 name is empty.
    void sub_71004D33E8(bool a1, bool a2);
    // 0x71004d00cc (placeholder name): the arrival / wait state update. Copies the timeline name into the NPC,
    // applies the item-state AS, then changes to the arrival child ("到着" / "雨宿り地点に到着") with the AS
    // name, rain anchor and start-same-AS parameters.
    void sub_71004D00CC(bool a1, bool a2);
    // 0x71004d0610 (placeholder name): changes to the 遷移待機 child with the dynamic AS name `as_name`
    // and stores the actor's position at _280; `a2` skips the item-state / meeting setup.
    void sub_71004D0610(const sead::SafeString& as_name, bool a2);
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
    s32 _e8 = 0;
    s32 _ec = 0;
    s32 _f0 = 0;
    s32 _f4 = 0;
    s32 _f8 = 0;
    s32 _fc = 0;  // fine-weather AS index passed to sub_710071300C
    s32 _100 = 0;  // rain AS index
    s32 _104 = 0;
    u64 _108 = 0;
    s32 _110 = 60;
    s32 _114 = -1;
    s32 _118 = -1;
    s32 _11c = 5;
    sead::SafeString _120[4]{};
    // Separate members: the original selects these with a csel of two addresses.
    sead::SafeString _160{};
    sead::SafeString _170{};
    sead::SafeString _180{};
    sead::SafeString _190{};
    sead::SafeString _1a0{};
    // Separate members: the original addresses these directly (no array index arithmetic).
    sead::SafeString _1b0{};
    sead::SafeString _1c0{};
    sead::SafeString _1d0{};
    sead::SafeString _1e0{};
    sead::SafeString _1f0{};
    sead::SafeString _200{};
    sead::SafeString _210{};
    sead::SafeString _220{};
    sead::SafeString _230{};
    sead::SafeString _240{};
    sead::SafeString _250{};
    sead::SafeString _260{};
    sead::SafeString _270{};
    sead::Vector3f _280;
    sead::Vector3f _28c;
    /* 0x298 */ sead::Vector3f _298;  // rotation used by the ground / upright check
    u8 _2a4[4];
    act::NPC* _2a8 = nullptr;
    ksys::act::BaseProcLink _2b0;
    Unk_710240bc48 _2c0{mActor, 0x8000009};
    Unk_710240bc70 _2f0{0x1800003};
};
KSYS_CHECK_SIZE_NX150(NPCMove, 0x330);

}  // namespace uking::ai
