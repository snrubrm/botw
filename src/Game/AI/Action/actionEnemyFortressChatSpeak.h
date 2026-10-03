#pragma once

#include "Game/AI/Action/actionEnemyFortressChatTalk.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EnemyFortressChatSpeak : public EnemyFortressChatTalk {
    SEAD_RTTI_OVERRIDE(EnemyFortressChatSpeak, EnemyFortressChatTalk)
public:
    explicit EnemyFortressChatSpeak(const InitArg& arg);
    ~EnemyFortressChatSpeak() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message* message) override;

protected:
    void calc_() override;
    void m32() override;
    bool m33(const ksys::MessageAck* ack) override;

    Unk_7102379988 _f0;
    Unk_71023799b0 _120;
    Unk_7102379960 _170;
};
KSYS_CHECK_SIZE_NX150(EnemyFortressChatSpeak, 0x1a0);

}  // namespace uking::action
