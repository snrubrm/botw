#pragma once

#include "Game/Actor/Action/actionOneHandActionWithLegTurn.h"
#include "Game/Actor/aiUnk_71007050e4.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class GiantOneHandAttackWithLegTurn : public OneHandActionWithLegTurn {
    SEAD_RTTI_OVERRIDE(GiantOneHandAttackWithLegTurn, OneHandActionWithLegTurn)
public:
    explicit GiantOneHandAttackWithLegTurn(const InitArg& arg);
    ~GiantOneHandAttackWithLegTurn() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    void m32(const sead::SafeString* name) override;
    void m33() override;

    /* 0x280 */ Unk_71007050e4 _280{mActor};
};
KSYS_CHECK_SIZE_NX150(GiantOneHandAttackWithLegTurn, 0x290);

}  // namespace uking::action
