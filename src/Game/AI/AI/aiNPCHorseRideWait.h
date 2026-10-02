#pragma once

#include <math/seadVector.h>
#include <thread/seadCriticalSection.h>
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

protected:
    // Lock + position; &_88 is the payload of message 0x3800005 (sent by enter_).
    struct Unk1 {
        sead::CriticalSection mLock;
        sead::Vector3f _40;
    };
    KSYS_CHECK_SIZE_NX150(Unk1, 0x50);

    Unk1 _38;
    Unk1 _88;
    bool _d8 = false;
    bool _d9 = false;
    u32 _dc = 1;
};
KSYS_CHECK_SIZE_NX150(NPCHorseRideWait, 0xe0);

}  // namespace uking::ai
