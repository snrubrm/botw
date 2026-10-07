#include "Game/AI/AI/aiPriestBossAttackGrave.h"
#include "Game/AI/aiUnk_710071edf8.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/Shape/Sphere/physSphereRigidBody.h"

namespace uking::ai {

PriestBossAttackGrave::PriestBossAttackGrave(const InitArg& arg) : AttackGrave(arg) {}

PriestBossAttackGrave::~PriestBossAttackGrave() = default;

bool PriestBossAttackGrave::init_(sead::Heap* heap) {
    return AttackGrave::init_(heap);
}

void PriestBossAttackGrave::enter_(ksys::act::ai::InlineParamPack* params) {
    AttackGrave::enter_(params);
}

void PriestBossAttackGrave::calc_() {
    AttackGrave::calc_();
    if (isCurrentChild("先行動") && !sub_710050F15C())
        getCurrentChild()->setFinished();
}

void PriestBossAttackGrave::leave_() {
    AttackGrave::leave_();
}

void PriestBossAttackGrave::loadParams_() {
    AttackGrave::loadParams_();
}

// NON_MATCHING: normalization register allocation and return-branch placement differ.
bool PriestBossAttackGrave::sub_710050F15C() {
    auto* body = sead::DynamicCast<ksys::phys::SphereRigidBody>(
        mActor->findPhysicsBodyByName("Atk", "AtkBody"));
    if (!body)
        return true;
    const f32 radius = body->getRadius();
    sead::Vector3f direction = getPlayerPosition() - mActor->getMtx().getTranslation();
    direction.normalize();
    const sead::Vector3f pos = radius * direction + mActor->getMtx().getTranslation();
    return sub_710071E600(&pos, 1.0f);
}

}  // namespace uking::ai
