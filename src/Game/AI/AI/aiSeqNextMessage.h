#pragma once

#include "Game/AI/AI/aiSeqTwoAction.h"
#include "Game/AI/aiUnk_7102357210.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqNextMessage : public SeqTwoAction {
    SEAD_RTTI_OVERRIDE(SeqNextMessage, SeqTwoAction)
public:
    explicit SeqNextMessage(const InitArg& arg);
    ~SeqNextMessage() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;
    bool handleMessage_(const ksys::Message& message) override;

    bool m35() const override;

protected:
    // static_param at offset 0x50
    const int* mDelayTimeMax_s{};
    Unk_710241d7c8 _58;
    float _90 = 0;
    int _94 = 0;
    int _98 = 0;
    bool _9c = false;
};

}  // namespace uking::ai
