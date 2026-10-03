#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class RemainsFireBattleMove : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(RemainsFireBattleMove, ksys::act::ai::Ai)
public:
    explicit RemainsFireBattleMove(const InitArg& arg);
    ~RemainsFireBattleMove() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    bool reenter_(ksys::act::ai::ActionBase* other, bool x) override;
    void leave_() override;
    void loadParams_() override;
    void handlePendingChildChange_() override;
    bool handleAck_(const ksys::MessageAck* ack) override;

    void sub_7100540FE4();

protected:
    Unk_7102418f20 _38{mActor, 0x8000045};
    Unk_710235aba0 _50{mActor, 0x8000040};
    bool _80 = false;
};
KSYS_CHECK_SIZE_NX150(RemainsFireBattleMove, 0x88);

}  // namespace uking::ai
