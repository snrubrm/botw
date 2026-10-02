#pragma once

#include "Game/AI/Action/actionTurnBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

class HoverTurn : public TurnBase {
    SEAD_RTTI_OVERRIDE(HoverTurn, TurnBase)
public:
    explicit HoverTurn(const InitArg& arg);
    ~HoverTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(f32 x) override;

    // static_param at offset 0x90
    const bool* mIsIgnoreSameAS_s{};
    // static_param at offset 0x98
    sead::SafeString mASKeyName_s{};
    ksys::act::CCAccessor mCCAccessor;
};

KSYS_CHECK_SIZE_NX150(HoverTurn, 0xb0);

}  // namespace uking::action
