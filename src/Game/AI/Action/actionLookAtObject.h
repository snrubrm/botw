#pragma once

#include "Game/AI/Action/actionLookAtObjectBase.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class LookAtObject : public LookAtObjectBase {
    SEAD_RTTI_OVERRIDE(LookAtObject, LookAtObjectBase)
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
