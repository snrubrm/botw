#pragma once

#include "Game/AI/Action/actionTakeHitImpactForce.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include <math/seadVector.h>

namespace uking::action {

class SmallDamageBackwardBase : public TakeHitImpactForce {
    SEAD_RTTI_OVERRIDE(SmallDamageBackwardBase, TakeHitImpactForce)
public:
    explicit SmallDamageBackwardBase(const InitArg& arg);
    ~SmallDamageBackwardBase() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;
    sead::Vector3f _90;
    // unknown object (0x24 bytes, no ctor; same type as FlyMoveBase::_84, methods 0x710073fa90/94)
    u8 _9c[0xc0 - 0x9c];
};

KSYS_CHECK_SIZE_NX150(SmallDamageBackwardBase, 0xc0);

}  // namespace uking::action
