#pragma once

#include "Game/AI/AI/aiNonPlayerHorseRide.h"
#include "Game/AI/aiLockedProcLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace uking::act {
class NPC;
}

namespace uking::ai {

class NPCHorseRide : public NonPlayerHorseRide {
    SEAD_RTTI_OVERRIDE(NPCHorseRide, NonPlayerHorseRide)
public:
    explicit NPCHorseRide(const InitArg& arg);
    ~NPCHorseRide() override;
    bool hasPreDeleteCb() override { return true; }
    void onPreDelete() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0xe0
    const int* mGearLevel_s{};
    // static_param at offset 0xe8
    const int* mGearResetPathNum_s{};
    // static_param at offset 0xf0
    const float* mPlayerNearDistance_s{};
    u8 _f8[8];
    u64 _100 = 0;
    u32 _108 = 0;
    act::NPC* _110 = nullptr;
    sead::Vector3f _118 = sead::Vector3f::zero;
    sead::Vector3f _124 = sead::Vector3f::zero;
    u64 _130 = 0;
    u64 _138 = 0;
    u64 _140 = 0;
    u16 _148 = 0;
    u8 _14a[0xe];
    ksys::MesTransceiverId _158;
    LockedVectorMaybe _170;
    LockedVectorMaybe _1c0;
    LockedProcLinkMaybe _210;
    // aitree_variable at offset 0x268
    void* mEventBindUnit_a{};
    u8 _270[0x10];  // object with a vtable (0x710237b9b8, ActorLinkForEventBind-like) + a pointer
};
KSYS_CHECK_SIZE_NX150(NPCHorseRide, 0x280);

}  // namespace uking::ai
