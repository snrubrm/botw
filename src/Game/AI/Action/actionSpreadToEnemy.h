#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SpreadToEnemy : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(SpreadToEnemy, OnetimeStopASPlay)
public:
    explicit SpreadToEnemy(const InitArg& arg);
    ~SpreadToEnemy() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x48
    const float* mSpreadDist_s{};
    // Unused by this class's functions.
    Unk_710235abc8 _50{mActor, 0x8000006};
};
KSYS_CHECK_SIZE_NX150(SpreadToEnemy, 0xa8);

}  // namespace uking::action
