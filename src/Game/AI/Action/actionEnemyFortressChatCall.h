#pragma once

#include "Game/AI/Action/actionEnemyFortressChatTalk.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyFortressChatCall : public EnemyFortressChatTalk {
    SEAD_RTTI_OVERRIDE(EnemyFortressChatCall, EnemyFortressChatTalk)
public:
    explicit EnemyFortressChatCall(const InitArg& arg);
    ~EnemyFortressChatCall() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32() override;
    bool m33(const ksys::MessageAck* ack) override;

    Unk_71023796e0 _f0;
};
KSYS_CHECK_SIZE_NX150(EnemyFortressChatCall, 0x120);

}  // namespace uking::action
