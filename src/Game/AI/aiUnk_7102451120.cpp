#include "Game/AI/aiUnk_7102451120.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

void sub_7100720140(ksys::act::Actor* actor) {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(actor))
        enemy->_e90 = 1;
}

bool Unk_7102451120::invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                            const ksys::phys::ContactPointInfo::Event& event) {
    if (event.body->getMotionType() != ksys::phys::MotionType::Dynamic ||
        event.body->hasFlag(ksys::phys::RigidBody::Flag::Fixed) || event.body->getMass() > _8) {
        *disable = ksys::phys::ContactPointInfo::ShouldDisableContact::Yes;
        return false;
    }
    return true;
}
