#pragma once

#include <thread/seadCriticalSection.h>
#include "Game/AI/AI/aiNPCTravelBase.h"
#include "Game/AI/aiLockedProcLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"

namespace uking::ai {

class NPCTravel : public NPCTravelBase {
    SEAD_RTTI_OVERRIDE(NPCTravel, NPCTravelBase)
public:
    explicit NPCTravel(const InitArg& arg);
    ~NPCTravel() override;
    bool hasPreDeleteCb() override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x78
    const float* mWaitHorseReturnDist_s{};
    // static_param at offset 0x80
    const float* mGiveUpWaitHorseTime_s{};
    u8 _88[0x38];
    u32 _c0 = 0;
    bool _c4 = false;
    bool _c5 = true;
    u16 _c6 = 0;
    u8 _c8[0x30];
    ksys::MesTransceiverId _f8;
    LockedProcLinkMaybe _110;
    sead::CriticalSection _168;
    u8 _1a8[0x10];
    u64 _1b8 = 0;
    u64 _1c0 = 0;
    u8 _1c8[0x7e8];  // contains a large embedded object at 0x1f8 whose ctor is 0x7100eec734
    bool _9b0 = false;
};

KSYS_CHECK_SIZE_NX150(NPCTravel, 0x9b8);

}  // namespace uking::ai
