#pragma once

#include "Game/AI/Action/actionSmallDamageDirectPreTargetBone.h"
#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class SmallDamageDirectPreTargetBack : public SmallDamageDirectPreTargetBone {
    SEAD_RTTI_OVERRIDE(SmallDamageDirectPreTargetBack, SmallDamageDirectPreTargetBone)
public:
    explicit SmallDamageDirectPreTargetBack(const InitArg& arg);
    ~SmallDamageDirectPreTargetBack() override;

protected:
    void m32(sead::Vector3f* dir, ksys::act::Actor* actor, uking::dmg::DamageManager* mgr) override;
    bool m33(sead::Vector3f* dir, uking::dmg::DamageManager* mgr) override;
};

}  // namespace uking::action
