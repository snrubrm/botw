#pragma once

#include "Game/AI/Action/actionTurnAndLookToObjBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LookAtObject : public TurnAndLookToObjBase {
    SEAD_RTTI_OVERRIDE(LookAtObject, TurnAndLookToObjBase)
public:
    explicit LookAtObject(const InitArg& arg);
    ~LookAtObject() override;

    bool init_(sead::Heap* heap) override;
    bool oneShot_() override;
    void loadParams_() override;

protected:
    void m33() override;
    void m37(ksys::act::BaseProcLink* link, const sead::Vector3f* pos) override;
};

}  // namespace uking::action
