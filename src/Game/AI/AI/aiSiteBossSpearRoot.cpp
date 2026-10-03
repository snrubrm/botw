#include "Game/AI/AI/aiSiteBossSpearRoot.h"
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace uking::ai {

SiteBossSpearRoot::SiteBossSpearRoot(const InitArg& arg) : SiteBossRoot(arg) {}

SiteBossSpearRoot::~SiteBossSpearRoot() = default;

bool SiteBossSpearRoot::init_(sead::Heap* heap) {
    return SiteBossRoot::init_(heap);
}

void SiteBossSpearRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossRoot::enter_(params);
}

void SiteBossSpearRoot::leave_() {
    SiteBossRoot::leave_();
    mActor->sub_71011DA868(&_318);
    mActor->sub_71011DA868(&_270);
    mActor->sub_71011DA868(&_1c8);
    mActor->sub_71011DA868(&_120);
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A2548()->cstr(), "SensorSpine1")) {
        if (body->isAddedToWorld())
            body->removeFromWorld();
    }
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A2548()->cstr(), "SensorSpine3")) {
        if (body->isAddedToWorld())
            body->removeFromWorld();
    }
    if (auto* body = mActor->findPhysicsBodyByName(sub_71007A2548()->cstr(), "SensorHead")) {
        if (body->isAddedToWorld())
            body->removeFromWorld();
    }
    if (mActor->getRootAi()->isActorGoingBackToRootAi()) {
        if (auto* physics = mActor->getPhysics()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&ksys::act::PlayerInfo::getSomeProcLink(), &accessor);
            if (accessor.hasProc()) {
                if (auto* handler = accessor.x(0))
                    physics->systemGroupHandlerStuff(handler, false);
            }
        }
    }
}

void SiteBossSpearRoot::loadParams_() {
    SiteBossRoot::loadParams_();
    getStaticParam(&mThrowSpearAttackPower_s, "ThrowSpearAttackPower");
    getStaticParam(&mThrowSpearMinDmage_s, "ThrowSpearMinDmage");
    getStaticParam(&mIceSplinterAttackPower_s, "IceSplinterAttackPower");
    getStaticParam(&mIceSplinterMinDamage_s, "IceSplinterMinDamage");
}

bool SiteBossSpearRoot::m35(act::SiteBoss* boss) {
    if (SiteBossRoot::m35(boss))
        return true;
    if (!boss->_14c8._30.isOnBit(9)) {
        if (auto* damage_mgr = sub_710072BA90(mActor)) {
            if (damage_mgr->checkDamageFlags(1) || damage_mgr->checkDamageFlags(0)) {
                if (damage_mgr->getField50() == 3)
                    return true;
            }
        }
    }
    return false;
}

}  // namespace uking::ai
