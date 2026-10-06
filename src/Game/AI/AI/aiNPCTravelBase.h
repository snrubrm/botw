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
    // 0x71004df978: plays the stance AS (slot 0x3b) selected by the schedule value (_1b0 / _1b4 / _1b8)
    void sub_71004DF978(bool a1, bool a2);
    // 0x71004df7ec: the NPC meeting state (NPCMove::sub_71004D44B0 without the name check): flags and awareness from the schedule state value (_1a0 / _1a4 / _1a8)
    void sub_71004DF7EC(bool a1, bool a2);
    // 0x71004df78c: plays the schedule DynAS name in the slots 0x37 and 0x38
    void sub_71004DF78C();
    // 0x71004dfa0c: switches the character controller to the "Crouching" / "Standing" form
    void sub_71004DFA0C(bool crouching);
    Unk_710240bc48 _38{mActor, 0x8000009};
    ksys::Timer _68{0, 0};
};
KSYS_CHECK_SIZE_NX150(NPCTravelBase, 0x78);

}  // namespace uking::ai
