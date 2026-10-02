#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include <prim/seadRuntimeTypeInfo.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemy.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseTargetedInfo.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSystem.h"

namespace ksys::act {

static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

inline Actor* ActorConstDataAccess::getActor() const {
    return static_cast<Actor*>(getProcIfActor(mProc));
}

bool ActorConstDataAccess::acquireActor(const ActorLinkConstDataAccess& other) {
    return acquire(getProcIfActor(other.mProc));
}

bool ActorConstDataAccess::hasProc(BaseProc* proc) const {
    return mProc == proc;
}

bool ActorConstDataAccess::hasProc(const BaseProcLink& link) const {
    return link.hasProcById(getActor());
}

bool ActorConstDataAccess::linkAcquire(BaseProcLink* link) const {
    auto* proc = getActor();
    if (proc)
        return link->acquire(proc, false);

    link->reset();
    return false;
}

bool ActorConstDataAccess::linkAcquireImmediately(BaseProcLink* link) const {
    auto* proc = getActor();
    if (proc)
        return link->acquire(proc, true);

    link->reset();
    return false;
}

bool ActorConstDataAccess::isPlayerProfile() const {
    return act::isPlayerProfile(getActor());
}

bool ActorConstDataAccess::isWeaponProfile() const {
    return act::isWeaponProfile(getActor());
}

bool ActorConstDataAccess::isNPCProfile() const {
    return act::isNPCProfile(getActor());
}

bool ActorConstDataAccess::isEnemyProfile() const {
    return act::isEnemyProfile(getActor());
}

const sead::SafeString& ActorConstDataAccess::getProfile() const {
    auto* actor = getActor();
    return actor && actor->getParam() ? actor->getProfile() : sead::SafeString::cEmptyString;
}

void ActorConstDataAccess::debugLog(s32, const sead::SafeString&) const {
    // Intentionally left empty.
}

const sead::SafeString& ActorConstDataAccess::getName() const {
    auto* proc = getProcIfActor(mProc);
    if (!proc)
        return sead::SafeString::cEmptyString;
    return proc->getName();
}

const sead::SafeString& ActorConstDataAccess::getLiftType() const {
    auto* actor = getActor();
    if (!actor)
        return sead::SafeString::cEmptyString;
    return actor->getParam()->getRes().mGParamList->getLiftable()->mLiftType.ref();
}

bool ActorConstDataAccess::isDisableFreezeLift() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->getParam()->getRes().mGParamList->getLiftable()->mDisableFreezeLift.ref();
}

bool ActorConstDataAccess::isDisableBurnLift() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->getParam()->getRes().mGParamList->getLiftable()->mDisableBurnLift.ref();
}

bool ActorConstDataAccess::hasTag(const char* tag) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->getParam()->getRes().mActorLink->hasTag(tag);
}

bool ActorConstDataAccess::hasTag(u32 tag) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->getParam()->getRes().mActorLink->hasTag(tag);
}

const char* ActorConstDataAccess::getUniqueName() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->getUniqueName();
}

u32 ActorConstDataAccess::getId() const {
    auto* proc = getActor();
    if (!proc)
        return 0xffffffff;
    return proc->getId();
}

bool ActorConstDataAccess::acquireConnectedCalcParent(ActorLinkConstDataAccess* accessor) const {
    auto* proc = getActor();
    if (!proc)
        return false;

    accessor->acquire(sead::DynamicCast<Actor>(proc->getConnectedCalcParent()));
    return accessor->mProc != nullptr;
}

bool ActorConstDataAccess::acquireConnectedCalcChild(ActorLinkConstDataAccess* accessor) const {
    auto* proc = getActor();
    if (!proc)
        return false;

    accessor->acquire(sead::DynamicCast<Actor>(proc->getConnectedCalcChild()));
    return accessor->mProc != nullptr;
}

bool ActorConstDataAccess::hasConnectedCalcParent() const {
    auto* proc = getActor();
    return proc && sead::DynamicCast<Actor>(proc->getConnectedCalcParent()) != nullptr;
}

bool ActorConstDataAccess::checkFlag2B() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->checkFlag(Actor::ActorFlag::_2b);
}

bool ActorConstDataAccess::deleteLater(BaseProc::DeleteReason reason) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->deleteLater(reason);
}

bool ActorConstDataAccess::deleteEx(BaseProc::DeleteReason reason) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->deleteEx(Actor::DeleteType::_1, reason);
}

bool ActorConstDataAccess::sleep(BaseProc::SleepWakeReason reason) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    actor->sleep(reason);
    return true;
}

bool ActorConstDataAccess::wakeUp(BaseProc::SleepWakeReason reason) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    actor->wakeUp(reason);
    return true;
}

bool ActorConstDataAccess::setProperties(int x, const sead::Matrix34f& mtx,
                                         const sead::Vector3f* vel, const sead::Vector3f* ang_vel,
                                         const sead::Vector3f* scale, bool is_life_infinite, int i,
                                         int life) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    actor->setProperties(x, mtx, vel, ang_vel, scale, is_life_infinite, i, life);
    return true;
}

bool ActorConstDataAccess::setProperties(const sead::Matrix34f& mtx, const sead::Vector3f* vel,
                                         const sead::Vector3f* ang_vel, const sead::Vector3f* scale,
                                         bool is_life_infinite, int i, int life) const {
    return setProperties(0, mtx, vel, ang_vel, scale, is_life_infinite, i, life);
}

bool ActorConstDataAccess::isStateSleep() const {
    auto* actor = getActor();
    return actor && actor->isSleep();
}

bool ActorConstDataAccess::isStateCalc() const {
    auto* actor = getActor();
    return actor && actor->isCalc();
}

bool ActorConstDataAccess::isDeletedOrDeleting() const {
    auto* actor = getActor();
    return actor && actor->isDeletedOrDeleting();
}

res::GParamList* ActorConstDataAccess::getGParamList() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->getParam()->getRes().mGParamList;
}

res::Shop* ActorConstDataAccess::getShopData() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->getParam()->getRes().mShopData;
}

const sead::SafeString& ActorConstDataAccess::getAttackSpHitActor() const {
    auto* actor = getActor();
    if (!actor)
        return sead::SafeString::cEmptyString;
    return actor->getParam()->getRes().mGParamList->getAttack()->mSpHitActor.ref();
}

const sead::SafeString& ActorConstDataAccess::getAttackSpHitTag() const {
    auto* actor = getActor();
    if (!actor)
        return sead::SafeString::cEmptyString;
    return actor->getParam()->getRes().mGParamList->getAttack()->mSpHitTag.ref();
}

const sead::SafeString& ActorConstDataAccess::getAttackWeakHitTag() const {
    auto* actor = getActor();
    if (!actor)
        return sead::SafeString::cEmptyString;
    return actor->getParam()->getRes().mGParamList->getAttack()->mSpWeakHitActor.ref();
}

f32 ActorConstDataAccess::getAttackSpHitRatio() const {
    auto* actor = getActor();
    if (!actor)
        return 1.0f;
    return actor->getParam()->getRes().mGParamList->getAttack()->mSpHitRatio.ref();
}

s32 ActorConstDataAccess::getAttackPower() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    return actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref();
}

map::ObjectLinkData* ActorConstDataAccess::getMapObjectLinkData() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;

    auto* object = actor->getMapObject();
    if (!object)
        return nullptr;

    return object->getLinkData();
}

map::Object* ActorConstDataAccess::getMapObject() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->getMapObject();
}

s32 ActorConstDataAccess::getEnemyRank() const {
    auto* actor = getActor();
    if (!actor)
        return 0;

    auto* gparam = actor->getParam()->getRes().mGParamList;
    if (!gparam || !gparam->getEnemy())
        return 0;

    return gparam->getEnemy()->mRank.ref();
}

bool ActorConstDataAccess::getSameGroupActorName(sead::SafeString* name) const {
    auto* actor = getActor();
    if (!actor) {
        *name = sead::SafeString::cEmptyString;
        return false;
    }

    auto* gparam = actor->getParam()->getRes().mGParamList;
    if (!gparam || !gparam->getSystem()) {
        *name = actor->getName();
        return false;
    }

    const auto& group_name = gparam->getSystem()->mSameGroupActorName.ref();
    if (group_name.isEmpty()) {
        *name = actor->getName();
        return false;
    }

    *name = group_name;
    return true;
}

bool ActorConstDataAccess::checkFlag18() const {
    auto* actor = getActor();
    return actor && actor->checkFlag(Actor::ActorFlag::_18);
}

bool ActorConstDataAccess::isPlayerTheConnectedParent() const {
    auto* actor = getActor();
    if (!actor)
        return false;

    auto* parent = sead::DynamicCast<Actor>(actor->getConnectedCalcParent());
    if (!parent)
        return false;

    return parent->getProfile() == "Player";
}

void ActorConstDataAccess::setThisActorAsParent(BaseProc* child, bool delete_parent_on_delete) {
    auto* actor = getActor();
    if (!actor)
        return;
    child->setConnectedCalcParent(actor, delete_parent_on_delete);
}

void ActorConstDataAccess::setThisActorAsChild(BaseProc* parent, bool delete_child_on_delete) {
    auto* actor = getActor();
    if (!actor)
        return;
    parent->setConnectedCalcChild(actor, delete_child_on_delete);
}

bool ActorConstDataAccess::isAttClientEnabled(const sead::SafeString& client) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return act::isAttClientEnabled(actor, client);
}

bool ActorConstDataAccess::isFlyingBalloon() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    bool* value;
    return actor->getRootAi()->getAITreeVariable(&value, "IsFlyingBalloon") && *value;
}

u32 ActorConstDataAccess::getBalloonHungActorBaseProcID() const {
    auto* actor = getActor();
    if (!actor)
        return -1;
    int* value;
    if (!actor->getRootAi()->getAITreeVariable(&value, "BalloonHungActorBaseProcID"))
        return -1;
    return *value;
}

bool ActorConstDataAccess::checkFlag25() const {
    auto* actor = getActor();
    return actor && actor->checkFlag(Actor::ActorFlag::_25);
}

f32 ActorConstDataAccess::getHorseMoveRadius() const {
    auto* actor = getActor();
    if (!actor)
        return -1.0;
    return actor->getParam()->getRes().mGParamList->getHorseTargetedInfo()->mHorseMoveRadius.ref();
}

f32 ActorConstDataAccess::getHorseAvoidOffset() const {
    auto* actor = getActor();
    if (!actor)
        return -1.0;
    return actor->getParam()->getRes().mGParamList->getHorseTargetedInfo()->mHorseAvoidOffset.ref();
}

bool ActorConstDataAccess::horseTargetedIsCircularMoveAlways() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* gparam = actor->getParam()->getRes().mGParamList;
    return gparam->getHorseTargetedInfo()->mIsCircularMoveAlways.ref();
}

bool acquireActor(BaseProcLink* link, ActorConstDataAccess* accessor) {
    return link->getProcInContext([accessor](BaseProc* proc, bool valid) {
        if (!proc) {
            if (!valid)
                accessor->acquire(nullptr);
            return false;
        }
        return accessor->acquire(sead::DynamicCast<Actor>(proc));
    });
}

bool ActorConstDataAccess::getAabb(sead::Vector3f* min, sead::Vector3f* max) const {
    auto* actor = getActor();
    if (!actor || !actor->mModel)
        return false;

    if (min)
        *min = actor->mAabb.getMin();
    if (max)
        *max = actor->mAabb.getMax();
    return true;
}

bool ActorConstDataAccess::sub_7100D13AE4(const sead::SafeString& name, BaseProc* proc,
                                          const res::AttCheck_Unk1* arg, bool a4) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    const auto* client = sub_7100EE3E2C(actor, name);
    if (!client)
        return false;
    return client->sub_7100D72554(proc, arg, a4);
}

bool ActorConstDataAccess::sub_7100D13BB8() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* unk = actor->m128();
    if (!unk)
        return false;
    return unk->m2();
}

phys::SystemGroupHandler* ActorConstDataAccess::sub_7100D10448(s32 idx) const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    auto* physics = actor->getPhysics();
    if (!physics)
        return nullptr;
    return physics->get178(idx);
}

void ActorConstDataAccess::getHomeMtx(sead::Matrix34f* mtx) const {
    auto* actor = getActor();
    if (!actor) {
        mtx->makeIdentity();
        return;
    }
    actor->getHomeMtx(mtx);
}

const sead::Vector3f& ActorConstDataAccess::getPreviousPos() const {
    auto* actor = getActor();
    if (!actor)
        return sead::Vector3f::zero;
    return actor->getPreviousPos();
}

// NON_MATCHING: the original selects between the two addresses (csel) instead of branching
const sead::Vector3f& ActorConstDataAccess::getPreviousPos2() const {
    auto* actor = getActor();
    if (!actor)
        return sead::Vector3f::zero;
    return actor->mPreviousPos2;
}

// NON_MATCHING: the original does not tail-call the virtual function
uking::act::Rideable* ActorConstDataAccess::getHorseOptions() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->getHorseOptionsMaybe();
}

// NON_MATCHING: the original does not tail-call the virtual function
uking::act::Unk_7100e8b2b8* ActorConstDataAccess::getHorseRideStuff() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->getMotorcyclePriorityStuffMaybe();
}

// NON_MATCHING: the original selects between the two addresses (csel) instead of branching
const sead::Vector3f& ActorConstDataAccess::getField44C_Vec3() const {
    auto* actor = getActor();
    if (!actor)
        return sead::Vector3f::zero;
    return actor->_454;
}

// NON_MATCHING: the original selects between the two addresses (csel) instead of branching
const sead::Vector3f& ActorConstDataAccess::getVelocity() const {
    auto* actor = getActor();
    if (!actor)
        return sead::Vector3f::zero;
    return actor->getVelocity();
}

// NON_MATCHING: the original selects between the two addresses (csel) instead of branching
const sead::Vector3f& ActorConstDataAccess::getAngVelocity() const {
    auto* actor = getActor();
    if (!actor)
        return sead::Vector3f::zero;
    return actor->getAngVelocity();
}

// 0x7100d10e6c: whether bit `bit` of the actor's previous ActorFlag2 value (Actor::_51c) is set.
bool ActorConstDataAccess::sub_7100D10E6C(int bit) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->mActorFlags2Prev.isOn(Actor::ActorFlag2(1 << bit));
}

// 0x7100d10fb8
bool ActorConstDataAccess::sub_7100D10FB8() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->getActorFlags2().isOn(Actor::ActorFlag2::_40);
}

bool ActorConstDataAccess::sub_7100D11F10() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    if (!actor->getMainBody() && !actor->getCharacterController())
        return false;
    return true;


}

int ActorConstDataAccess::sub_7100D131D0(int idx) const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    Chemical* chemical;
    if (idx < 0) {
        chemical = actor->getChemicalStuff();
    } else {
        auto* chemicals = actor->mChemical;
        if (!chemicals)
            return 0;
        chemical = chemicals->getStuff(idx);
    }
    if (!chemical)
        return 0;
    return chemical->_c0;
}

s32 ActorConstDataAccess::getLife() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    auto* life = actor->getLife();
    if (!life)
        return 1;
    return *life;
}

s32 ActorConstDataAccess::getMaxLife() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    return actor->getMaxLife();
}

}  // namespace ksys::act
