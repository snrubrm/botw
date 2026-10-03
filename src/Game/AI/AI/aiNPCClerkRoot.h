#pragma once

#include "Game/AI/AI/aiNPCRoot.h"
#include "KingSystem/Event/evtResidentEvent.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NPCClerkRoot : public NPCRoot {
    SEAD_RTTI_OVERRIDE(NPCClerkRoot, NPCRoot)
public:
    explicit NPCClerkRoot(const InitArg& arg);
    ~NPCClerkRoot() override;
    bool hasPreDeleteCb() override { return true; }

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    void onPreDelete() override;

protected:
    bool _238 = false;
    bool _239 = false;
    ksys::evt::ResidentEvent _240;
};
KSYS_CHECK_SIZE_NX150(NPCClerkRoot, 0x410);

}  // namespace uking::ai
