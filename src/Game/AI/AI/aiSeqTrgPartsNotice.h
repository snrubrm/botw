#pragma once

#include "Game/AI/AI/aiSeqTwoAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class SeqTrgPartsNotice : public SeqTwoAction {
    SEAD_RTTI_OVERRIDE(SeqTrgPartsNotice, SeqTwoAction)
public:
    explicit SeqTrgPartsNotice(const InitArg& arg);
    ~SeqTrgPartsNotice() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    struct Params {
        // static_param at offset 0x50
        const bool* mIsFinishByNoNoticeActionEnd_s{};
        // static_param at offset 0x58
        sead::SafeString mPartsName_s{};
    };
    Params mParams;
};

}  // namespace uking::ai
