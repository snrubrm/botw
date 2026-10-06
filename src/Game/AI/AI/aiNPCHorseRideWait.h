#pragma once

#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
#include "Game/AI/aiLockedProcLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCHorseRideWait : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCHorseRideWait, ksys::act::ai::Ai)
public:
    explicit NPCHorseRideWait(const InitArg& arg);
    ~NPCHorseRideWait() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

    // 0x71004cc76c: resets the schedule, sends 0x380000b (_dc) and 0x3800004 (_38) to the horse
    // ride info's actor and changes to the child that moves with "GearSpeed" = _dc.
    void sub_71004CC76C();

protected:
    // 0x71004cc680: copies the schedule timeline name to the key name, _dc = 0, then the "到着" child with the gear speed
    void sub_71004CC680();
    // Lock + position; &_88 is the payload of message 0x3800005 (sent by enter_).
    LockedVectorMaybe _38;
    LockedVectorMaybe _88;
    bool _d8 = false;
    bool _d9 = false;
    s32 _dc = 1;
};
KSYS_CHECK_SIZE_NX150(NPCHorseRideWait, 0xe0);

}  // namespace uking::ai
