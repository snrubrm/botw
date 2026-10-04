#pragma once

#include "Game/AI/Action/actionGiantOneHandActionWithLegTurn.h"
#include "Game/AI/aiUnk_7100704914.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantOneHandPunchWithLegTurn : public GiantOneHandActionWithLegTurn {
    SEAD_RTTI_OVERRIDE(GiantOneHandPunchWithLegTurn, GiantOneHandActionWithLegTurn)
public:
    explicit GiantOneHandPunchWithLegTurn(const InitArg& arg);
    ~GiantOneHandPunchWithLegTurn() override;

    bool init_(sead::Heap* heap) override;
    void leave_() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(const sead::SafeString* name) override;
    void m33() override;

    /* 0x280 */ Unk_7100704914 _280{mActor};
};
KSYS_CHECK_SIZE_NX150(GiantOneHandPunchWithLegTurn, 0x2c0);

}  // namespace uking::action
