#pragma once

#include "Game/AI/AI/aiNPCRoot.h"
#include "Game/AI/aiLockedProcLink.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include <thread/seadCriticalSection.h>
#include "KingSystem/System/Timer.h"

namespace uking::act {
class NPC;
}

namespace uking::ai {

class NPCTravelerRoot : public NPCRoot {
    SEAD_RTTI_OVERRIDE(NPCTravelerRoot, NPCRoot)
public:
    explicit NPCTravelerRoot(const InitArg& arg);
    ~NPCTravelerRoot() override;
    bool hasPreDeleteCb() override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    // static_param at offset 0x238
    const bool* mIsRiderChangableAction_s{};
    bool _240 = false;
    act::NPC* _248 = nullptr;
    LockedProcLinkMaybe _250;
    ksys::Timer _2a8{-1.0f, -1.0f, 0.0f};
};
KSYS_CHECK_SIZE_NX150(NPCTravelerRoot, 0x2b8);

}  // namespace uking::ai
