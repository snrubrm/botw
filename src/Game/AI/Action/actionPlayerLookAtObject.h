#pragma once

#include "Game/AI/Action/actionLookAtObjectBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class PlayerLookAtObject : public LookAtObjectBase {
    SEAD_RTTI_OVERRIDE(PlayerLookAtObject, LookAtObjectBase)
public:
    explicit PlayerLookAtObject(const InitArg& arg);
    ~PlayerLookAtObject() override;

    bool init_(sead::Heap* heap) override;
    void loadParams_() override;
    void m33() override;
    bool oneShot_() override;

protected:
    void m37(ksys::act::BaseProcLink* link, const sead::Vector3f* pos) override;
    void m38() override;
};

}  // namespace uking::action
