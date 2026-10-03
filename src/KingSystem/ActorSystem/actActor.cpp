#include "KingSystem/ActorSystem/actActor.h"
#include <mc/seadCoreInfo.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGeneral.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"
#include "KingSystem/ActorSystem/actBoneControl.h"
#include "KingSystem/ActorSystem/actBoneHandle.h"
#include "KingSystem/ActorSystem/actModelBindInfo.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/RigidBody/physRigidBodySet.h"
#include "KingSystem/Physics/StaticCompound/physStaticCompoundMgr.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
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
    if (mCreator)
        mCreator->eraseActor(this);
    if (mPhysics) {
        delete mPhysics;
        mPhysics = nullptr;
    }
    if (mActorParam) {
        ActorParamMgr::instance()->unloadParam(mActorParam);
        mActorParam = nullptr;
    }
    while (_5b0) {
        auto* node = _5b0;
        _5b0 = node->mNext;
        delete node;
    }
    if (mDualHeap2) {
        mDualHeap2->destroy();
        mDualHeap2 = nullptr;
    }
    if (!sActorDebugFlagsMaybe.isOnBit(4)) {
        if (mDualHeap) {
            mDualHeap->destroy();
            mDualHeap = nullptr;
        }
    }
    if (mMsgTransceiver.checkReceiverFlag())
        mMsgTransceiver.isWaitingForAck();
}

bool Actor::sendMessage(const MesTransceiverId& dest, const MessageType& type, void* user_data,
                        bool ack) {
    return mMsgTransceiver.sendMessage(dest, type, user_data, ack);
}

bool Actor::sendMessageOnProcessingThread(const MesTransceiverId& dest, const MessageType& type,
                                          void* user_data, bool ack) {
    return mMsgTransceiver.sendMessageOnProcessingThread(dest, type, user_data, ack);
}

bool Actor::sendMessage(IMessageBroker& broker, const MessageType& type, void* user_data,
                        bool ack) {
    return mMsgTransceiver.sendMessage(broker, type, user_data, ack);
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
    if (m80(ack))
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

void Actor::setMatrix(const sead::Matrix34f& mtx, const sead::Vector3f* scale) {
    mMtx = mtx;
    if (mFieldBodyGroup) {
        mHomeMtx = phys::System::instance()->getStaticCompoundMgr()->getInvTransformedMatrix(
            mFieldBodyGroup, mtx);
    } else {
        mHomeMtx = mtx;
    }
    if (scale)
        mScale = *scale;
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

void Actor::boneHandleStuff(BoneHandleBase* handle, bool sorted) {
    if (mModel)
        handle->sub_7100D3BAAC(&_4d8, mModel, sorted);
}

void Actor::sub_71011DA868(BoneHandleBase* handle) {
    handle->sub_7100D3BBD4(&_4d8);
}

bool Actor::deleteAndEmit(int a1) {
    if (isDeletedOrDeleting() || _687)
        return false;
    if (!deleteLater(DeleteReason::_0))
        return false;
    emitSignalsOrDisappearEffectForDelete(a1);
    return true;
}

void Actor::clearFadeInCreate() {
    if (mFadeOutDeleteType == 0) {
        mStartModelOpacity = 1.0f;
        _68e = true;
        _4f8 = 0.0f;
    }
    mNoFadeInCreate = true;
}

void Actor::sub_71011CCB1C(f32 value) {
    if (_4f0 != value) {
        _4f0 = value;
        _68e = true;
    }
}

void Actor::sub_71011DA824(ActorBind* info) {
    if (!mActorFlags.isOnBit(ActorFlag::_5))
        mModelBindInfo = info;
}

void Actor::sub_71011DA834(ActorBind* info) {
    if (!mActorFlags.isOnBit(ActorFlag::_5))
        mModelBindInfo = nullptr;
}

Unk_7100d860d8* Actor::sub_71011D8A10() {
    if (!mBoneControl)
        return nullptr;
    auto* control = mBoneControl->_0;
    if (!control)
        return nullptr;
    return &control->_10;
}

const sead::Vector3f& Actor::getPreviousPos() const {
    return mPreviousPos;
}

void Actor::actorPhysicsSetFlag2() {
    if (mPhysics)
        mPhysics->setFlag2();
}

s32 Actor::getMaxLife() {
    return getMaxHp_();
}

phys::CharacterController* Actor::getCharacterController() {
    if (!mPhysics)
        return nullptr;
    return mPhysics->getCharacterController();
}

phys::RagdollInstance* Actor::getRagdollInstance() {
    if (!mPhysics)
        return nullptr;
    return mPhysics->getRagdollInstance();
}

bool Actor::sub_71011CEA90() const {
    if (!mPhysics)
        return false;
    auto* ragdoll = mPhysics->getRagdollInstance();
    return ragdoll && ragdoll->getWorldState() == phys::RagdollInstance::WorldState::AddedToWorld;
}

void Actor::updateMtxFromPhysics() {
    if (mPhysics) {
        if (auto* controller = mPhysics->getCharacterController()) {
            if (controller->sub_7100F5E954()) {
                controller->sub_7100F635C4()->getLinearVelocity(&mVelocity);
                mVelocity = mVelocity * (1.0f / 30.0f);
                controller->sub_7100F635C4()->getAngularVelocity(&mAngVelocity);
                mAngVelocity = mAngVelocity * (1.0f / 30.0f);
            }
            controller->physicsXXXGetMtx_1(&mMtx);
            return;
        }
    }

    if (auto* body = mMainBody.load()) {
        if (body->isAddedToWorld()) {
            auto* accessor = body->getRigidBodyAccessor();
            accessor->getLinearVelocity(&mVelocity);
            mVelocity = mVelocity * (1.0f / 30.0f);
            accessor->getAngularVelocity(&mAngVelocity);
            mAngVelocity = mAngVelocity * (1.0f / 30.0f);
        }
        body->getTransform(&mMtx);
    } else if (mPhysicsMtx && mActorFlags.isOnBit(ActorFlag::_2)) {
        mMtx = *mPhysicsMtx;
        mActorFlags.resetBit(ActorFlag::_2);
    }
}

void Actor::m110(f32* a1, s32* a2) {
    *a1 = 0.2f;
    *a2 = 0;
}

void Actor::m111(f32* a1, s32* a2) {
    *a1 = 0.2f;
    *a2 = 2;
}

void Actor::m112(f32* a1, s32* a2) {
    *a1 = 0.01f;
    *a2 = 1;
}

void Actor::m113(f32* a1, s32* a2) {
    *a1 = 0.01f;
    *a2 = 2;
}

f32 Actor::m38() {
    if (mPhysics) {
        if (auto* controller = mPhysics->getCharacterController()) {
            if (auto* body = controller->sub_7100F61A34())
                return body->getMass();
        }
    }
    if (auto* body = mMainBody.load())
        return body->getMass();
    return 0.0f;
}

void Actor::m107() {
    mSkipJobPushTimer = 2;
    if (_598)
        _598->sub_710125122C();
}

f32 Actor::m139() {
    return _4f0 * mStartModelOpacity * _4e8;
}

bool Actor::isWaitRevivalForUsed() const {
    if (!mMapObject)
        return false;
    return mMapObject->checkRevivalFlag(map::ActorData::Flag::RevivalForUsed);
}

void Actor::setRevivalFlagForUsed(bool value) {
    if (mMapObject)
        mMapObject->setRevivalFlagValueIf(map::ActorData::Flag::RevivalForUsed, value);
}

phys::RigidBody* Actor::getPhysicsMainBody() {
    if (mPhysics) {
        if (auto* controller = mPhysics->getCharacterController()) {
            if (auto* body = controller->sub_7100F61A34())
                return body;
        }
    }
    return mMainBody;
}

phys::RigidBody* Actor::findPhysicsBodyByName(const char* group_name, const char* body_name) const {
    if (!mPhysics)
        return nullptr;
    const phys::RigidBodySet* group = mPhysics->findBodyGroupByName(group_name);
    if (!group)
        return nullptr;
    return group->findBodyByHavokName(body_name);
}

bool Actor::sub_71011D57F8(sead::Matrix34f* mtx, const sead::SafeString& bone_name) const {
    if (!mModel)
        return false;
    const auto key = mModel->searchBone(bone_name);
    if (!key.isValid() || !mModel)
        return false;
    mModel->getUnits()(key.model_unit_index)->mModelUnit->getBoneWorldMatrix(mtx, key.bone_index);
    return true;
}

void Actor::fadeOutSleep(SleepWakeReason reason) {
    if (isDeletedOrDeleting())
        return;
    if (mFadeOutSleepFlags.setBitOn(int(reason)))
        onFadeOutSleep();
    if (isSleep() || mStateFlags.isOn(StateFlags::RequestWakeUp))
        sleep(reason);
}

void Actor::emitDeadUpLifeZeroAndSetRevival() {
    emitSignal(map::MapLinkDefType::DeadUp, true);
    emitSignal(map::MapLinkDefType::LifeZero, true);
    if (mMapObject)
        mMapObject->setFlags0(map::Object::Flag0::_100000);
    if (mMapObject)
        mMapObject->setRevivalFlagValueIf(map::ActorData::Flag::RevivalEnable, true);
}

void Actor::sub_71011D7E24() {
    auto* physics = mPhysics;
    if (!physics)
        return;
    if (auto* ragdoll = physics->getRagdollInstance()) {
        ragdoll->changeWorldState(phys::RagdollInstance::WorldState::AddedToWorld);
        physics->sub_7100FBC838(1);
    }
}

void Actor::sub_71011D7E68() {
    auto* physics = mPhysics;
    if (!physics)
        return;
    if (auto* ragdoll = physics->getRagdollInstance()) {
        ragdoll->changeWorldState(phys::RagdollInstance::WorldState::NotAddedToWorld);
        physics->sub_7100FBC838(0);
    }
}

phys::RigidBodySet* Actor::getRigidBodyByName(const char* name) {
    if (!mPhysics)
        return nullptr;
    return mPhysics->findBodyGroupByName(name);
}

Chemical* Actor::sub_71011D8A34(int idx) {
    if (!mChemical)
        return nullptr;
    return mChemical->getStuff(idx);
}

Chemical* Actor::sub_71011D8A44(int idx) {
    if (!mChemical)
        return nullptr;
    return mChemical->sub_7100E37788(idx);
}

Chemical* Actor::getChemicalStuff() {
    auto* chemicals = mChemical;
    if (chemicals && chemicals->_58.size() + chemicals->_80 > 0 && chemicals->getStuff(0))
        return chemicals->getStuff(0);
    return nullptr;
}

bool Actor::m50() {
    auto* chemical = getChemicalStuff();
    if (!chemical)
        return false;
    return chemical->_bc >> 3 & 1;
}

phys::NavMeshCharacter* Actor::m45() {
    if (!mPhysics)
        return nullptr;
    return mPhysics->getNavMeshCharacter();
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

void Actor::m34(sead::Vector3f* pos, f32* value) {}

void Actor::m42(const sead::Matrix34f& mtx) {}

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

void Actor::m56(sead::Vector3f* pos) {
    x_18(pos);
}

bool Actor::m57() {
    return mActorFlags2.isOn(ActorFlag2::_40);
}

void Actor::nullsub_4648() {}

void Actor::sub_71011C88C0(const sead::Matrix34f& mtx) {
    if (mPhysicsMtx) {
        *mPhysicsMtx = mtx;
        mActorFlags.setBit(ActorFlag::_2);
    }
}

void Actor::onPreFadeOutDelete() {}

void Actor::onFadeOutSleep() {}

void Actor::m60() {}

void Actor::m61() {}

bool Actor::shouldUnload(s32* a1) {
    return shouldUnloadBecauseOfDistance(a1);
}

void Actor::m63() {}

void Actor::initMaybe() {}

void Actor::updateLodStuff(Actor* other) {}

void Actor::m66() {}

void Actor::calcMaybe() {}

void Actor::m70() {}

void Actor::updatePositionMaybe() {}

void Actor::m72() {}

void Actor::m73() {}

void Actor::afterModelMatrixUpdate() {}

void Actor::m76(VFR::ScopedDeltaSetter* setter) {}

void Actor::m77(VFR::ScopedDeltaSetter* setter) {}

void Actor::m79() {}

bool Actor::m80(const MessageAck& ack) {
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

bool Actor::m86() {
    if (mActorFlags2.isOn(ActorFlag2::_40))
        return false;
    if (mActorFlags.isOnBit(ActorFlag::_3f))
        return mActorFlags2.isOn(ActorFlag2::_200);
    return true;
}

Actor* Actor::m31() {
    if (mActorFlags.isOnBit(ActorFlag::_5) && mModelBindInfo)
        return mModelBindInfo->sub_7100D3C5E0(this);
    return nullptr;
}

bool Actor::m49() {
    return false;
}

bool Actor::m67() {
    return true;
}

PlayerArmors* Actor::getArmors() {
    return nullptr;
}

PlayerLink* Actor::m129() {
    return nullptr;
}

void Actor::m96(s32* a1, s32* a2) {
    *a1 = -1;
    *a2 = 0;
}

ActorWeapons* Actor::getWeapons() {
    return nullptr;
}

Actor* Actor::m48() {
    return nullptr;
}

Unk_7100e4e084* Actor::m100() {
    return nullptr;
}

uking::act::Unk_7100d3cd74* Actor::m101() {
    return nullptr;
}

int Actor::getExtraHeapSize() {
    return 0;
}

void Actor::m103() {}

void Actor::m114() {}

void Actor::m117(Unk117*) {}

void Actor::m147() {}

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

Unk_71025ae640* Actor::getAtk() {
    return nullptr;
}

uking::act::HorseRideInfo* Actor::getPlayerRideInfo() {
    return nullptr;
}

uking::act::Rideable* Actor::getHorseOptionsMaybe() {
    return nullptr;
}

uking::act::RideableBase* Actor::m132() {
    return nullptr;
}

uking::act::Unk_7100e8b2b8* Actor::getMotorcyclePriorityStuffMaybe() {
    return nullptr;
}

Actor::Unk3* Actor::m135() {
    return nullptr;
}

Unk_71006e45c4* Actor::m128() {
    return nullptr;
}

Unk_71025b08f8* Actor::m126() {
    return nullptr;
}

Unk_71025ae620* Actor::getDropData() {
    return nullptr;
}

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

void Actor::m36(const sead::Vector3f& a1, const sead::Vector3f& a2, bool a3, bool a4, bool a5) {
    sub_71011D8718(a1, a2, false, false, a4, -1, a3, a5);
}

void Actor::m41(sead::Matrix34f* mtx) {
    getCharacterController()->physicsXXXGetMtx_1(mtx);
}

void Actor::m51(bool on) {
    if (auto* chemical = getChemicalStuff())
        chemical->sub_7100D90F60(on);
}

sead::Matrix34f Actor::m122() {
    if (mModel)
        return mModel->getMatrix();
    return sead::Matrix34f::ident;
}

Actor* Actor::m141(const s32* index) {
    return nullptr;
}

// NON_MATCHING: the original keeps the default `_0 = 0` store of the request and stores `_0` again together
// with the core number (the three Unk117 wrappers)
void Actor::x_15(void* a1, const char* a2) {
    Unk117 arg;
    arg._0 = 0;
    arg._4 = sead::CoreInfo::getCurrentCoreId();
    arg._8 = nullptr;
    arg._10 = a1;
    arg._18 = a2;
    x_17(&arg);
}

// NON_MATCHING: see x_15
void Actor::sub_71011C98F8() {
    Unk117 arg;
    arg._0 = 2;
    arg._4 = sead::CoreInfo::getCurrentCoreId();
    arg._8 = nullptr;
    arg._10 = nullptr;
    arg._18 = nullptr;
    x_17(&arg);
}

// NON_MATCHING: see x_15
void Actor::sub_71011C9964(Actor* other) {
    Unk117 arg;
    arg._0 = 3;
    arg._4 = sead::CoreInfo::getCurrentCoreId();
    arg._8 = static_cast<Unk117::Kind3*>(other->_1a0);
    arg._10 = nullptr;
    arg._18 = nullptr;
    x_17(&arg);
}

void Actor::m92(phys::RigidBody* body) {
    if (getProfile() == "AirWall")
        return;
    if (getProfile() != "Bullet")
        body->getPosition();
    deleteLater(DeleteReason::_0);
}

void* Actor::m40() {
    return nullptr;
}

void* Actor::m46() {
    return nullptr;
}

void Actor::m143() {
    _7d8 = true;
    ActorEditorNode::ConnectArg arg{};
    arg.actor_name = mName;
    arg.actor_id = mId;
    arg.root_ai = mRootAi;
    mActorEditorNode.connect(arg);
}

void Actor::killWithDropsAndEffects(int a1) {
    if (isDeletedOrDeleting())
        return;
    createDrops(1, 0);
    if (!isDeletedOrDeleting() && !_687) {
        if (deleteLater(DeleteReason::_0))
            emitSignalsOrDisappearEffectForDelete(a1);
    }
}

void Actor::sub_71011D0204(u32 flags) {
    if (!mStasisFlags.isOn(StasisFlag(flags))) {
        mStasisFlags.set(StasisFlag(flags));
        mActorFlags2.set(ActorFlag2::_400000);
    }
}

void Actor::sub_71011D0228(u32 flags) {
    if (mStasisFlags.isOn(StasisFlag(flags))) {
        mStasisFlags.reset(StasisFlag(flags));
        mActorFlags2.set(ActorFlag2::_400000);
    }
}

// NON_MATCHING: register allocation of the two candidate values of the xlink flag word
void Actor::setModelDrawEnabled(bool enabled) {
    mActorFlags2.change(ActorFlag2::_20, enabled);
    if (mXLink) {
        if (enabled)
            mXLink->_cc.reset(0x80000);
        else
            mXLink->_cc.set(0x80000);
    }
}

void* Actor::m119() {
    return nullptr;
}

bool Actor::m120(const char* name) {
    if (mASList != &as::sNullASListMaybe && mASList)
        mASList->startAnimationMaybe(-1.0f, -1.0f, sead::SafeString(name), 0, 0, true);
    return false;
}

bool Actor::m121() {
    if (mASList == &as::sNullASListMaybe || !mASList)
        return true;
    return mASList->x_4(0, 0);
}

}  // namespace ksys::act
