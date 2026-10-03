#pragma once

#include "Game/AI/Action/actionCarried.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class CarriedNoHit : public Carried {
    SEAD_RTTI_OVERRIDE(CarriedNoHit, Carried)
public:
    explicit CarriedNoHit(const InitArg& arg);
    ~CarriedNoHit() override;

    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;

protected:
    u8 _68[0x100];
};
KSYS_CHECK_SIZE_NX150(CarriedNoHit, 0x168);

}  // namespace uking::action
