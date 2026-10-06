#pragma once

#include "Game/AI/Action/actionOnetimeStopASPlay.h"
#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SendPlayerNoticeMessageBase : public OnetimeStopASPlay {
    SEAD_RTTI_OVERRIDE(SendPlayerNoticeMessageBase, OnetimeStopASPlay)
public:
    explicit SendPlayerNoticeMessageBase(const InitArg& arg);
    ~SendPlayerNoticeMessageBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    virtual void m32();

    // static_param at offset 0x48
    sead::SafeString mTargetActorName_s{};
    Unk_710235abc8 _58{mActor, 0x8000006};
};

}  // namespace uking::action
