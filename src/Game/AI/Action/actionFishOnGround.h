#pragma once

#include "Game/AI/Action/actionStopBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

class FishOnGround : public StopBase {
    SEAD_RTTI_OVERRIDE(FishOnGround, StopBase)
public:
    explicit FishOnGround(const InitArg& arg);
    ~FishOnGround() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    sead::SafeString mASKey_s{};
    ksys::act::MotionType _40{};
};

}  // namespace uking::action
