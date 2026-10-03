#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/System/Timer.h"

namespace uking::ai {

class NPCTravelBase : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(NPCTravelBase, ksys::act::ai::Ai)
public:
    explicit NPCTravelBase(const InitArg& arg);
    ~NPCTravelBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    Unk_710240bc48 _38{mActor, 0x8000009};
    ksys::Timer _68{0, 0};
};
KSYS_CHECK_SIZE_NX150(NPCTravelBase, 0x78);

}  // namespace uking::ai
