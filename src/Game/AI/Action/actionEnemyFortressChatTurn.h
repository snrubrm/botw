#pragma once

#include "Game/AI/Action/actionEnemyFortressChatTurnBase.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyFortressChatTurn : public EnemyFortressChatTurnBase {
    SEAD_RTTI_OVERRIDE(EnemyFortressChatTurn, EnemyFortressChatTurnBase)
public:
    explicit EnemyFortressChatTurn(const InitArg& arg);
    ~EnemyFortressChatTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(ksys::act::BaseProcLink* link) override;
    bool m33(const ksys::MessageAck* ack) override;

    // dynamic_param at offset 0xc8
    ksys::act::BaseProcLink* mTargetActor_d{};
    Unk_7102379c80 _d0;
};
KSYS_CHECK_SIZE_NX150(EnemyFortressChatTurn, 0x100);

}  // namespace uking::action
