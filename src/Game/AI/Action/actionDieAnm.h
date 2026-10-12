#pragma once

#include "Game/AI/Action/actionStopBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class DieAnm : public StopBase {
    SEAD_RTTI_OVERRIDE(DieAnm, StopBase)
public:
    explicit DieAnm(const InitArg& arg);

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x30
    sead::SafeString mASName_s{};
};

}  // namespace uking::action
