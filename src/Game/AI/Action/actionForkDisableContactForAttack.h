#pragma once

#include "Game/AI/Action/actionForkDisableContact.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ForkDisableContactForAttack : public ForkDisableContact {
    SEAD_RTTI_OVERRIDE(ForkDisableContactForAttack, ForkDisableContact)
public:
    explicit ForkDisableContactForAttack(const InitArg& arg);
    ~ForkDisableContactForAttack() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    bool m33() override;
    bool m32() override;
};
KSYS_CHECK_SIZE_NX150(ForkDisableContactForAttack, 0xd8);

}  // namespace uking::action
