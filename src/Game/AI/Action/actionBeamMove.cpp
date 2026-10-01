#include "Game/AI/Action/actionBeamMove.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

BeamMove::BeamMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BeamMove::~BeamMove() = default;

bool BeamMove::init_(sead::Heap* heap) {
    _50 = mActor->getMainBody();
    _58 = mActor->findPhysicsBodyByName("Atk", "AtkBody");
    _60 = mActor->findPhysicsBodyByName("Atk", "AtkExplode");
    if (!_50 || !_58)
        return false;
    _50->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
    _50->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
    return true;
}

void BeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BeamMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void BeamMove::loadParams_() {
    getStaticParam(&mAtMinDamage_s, "AtMinDamage");
    getStaticParam(&mShieldDamage_s, "ShieldDamage");
    getStaticParam(&mForceExplodeFrame_s, "ForceExplodeFrame");
    getAITreeVariable(&mIsReflectThrownBullet_a, "IsReflectThrownBullet");
}

void BeamMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
