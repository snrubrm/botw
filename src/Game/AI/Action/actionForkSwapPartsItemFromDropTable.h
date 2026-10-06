#pragma once

#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "Game/AI/Action/actionFork.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkSwapPartsItemFromDropTable : public Fork {
    SEAD_RTTI_OVERRIDE(ForkSwapPartsItemFromDropTable, Fork)
public:
    explicit ForkSwapPartsItemFromDropTable(const InitArg& arg);
    ~ForkSwapPartsItemFromDropTable() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_params at offset 0x30: PartsKey0 .. PartsKey4 (indexed by calc_)
    sead::SafeString mPartsKey_s[5]{};
    ksys::act::BaseProcHandle _80[5];
};
KSYS_CHECK_SIZE_NX150(ForkSwapPartsItemFromDropTable, 0xd0);

}  // namespace uking::action
