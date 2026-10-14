#pragma once

#include "KingSystem/ActorSystem/actBaseProcHandle.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class EventCreateParaShawlSetToPlayer : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(EventCreateParaShawlSetToPlayer, ksys::act::ai::Action)
public:
    explicit EventCreateParaShawlSetToPlayer(const InitArg& arg);
    ~EventCreateParaShawlSetToPlayer() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // dynamic_param at offset 0x20
    int* mParaShawlType_d{};
    ksys::act::BaseProcHandle _28;
};
KSYS_CHECK_SIZE_NX150(EventCreateParaShawlSetToPlayer, 0x38);

}  // namespace uking::action
