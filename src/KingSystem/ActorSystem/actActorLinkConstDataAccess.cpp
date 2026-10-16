#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include <prim/seadRuntimeTypeInfo.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include "Game/Actor/actHorseRideInfo.h"
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/MessageTransceiverId.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyFromShape.h"
#include "KingSystem/Physics/physMaterialMask.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/System/physSystem.h"
#include "KingSystem/Resource/Actor/resResourceDrop.h"
#include "KingSystem/Resource/Actor/resResourceModelList.h"
#include "KingSystem/ActorSystem/actUnk_7100e4e084.h"
#include "KingSystem/ActorSystem/actUnk_71024ef620.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapLinkTag.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemy.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorseTargetedInfo.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSystem.h"

namespace ksys::act {

MesTransceiverId sDefaultMesTransceiverId;

const MesTransceiverId* BaseProcAccessor::getMessageTransceiverId() const {
    const Actor* actor = mProc ? sead::DynamicCast<Actor>(mProc) : nullptr;
    if (!actor || actor->checkFlag(Actor::ActorFlag::_2e))
        return &sDefaultMesTransceiverId;
    return actor->getMesTransceiverId();
}

const sead::Matrix34f& BaseProcAccessor::getActorMtx() const {
    const Actor* actor = mProc ? sead::DynamicCast<Actor>(mProc) : nullptr;
    if (actor)
        return actor->getMtx();
    return sead::Matrix34f::ident;
}

bool BaseProcAccessor::sub_7100D11860(sead::Matrix34f* mtx) const {
    if (auto* actor = mProc ? sead::DynamicCast<Actor>(mProc) : nullptr) {
        if (auto* body = actor->getMainBody()) {
            body->getRigidBodyAccessor()->getTransform(mtx);
            return true;
        }
    }
    const Actor* actor = mProc ? sead::DynamicCast<Actor>(mProc) : nullptr;
    *mtx = actor ? actor->getMtx() : sead::Matrix34f::ident;
    return false;
}


u32 ActorLinkConstDataAccess::sub_71006E3EC0() const {
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(getActor()))
        return enemy->_e90;
    return u32(-1);
}

namespace {
phys::StaticCompoundRigidBodyGroup* sNullFieldBodyGroup = nullptr;
}  // namespace

static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

inline Actor* ActorLinkConstDataAccess::getActor() const {
    return static_cast<Actor*>(getProcIfActor(mProc));
}

bool ActorLinkConstDataAccess::acquireActor(const BaseProcAccessor& other) {
    return acquire(getProcIfActor(other.mProc));
}

bool ActorLinkConstDataAccess::hasProc(BaseProc* proc) const {
    return mProc == proc;
}

bool ActorLinkConstDataAccess::hasProc(const BaseProcLink& link) const {
    return link.hasProcById(getActor());
}

bool ActorLinkConstDataAccess::linkAcquire(BaseProcLink* link) const {
    auto* proc = getActor();
    if (proc)
        return link->acquire(proc, false);

    link->reset();
    return false;
}

bool ActorLinkConstDataAccess::linkAcquireImmediately(BaseProcLink* link) const {
    auto* proc = getActor();
    if (proc)
        return link->acquire(proc, true);

    link->reset();
    return false;
}

bool ActorLinkConstDataAccess::isPlayerProfile() const {
    return act::isPlayerProfile(getActor());
}

bool ActorLinkConstDataAccess::isWeaponProfile() const {
    return act::isWeaponProfile(getActor());
}

bool ActorLinkConstDataAccess::isNPCProfile() const {
    return act::isNPCProfile(getActor());
}

bool ActorLinkConstDataAccess::isEnemyProfile() const {
    return act::isEnemyProfile(getActor());
}

const sead::SafeString& ActorLinkConstDataAccess::getProfile() const {
    auto* actor = getActor();
    return actor && actor->getParam() ? actor->getProfile() : sead::SafeString::cEmptyString;
}

void ActorLinkConstDataAccess::debugLog(s32, const sead::SafeString&) const {
    // Intentionally left empty.
}

const sead::SafeString& ActorLinkConstDataAccess::getName() const {
    auto* proc = getProcIfActor(mProc);
    if (!proc)
        return sead::SafeString::cEmptyString;
    return proc->getName();
}

const sead::SafeString& ActorLinkConstDataAccess::getLiftType() const {
    auto* actor = getActor();
    if (!actor)
        return sead::SafeString::cEmptyString;
    return actor->getParam()->getRes().mGParamList->getLiftable()->mLiftType.ref();
}

bool ActorLinkConstDataAccess::isDisableFreezeLift() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->getParam()->getRes().mGParamList->getLiftable()->mDisableFreezeLift.ref();
}

bool ActorLinkConstDataAccess::isDisableBurnLift() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->getParam()->getRes().mGParamList->getLiftable()->mDisableBurnLift.ref();
}

bool ActorLinkConstDataAccess::hasTag(const char* tag) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->getParam()->getRes().mActorLink->hasTag(tag);
}

bool ActorLinkConstDataAccess::hasTag(u32 tag) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->getParam()->getRes().mActorLink->hasTag(tag);
}

const char* ActorLinkConstDataAccess::getUniqueName() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->getUniqueName();
}

u32 ActorLinkConstDataAccess::getId() const {
    auto* proc = getActor();
    if (!proc)
        return 0xffffffff;
    return proc->getId();
}

bool ActorLinkConstDataAccess::acquireConnectedCalcParent(BaseProcAccessor* accessor) const {
    auto* proc = getActor();
    if (!proc)
        return false;

    accessor->acquire(sead::DynamicCast<Actor>(proc->getConnectedCalcParent()));
    return accessor->mProc != nullptr;
}

bool ActorLinkConstDataAccess::acquireConnectedCalcChild(BaseProcAccessor* accessor) const {
    auto* proc = getActor();
    if (!proc)
        return false;

    accessor->acquire(sead::DynamicCast<Actor>(proc->getConnectedCalcChild()));
    return accessor->mProc != nullptr;
}

bool ActorLinkConstDataAccess::hasConnectedCalcParent() const {
    auto* proc = getActor();
    return proc && sead::DynamicCast<Actor>(proc->getConnectedCalcParent()) != nullptr;
}

bool ActorLinkConstDataAccess::checkFlag2B() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->checkFlag(Actor::ActorFlag::_2b);
}

bool ActorLinkConstDataAccess::deleteLater(BaseProc::DeleteReason reason) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->deleteLater(reason);
}

bool ActorLinkConstDataAccess::deleteEx(BaseProc::DeleteReason reason) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->deleteEx(Actor::DeleteType::_1, reason);
}

bool ActorLinkConstDataAccess::sleep(BaseProc::SleepWakeReason reason) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    actor->sleep(reason);
    return true;
}

bool ActorLinkConstDataAccess::wakeUp(BaseProc::SleepWakeReason reason) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    actor->wakeUp(reason);
    return true;
}

bool ActorLinkConstDataAccess::setProperties(int x, const sead::Matrix34f& mtx,
                                         const sead::Vector3f* vel, const sead::Vector3f* ang_vel,
                                         const sead::Vector3f* scale, bool is_life_infinite, int i,
                                         int life) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    actor->setProperties(x, mtx, vel, ang_vel, scale, is_life_infinite, i, life);
    return true;
}

bool ActorLinkConstDataAccess::setProperties(const sead::Matrix34f& mtx, const sead::Vector3f* vel,
                                         const sead::Vector3f* ang_vel, const sead::Vector3f* scale,
                                         bool is_life_infinite, int i, int life) const {
    return setProperties(0, mtx, vel, ang_vel, scale, is_life_infinite, i, life);
}

bool ActorLinkConstDataAccess::isStateSleep() const {
    auto* actor = getActor();
    return actor && actor->isSleep();
}

bool ActorLinkConstDataAccess::isStateCalc() const {
    auto* actor = getActor();
    return actor && actor->isCalc();
}

bool ActorLinkConstDataAccess::isDeletedOrDeleting() const {
    auto* actor = getActor();
    return actor && actor->isDeletedOrDeleting();
}

res::GParamList* ActorLinkConstDataAccess::getGParamList() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->getParam()->getRes().mGParamList;
}

res::Shop* ActorLinkConstDataAccess::getShopData() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->getParam()->getRes().mShopData;
}

const sead::SafeString& ActorLinkConstDataAccess::getAttackSpHitActor() const {
    auto* actor = getActor();
    if (!actor)
        return sead::SafeString::cEmptyString;
    return actor->getParam()->getRes().mGParamList->getAttack()->mSpHitActor.ref();
}

const sead::SafeString& ActorLinkConstDataAccess::getAttackSpHitTag() const {
    auto* actor = getActor();
    if (!actor)
        return sead::SafeString::cEmptyString;
    return actor->getParam()->getRes().mGParamList->getAttack()->mSpHitTag.ref();
}

const sead::SafeString& ActorLinkConstDataAccess::getAttackWeakHitTag() const {
    auto* actor = getActor();
    if (!actor)
        return sead::SafeString::cEmptyString;
    return actor->getParam()->getRes().mGParamList->getAttack()->mSpWeakHitActor.ref();
}

f32 ActorLinkConstDataAccess::getAttackSpHitRatio() const {
    auto* actor = getActor();
    if (!actor)
        return 1.0f;
    return actor->getParam()->getRes().mGParamList->getAttack()->mSpHitRatio.ref();
}

s32 ActorLinkConstDataAccess::getAttackPower() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    return actor->getParam()->getRes().mGParamList->getAttack()->mPower.ref();
}

map::ObjectLinkData* ActorLinkConstDataAccess::getMapObjectLinkData() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;

    auto* object = actor->getMapObject();
    if (!object)
        return nullptr;

    return object->getLinkData();
}

map::Object* ActorLinkConstDataAccess::getMapObject() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->getMapObject();
}

s32 ActorLinkConstDataAccess::getEnemyRank() const {
    auto* actor = getActor();
    if (!actor)
        return 0;

    auto* gparam = actor->getParam()->getRes().mGParamList;
    if (!gparam || !gparam->getEnemy())
        return 0;

    return gparam->getEnemy()->mRank.ref();
}

bool ActorLinkConstDataAccess::getSameGroupActorName(sead::SafeString* name) const {
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

bool ActorLinkConstDataAccess::checkFlag18() const {
    auto* actor = getActor();
    return actor && actor->checkFlag(Actor::ActorFlag::_18);
}

bool ActorLinkConstDataAccess::isPlayerTheConnectedParent() const {
    auto* actor = getActor();
    if (!actor)
        return false;

    auto* parent = sead::DynamicCast<Actor>(actor->getConnectedCalcParent());
    if (!parent)
        return false;

    return parent->getProfile() == "Player";
}

void ActorLinkConstDataAccess::setThisActorAsParent(BaseProc* child, bool delete_parent_on_delete) {
    auto* actor = getActor();
    if (!actor)
        return;
    child->setConnectedCalcParent(actor, delete_parent_on_delete);
}

void ActorLinkConstDataAccess::setThisActorAsChild(BaseProc* parent, bool delete_child_on_delete) {
    auto* actor = getActor();
    if (!actor)
        return;
    parent->setConnectedCalcChild(actor, delete_child_on_delete);
}

bool ActorLinkConstDataAccess::isAttClientEnabled(const sead::SafeString& client) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return act::isAttClientEnabled(actor, client);
}

bool ActorLinkConstDataAccess::isFlyingBalloon() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    bool* value;
    return actor->getRootAi()->getAITreeVariable(&value, "IsFlyingBalloon") && *value;
}

u32 ActorLinkConstDataAccess::getBalloonHungActorBaseProcID() const {
    auto* actor = getActor();
    if (!actor)
        return -1;
    int* value;
    if (!actor->getRootAi()->getAITreeVariable(&value, "BalloonHungActorBaseProcID"))
        return -1;
    return *value;
}

bool ActorLinkConstDataAccess::checkFlag25() const {
    auto* actor = getActor();
    return actor && actor->checkFlag(Actor::ActorFlag::_25);
}

f32 ActorLinkConstDataAccess::getHorseMoveRadius() const {
    auto* actor = getActor();
    if (!actor)
        return -1.0;
    return actor->getParam()->getRes().mGParamList->getHorseTargetedInfo()->mHorseMoveRadius.ref();
}

f32 ActorLinkConstDataAccess::getHorseAvoidOffset() const {
    auto* actor = getActor();
    if (!actor)
        return -1.0;
    return actor->getParam()->getRes().mGParamList->getHorseTargetedInfo()->mHorseAvoidOffset.ref();
}

bool ActorLinkConstDataAccess::horseTargetedIsCircularMoveAlways() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* gparam = actor->getParam()->getRes().mGParamList;
    return gparam->getHorseTargetedInfo()->mIsCircularMoveAlways.ref();
}

bool acquireActor(const BaseProcLink* link, ActorLinkConstDataAccess* accessor) {
    return link->getProcInContext([accessor](BaseProc* proc, bool valid) {
        if (!proc) {
            if (!valid)
                accessor->acquire(nullptr);
            return false;
        }
        return accessor->acquire(sead::DynamicCast<Actor>(proc));
    });
}

bool ActorLinkConstDataAccess::getAabb(sead::Vector3f* min, sead::Vector3f* max) const {
    auto* actor = getActor();
    if (!actor || !actor->mModel)
        return false;

    if (min)
        *min = actor->mAabb.getMin();
    if (max)
        *max = actor->mAabb.getMax();
    return true;
}

const sead::BoundBox3f& ActorLinkConstDataAccess::sub_7100D0FD54() const {
    auto* actor = getActor();
    if (actor && actor->getModel())
        return actor->getAabb();
    return sead::BoundBox3f::cUndefined;
}

bool ActorLinkConstDataAccess::sub_7100D13AE4(const sead::SafeString& name, BaseProc* proc,
                                          const res::AttCheck_Unk1* arg, bool a4) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    const auto* client = sub_7100EE3E2C(actor, name);
    if (!client)
        return false;
    return client->sub_7100D72554(proc, arg, a4);
}

bool ActorLinkConstDataAccess::sub_7100D13BB8() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* unk = actor->m128();
    if (!unk)
        return false;
    return unk->m2();
}

phys::SystemGroupHandler* ActorLinkConstDataAccess::sub_7100D10448(s32 idx) const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    auto* physics = actor->getPhysics();
    if (!physics)
        return nullptr;
    return physics->get178(idx);
}

phys::SystemGroupHandler* ActorLinkConstDataAccess::x(s32 idx) const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    auto* physics = actor->getPhysics();
    if (!physics)
        return nullptr;
    return physics->get188(idx);
}

bool ActorLinkConstDataAccess::sub_7100D12E64() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* info = actor->getPlayerRideInfo();
    if (!info)
        return false;
    return info->_30 & 1;
}

bool ActorLinkConstDataAccess::sub_7100D0FEAC() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->m50();
}

bool ActorLinkConstDataAccess::sub_7100D11188(sead::Matrix34f* out) const {
    if (auto* actor = getActor()) {
        if (auto* chemical = actor->getChemicalStuff()) {
            chemical->sub_7100D9153C(out);
            return true;
        }
    }
    out->makeIdentity();
    return false;
}

f32 ActorLinkConstDataAccess::sub_7100D11254() const {
    f32 value = 0.0f;
    if (auto* actor = getActor()) {
        if (auto* chemical = actor->getChemicalStuff())
            value = chemical->_34;
    }
    return value;
}

void ActorLinkConstDataAccess::getHomeMtx(sead::Matrix34f* mtx) const {
    auto* actor = getActor();
    if (!actor) {
        mtx->makeIdentity();
        return;
    }
    actor->getHomeMtx(mtx);
}

void ActorLinkConstDataAccess::sub_7100D105A8(sead::Matrix34f* mtx) const {
    auto* actor = getActor();
    if (!actor) {
        mtx->makeIdentity();
        return;
    }
    *mtx = actor->getHomeMtxRaw();
}

void ActorLinkConstDataAccess::sub_7100D10BD4(sead::Vector3f* out) const {
    if (!out)
        return;
    auto* actor = getActor();
    if (actor)
        *out = actor->_46c;
    else
        *out = sead::Vector3f::zero;
}

const sead::Vector3f& ActorLinkConstDataAccess::getPreviousPos() const {
    auto* actor = getActor();
    if (!actor)
        return sead::Vector3f::zero;
    return actor->getPreviousPos();
}

// NON_MATCHING: the original selects between the two addresses (csel) instead of branching
const sead::Vector3f& ActorLinkConstDataAccess::getPreviousPos2() const {
    auto* actor = getActor();
    if (!actor)
        return sead::Vector3f::zero;
    return actor->mPreviousPos2;
}

phys::NavMeshCharacter* ActorLinkConstDataAccess::sub_7100D0F57C() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    if (auto* info = actor->getPlayerRideInfo()) {
        if (info->_28)
            return info->_28;
    }
    return actor->m45();
}

// NON_MATCHING: the original does not tail-call the virtual function
uking::act::Rideable* ActorLinkConstDataAccess::getHorseOptions() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->getHorseOptionsMaybe();
}

// NON_MATCHING: the original does not tail-call the virtual function
uking::act::Unk_7100e8b2b8* ActorLinkConstDataAccess::getHorseRideStuff() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->getMotorcyclePriorityStuffMaybe();
}

u64 ActorLinkConstDataAccess::sub_7100D1443C() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    auto* rideable = actor->m132();
    if (!rideable)
        return 0;
    return rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b;
}

f32 ActorLinkConstDataAccess::sub_7100D110E4() const {
    f32 depth = 0;
    if (auto* actor = getActor()) {
        if (actor->get68f().load()) {
            const f32 y = actor->getMtx().m[1][3];
            depth = actor->get6f0() - y;
        }
    }
    return depth;
}

bool ActorLinkConstDataAccess::sub_7100D0F048() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->_4f8 > 0;
}

bool ActorLinkConstDataAccess::sub_7100D0F180() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->mFadeOutDeleteType != 0;
}

bool ActorLinkConstDataAccess::sub_7100D0FF48() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->_68f != 0;
}

xlink::XLink* ActorLinkConstDataAccess::sub_7100D0F214() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->mXLink;
}

Schedule* ActorLinkConstDataAccess::sub_7100D0F3D0() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->mSchedule;
}

f32 ActorLinkConstDataAccess::sub_7100D10A08() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    return actor->_490;
}

f32 ActorLinkConstDataAccess::sub_7100D12100() const {
    auto* actor = getActor();
    if (!actor)
        return 1;
    return actor->mScale.x;
}

bool ActorLinkConstDataAccess::sub_7100D11048() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->m57();
}

f32 ActorLinkConstDataAccess::sub_7100D14114() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    return actor->m38();
}

// NON_MATCHING: the original does not tail-call the virtual function
Chemical* ActorLinkConstDataAccess::sub_7100D14E0C() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    return actor->getChemicalStuff();
}

f32 ActorLinkConstDataAccess::sub_7100D13080() const {
    f32 value = 0;
    if (auto* actor = getActor()) {
        if (auto* chemical = actor->getChemicalStuff())
            value = chemical->_1b8;
    }
    return value;
}

f32 ActorLinkConstDataAccess::sub_7100D13128() const {
    f32 value = 0;
    if (auto* actor = getActor()) {
        if (auto* chemical = actor->getChemicalStuff())
            value = chemical->_1bc;
    }
    return value;
}

bool ActorLinkConstDataAccess::sub_7100D146D8() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* obj = actor->m100();
    if (!obj)
        return false;
    return obj->_100 == 2;
}

bool ActorLinkConstDataAccess::sub_7100D0EFA4(s32 idx) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->mSpecialJobTypesMaskOverride.isOnBit(idx);
}

void ActorLinkConstDataAccess::sub_7100D15448() const {
    if (auto* actor = getActor())
        actor->_720.increment();
}

void ActorLinkConstDataAccess::sub_7100D154DC() const {
    if (auto* actor = getActor())
        actor->_720.decrement();
}

bool ActorLinkConstDataAccess::sub_7100D13C64() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    if (auto* obj = actor->m128())
        return obj->m9();
    return false;
}

bool ActorLinkConstDataAccess::sub_7100D13D10() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    if (auto* obj = actor->m128())
        return obj->m16();
    return false;
}

void ActorLinkConstDataAccess::sub_7100D1525C() const {
    if (auto* actor = getActor())
        actor->_687 = true;
}

// NON_MATCHING: the original selects between the two addresses (csel) instead of branching
const sead::Vector3f& ActorLinkConstDataAccess::getField44C_Vec3() const {
    auto* actor = getActor();
    if (!actor)
        return sead::Vector3f::zero;
    return actor->_454;
}

// NON_MATCHING: the actor-null and failed-type paths are merged by the compiler.
const sead::Vector3f& ActorLinkConstDataAccess::getField440_Vec3() const {
    auto* actor = getActor();
    return actor ? actor->_448 : sead::Vector3f::zero;
}

// NON_MATCHING: the actor-null and failed-type paths are merged by the compiler.
const sead::Vector3f& ActorLinkConstDataAccess::getField484_Vec3() const {
    auto* actor = getActor();
    return actor ? actor->mPreviousPos3 : sead::Vector3f::zero;
}

// NON_MATCHING: the actor-null and failed-type paths are merged by the compiler.
const sead::Vector3f& ActorLinkConstDataAccess::getField458_Vec3() const {
    auto* actor = getActor();
    return actor ? actor->_460 : sead::Vector3f::zero;
}

// NON_MATCHING: the actor-null and failed-type paths are merged by the compiler.
const sead::Vector3f& ActorLinkConstDataAccess::getField470_Vec3() const {
    auto* actor = getActor();
    return actor ? actor->_478 : sead::Vector3f::zero;
}

// NON_MATCHING: the actor-null and failed-type paths are merged by the compiler.
phys::StaticCompoundRigidBodyGroup* const& ActorLinkConstDataAccess::getFieldBodyGroup() const {
    auto* actor = getActor();
    return actor ? actor->getFieldBodyGroup() : sNullFieldBodyGroup;
}

// NON_MATCHING: the actor-null and failed-type paths are merged by the compiler.
const sead::Vector3f& ActorLinkConstDataAccess::getField418() const {
    auto* actor = getActor();
    return actor ? actor->mScale : sead::Vector3f::ones;
}

// NON_MATCHING: the original selects between the two addresses (csel) instead of branching
const sead::Vector3f& ActorLinkConstDataAccess::getVelocity() const {
    auto* actor = getActor();
    if (!actor)
        return sead::Vector3f::zero;
    return actor->getVelocity();
}

// NON_MATCHING: the original selects between the two addresses (csel) instead of branching
const sead::Vector3f& ActorLinkConstDataAccess::getAngVelocity() const {
    auto* actor = getActor();
    if (!actor)
        return sead::Vector3f::zero;
    return actor->getAngVelocity();
}

// 0x7100d10e6c: whether bit `bit` of the actor's previous ActorFlag2 value (Actor::_51c) is set.
bool ActorLinkConstDataAccess::sub_7100D10E6C(int bit) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->mActorFlags2Prev.isOn(Actor::ActorFlag2(1 << bit));
}

// 0x7100d10fb8
bool ActorLinkConstDataAccess::sub_7100D10FB8() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->getActorFlags2().isOn(Actor::ActorFlag2::_40);
}

bool ActorLinkConstDataAccess::sub_7100D11F10() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    if (!actor->getMainBody() && !actor->getCharacterController())
        return false;
    return true;


}

bool ActorLinkConstDataAccess::sub_7100D1463C() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->m140();
}

int ActorLinkConstDataAccess::sub_7100D131D0(int idx) const {
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

bool ActorLinkConstDataAccess::sub_7100D13448(int idx) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* chemicals = actor->mChemical;
    if (!chemicals)
        return false;
    auto* chemical = chemicals->getStuff(idx < 0 ? 0 : idx);
    if (chemical && chemical->_c0 == 2)
        return true;
    return false;
}

s32 ActorLinkConstDataAccess::getLife() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    auto* life = actor->getLife();
    if (!life)
        return 1;
    return *life;
}

s32 ActorLinkConstDataAccess::getMaxLife() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    return actor->getMaxLife();
}

// 0x7100d0e39c: the ModelList's attack target offset (0 if there is none).
f32 ActorLinkConstDataAccess::sub_7100D0E39C() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    auto* list = actor->getParam()->getRes().mModelList;
    if (!list)
        return 0;
    return list->getAttention().mAttackTargetOffsetBack.ref();
}

// 0x7100d0eaa4: stores `value` in Actor::m135()'s Unk3::_4, then deletes the actor with type 4.
bool ActorLinkConstDataAccess::sub_7100D0EAA4(s64 value) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    if (auto* unk = actor->m135())
        unk->_4 = value;
    return actor->deleteEx(Actor::DeleteType::_4, BaseProc::DeleteReason::_0);
}

// 0x7100d0fdf8: Actor::_548's awareness entry (Unk_71024dca28::m8()).
Unk_71024dc978* ActorLinkConstDataAccess::sub_7100D0FDF8() const {
    auto* actor = getActor();
    if (!actor)
        return nullptr;
    if (actor->_548 && actor->_548->m8())
        return actor->_548->m8();
    return nullptr;
}

// 0x7100d0ffdc: flag bit 27 of the chemical `idx` (the actor's first chemical if idx < 0).
bool ActorLinkConstDataAccess::sub_7100D0FFDC(int idx) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    Chemical* chemical;
    if (idx < 0) {
        chemical = actor->getChemicalStuff();
    } else {
        auto* chemicals = actor->mChemical;
        if (!chemicals)
            return false;
        chemical = chemicals->getStuff(idx);
    }
    if (!chemical)
        return false;
    return chemical->_c & 0x8000000;
}

// 0x7100d10f0c
bool ActorLinkConstDataAccess::sub_7100D10F0C() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    if (actor->get1a0())
        return true;
    if (auto* obj = actor->getMapObject()) {
        if (obj->getFlags0().isOn(map::Object::Flag0::_20000))
            return true;
    }
    return false;
}

// 0x7100d12f08: Chemical::sub_7100D9108C() of the chemical `idx` (the actor's first chemical if idx < 0).
// NON_MATCHING: the original evaluates `index < 0 || count < index` into a bool before the ChemicalMgr lookup.
bool ActorLinkConstDataAccess::sub_7100D12758(Chemical* chemical, int flags, int index) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* chemicals = actor->getChemicalContainer();
    if (!chemicals)
        return false;
    const s32 count = chemicals->_58.size() + chemicals->_80;
    if (count <= 0)
        return false;
    auto* mgr = world::Manager::instance()->getChemicalMgr();
    Chemical* target;
    if (index < 0 || count < index)
        target = actor->getChemicalStuff();
    else
        target = actor->sub_71011D8A34(index);
    mgr->sub_71010CBDCC(target, chemical, flags);
    return false;
}

bool ActorLinkConstDataAccess::sub_7100D12F08(int idx) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    Chemical* chemical;
    if (idx < 0) {
        chemical = actor->getChemicalStuff();
    } else {
        auto* chemicals = actor->mChemical;
        if (!chemicals)
            return false;
        chemical = chemicals->getStuff(idx);
    }
    if (!chemical)
        return false;
    return chemical->sub_7100D9108C();
}

// 0x7100d13290
bool ActorLinkConstDataAccess::sub_7100D13290(int idx) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    Chemical* chemical;
    if (idx < 0) {
        chemical = actor->getChemicalStuff();
    } else {
        auto* chemicals = actor->mChemical;
        if (!chemicals)
            return false;
        chemical = chemicals->getStuff(idx);
    }
    if (!chemical)
        return false;
    if (!(chemical->mMaterial->attribute.ref() & 1))
        return false;
    return !(chemical->_be & 1);
}

// 0x7100d1336c
bool ActorLinkConstDataAccess::sub_7100D1336C(int idx) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    Chemical* chemical;
    if (idx < 0) {
        chemical = actor->getChemicalStuff();
    } else {
        auto* chemicals = actor->mChemical;
        if (!chemicals)
            return false;
        chemical = chemicals->getStuff(idx);
    }
    if (!chemical)
        return false;
    if (!(chemical->mMaterial->attribute.ref() & 8))
        return false;
    return !(chemical->_be & 4);
}

// 0x7100d134f8
s32 ActorLinkConstDataAccess::sub_7100D134F8(int idx) const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    auto* chemicals = actor->mChemical;
    if (!chemicals)
        return 0;
    auto* chemical = chemicals->getStuff(idx < 0 ? 0 : idx);
    if (!chemical)
        return 0;
    return chemical->sub_7100D91360();
}

// 0x7100d135a0
f32 ActorLinkConstDataAccess::sub_7100D135A0(int idx) const {
    f32 value = 0;
    if (auto* actor = getActor()) {
        if (auto* chemicals = actor->mChemical) {
            if (auto* chemical = chemicals->getStuff(idx < 0 ? 0 : idx)) {
                if (!(chemical->_c & 0x1000000))
                    value = chemical->_190;
            }
        }
    }
    return value;
}

// 0x7100d13654
bool ActorLinkConstDataAccess::sub_7100D13654(int idx) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* chemicals = actor->mChemical;
    if (!chemicals)
        return false;
    auto* chemical = chemicals->getStuff(idx < 0 ? 0 : idx);
    if (chemical && chemical->_c0 == 2 && chemical->sub_7100D913A8())
        return true;
    return false;
}

// 0x7100d1370c
bool ActorLinkConstDataAccess::sub_7100D1370C(int idx) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* chemicals = actor->mChemical;
    if (!chemicals)
        return false;
    auto* chemical = chemicals->getStuff(idx < 0 ? 0 : idx);
    if (!chemical)
        return false;
    if (chemical->_bf & 2)
        return false;
    return chemical->mMaterial->attribute.ref() & 0x8000;
}

// 0x7100d13860: ActorAttention::getNumClients().
s32 ActorLinkConstDataAccess::sub_7100D13860() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    auto* attention = actor->getAttention();
    if (!attention)
        return 0;
    return attention->getNumClients();
}

// 0x7100d13994: AttClient::isEnabled() of the actor's attention client `idx`.
bool ActorLinkConstDataAccess::sub_7100D13994(s32 idx) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    const auto* attention = actor->getAttention();
    if (!attention)
        return false;
    auto* client = attention->getClientByIdx(idx);
    if (!client)
        return false;
    return client->isEnabled();
}

// 0x7100d13a3c: AttClient::sub_7100D72534() of the actor's attention client `idx` (8 without one).
s32 ActorLinkConstDataAccess::sub_7100D13A3C(s32 idx) const {
    auto* actor = getActor();
    if (!actor)
        return 8;
    const auto* attention = actor->getAttention();
    if (!attention)
        return 8;
    auto* client = attention->getClientByIdx(idx);
    if (!client)
        return 8;
    return client->sub_7100D72534();
}

// 0x7100d13e9c: Unk_71024dc858::_50 of Actor::_548's entry.
bool ActorLinkConstDataAccess::sub_7100D13E9C() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    if (auto* unk = actor->get548())
        return unk->_18._50;
    return false;
}

// 0x7100d13f38: LodState flag bit 7.
bool ActorLinkConstDataAccess::sub_7100D13F38() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    if (auto* lod = actor->getLodState())
        return lod->mFlags8.isOnBit(7);
    return false;
}

// 0x7100d144ec
uking::act::Rideable::Gear ActorLinkConstDataAccess::sub_7100D144EC() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    auto* rideable = actor->getHorseOptionsMaybe();
    if (!rideable)
        return 0;
    return rideable->m23();
}

// 0x7100d14598
Unk_7100d14598 ActorLinkConstDataAccess::sub_7100D14598() const {
    auto* actor = getActor();
    if (!actor)
        return 1;
    auto* unk = actor->getMotorcyclePriorityStuffMaybe();
    if (!unk)
        return 1;
    return unk->sub_7100E8C03C();
}

// 0x7100d11c5c
bool ActorLinkConstDataAccess::sub_7100D11C5C(sead::Vector3f* out) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* unk = actor->m128();
    if (!unk)
        return false;
    unk->m10(out, nullptr);
    return true;
}

// 0x7100d152e4
bool ActorLinkConstDataAccess::sub_7100D152E4() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    if (actor->isAwakeMaybe()) {
        if (auto* unk = actor->m128()) {
            unk->m11();
            return true;
        }
    }
    return false;
}

// 0x7100d153a4: Actor::x_3(value).
void ActorLinkConstDataAccess::sub_7100D153A4(f32 value) const {
    if (auto* actor = getActor())
        actor->x_3(value);
}

// 0x7100d14250: BaseProc flag 0x10 (DoNotDelete).
bool ActorLinkConstDataAccess::sub_7100D14250() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    return actor->isDoNotDeleteMaybe();
}

// 0x7100d141b0: RigidBody::getVolume() of the main body.
f32 ActorLinkConstDataAccess::sub_7100D141B0() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    auto* body = actor->getMainBody();
    if (!body)
        return 0;
    return body->getVolume();
}

// 0x7100d115e8: the main body's center of mass in local space (zero without a body).
bool ActorLinkConstDataAccess::sub_7100D115E8(sead::Vector3f* out) const {
    if (!out)
        return false;
    if (auto* actor = getActor()) {
        if (auto* body = actor->getMainBody()) {
            body->getCenterOfMassInLocal(out);
            return true;
        }
    }
    *out = sead::Vector3f::zero;
    return false;
}

// 0x7100d117c0: the main body's contact layer.
bool ActorLinkConstDataAccess::sub_7100D117C0(phys::ContactLayer* out) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* body = actor->getMainBody();
    if (!body)
        return false;
    *out = body->getContactLayer();
    return true;
}

// 0x7100d11fb0
bool ActorLinkConstDataAccess::sub_7100D11FB0() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* unk = actor->getMotorcyclePriorityStuffMaybe();
    if (!unk)
        return false;
    const uking::act::Unk_7100e8b2b8::Unk8 type = unk->_8 & 0xff;
    return int(type) != uking::act::Unk_7100e8b2b8::Unk8::_0;
}

// NON_MATCHING: the original returns the select in s0 and the early -1 separately (we keep a phi in s8)
// 0x7100d14780: CharacterController::sub_7100F62E74 for the current body (-1 without one).
f32 ActorLinkConstDataAccess::sub_7100D14780() const {
    f32 result = -1.0f;
    if (auto* actor = getActor()) {
        if (auto* controller = actor->getCharacterController()) {
            f32 value = 0;
            if (controller->sub_7100F62E74(&value, controller->_224))
                result = value;
        }
    }
    return result;
}

// 0x7100d14c80: the actor's gravity (the physics system's default one without an actor).
bool ActorLinkConstDataAccess::sub_7100D14C80(sead::Vector3f* out) const {
    auto* actor = getActor();
    if (actor) {
        sub_7100EE5B84(out, actor);
        return true;
    }
    *out = phys::System::instance()->getField48();
    return false;
}

// 0x7100d14d40: while the actor sleeps, moves it to `mtx`.
bool ActorLinkConstDataAccess::sub_7100D14D40(const sead::Matrix34f& mtx) const {
    auto* actor = getActor();
    if (!actor)
        return false;
    if (actor->isSleep()) {
        actor->setMtx(mtx, true, true);
        actor->nullsub_4648();
        return true;
    }
    return false;
}

// 0x7100d13dbc: whether the character controller's current body is the physics group "Swimming".
bool ActorLinkConstDataAccess::sub_7100D13DBC() const {
    auto* actor = getActor();
    if (!actor)
        return false;
    auto* controller = actor->getCharacterController();
    if (!controller)
        return false;
    s32 idx = -1;
    if (auto* physics = actor->getPhysics())
        idx = physics->sub_7100FBE7F0("Swimming");
    if (idx >= 0 && controller->_224 == idx)
        return true;
    return false;
}

// 0x7100d15cb8 / 0x7100d15d84 / 0x7100d15e50: integer map unit parameters.
s32 ActorLinkConstDataAccess::sub_7100D15CB8() const {
    auto* actor = getActor();
    if (!actor)
        return -1;
    auto* ai = actor->getRootAi();
    if (!ai)
        return -1;
    const s32* value;
    if (!ai->getMapUnitParam(&value, "EquipStandSlot"))
        return -1;
    return *value;
}

s32 ActorLinkConstDataAccess::sub_7100D15D84() const {
    auto* actor = getActor();
    if (!actor)
        return -1;
    auto* ai = actor->getRootAi();
    if (!ai)
        return -1;
    const s32* value;
    if (!ai->getMapUnitParam(&value, "ArmorDyeColor"))
        return -1;
    return *value;
}

s32 ActorLinkConstDataAccess::sub_7100D15E50() const {
    auto* actor = getActor();
    if (!actor)
        return -2;
    auto* ai = actor->getRootAi();
    if (!ai)
        return -2;
    const s32* value;
    if (!ai->getMapUnitParam(&value, "ShopSellType"))
        return -2;
    return *value;
}

// 0x7100d15570 / 0x7100d155f8 / 0x7100d15680 / 0x7100d15708: Actor::_68d = 1 / 2 / 3 / 4.
void ActorLinkConstDataAccess::sub_7100D15570() const {
    if (auto* actor = getActor())
        actor->_68d = 1;
}

void ActorLinkConstDataAccess::sub_7100D155F8() const {
    if (auto* actor = getActor())
        actor->_68d = 2;
}

void ActorLinkConstDataAccess::sub_7100D15680() const {
    if (auto* actor = getActor())
        actor->_68d = 3;
}

void ActorLinkConstDataAccess::sub_7100D15708() const {
    if (auto* actor = getActor())
        actor->_68d = 4;
}

// 0x7100d15198: sets the root AI's two vectors and value (RootAi::sub_7100D66B48).
void ActorLinkConstDataAccess::sub_7100D15198(const sead::Vector3f& a, const sead::Vector3f& b,
                                          f32 value) const {
    if (auto* actor = getActor()) {
        if (auto* ai = actor->getRootAi())
            ai->sub_7100D66B48(a, b, value);
    }
}

// 0x7100d15038: if `other` has `_1a0` or a map object with flag 0x20000, Actor::sub_71011C9964(other).
void ActorLinkConstDataAccess::sub_7100D15038(Actor* other) const {
    auto* actor = getActor();
    if (!actor)
        return;
    if (other->get1a0()) {
        actor->sub_71011C9964(other);
        return;
    }
    if (auto* obj = other->getMapObject()) {
        if (obj->getFlags0().isOn(map::Object::Flag0::_20000))
            actor->sub_71011C9964(other);
    }
}

void ActorLinkConstDataAccess::sub_7100D150E8(Actor* owner) {
    auto* actor = getActor();
    if (!actor)
        return;
    if (owner->get1a0()) {
        sub_71011D7650(actor, owner);
        return;
    }
    if (auto* object = owner->getMapObject()) {
        if (object->getFlags0().isOn(map::Object::Flag0::_20000))
            sub_71011D7650(actor, owner);
    }
}

// 0x7100d137c0
s32 ActorLinkConstDataAccess::sub_7100D137C0(const sead::SafeString& name) const {
    auto* actor = getActor();
    if (!actor)
        return -1;
    auto* chemicals = actor->mChemical;
    if (!chemicals)
        return -1;
    return chemicals->sub_7100E382C4(name);
}

// 0x7100d142e0
u64 ActorLinkConstDataAccess::sub_7100D142E0() const {
    auto* actor = getActor();
    if (!actor)
        return 0;
    auto* info = actor->getPlayerRideInfo();
    if (!info)
        return 0;
    ActorLinkConstDataAccess rider;
    ksys::act::acquireActor(&info->_18, &rider);
    auto* rider_actor = rider.getActor();
    if (!rider_actor)
        return 0;
    auto* rideable = rider_actor->m132();
    if (!rideable)
        return 0;
    return rideable->_18._b == 0 ? rideable->_18._9 : rideable->_18._b;
}

bool ActorLinkConstDataAccess::sub_7100D15C0C(phys::Constraint* constraint) const {
    auto* actor = getActor();
    if (!actor)
        return false;

    auto* body = actor->getPhysicsMainBody();
    if (!body)
        return false;

    constraint->sub_7100F6A92C(body);
    return true;
}

}  // namespace ksys::act

// NON_MATCHING: the original does not tail-call getRandomDropFromTable
const sead::SafeString& golemWeakPointGetOneDrop(const ksys::act::ActorLinkConstDataAccess& accessor,
                                                 const sead::SafeString& table) {
    auto* actor = accessor.getActor();
    if (actor) {
        if (auto* drop = actor->getParam()->getRes().mDropTable)
            return drop->getRandomDropFromTable(table);
    }
    return sead::SafeString::cEmptyString;
}

namespace ksys::act {

bool ActorLinkConstDataAccess::checkLinkTagActivated(bool a, bool b) {
    auto* proc = mProc;
    if (!proc)
        return false;
    auto* tag = sead::DynamicCast<map::LinkTag>(proc);
    if (!tag)
        return false;
    if (a)
        return (tag->_1e0 & 8) != 0;
    return tag->sub_7100D39420(b);
}

bool ActorLinkConstDataAccess::sub_7100D1584C(s32 index) const {
    auto* proc = mProc;
    if (!proc)
        return false;
    if (auto* tag = sead::DynamicCast<map::LinkTag>(proc))
        return tag->sub_7100D39420(index == 9);
    if (auto* actor = sead::DynamicCast<Actor>(proc))
        return actor->mSignals.isOnBit(index);
    return false;
}

void ActorLinkConstDataAccess::sub_7100D15964(s32 core, MessageTransceiverBase* sender, s32 a1,
                                         s32 a2, s32 message, void* user_data,
                                         const sead::SafeString* target) const {
    auto* proc = mProc;
    if (!proc)
        return;
    if (auto* tag = sead::DynamicCast<map::LinkTag>(proc)) {
        if (!sub_71011D7194(tag, core))
            return;
        if (tag->mObj) {
            if (auto* links = tag->mObj->getLinkData())
                links->sub_7100D4F1D0(core, sender, a1, a2, message, user_data, target);
        }
        return;
    }
    if (auto* actor = sead::DynamicCast<Actor>(proc))
        actor->sub_71011D8BCC(core, sender, a1, a2, message, user_data, target);
}

void ActorLinkConstDataAccess::triggerLink() {
    auto* proc = mProc;
    if (!proc)
        return;
    if (auto* tag = sead::DynamicCast<map::LinkTag>(proc)) {
        tag->sub_7100D39120();
        return;
    }
    if (auto* actor = sead::DynamicCast<Actor>(proc))
        actor->m107();
}

bool ActorLinkConstDataAccess::getMtxPos(sead::Vector3f* out) const {
    if (auto* actor = getActor()) {
        if (auto* body = actor->getMainBody()) {
            body->getCenterOfMassInWorld(out);
            return true;
        }
    }
    getActorMtx().getTranslation(*out);
    return false;
}

bool ActorLinkConstDataAccess::sub_7100D11E54(sead::Matrix34f* out) const {
    if (auto* actor = getActor()) {
        sub_7100D36FA0(out, actor);
        return true;
    }
    out->makeIdentity();
    return false;
}

bool ActorLinkConstDataAccess::sub_7100D116B4(phys::MaterialMask* out) const {
    if (auto* actor = getActor()) {
        if (auto* body = sead::DynamicCast<phys::RigidBodyFromShape>(actor->getMainBody())) {
            out->set(body->tryGetMaterialMask()->getData());
            return true;
        }
    }
    return false;
}

bool ActorLinkConstDataAccess::sub_7100D119A8(sead::Matrix34f* out,
                                        const sead::SafeString& name) const {
    if (auto* actor = getActor()) {
        if (auto* body = actor->findPhysicsBodyByName("Body", name.cstr())) {
            body->getRigidBodyAccessor()->getTransform(out);
            return true;
        }
    }
    *out = getActorMtx();
    return false;
}

bool ActorLinkConstDataAccess::sub_7100D11B14(sead::Vector3f* out) const {
    if (auto* actor = getActor())
        return actor->x_18(out);
    getActorMtx().getTranslation(*out);
    return false;
}

bool ActorLinkConstDataAccess::sub_7100D11D14(sead::Vector3f* out) const {
    if (auto* actor = getActor()) {
        sub_7100D36EE0(out, actor);
        return true;
    }
    getActorMtx().getTranslation(*out);
    return false;
}

void ActorLinkConstDataAccess::sub_7100D14F94(Unk_71024ef620* out) const {
    if (auto* actor = getActor()) {
        if (auto* body = actor->findPhysicsBodyByName("Body", "ConnectRope"))
            out->_30 = body;
    }
}

// NON_MATCHING: the boolean return is merged with the fallback instead of using the native tail.
bool ActorLinkConstDataAccess::sub_7100D122EC(phys::NavMeshCharacter* character) const {
    if (auto* actor = getActor()) {
        if (auto* physics = actor->getPhysics()) {
            if (auto* objects = physics->sub_7100FC0124()) {
                if (auto* data = objects->getBufferPtr())
                    return character->sub_7100F7D234(data) >= 0;
            }
        }
    }
    return false;
}

// NON_MATCHING: the final DynamicCast keeps a null branch and the matrix copy is scheduled differently.
bool ActorLinkConstDataAccess::sub_7100D112FC(sead::Matrix34f* out) const {
    if (auto* actor = getActor()) {
        if (sead::DynamicCast<Actor>(actor->getConnectedCalcParent())) {
            *out = sead::DynamicCast<Actor>(actor->getConnectedCalcParent())->getMtx();
            return true;
        }
    }
    out->makeIdentity();
    return false;
}

// NON_MATCHING: the RTTI/input guards are merged differently and the chemical call is not a tail call.
bool ActorLinkConstDataAccess::sub_7100D12FCC(const Chemical* other) const {
    if (auto* actor = getActor()) {
        if (other) {
            if (auto* chemical = actor->getChemicalStuff())
                return chemical->sub_7100D913BC(*other);
        }
    }
    return false;
}

// NON_MATCHING: the name and output use opposite saved registers.
void ActorLinkConstDataAccess::sub_7100D1288C(gsys::BoneAccessKeyEx* out,
                                       const sead::SafeString& name) const {
    if (auto* actor = getActor()) {
        if (auto* model = actor->getModel()) {
            out->search(model, name);
            return;
        }
    }
    out->getKey().reset();
}

// NON_MATCHING: the lowercase loop uses wider indices and different branch scheduling.
bool ActorLinkConstDataAccess::sub_7100D12944(sead::Matrix34f* out,
                                       const sead::SafeString& name) const {
    if (auto* actor = getActor()) {
        isRope(actor);
        if (auto* model = actor->getModel()) {
            auto key = model->searchBone(name);
            if (!key.isValid()) {
                sead::FixedSafeString<128> lower_name;
                const s32 length = name.calcLength() + 1;
                for (s32 i = 0; i < length; ++i) {
                    if (name[i] >= 'A' && name[i] <= 'Z')
                        lower_name.append(name[i] + ('a' - 'A'));
                    else
                        lower_name.append(name[i]);
                }
                key = model->searchBone(lower_name);
            }
            if (key.isValid()) {
                model->getUnits()(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(
                    out, key.bone_index);
                return true;
            }
        }
    }
    out->makeIdentity();
    return false;
}

}  // namespace ksys::act
