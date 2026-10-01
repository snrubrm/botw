#include "KingSystem/ActorSystem/actActor.h"
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGeneral.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physSystem.h"

namespace ksys::act {

namespace {
BaseProcLink sDummyBaseProcLink;
}  // namespace

BaseProcLink& getDummyBaseProcLink() {
    return sDummyBaseProcLink;
}

Actor::Actor(const CreateArg& arg) : BaseProc(arg) {
    mJobHandlers[BaseProcMgr::getConstant0()] = &mJob0;
    mJobHandlers[BaseProcMgr::getConstant1()] = &mJob1;
    mJobHandlers[BaseProcMgr::getConstant2()] = &mJob2;
    mJobHandlers[BaseProcMgr::getConstant4()] = &mJob4;

    mUnk1.actor = this;
    mUnk1._4 = 0;
}

Actor::~Actor() {
    // FIXME
}

void Actor::clearFlag(Actor::ActorFlag flag) {
    mActorFlags.resetBit(flag);
}

bool Actor::checkFlag(Actor::ActorFlag flag) const {
    return mActorFlags.isOnBit(flag);
}

void Actor::setFlag(Actor::ActorFlag flag) {
    setFlag(flag, true);
}

void Actor::setFlag(Actor::ActorFlag flag, bool on) {
    mActorFlags.changeBit(flag, on);
}

bool Actor::checkSignal(map::MapLinkDefType type) const {
    if (mMapObject && mMapObject->getLinkData())
        return mMapObject->getLinkData()->mLinksToSelf.checkLink(type, false);
    return false;
}

map::ObjectLink* Actor::findPlacementLinkWithType(map::MapLinkDefType type) const {
    if (mMapObject && mMapObject->getLinkData())
        return mMapObject->getLinkData()->mLinksToSelf.findLinkWithType(type);
    return nullptr;
}

void Actor::emitSignal(map::MapLinkDefType type, bool on) {
    const auto thread = sead::ThreadMgr::instance()->getCurrentThread();
    thread->getPriority();

    if (mSignals.isOnBit(int(type)) == on)
        return;
    mSignals.changeBit(int(type), on);

    if (!mMapObject || !mMapObject->getLinkData())
        return;

    for (auto& link : mMapObject->getLinkData()->mLinksOther.links) {
        if (link.type != type)
            continue;
        ActorConstDataAccess accessor;
        link.getObjectProcWithAccessor(accessor);
        accessor.triggerLink();
    }
}

bool Actor::checkLinkSignal(map::MapLinkDefType type) const {
    if (mMapObject && mMapObject->getLinkData())
        return mMapObject->getLinkData()->mLinksOther.checkLink(type, true);
    return false;
}

bool Actor::hasForbidAttentionLink() const {
    if (!findPlacementLinkWithType(map::MapLinkDefType::ForbidAttention))
        return false;
    if (!mUniqueName)
        return false;
    return mUniqueName->change_attention_type.isEmpty();
}

void Actor::nullsub_4649() {}

const sead::SafeString& Actor::getProfile() const {
    return mActorParam->getProfile();
}

const char* Actor::getUniqueName() const {
    const char* unique_name = nullptr;

    if (mMapObjIter.tryGetParamStringByKey(&unique_name, "UniqueName"))
        return unique_name;

    if (mUniqueName && mUniqueName->unique_name)
        unique_name = mUniqueName->unique_name->cstr();

    return unique_name;
}

void Actor::handleAck(const MessageAck& ack) {
    if (m80())
        return;

    if (mRootAi)
        mRootAi->handleAck(ack);
}

int Actor::handleMessage(const Message& message) {
    const auto result = doHandleMessage_(message);
    switch (result) {
    default:
        return 0;
    case HandleMessageResult::_1:
        return 1;
    case HandleMessageResult::_2:
        m107();
        return 1;
    }
}

bool Actor::x_18(sead::Vector3f* out) const {
    sead::Matrix34f mtx = sead::Matrix34f::ident;
    if (mPhysics && mPhysics->getCharacterController()) {
        mPhysics->getCharacterController()->physicsXXXGetMtx_1(&mtx);
    } else if (phys::RigidBody* body = mMainBody) {
        body->getTransform(&mtx);
    } else {
        mMtx.getTranslation(*out);
        return false;
    }
    *out = _4b4;
    *out *= mtx;
    return true;
}

void Actor::getHomeMtx(sead::Matrix34f* mtx) const {
    if (mFieldBodyGroup) {
        *mtx = phys::System::instance()->getStaticCompoundMgr()->getTransformedMatrix(
            mFieldBodyGroup, mHomeMtx);
    } else {
        *mtx = mHomeMtx;
    }
}

void Actor::getHomePos(sead::Vector3f* pos) const {
    if (mFieldBodyGroup) {
        sead::Vector3f home_pos;
        mHomeMtx.getTranslation(home_pos);
        *pos = phys::System::instance()->getStaticCompoundMgr()->getTransformedPos(mFieldBodyGroup,
                                                                                   home_pos);
    } else {
        mHomeMtx.getTranslation(*pos);
    }
}

const sead::Vector3f& Actor::getPreviousPos() const {
    return mPreviousPos;
}

phys::CharacterController* Actor::getCharacterController() {
    if (!mPhysics)
        return nullptr;
    return mPhysics->getCharacterController();
}

void Actor::destruct_(int should_destruct) {
    BaseProc::destruct_(should_destruct);
}

void Actor::onDeleteRequested_(DeleteReason reason) {}

bool Actor::shouldClearStateFlag4000_() {
    return true;
}

void Actor::preDelete1_() {}

// In the original vtable this function is in the prepareForPreDelete_ slot (7); the startPreparingForPreDelete_
// slot (8) holds a different (bool) function (0x71011c828c).
Actor::PreDeletePrepareResult Actor::prepareForPreDelete_() {
    unlinkPlacementObj();
    return PreDeletePrepareResult::Done;
}

void Actor::afterUpdateState_() {
    BaseProc::afterUpdateState_();
    mActorFlags2Prev = mActorFlags2;
}

void Actor::setFlag0x40() {
    if (isInit())
        mActorFlags.setBit(ActorFlag::_6);
}

void Actor::setVelocity(const sead::Vector3f* vel, const sead::Vector3f* ang_vel) {
    if (!isInit() && !isSleep())
        return;

    if (vel)
        mVelocity = *vel;
    if (ang_vel)
        mAngVelocity = *ang_vel;
    if (vel || ang_vel)
        _68a = true;
}

void Actor::resetMubinBymlIter() {
    mMapObjIter = map::MubinIter();
}

s32 Actor::getMaxHp_() {
    const auto* gparamlist = mActorParam->getRes().mGParamList;
    if (!gparamlist)
        return 1;
    const auto* general = gparamlist->getGeneral();
    if (!general)
        return 1;
    return general->mLife.ref();
}

void Actor::m32() {
    m31();
}

bool Actor::m33() {
    return false;
}

f32 Actor::getGuardableAngle() {
    return 0.0f;
}

bool Actor::m39() {
    return false;
}

void Actor::m42() {}

void Actor::m43(bool on) {}

bool Actor::m47() {
    return false;
}

bool Actor::m53() {
    return false;
}

bool Actor::m55() {
    return false;
}

bool Actor::m56(sead::Vector3f* pos) {
    return x_18(pos);
}

bool Actor::m57() {
    return mActorFlags2.isOn(ActorFlag2::_40);
}

void Actor::nullsub_4648() {}

void Actor::onPreFadeOutDelete() {}

void Actor::onFadeOutSleep() {}

void Actor::m60() {}

bool Actor::shouldUnload() {
    return shouldUnloadBecauseOfDistance();
}

void Actor::m63() {}

void Actor::initMaybe() {}

void Actor::m66() {}

void Actor::calcMaybe() {}

void Actor::m70() {}

void Actor::updatePositionMaybe() {}

void Actor::m72() {}

void Actor::m73() {}

void Actor::afterModelMatrixUpdate() {}

void Actor::m79() {}

bool Actor::m80() {
    return false;
}

int Actor::getCalcTiming() {
    return 0;
}

bool Actor::m83() {
    return true;
}

s32* Actor::getLife() {
    return nullptr;
}

void Actor::m93(int a1, float a2) {}

s32 Actor::m94() {
    return 0;
}

ActorWeapons* Actor::getWeapons() {
    return nullptr;
}

int Actor::getExtraHeapSize() {
    return 0;
}

void Actor::m103() {}

bool Actor::m106() {
    return true;
}

int Actor::m109() {
    return 8;
}

void Actor::m115() {}

void Actor::m116() {}

bool Actor::m123() {
    return true;
}

void Actor::onPlacementObjReset() {}

uking::dmg::DamageManagerBase* Actor::getDamageMgr() {
    return nullptr;
}

LifeRecoverInfo* Actor::getLifeRecoverInfo() {
    return nullptr;
}

bool Actor::m137() {
    return false;
}

bool Actor::m138() {
    return false;
}

bool Actor::m140() {
    return false;
}

bool Actor::m142() {
    return false;
}

void Actor::m144() {
    _7d8 = false;
    mActorEditorNode.disconnect();
}

void Actor::m145() {}

bool Actor::m146() {
    return false;
}

}  // namespace ksys::act
