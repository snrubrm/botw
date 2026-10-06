#include "Game/AI/Action/actionStalEnemyDie.h"
#include "KingSystem/ActorSystem/Profiles/actDynamicActor.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::action {

StalEnemyDie::StalEnemyDie(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StalEnemyDie::~StalEnemyDie() = default;

bool StalEnemyDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StalEnemyDie::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StalEnemyDie::leave_() {
    auto* actor = mActor;
    if (auto* dynamic_actor = sead::DynamicCast<ksys::act::DynamicActor>(actor))
        dynamic_actor->sub_71006DD92C(false);
    ksys::act::enableAllAttClients(actor);
    if (auto* controller = actor->getCharacterController()) {
        controller->sub_7100F60604();
        controller->sub_7100F5F458(ksys::act::MotionType::_0);
        controller->sub_7100F62CA8(true);
        controller->sub_7100F60604();
    }
    if (auto* physics = actor->getPhysics()) {
        physics->sub_7100FBDB90(physics->get112(), 0.0f);
        if (auto* ragdoll = physics->getRagdollInstance()) {
            const int num = ragdoll->getNumConstraints();
            for (int i = 0; i < num; ++i)
                ragdoll->enableConstraint(i, true);
        }
    }
    sub_71007A3800(actor);
}

void StalEnemyDie::loadParams_() {
    getStaticParam(&mTime_s, "Time");
    getStaticParam(&mAngReduceRatio_s, "AngReduceRatio");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mForceDropWeapon_s, "ForceDropWeapon");
    getStaticParam(&mPreDieASName_s, "PreDieASName");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mPosBaseRagdollName_s, "PosBaseRagdollName");
    getStaticParam(&mEnableConstraintName_s, "EnableConstraintName");
}

void StalEnemyDie::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
