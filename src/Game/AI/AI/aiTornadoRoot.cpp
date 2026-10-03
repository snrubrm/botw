#include "Game/AI/AI/aiTornadoRoot.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

namespace uking::ai {

TornadoRoot::TornadoRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TornadoRoot::~TornadoRoot() {
    if (auto* physics = mActor->getPhysics())
        physics->sub_7100FBDFA4(physics->get178(0));
}

bool TornadoRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void TornadoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    changeChild("移動");
    sub_71005CAE90();
}

void TornadoRoot::sub_71005CAE90() {
    sub_71007A2C30(mActor, "AtkBody", &mActor->getMtx());
    getActorAttackSensor(mActor)->activateAttackSensor(
        8, 0xc, *mAttackPower_m,
        mActor->getParam()->getRes().mGParamList->getAttack()->mImpulseLarge.ref(), 0.0f, 0, 1, -1,
        false, *mAtMinDamage_m, -1);

    if (*mIsHitOnlyPlayer_s) {
        if (auto* body = mActor->findPhysicsBodyByName(sub_71007A24BC()->cstr(), "AtkBody")) {
            body->enableContactLayer(ksys::phys::ContactLayer::SensorObject);
            body->enableContactLayer(ksys::phys::ContactLayer::SensorNPC);
            body->enableContactLayer(ksys::phys::ContactLayer::SensorRope);
            body->enableContactLayer(ksys::phys::ContactLayer::SensorTree);
            body->enableContactLayer(ksys::phys::ContactLayer::SensorHorse);
        }
    }
}

void TornadoRoot::calc_() {
    if (!isCurrentChild("移動"))
        return;

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        changeChild("削除");
}

void TornadoRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void TornadoRoot::loadParams_() {
    getStaticParam(&mIsHitOnlyPlayer_s, "IsHitOnlyPlayer");
    getMapUnitParam(&mAtMinDamage_m, "AtMinDamage");
    getMapUnitParam(&mAttackPower_m, "AttackPower");
}

}  // namespace uking::ai
