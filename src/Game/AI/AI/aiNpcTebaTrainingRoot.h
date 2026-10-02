#pragma once

#include "Game/AI/AI/aiNPCRoot.h"
#include "Game/AI/aiMessage3DText.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class NpcTebaTrainingRoot : public NPCRoot {
    SEAD_RTTI_OVERRIDE(NpcTebaTrainingRoot, NPCRoot)
public:
    explicit NpcTebaTrainingRoot(const InitArg& arg);
    ~NpcTebaTrainingRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    Message3DText _238;
};
KSYS_CHECK_SIZE_NX150(NpcTebaTrainingRoot, 0x310);

}  // namespace uking::ai
