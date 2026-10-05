#include "Game/AI/AI/aiGuardianBeam.h"
#include "Game/Actor/actBeamBase.h"
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

// NON_MATCHING: Position snapshot storage and branch layout differ.
void GuardianBeam::calc_() {
    sead::Vector3f home = sead::Vector3f::zero;
    mActor->getHomePos(&home);
    bool exceeded_range = false;
    if (isCurrentChild("着弾前")) {
        getCurrentChild()->setDynamicParam(home, "EyePos");
        float maximum = *mMaxDistance_s;
        if (auto* beam = sead::DynamicCast<act::Beam>(mActor))
            maximum = maximum < beam->_c24 ? maximum : beam->_c24;
        const sead::Vector3f position = mActor->getMtx().getTranslation();
        exceeded_range = (home - position).squaredLength() > maximum * maximum;
        if (exceeded_range) {
            if (_40) {
                _40->setPosition(position, ksys::phys::PropagateToLinkedMotions{true});
                _40->setLinearVelocity(sead::Vector3f::zero);
            }
            if (_48) {
                _48->setPosition(mActor->getMtx().getTranslation(),
                                 ksys::phys::PropagateToLinkedMotions{true});
                _48->setLinearVelocity(sead::Vector3f::zero);
            }
        }
    }
    if (!exceeded_range) {
        auto* child = getCurrentChild();
        if (!child || !(child->isFinished() || child->isFailed() || child->isChangeable()))
            return;
    }
    if (exceeded_range || isCurrentChild("着弾前")) {
        if (auto* chemical = mActor->getChemicalStuff())
            chemical->sub_7100D909A4();
        if (_40)
            _40->setLinearVelocity(sead::Vector3f::zero);
        if (_48) {
            _48->removeFromWorld();
            _48->setLinearVelocity(sead::Vector3f::zero);
        }
        changeChild("爆発", nullptr);
    } else if (isCurrentChild("爆発")) {
        if (_48)
            _48->removeFromWorld();
        if (_40)
            _40->removeFromWorld();
        changeChild("爆発後", nullptr);
    } else if (isCurrentChild("爆発後")) {
        mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        if (auto* chemical = mActor->getChemicalStuff())
            chemical->sub_7100D90858(false, 3, false, true, false);
        setFinished();
    }
}

void GuardianBeam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GuardianBeam::loadParams_() {
    getStaticParam(&mMaxDistance_s, "MaxDistance");
}

}  // namespace uking::ai
