#include "KingSystem/ActorSystem/actActor.h"
#include "Game/gameEventMgr1.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include <mc/seadCoreInfo.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actImpulseBaseProcLink.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/ActorSystem/actActorParamMgr.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerArmors.h"
#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/UIGlue.h"
#include "KingSystem/Graphics/gfxUnk_710260af28.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/Actor/resResourceModelList.h"
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

// NON_MATCHING: the conditional offset reference avoids a temporary vector copy.
void Actor::m89() {
    res::ModelList::AttentionInfo attention_info;
    const bool has_attention =
        mActorParam && mActorParam->getRes().mModelList &&
        mActorParam->getRes().mModelList->getAttentionInfo(&attention_info);
    x_0(&_498, has_attention ? attention_info.look_at_offset : sead::Vector3f::zero,
        has_attention, &mPreviousPos2);
}

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

void Actor::m88() {
    if (mAttention) {
        mAttention->sub_7100D73454(&mPreviousPos);
        return;
    }
    if (!x_18(&mPreviousPos))
        mMtx.getTranslation(mPreviousPos);
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

bool Actor::areMtxAndHomeMtxPosDesynced() const {
    sead::Vector3f home_pos;
    if (mFieldBodyGroup) {
        sead::Vector3f pos;
        mHomeMtx.getTranslation(pos);
        home_pos = phys::System::instance()->getStaticCompoundMgr()->getTransformedPos(
            mFieldBodyGroup, pos);
    } else {
        mHomeMtx.getTranslation(home_pos);
    }
    sead::Vector3f pos;
    mMtx.getTranslation(pos);
    return (home_pos - pos).squaredLength() > 0.5f;
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

// NON_MATCHING: the main-body fallback tail (mMainBody, else the first rigid body of the physics
// set) is jump-threaded for the no-physics path; the original keeps one shared test block.
void Actor::setMtx(const sead::Matrix34f& mtx, bool a2, bool a3) {
    if (a2) {
        mMtx = mtx;
        if (mModel)
            mModel->setMatrix(mtx);
    } else {
        sub_71011C88C0(mtx);
    }

    auto* physics = mPhysics;
    auto* controller = physics ? physics->getCharacterController() : nullptr;
    if (controller) {
        controller->sub_7100F60500(mtx);
    } else {
        auto* body = mMainBody.load();
        if (!body)
            body = physics ? physics->sub_7100FBAEDC(0, 0) : nullptr;
        if (body)
            body->setTransform(mtx);
    }

    m42(mtx);

    if (physics && a3) {
        physics->setFlag2();
        physics->clothVisibleStuff_0(-2);
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

bool Actor::sub_71011C5C4C() const {
    if (!mMapObject)
        return false;
    return mMapObject->getFlags0().isOn(map::Object::Flag0::_2);
}

bool Actor::sub_71011C7A98() const {
    return checkFlag(ActorFlag::_8);
}

bool Actor::sub_71011CBC28() const {
    if (checkFlag(ActorFlag::_a))
        return true;
    return mFadeOutDeleteType == 2;
}

bool Actor::sub_71011D7790() const {
    if (!checkFlag(ActorFlag::_a))
        return false;
    return !mActorFlags2.isOn(ActorFlag2::_8000);
}

bool Actor::sub_71011DB30C() const {
    if (!_598)
        return false;
    return _598->mFlags8.isOnBit(11);
}

bool Actor::isWaitRevivalForDrop() const {
    if (!mMapObject)
        return false;
    return mMapObject->checkRevivalFlag(map::ActorData::Flag::RevivalForDrop);
}

void Actor::setRevivalFlagForDrop(bool value) {
    if (mMapObject)
        mMapObject->setRevivalFlagValueIf(map::ActorData::Flag::RevivalForDrop, value);
}

void Actor::set6f0(float value) {
    _6f0 = value;
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

void Actor::decrementSkipJobPushTimer() {
    if (mSkipJobPushTimer)
        --mSkipJobPushTimer;
}

bool Actor::sub_71011CDDCC() const {
    if (mSkipJobPushTimer)
        return false;
    if (_1a0)
        return false;
    if (mMapObject && mMapObject->getFlags0().isOn(map::Object::Flag0::_20000))
        return false;
    return true;
}

void Actor::sub_71011DB138() {
    mActorFlags.setBit(ActorFlag::_1);
}

void Actor::sub_71011DAFB4(int a, int b) {
    _6fc = a;
    _700 = b;
}

// NON_MATCHING: getCharacterController is inlined rather than called out of line.
bool Actor::sub_710084CD70() {
    auto* controller = getCharacterController();
    return controller && (controller->_116 & 4);
}

f32 Actor::getDepthInWater() const {
    f32 depth = -1.0f;
    if (mPhysics) {
        if (auto* controller = mPhysics->getCharacterController()) {
            if (controller->_116 & 4)
                depth = controller->_210;
        }
    }
    return depth;
}

void Actor::fadeOutWakeUp(SleepWakeReason reason) {
    if (!isDeletedOrDeleting()) {
        if (mFadeOutSleepFlags.setBitOff(int(reason)))
            m60();
    }
    if (!isAwakeMaybe())
        wakeUp(reason);
}

// NON_MATCHING: the original keeps the 1/30 constant in a callee-saved register across the calls
void Actor::updateVelocityStuff() {
    constexpr f32 k = 1.0f / 30.0f;
    auto* controller = mPhysics ? mPhysics->getCharacterController() : nullptr;
    if (controller) {
        if (!controller->sub_7100F5E954())
            return;
        controller->sub_7100F5F598(&mVelocity);
        mVelocity *= k;
        controller->sub_7100F635BC(&mAngVelocity);
    } else {
        auto* body = mMainBody.load();
        if (!body || !body->isAddedToWorld())
            return;
        body->getLinearVelocity(&mVelocity);
        mVelocity *= k;
        body->getAngularVelocity(&mAngVelocity);
    }
    mAngVelocity *= k;
}

void Actor::x_22(const sead::Vector3f& vel, const sead::Vector3f& ang_vel) {
    if (auto* body = mMainBody.load()) {
        body->setLinearVelocity(vel);
        body->setAngularVelocity(ang_vel);
    }
    if (mPhysics) {
        if (auto* controller = mPhysics->getCharacterController()) {
            controller->sub_7100F5F6FC(vel);
            controller->sub_7100F5FB24(ang_vel);
        }
    }
}

// NON_MATCHING: register / scheduling difference in the main body test
bool Actor::sub_71011DAE0C() const {
    if (mPhysics) {
        if (mPhysics->getCharacterController())
            return false;
        if (mPhysics->getRagdollInstance())
            return false;
    }
    if (!getMainBody())
        return false;
    return getMainBody()->getMotionType() == phys::MotionType::Fixed;
}

bool Actor::sub_71011D55A8(void* a1, sead::Heap* heap) {
    auto* node = new (heap, 8) ActorUnk5b0Node;
    if (!node)
        return false;
    node->_0 = a1;
    node->mNext = _5b0;
    _5b0 = node;
    return true;
}

// NON_MATCHING: the original has a separate epilogue for the empty list
bool Actor::sub_71011C4EF4() {
    if (_5b0) {
        do {
            auto* node = _5b0;
            _5b0 = node->mNext;
            delete node;
        } while (_5b0);
    }
    return true;
}

// NON_MATCHING: the original loads the flag word before the state and combines them with `orr`
bool Actor::sub_71011D90B0() {
    if (!_738.hasProc())
        return true;
    auto* parent = sead::DynamicCast<Actor>(_738.getProc(nullptr));
    if (!parent)
        return true;
    const bool flag6 = mActorFlags.isOnBit(ActorFlag::_6);
    const bool calc = parent->isCalc();
    if (flag6 && !calc)
        return parent->x00000071011ba9fc();
    return calc || flag6;
}

bool Actor::sub_71011DA808(const ActorConstDataAccess& accessor) {
    if (mMapObject) {
        if (auto* link_data = mMapObject->getLinkData())
            return link_data->sub_7100D4EF30(accessor);
    }
    return false;
}

Actor* Actor::getPlacementLODActor(bool a1) {
    if (mMapObject) {
        if (auto* link_data = mMapObject->getLinkData()) {
            map::ObjectLink* link;
            if (a1)
                link = link_data->findLinkWithType(map::MapLinkDefType::PlacementLOD);
            else
                link = link_data->mLinksToSelf.findLinkWithType(map::MapLinkDefType::PlacementLOD);
            if (link)
                return link->getObjectActor();
        }
    }
    return nullptr;
}

s32 Actor::getFieldBodyGroupId() const {
    s32 id = -1;
    if (!mMapObjIter.tryGetParamIntByKey(&id, "FieldBodyGroup"))
        id = -1;
    return id;
}

// In the TU of the Actor functions around it (0x7100ee690c - 0x7100ee6974); defining it in actWeaponBase.cpp would
// inline it into WeaponBase::m200.
void WeaponBase::sub_7100EE6AFC() {
    mActorFlags2.reset(ActorFlag2::_1);
    mActorFlags2.reset(ActorFlag2::_20);
    auto* model = mModel;
    if (model) {
        model->x(true, 0);
        if (mModel) {
            auto* unit = mModel->getUnits().unsafeAt(0)->mModelUnit;
            if (unit && unit->isRenderViewOptionEnabled(0, gsys::ModelEnum::RenderViewOption(1), 0))
                model->sub_7100BF8CB8(false, -1);
        }
    }
}

// NON_MATCHING: the original starts with a discarded read of the map object's flag word (`ldr wzr, [x8]`)
void Actor::resetPlacementObj() {
    if (!mMapObject)
        return;
    mMapObject->resetFlags0(map::Object::Flag0::_800);
    mMapObject = nullptr;
    ActorSystem::instance()->registerActorThatLostPlacementObj(this);
    mMapObjIter = map::MubinIter();
    onPlacementObjReset();
}

void Actor::emitDeadUpLifeZeroAndSetRevival() {
    emitSignal(map::MapLinkDefType::DeadUp, true);
    emitSignal(map::MapLinkDefType::LifeZero, true);
    if (mMapObject)
        mMapObject->setFlags0(map::Object::Flag0::_100000);
    if (mMapObject)
        mMapObject->setRevivalFlagValueIf(map::ActorData::Flag::RevivalEnable, true);
}

void Actor::emitSignalsOrDisappearEffectForDelete(int reason) {
    emitSignal(map::MapLinkDefType::DeadUp, true);
    emitSignal(map::MapLinkDefType::LifeZero, true);
    if (mMapObject) {
        mMapObject->setFlags0(map::Object::Flag0::_100000);
        if (mMapObject) {
            mMapObject->setRevivalFlagValueIf(map::ActorData::Flag::RevivalEnable, true);
            if (mMapObject && mMapObject->getLinkData())
                mMapObject->getLinkData()->sub_7100D4FAD8();
        }
    }
    if (reason == 2)
        return;
    EventMgr1::instance()->sub_7100E48D8C(getName());
    if (reason != 1)
        emitDisappearEffect();
}

void Actor::emitDisappearEffect() {
    // NON_MATCHING: the switch omits the original redundant stack stores and loads of the type.
    const auto* info = m135();
    if (!info)
        return;
    switch (info->_4) {
    case 1: {
        if (!mXLink)
            break;
        Unk_71012419b4 handle;
        xlinkSearchAndEmit(this, "Disappear", 2, &handle);
        auto* event = static_cast<xlink2::EventELink*>(handle.mELink.getEvent());
        if (event && event->getCreateId() == handle.mELink.getCreateId() &&
            event->getMtxSetType() == 0) {
            sead::Matrix34f scale;
            scale.makeS(mScale);
            handle.sub_7101241A44(mMtx * scale);
        }
        break;
    }
    case 2:
        if (mXLink)
            xlinkSearchAndEmit(this, "Disappear", 2, nullptr);
        break;
    case 4:
        sub_71011D6E88(false);
        break;
    case 5:
    case 6:
    case 7:
    case 13:
        sub_71011D6E88(true);
        break;
    case 8:
        xlinkSearchAndEmit(this, "AntiChemical_KillFire", 2, nullptr);
        break;
    case 9:
        xlinkSearchAndEmit(this, "AntiChemical_KillIce", 2, nullptr);
        break;
    default:
        break;
    }
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

bool Actor::sub_71011C7990() const {
    return !mSignals.isOnBit(13);
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

void Actor::m75() {
    if (mXLink)
        mXLink->sub_7101231500();
}

void Actor::logForEditor(const sead::SafeString& system, const sead::SafeString& message) const {
    mActorEditorNode.log(system, message);
}

bool Actor::isEditorNodeConnected() const {
    return mActorEditorNode.isConnected();
}

void Actor::onAiEnter(const char* name, const char* context) {
    if (mXLink)
        mXLink->prepareAIChangeMaybe(name, context);
    mActorEditorNode.onAiEnter();
}

void Actor::m35() {
    if (mImpulseBaseProcLink)
        mImpulseBaseProcLink->sub_71011D8260();
}

Chemical* Actor::sub_71011D8A54(const sead::SafeString& name) {
    if (!mChemical)
        return nullptr;
    return mChemical->sub_7100E381DC(name);
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

as::ASList* Actor::sub_71011C9A88() const {
    return mASList == &as::sNullASListMaybe ? nullptr : mASList;
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

void Actor::x_3(f32 value) {
    if (_4f4 != value) {
        _4f4 = value;
        if (mModel)
            Unk_710260af28::instance()->sub_7100F1E1F8(mModel);
    }
}

void Actor::x_16() {
    handleModelFadeInOutAndFadeDelete();
    checkDeleteDistanceAndDeleteIfNeeded();
}

void Actor::job2_2() {
    if (mActorFlags2.isOn(ActorFlag2::_200))
        return;
    if (BaseProcMgr::instance()->getMode() != BaseProcMgr::Mode::_0)
        return;
    attentionStuff();
}

void Actor::onSleepRequested_(SleepWakeReason reason) {
    if (auto* weapons = getWeapons())
        weapons->sleep(reason);
    if (auto* armors = getArmors())
        armors->sleep(reason);
}

void Actor::onWakeUpRequested_(SleepWakeReason reason) {
    if (auto* weapons = getWeapons())
        weapons->wakeUp(reason);
    if (auto* armors = getArmors())
        armors->sub_7100E3170C(reason);
}

void Actor::onJobPush1_(JobType type) {
    if (type == JobType(0))
        mActorFlags.changeBit(ActorFlag::_3f, evt::Manager::instance()->someWeirdHardcodedCheck_KorokOrGanonOrBowling(this));
}

bool Actor::shouldSkipJobPush_(JobType type) {
    if (mActorFlags.isOnBit(ActorFlag::_18) || mStateFlags.isOn(StateFlags::RequestDelete))
        return type != JobType(4);

    bool no_job_push;
    if (_1a0)
        no_job_push = true;
    else if (mMapObject && mMapObject->getFlags0().isOn(map::Object::Flag0::_20000))
        no_job_push = true;
    else
        no_job_push = false;

    if (type == JobType(0)) {
        if (no_job_push || mActorFlags2.isOn(ActorFlag2::_100))
            mActorFlags.resetBit(ActorFlag::_32);
    }

    if (mActiveActorListNode.isLinked() || no_job_push)
        return false;
    if (mSkipJobPushTimer)
        return false;
    return !mActorFlags2.isOn(ActorFlag2::_100);
}

Actor::IsSpecialJobTypeResult Actor::isSpecialJobType_(JobType type) {
    if (mActorFlags2.isOn(ActorFlag2::_200)) {
        if (BaseProcMgr::instance()->getMode() == BaseProcMgr::Mode(1))
            return IsSpecialJobTypeResult::No;
        return IsSpecialJobTypeResult(!ui::sub_7100EDC4A0());
    }

    if (type == JobType(BaseProcMgr::getConstant4()))
        BaseProc::isSpecialJobType_(type);

    if (mActorFlags.isOnBit(ActorFlag::_3f) && !mActorFlags.isOnBit(ActorFlag::_1c) &&
        !(type == JobType(BaseProcMgr::getConstant1()) && !mActorFlags.isOnBit(ActorFlag::_1d)) &&
        mSpecialJobTypesMaskOverride.isOnBit(int(type))) {
        return IsSpecialJobTypeResult::Yes;
    }
    return BaseProc::isSpecialJobType_(type);
}

void Actor::job4() {
    VFR::instance()->useBufferB();
    xlinkAlwaysEffectStuff();
    if (!_598 || !_598->mFlags8.isOnBit(12) || mXLink->x_1() || !mXLink->x_2()) {
        m75();
        mSpecialJobTypesMaskOverride.setBit(BaseProcMgr::getConstant4());
    }
    VFR::instance()->useBufferA();
}

void Actor::job1_2() {
    if (_548) {
        _548->m6(this);
        _548->sub_7100D77EAC(this);
    }
    if (!mActorFlags2.isOn(ActorFlag2::_200)) {
        mActorFlags2Prev = mActorFlags2;
        if (getState() != State::Delete && !isDeleteRequested() &&
            (!_598 || !_598->mFlags8.isOnBit(8)) && !(_4f8 > 0) &&
            mSpecialJobTypesMaskOverride.isOnBit(BaseProcMgr::getConstant1())) {
            m74();
        }
    }
    m72();
}

}  // namespace ksys::act
