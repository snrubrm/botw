#pragma once

#include "Game/AI/Action/actionForkHoverKeepRotateTurnBase.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkHoverKeepRotateTurn : public ForkHoverKeepRotateTurnBase {
    SEAD_RTTI_OVERRIDE(ForkHoverKeepRotateTurn, ForkHoverKeepRotateTurnBase)
public:
    explicit ForkHoverKeepRotateTurn(const InitArg& arg);
    ~ForkHoverKeepRotateTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    /* 0x68 */ ksys::act::CCAccessor _68;
};
KSYS_CHECK_SIZE_NX150(ForkHoverKeepRotateTurn, 0x70);

}  // namespace uking::action
