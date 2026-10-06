#pragma once

#include <math/seadMatrix.h>
#include <thread/seadCriticalSection.h>
#include "Game/AI/AI/aiNPCTravelBase.h"
#include "Game/AI/aiLockedProcLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace uking::act {
class NPC;
}

namespace uking::ai {

class NPCTravel : public NPCTravelBase {
    SEAD_RTTI_OVERRIDE(NPCTravel, NPCTravelBase)
public:
    explicit NPCTravel(const InitArg& arg);
    ~NPCTravel() override;
    bool hasPreDeleteCb() override { return true; }
    void onPreDelete() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    // 0x71004e59d4: sends message 0x3800007 to the horse of _88 when it is closer than 2
    void sub_71004E59D4();
    // 0x71004e3b10: with the horse ride info's actor of _88 acquired: locks _110, links this actor,
    // stores `value` and sends message 0x3800008 with _110 as its payload.
    void sub_71004E3B10(f32 value, bool onProcessingThread);

    // static_param at offset 0x78
    const float* mWaitHorseReturnDist_s{};
    // static_param at offset 0x80
    const float* mGiveUpWaitHorseTime_s{};
    act::NPC* _88 = nullptr;
    u8 _90[0x30];
    u32 _c0 = 0;
    bool _c4 = false;
    bool _c5 = true;
    bool _c6 = false;
    bool _c7 = false;
    sead::Matrix34f _c8;  // sent by the sheltering ShelterFromRain action (message 0x8000075)
    ksys::MesTransceiverId _f8;
    LockedProcLinkMaybe _110;
    sead::CriticalSection _168;
    u8 _1a8[0x10];
    u64 _1b8 = 0;
    u64 _1c0 = 0;
    u8 _1c8[0x30];
    u8 _1f8[0x7b8];  // a large embedded object (ctor 0x7100eec734); NPC::_840 points to it
    bool _9b0 = false;
};

KSYS_CHECK_SIZE_NX150(NPCTravel, 0x9b8);

}  // namespace uking::ai
