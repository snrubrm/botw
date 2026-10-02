#pragma once

#include "Game/AI/aiUnk_7102357d20.h"
#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class AddDemoCall : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(AddDemoCall, ksys::act::ai::Ai)
public:
    explicit AddDemoCall(const InitArg& arg);
    ~AddDemoCall() override;
    bool isFinished() const override;
    bool isFailed() const override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void calc_() override;
    void leave_() override;
    void loadParams_() override;

protected:
    // static_param at offset 0x38
    const bool* mOnlyOne_s{};
    // static_param at offset 0x40
    const bool* mIsBroadCastOnlyOne_s{};
    // static_param at offset 0x48
    sead::SafeString mEntryPoint_s{};
    // static_param at offset 0x58
    sead::SafeString mDemoName_s{};
    Unk_71023d31f8 _68{mActor, 0x8000044};
    bool _98 = false;
};

}  // namespace uking::ai
