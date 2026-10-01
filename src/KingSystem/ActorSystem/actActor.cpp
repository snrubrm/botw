#include "KingSystem/ActorSystem/actActor.h"
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
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

phys::CharacterController* Actor::getCharacterController() {
    if (!mPhysics)
        return nullptr;
    return mPhysics->getCharacterController();
}

}  // namespace ksys::act
