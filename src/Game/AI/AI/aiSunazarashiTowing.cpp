#include "Game/AI/AI/aiSunazarashiTowing.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SunazarashiTowing::SunazarashiTowing(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SunazarashiTowing::~SunazarashiTowing() = default;

bool SunazarashiTowing::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SunazarashiTowing::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* controller = mActor->getCharacterController()) {
        controller->sub_7100F5EDE0(0.0f);
        controller->sub_7100F5EDD8(1.0f);
    }
    changeChild("牽引開始");
}

void SunazarashiTowing::leave_() {
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;

    physics->sub_7100FBAD74();
    if (auto* set = physics->findBodyByName("Tgt")) {
        for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i) {
            if (auto* body = set->getRigidBodies()[i])
                body->resetFlag200();
        }
    }
}

void SunazarashiTowing::loadParams_() {}

bool SunazarashiTowing::isChangeable() const {
    if (isCurrentChild("牽引開始") || isCurrentChild("プレイヤーを牽引"))
        return false;
    auto* child = getCurrentChild();
    if (isCurrentChild("牽引終了"))
        return child->isFinished();
    return ksys::act::ai::Ai::isChangeable();
}

void SunazarashiTowing::calc_() {
    auto* child = getCurrentChild();
    if (isCurrentChild("牽引開始") && child->isFinished()) {
        sub_71005B012C();
        return;
    }

    if (!isCurrentChild("牽引開始") && !isCurrentChild("牽引終了") && child->isFinished())
        changeChild("牽引終了");
}

void SunazarashiTowing::sub_71005B012C() {
    changeChild("プレイヤーを牽引");
    auto* physics = mActor->getPhysics();
    if (!physics)
        return;

    physics->sub_7100FBAC4C(ksys::phys::ContactLayer::SensorAttackPlayer);
    physics->sub_7100FBAC4C(ksys::phys::ContactLayer::SensorObject);
    physics->sub_7100FBAC4C(ksys::phys::ContactLayer::SensorInDoor);
    physics->sub_7100FBAC4C(ksys::phys::ContactLayer::SensorTree);
    if (auto* set = physics->findBodyByName("Tgt")) {
        for (int i = 0, n = set->getRigidBodies().size(); i < n; ++i) {
            if (auto* body = set->getRigidBodies()[i])
                body->setFlag200();
        }
    }
}

}  // namespace uking::ai
