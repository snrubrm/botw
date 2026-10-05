#include "Game/AI/AI/aiGuardianBeam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

GuardianBeam::GuardianBeam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GuardianBeam::~GuardianBeam() = default;

bool GuardianBeam::init_(sead::Heap* heap) {
    _40 = mActor->getMainBody();
    _48 = mActor->findPhysicsBodyByName("Atk", "AtkBody");
    if (!_40 || !_48)
        return false;
    return true;
}

void GuardianBeam::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* chemical = mActor->getChemicalStuff())
        chemical->sub_7100D90858(false, 3, false, true, false);
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FBB29C();
    if (_40) {
        _40->setTransform(mActor->getMtx(), ksys::phys::PropagateToLinkedMotions{true});
        _40->enableContactLayer(ksys::phys::ContactLayer::EntityNPC);
        _40->addToWorld();
    }
    if (_48) {
        _48->setTransform(mActor->getMtx(), ksys::phys::PropagateToLinkedMotions{true});
        _48->enableContactLayer(ksys::phys::ContactLayer::SensorNPC);
        _48->addToWorld();
    }
    sead::Vector3f home;
    mActor->getHomePos(&home);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(home, "EyePos", -1);
    changeChild("着弾前", &pack);
}

void GuardianBeam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianBeam::loadParams_() {
    getStaticParam(&mMaxDistance_s, "MaxDistance");
}

}  // namespace uking::ai
