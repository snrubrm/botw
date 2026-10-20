#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/Damage/dmgDamageManagerBase.h"
#include "Game/gameGraphics.h"
#include "Game/gameStasisMgr.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actReaction.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorAtk.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/Utils/Thread/MessageDispatcher.h"
#include <container/seadPtrArray.h>
#include <heap/seadHeapMgr.h>
#include "KingSystem/Resource/resResDerived.h"
#include "KingSystem/Resource/resUnk_71024F9938.h"
#include "KingSystem/Map/mapPlacementMgr.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/System/physHavokAI.h"
#include "KingSystem/Mii/miiHylianInfo.h"
#include "KingSystem/Mii/miiUMii.h"
#include "Game/gameEventMgr1.h"
#include "Game/Actor/actNPCBase.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include <mc/seadCoreInfo.h>
#include <gsys/gsysModelAccessKey.h>
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
#include <thread/seadThread.h>
#include "KingSystem/ActorSystem/actLodState.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorX6A0.h"
#include "KingSystem/Resource/Actor/resResourceChemical.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/ActorSystem/actImpulseBaseProcLink.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/AS/asElement.h"
#include <gsys/gsysModelAnimation.h>
#include <nn/g3d/ResSkeletalAnim.h>
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
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
#include "KingSystem/Resource/Actor/resResourceAnimInfo.h"
#include "KingSystem/Resource/Actor/resResourceASList.h"
#include "KingSystem/Resource/Actor/resResourceBoneControl.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGrab.h"
#include "KingSystem/Resource/Actor/resResourceModelList.h"
#include "KingSystem/Resource/resBfRes.h"
#include "KingSystem/System/OverlayArenaSystem.h"
#include <nn/g3d/ResFile.h>
#include <nn/g3d/ResModel.h>
#include <nn/g3d/ResSkeleton.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGeneral.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
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
#include "KingSystem/Physics/System/physStaticCompoundMgr.h"
#include "KingSystem/Physics/Ragdoll/physRagdollInstance.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/Cloth/physClothSet.h"
#include "KingSystem/ActorSystem/actActorUnk6b8.h"
#include "KingSystem/Physics/System/physSystem.h"

// Existing profile classification utility; original namespace is unknown.
bool isAreaOrLinkTagOrOtherTag(const sead::SafeString& profile);

namespace ksys::act {

void Actor::x_14(bool on) {
    const bool fixed = on | mActorFlags.isOnBit(ActorFlag::_2b);
    if (fixed) {
        mActorFlags2.set(ActorFlag2::_400);
    } else {
        if (!mActorFlags2.isOn(ActorFlag2::_400))
            return;
        mActorFlags2.reset(ActorFlag2::_400);
    }
    if (mPhysics) {
        mPhysics->sub_7100FB9C54(
            static_cast<phys::Fixed>(fixed),
            static_cast<phys::MarkLinearVelAsDirty>(evt::Manager::instance()->_1d2f8 < 2));
        updateVelocityStuff();
    }
    m43(fixed);
    if (_6b8)
        _6b8->sub_7100EBBCB8(fixed);
}

void Actor::sub_71011DB070() {
    if (!mActorFlags.isOnBit(ActorFlag::_1))
        return;
    x_14(false);
    mActorFlags.resetBit(ActorFlag::_1);
}

// NON_MATCHING: the XLink flag update branches instead of selecting its value.
void Actor::onJobPush2_(JobType type) {
    switch (type) {
    case JobType::PreCalc:
        deleteIfPlacementStuff();
        decrementSkipJobPushTimer();
        if (shouldSkipJobPush(JobType::PreCalc)) {
            x_14(true);
            handleModelFadeInOutAndFadeDelete();
        }
        break;
    case JobType::Calc1:
        shouldSkipJobPush(JobType::Calc1);
        break;
    case JobType::Calc4:
        if (mXLink)
            mXLink->_cc.change(8, mActorFlags.isOffBit(ActorFlag::_18));
        break;
    default:
        break;
    }
}

// NON_MATCHING: typed key comparison and forwarding, stack placement and loop scheduling differ.
void Actor::swordBlurStuff() {
    if (mASList == &as::sNullASListMaybe || !mASList)
        return;

    s32 range_counts[512]{};
    const res::AS* resources[512];
    as::Element* elements[512];
    sead::Buffer<const res::AS*> resource_buffer(512, resources);
    sead::Buffer<as::Element*> element_buffer(512, elements);
    as::Element::EventRanges ranges;
    as::Element::EventRanges previous_ranges;
    auto* model = mModel;
    const s32 count = mASList->sub_7101160A70(&resource_buffer, &element_buffer, 48);
    if (!model || count <= 0)
        return;

    for (s32 i = 0; i < count; ++i) {
        element_buffer[i]->sub_71011655A0(&ranges, 48, resource_buffer[i]);
        s32 previous;
        for (previous = 0; previous < i; ++previous) {
            element_buffer[previous]->sub_71011655A0(&previous_ranges, 48,
                                                    resource_buffer[previous]);
            if (!range_counts[previous])
                continue;
            // ASList1160A70 accepts only SkeltalAsset via its RTTI before filling this buffer.
            const auto key = static_cast<as::SkeltalAsset*>(element_buffer[i])->mKey;
            const auto previous_key =
                static_cast<as::SkeltalAsset*>(element_buffer[previous])->mKey;
            if (key.type != previous_key.type || key.index != previous_key.index)
                continue;
            const s32 start = ranges.ranges[0].start;
            const s32 end = ranges.ranges[0].end;
            const s32 previous_start = previous_ranges.ranges[0].start;
            const s32 previous_end = previous_ranges.ranges[0].end;
            if (start != previous_start || end != previous_end) {
                model->getAnimation()->setSkeletalAnmByKey(0, key, nullptr);
                auto* animation = model->getAnimation();
                const auto& resource = animation->mSkeletalResources[
                    animation->mSkeletalAnms[0].key.index];
                const auto* skeletal =
                    static_cast<const nn::g3d::ResSkeletalAnim*>(resource.resource->resource);
                sead::FormatFixedSafeString<128> error(
                    "SwordBlurFrmErr[%s:%d/%d/%d/%d]", skeletal->GetName(), start, end,
                    previous_start, previous_end);
            }
            range_counts[i] = 0;
            break;
        }
        if (previous == i && ranges.count > 0)
            range_counts[i] += ranges.count < 2 ? 1 : ranges.count;
    }
}


phys::RigidBody* Actor::sub_71011DB364(phys::RigidBody* body) {
    if (body->isSensor())
        return nullptr;
    auto* physics = getPhysics();
    if (!physics || !physics->sub_7100FBB374(body))
        return nullptr;
    return mMainBody.exchange(body);
}

phys::RigidBody* Actor::sub_710011DBB8(phys::RigidBody* body) {
    if (!body->isSensor())
        return nullptr;
    auto* physics = getPhysics();
    if (!physics || !physics->sub_7100FBB374(body))
        return nullptr;
    return mTgtBody.exchange(body);
}

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

BaseProc* Actor::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Actor(arg);
}

Actor::Actor(const CreateArg& arg) : BaseProc(arg) {
    static_assert(offsetof(Actor, mTextureCache) == 0x658);
    static_assert(offsetof(Actor, mTextureBindings) == 0x660);
    static_assert(offsetof(Actor, mModelResources) == 0x670);
    static_assert(offsetof(Actor, _680) == 0x680);
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
        ActorLinkConstDataAccess accessor;
        link.getObjectProcWithAccessor(accessor);
        accessor.triggerLink();
    }
}

bool Actor::checkLinkSignal(map::MapLinkDefType type) const {
    if (mMapObject && mMapObject->getLinkData())
        return mMapObject->getLinkData()->mLinksOther.checkLink(type, true);
    return false;
}

bool Actor::sub_71011DA69C(const Actor* other) const {
    if (other && mMapObject && mMapObject->getLinkData())
        return mMapObject->getLinkData()->sub_7100D4F9DC(other->mMapObject);
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

// NON_MATCHING: creation-argument store scheduling and inlined name-prefix comparison differ.
bool Actor::createXlinkInstance(sead::Heap* heap) {
    xlink::XLink::CreateArg arg;
    arg.actor = this;
    arg.actorName = mName;
    arg.model = mModel;
    arg.rootMtx = &mMtx;
    arg.scale = &mScale;
    const char* unique_name = getUniqueName();
    if (unique_name && sead::SafeString(unique_name).startsWith("xlink:")) {
        arg.uniqueName = unique_name;
        arg.flags = 3;
    }
    mXLink = arg.build(heap);
    if (mXLink)
        mXLink->setMask(xlink::XLink::MaskBit::_0);
    return mXLink != nullptr;
}

void Actor::handleAck(const MessageAck& ack) {
    if (m80(ack))
        return;

    if (mRootAi)
        mRootAi->handleAck(ack);
}

int Actor::handleMessage(const Message* message) {
    const auto result = doHandleMessage_(*message);
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

// 0x71011c8b04: sets the home matrix from a world matrix.
void Actor::sub_71011C8B04(const sead::Matrix34f& mtx) {
    if (mFieldBodyGroup) {
        mHomeMtx = phys::System::instance()->getStaticCompoundMgr()->getInvTransformedMatrix(
            mFieldBodyGroup, mtx);
    } else {
        mHomeMtx = mtx;
    }
}

// NON_MATCHING: the original hoists &mMtx (add x2, x19, #0x398) above the getInvTransformedMatrix branch and
// reuses it in the else branch
void Actor::sub_71011C7020(const sead::Vector3f* pos, const sead::Matrix33f* rot,
                           const sead::Vector3f* scale) {
    if (pos) {
        mMtx.m[0][3] = pos->x;
        mMtx.m[1][3] = pos->y;
        mMtx.m[2][3] = pos->z;
    }
    if (rot) {
        mMtx.m[0][0] = rot->m[0][0];
        mMtx.m[0][1] = rot->m[0][1];
        mMtx.m[0][2] = rot->m[0][2];
        mMtx.m[1][0] = rot->m[1][0];
        mMtx.m[1][1] = rot->m[1][1];
        mMtx.m[1][2] = rot->m[1][2];
        mMtx.m[2][0] = rot->m[2][0];
        mMtx.m[2][1] = rot->m[2][1];
        mMtx.m[2][2] = rot->m[2][2];
    }
    if (scale)
        mScale = *scale;
    if (mFieldBodyGroup) {
        mHomeMtx = phys::System::instance()->getStaticCompoundMgr()->getInvTransformedMatrix(
            mFieldBodyGroup, mMtx);
    } else {
        mHomeMtx = mMtx;
    }
}

// NON_MATCHING: only the register allocation of one fmul/str pair (s2 vs s5) differs
void Actor::sub_71011CFA74() {
    phys::RigidBody* body = nullptr;
    if (mPhysics) {
        if (auto* controller = mPhysics->getCharacterController())
            body = controller->sub_7100F61A34();
    }
    if (!body)
        body = mMainBody;
    if (body) {
        sead::BoundBox3f aabb(sead::Vector3f::zero, sead::Vector3f::ones);
        body->getAabbInLocal(&aabb);
        _4b4 = aabb.getCenter();
    } else {
        mMtx.getTranslation(mEnterCalcPos);
    }
}

void Actor::sub_71011DABC0(const u8* flags) {
    if (*flags & 1) {
        if (mPhysics) {
            if (auto* body = mPhysics->sub_7100FBAEDC(0, 0))
                body->addToWorld();
        }
    }
    if (*flags & 4) {
        if (auto* body = mMainBody.load())
            body->addToWorld();
    }
    if (*flags & 8) {
        if (mPhysics) {
            if (auto* controller = mPhysics->getCharacterController())
                controller->sub_7100F5EC30();
        }
    }
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

s32 Actor::sub_71011CA00C() const {
    return mUMiiHylianInfo ? mUMiiHylianInfo->_18 : -1;
}

Unk_7100d8557c* Actor::sub_71011D89F8() {
    return mBoneControl ? mBoneControl->_0 : nullptr;
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

void Actor::sub_71011CEA10() {
    if (auto* atk = getAtk()) {
        atk->m9();
        if (atk->m10() || atk->hasAttackInfoMaybe())
            m107();
    }
}

bool Actor::sub_71011CEA90() const {
    if (!mPhysics)
        return false;
    auto* ragdoll = mPhysics->getRagdollInstance();
    return ragdoll && ragdoll->getWorldState() == phys::RagdollInstance::WorldState::AddedToWorld;
}

// NON_MATCHING: nested scan exits, inlined buffer size and register allocation.
void Actor::sub_71011CABA4(const sead::SafeString& name, bool enabled) {
    if (!mPhysics || !mModel)
        return;
    auto* support = mPhysics->_e8;
    if (!support)
        return;
    if (name.isEmpty()) {
        const s32 units = mModel->getUnits().size();
        for (s32 unit = 0; unit < units; ++unit) {
            auto* model_unit = mModel->getUnits()[unit]->mModelUnit;
            const s32 bones = model_unit->getBoneNum();
            for (s32 bone = 0; bone < bones; ++bone) {
                const auto bone_name = model_unit->getBoneName(bone);
                const s32 index = support->sub_71012273A8(bone_name);
                if (index != -1)
                    support->_48[index].enabled = enabled;
            }
        }
        return;
    }
    const auto* control = mActorParam->getRes().mBoneControl;
    if (!control)
        return;
    const auto* group = control->getBoneGroup(name);
    if (group) {
        const s32 count = group->bones.size();
        for (s32 bone = 0; bone < count; ++bone) {
            const s32 index = support->sub_71012273A8(group->bones[bone].name.ref());
            if (index != -1)
                support->_48[index].enabled = enabled;
        }
        return;
    }
    if (enabled)
        return;
    auto* list = mASList;
    if (list == &as::sNullASListMaybe || !list)
        return;
    sead::FixedSafeString<64> message;
    const s32 slots = list->mSlots.size();
    bool found = false;
    for (s32 slot = 0; slot < slots && !found; ++slot) {
        const s32 banks = list->mSlots[slot]._20.size();
        for (s32 bank = 0; bank < banks && !found; ++bank) {
            as::ASList::EventQueryResults results;
            list->sub_710115FB60(&results, 31, slot, bank,
                                &as::ASList::Unk2::sub_7101163908, true);
            for (s64 event = 0; event < results.count; ++event) {
                const auto& entry = results.events[event];
                entry.name.cstr();
                if (entry.name == name) {
                    message.format("再生中AS %d-%d:%s", slot, bank,
                                   list->x_1(slot, bank).cstr());
                    found = true;
                    break;
                }
            }
        }
    }
}

// NON_MATCHING: nested scan exits, inlined buffer size and block order.
void Actor::sub_71011CAFBC(const sead::SafeString& name, bool enabled) {
    if (!mPhysics)
        return;
    auto* cloth = mPhysics->getClothSet();
    if (!cloth)
        return;
    if (name.isEmpty()) {
        const s32 count = cloth->_18.size();
        for (s32 i = 0; i < count; ++i) {
            if (enabled)
                cloth->_18[i]._18 &= ~u32(8);
            else
                cloth->_18[i]._18 |= 8;
        }
        return;
    }
    const s32 index = cloth->sub_71012193C4(name);
    if (index >= 0) {
        if (enabled)
            cloth->_18[index]._18 &= ~u32(8);
        else
            cloth->_18[index]._18 |= 8;
        return;
    }
    if (enabled)
        return;
    sead::FixedSafeString<64> message;
    auto* list = mASList;
    if (list == &as::sNullASListMaybe || !list)
        return;
    const s32 slots = list->mSlots.size();
    bool found = false;
    for (s32 slot = 0; slot < slots && !found; ++slot) {
        const s32 banks = list->mSlots[slot]._20.size();
        for (s32 bank = 0; bank < banks && !found; ++bank) {
            as::ASList::EventQueryResults results;
            list->sub_710115FB60(&results, 30, slot, bank,
                                &as::ASList::Unk2::sub_7101163908, true);
            for (s64 event = 0; event < results.count; ++event) {
                const auto& entry = results.events[event];
                entry.name.cstr();
                if (entry.name == name) {
                    message.format("再生中AS %d-%d:%s", slot, bank,
                                   list->x_1(slot, bank).cstr());
                    found = true;
                    break;
                }
            }
        }
    }
}

void Actor::sub_71011CB390() {
    auto* physics = mPhysics;
    if (!physics)
        return;
    auto* controller = physics->getCharacterController();
    auto* body = mMainBody.load();
    if (mModelBindInfo) {
        if (mModelBindInfo->m6(this)) {
            physics->setFlag2();
            mModelBindInfo->m9(this);
        } else if (mModelBindInfo->m8(this)) {
            physics->clothVisibleStuff();
            mModelBindInfo->m9(this);
        }
    }
    sead::Matrix34f mtx;
    if (controller) {
        m41(&mtx);
    } else if (body) {
        body->getTransform(&mtx);
    } else if (auto* fallback = physics->sub_7100FBAEDC(0, 0)) {
        fallback->getTransform(&mtx);
    }
    physics->sub_7100FBBEC4(mtx, mScale.x);
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

bool Actor::x_20(phys::RigidBody* body) const {
    if (!body || !mPhysics)
        return false;
    return mPhysics->sub_7100FBE184(body);
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
    if (!mSkipJobPushTimer && !_1a0) {
        if (!mMapObject || !mMapObject->getFlags0().isOn(map::Object::Flag0::_20000))
            return true;
    }
    return false;
}

void Actor::sub_71011DB138() {
    mActorFlags.setBit(ActorFlag::_1);
}

// NON_MATCHING: the byte read is shared and the set/clear branch becomes a conditional select.
void Actor::sub_71011DAF44(Flag68f bit, bool on) {
    const u8 mask = 1 << int(bit);
    if (on)
        _68f.store(_68f.load() | mask);
    else
        _68f.store(_68f.load() & ~mask);
}

void Actor::sub_71011DAF7C(Flag68f bit, bool on) {
    _691.changeBit(int(bit), on);
}

void Actor::sub_71011DAFB4(int a, int b) {
    _6fc = a;
    _700 = b;
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
        if (!isAwakeMaybe())
            wakeUp(reason);
    }
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

bool Actor::sub_71011DAE0C() const {
    if (mPhysics) {
        if (mPhysics->getCharacterController())
            return false;
        if (mPhysics->getClothSet())
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

// Frees the list `_5b0`: false if it was empty.
bool Actor::sub_71011C4EF4() {
    if (!_5b0)
        return false;
    do {
        auto* node = _5b0;
        _5b0 = node->mNext;
        delete node;
    } while (_5b0);
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

bool Actor::sub_71011DA808(const ActorLinkConstDataAccess& accessor) {
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

// NON_MATCHING: the original masks `flag` after the SafeString assignment call (ours before it)
bool sub_7100EE6B88(Actor* actor, const sead::SafeString& name, bool flag) {
    if (!actor || !actor->getASList())
        return false;
    if (auto* npc = sead::DynamicCast<uking::act::NPCBase>(actor)) {
        npc->_8a8 = name;
        npc->_8b8 = flag;
    } else if (actor->getASList()->goLimpFromHeadShotMaybe(55, name, 0)) {
        return true;
    }
    return false;
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

void Actor::attentionStuff() {
    auto* attention = mAttention;
    if (!attention)
        return;
    attention->sub_7100D738EC();
    if (_689)
        return;
    if (mMapObject && mMapObject->getLinkData() &&
        mMapObject->getLinkData()->mLinksToSelf.checkLink(map::MapLinkDefType::Freeze, false))
        return;
    if (_598 && _598->mFlags8.isOnBit(10))
        return;
    if (!mActorFlags2.isOn(ActorFlag2::_40)) {
        attention->sub_7100D73924();
        return;
    }
    const s32 num_clients = attention->getNumClients();
    for (s32 i = 0; i < num_clients; ++i) {
        auto* client = attention->getClientByIdx(i);
        if (client->sub_7100D72534() == 2 || client->sub_7100D72534() == 1)
            client->sub_7100D721C0();
    }
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

// NON_MATCHING: the compiler merges the flag-test exits and keeps the retained link in a different register.
void Actor::unlinkPlacementObj() {
    if (!mMapObject)
        return;
    if (auto* link = mMapObject->getLinkData()) {
        if (mActorFlags.isOnBit(ActorFlag::_e)) {
            mActorFlags.resetBit(ActorFlag::_e);
            link->incrementGenGroupNumPrepareDelete();
            link = mMapObject->getLinkData();
        }
        if (link) {
            if (mActorFlags.isOnBit(ActorFlag::_f)) {
                mActorFlags.resetBit(ActorFlag::_f);
                link->x_3(false);
                link = mMapObject->getLinkData();
            }
            if (link && mActorFlags.isOnBit(ActorFlag::_10)) {
                mActorFlags.resetBit(ActorFlag::_10);
                link->sub_7100D4F884();
            }
        }
    }
    mMapObject->unlinkProc(mActorFlags.isOnBit(ActorFlag::_14) ||
                          mActorFlags.isOnBit(ActorFlag::_36));
    mMapObject = nullptr;
}

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

void Actor::sub_71011C8BA4(u32 value) {
    if ((isInit() || isSleep()) && mRootAi)
        mRootAi->setI(value);
}

void Actor::sub_71011C75D4() {
    if (!ActorSystem::instance()->get139())
        return;
    if (getCharacterController() || m31())
        _4f8 = 1.0f;
    else
        _4f8 = 10.0f;
}

void Actor::x_42(bool flag, bool reset_bones) {
    m114(flag, reset_bones);
    auto* as_list = sub_71011C9A88();
    if (as_list) {
        as_list->sub_710115C634(mSpecialJobTypesMaskOverride.isOnBit(0));
        as_list->sub_710115C6F0();
    }
    m115();
    if (as_list)
        as_list->sub_710115C7A8(false);
    if (mPhysics) {
        mPhysics->sub_7100FBA7BC(!flag, _598);
        if (_598) {
            const bool active = _598->mFlags8.isOn(6);
            reset_bones |= mActorFlags.isOnBit(ActorFlag::_d) && !active;
            mActorFlags.changeBit(ActorFlag::_d, active);
        }
        mPhysics->sub_7100FBBEC0();
    }
    if (as_list && mModel) {
        if (reset_bones) {
            auto* unit = mModel->getUnits().unsafeAt(0)->mModelUnit;
            if (unit)
                unit->clearBoneLocalMatrix();
        }
        if (mActorFlags.isOnBit(ActorFlag::_8) &&
            *mUMii->getBody().race == mii::UMii::Body::Race_Hylian) {
            auto* unit = mModel->getUnits().unsafeAt(0)->mModelUnit;
            if (unit)
                unit->clearBoneLocalMatrix();
            if (mUMiiHylianInfo) {
                mUMiiHylianInfo->sub_71012A5418(as_list);
                if (mModel->getAnimation())
                    mUMiiHylianInfo->sub_71012A56FC(mModel->getAnimation());
            }
        }
        as_list->sub_710115C8D8(flag, false);
        // 11C77DC reloads this relaxed atomic flags word after the AS-list update.
        mActorFlags.getWord(ActorFlag::_8).load();
    }
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

bool Actor::sub_71011D8F44() {
    return isSpecialJobType(JobType(BaseProcMgr::getConstant0()));
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

bool Actor::m52(sead::Vector3f* out, Chemical* chemical) {
    if (getChemicalStuff() != chemical) {
        const auto& pos = chemical->_18->m5();
        out->x = pos.x;
        out->y = pos.y;
        out->z = pos.z;
    } else {
        out->x = mMtx(0, 3);
        out->y = mMtx(1, 3);
        out->z = mMtx(2, 3);
    }
    return true;
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

void Actor::m61(f32 rate) {}

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

bool Actor::m49(phys::RigidBody*) {
    return false;
}

bool Actor::m67(sead::Heap* heap) {
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

int Actor::getExtraHeapSize(const ActorHeapInitArgMaybe& arg) {
    return 0;
}

void Actor::m103() {}

void Actor::m114(bool, bool) {}

void Actor::m117(Unk117*) {}

void Actor::m147(sead::PtrArray<Actor>*) {}

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

uking::act::DamageManagerBase* Actor::getDamageMgr() {
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

const sead::SafeString& Actor::sub_71011DB1E4(int slot) {
    const auto* gparam = mActorParam->getRes().mGParamList;
    if (!gparam)
        return sead::SafeString::cEmptyString;
    const auto* grab = gparam->getGrab();
    if (!grab)
        return sead::SafeString::cEmptyString;
    switch (slot) {
    case 0:
        return grab->mSlot0Node.ref();
    case 1:
        return grab->mSlot1Node.ref();
    case 2:
        return grab->mSlot2Node.ref();
    case 3:
        return grab->mSlot3Node.ref();
    case 4:
        return grab->mSlot4Node.ref();
    case 5:
        return grab->mSlot5Node.ref();
    default:
        return sead::SafeString::cEmptyString;
    }
}

const sead::SafeString& Actor::sub_71011DB280() {
    const auto* bone_control = mActorParam->getRes().mBoneControl;
    if (!bone_control)
        return sead::SafeString::cEmptyString;
    const auto& spine = bone_control->getSpine();
    const int idx = spine.spineNodeNum.ref() - 1;
    if (idx < 0)
        return sead::SafeString::cEmptyString;
    return spine.spineNodes[idx].boneName.ref();
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

// NON_MATCHING: the original copies the position through a temporary that is reused for the velocity (stack slots)
void Actor::m44(phys::NavMeshCharacter* nav) {
    if (!mPhysics)
        return;
    auto* controller = mPhysics->getCharacterController();
    if (!controller)
        return;

    sead::Matrix34f mtx;
    controller->physicsXXXGetMtx_1(&mtx);
    sead::Vector3f position;
    controller->sub_7100F5F6E0(&position);
    sead::Vector3f velocity;
    controller->sub_7100F5F598(&velocity);
    nav->sub_7100F76380(position, controller->get64(), velocity,
                        sead::Vector3f(mtx(0, 2), mtx(1, 2), mtx(2, 2)));
}

void Actor::m35(f32 impulse, phys::RigidBody* body_a, phys::RigidBody* body_b) {
    if (mImpulseBaseProcLink)
        mImpulseBaseProcLink->sub_71011D8260(impulse, body_a, body_b);
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

// NON_MATCHING: operand order of the final signed minimum selection.
void Actor::sub_71011C9C80(gsys::ModelAnimation::CreateArg& arg) {
    auto* model_list = mActorParam->getRes().mModelList;
    s32 skeletal_slots = 0;
    s32 material_max = 0;
    s32 partial_slots = 0;
    for (s32 i = 0; i < model_list->getNumAnmTargets(); ++i) {
        const s32 slots = model_list->getNumASSlot(i);
        if (model_list->getAnmTargets()[i].target_type.ref() == 2) {
            partial_slots += slots;
        } else {
            skeletal_slots += slots;
            material_max = sead::Mathi::max(material_max, slots);
        }
    }
    material_max += partial_slots;
    skeletal_slots = sead::Mathi::max(skeletal_slots, 1);
    material_max = sead::Mathi::max(material_max, 1);
    auto* as_res = mActorParam->getRes().mASList;
    if (as_res) {
        s32 skeletal_multiplier = as_res->_2b0;
        s32 material_multiplier = as_res->_2b1;
        if (mASList != &as::sNullASListMaybe && mASList) {
            s32 skeletal = 0;
            s32 material = 0;
            mASList->sub_710115E1D4(&skeletal, &material);
            skeletal_multiplier = sead::Mathi::max(skeletal_multiplier, skeletal);
            material_multiplier = sead::Mathi::max(material_multiplier, material);
            if (material > 0)
                ++material_max;
        }
        arg._0 = skeletal_multiplier * skeletal_slots;
        if (as_res->getCFDefines().size() > 0 || as_res->_2b2)
            arg._0 *= 3;
        arg._4 = material_multiplier * material_max;
        if (mActorFlags.isOnBit(ActorFlag::_8))
            arg._4 += 2;
        if (hasTag(this, 0x216a3a63))
            arg._4 += 2;
        arg._0 = sead::Mathi::min(arg._0, m109());
    } else {
        arg._0 = skeletal_slots;
        arg._4 = material_max;
    }
    if (model_list->getControllerInfo().mVariationMatAnim.ref()[0] != '\0')
        ++arg._4;
    if (model_list->getControllerInfo().mVariationShaderAnim.ref()[0] != '\0')
        ++arg._4;
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
            Unk_710260af28::instance()->sub_7100F1E1F8(mModel, value);
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

res::AnimInfo::SwordBlurInfo* sub_71011D66C0(Actor* actor) {
    return actor->getParam()->getRes().mAnimationInfo->getSwordBlurInfo();
}

void Actor::sub_71011C5630(gsys::Model* model) {
    if (!model)
        return;
    // The two 32-bit shader user-data slots hold the pointer's bits.
    Unk_710260af28::instance()->sub_7100F1CC38(model, reinterpret_cast<u64>(&mUnk1));
    Unk_710260af28::instance()->sub_7100F1CACC(model, mStasisFlags.isOn(StasisFlag(0x800)));
}

// sinit_actor initializes three inline buffers of 256 process pointers at 0x7102650688.
sead::SafeArray<sead::FixedPtrArray<BaseProc, 256>, 3> sActorListsMaybe;

bool sub_71011D7194(BaseProc* proc, s32 index) {
    auto& actors = sActorListsMaybe[index];
    if (actors.indexOf(proc) >= 0)
        return false;
    actors.pushBack(proc);
    return true;
}

void Actor::sub_71011D8AFC(s32 a1, s32 a2, s32 message, void* user_data,
                          const sead::SafeString* target) {
    if (!mMapObject || !mMapObject->getLinkData())
        return;
    const s32 core = sead::CoreInfo::getCurrentCoreId();
    sActorListsMaybe[core].clear();
    sub_71011D8BCC(core, &mMsgTransceiver, a1, a2, message, user_data, target);
}

void Actor::sub_71011CCB38() {
    if (!_68e)
        return;
    const f32 opacity = m139();
    if (mModel) {
        const bool fade = mStartModelOpacity < 1.0f && mActorFlags.isOffBit(ActorFlag::_21);
        Unk_710260af28::instance()->sub_7100F1DCA8(mModel, opacity, fade);
    }
    m61(opacity);
    _68e = false;
}

void Actor::sub_710011CCBD0() {
    if (!_68e)
        return;
    const f32 opacity = m139();
    if (mModel) {
        const bool fade = mStartModelOpacity < 1.0f && mActorFlags.isOffBit(ActorFlag::_21);
        Unk_710260af28::instance()->sub_7100F1DCA8(mModel, opacity, fade);
    }
    m61(opacity);
    _68e = false;
}

void Actor::sub_71011D7EC4(phys::RigidBody* body) {
    // NON_MATCHING: one multiply/store pair uses a different floating-point register.
    if (!body)
        return;
    phys::RigidBody* main_body = nullptr;
    if (mPhysics) {
        if (auto* controller = mPhysics->getCharacterController())
            main_body = controller->sub_7100F61A34();
    }
    if (!main_body)
        main_body = mMainBody;
    if (main_body == body)
        sub_71011CFA74();
    if (mTgtBody == body) {
        if (auto* nav_body = mTgtBody.load()) {
            sead::BoundBox3f aabb(sead::Vector3f::zero, sead::Vector3f::ones);
            nav_body->getAabbInLocal(&aabb);
            mEnterCalcPos = aabb.getCenter();
        } else {
            mMtx.getTranslation(mEnterCalcPos);
        }
    }
}

// NON_MATCHING: fade-mode branches, chase temporaries and the shared movement tail are reordered.
void Actor::handleModelFadeInOutAndFadeDelete() {
    s32 mode = 0;
    f32 target;
    if (ui::sub_7100EDC6E8()) {
        target = _68d == 0 ? 1.0f : 0.01f;
        mode = 2;
    } else if (_68d == 0) {
        target = 1.0f;
    } else if (_68d == 1) {
        m110(&target, &mode);
    } else if (_68d == 2) {
        m111(&target, &mode);
    } else if (_68d == 3) {
        m112(&target, &mode);
    } else {
        m113(&target, &mode);
    }
    _68d = 0;
    if (_4e8 != target) {
        if (mode == 0) {
            sead::Mathf::chase(&_4e8, target, VFR::instance()->getIntervalRatio() * (1.0f / 6.0f));
        } else if (mode == 1) {
            if (_4e8 > 0.7f)
                _4e8 = 0.7f;
            else if (_4e8 > 0.3f)
                _4e8 = 0.3f;
            else
                _4e8 = target;
        } else {
            _4e8 = target;
        }
        _68e = true;
    }
    if (_4f8 > 0.0f)
        sead::Mathf::chase(&_4f8, 0.0f, VFR::instance()->getIntervalRatio());

    bool check_movement = false;
    const s32 delete_type = mFadeOutDeleteType;
    if (delete_type != 0 || mFadeOutSleepFlags.load() > 0 || _68c.load() != 0) {
        if (mModel)
            sead::Mathf::chase(&mStartModelOpacity, 0.0f,
                               VFR::instance()->getIntervalRatio() * (1.0f / 6.0f));
        else
            mStartModelOpacity = 0.0f;
        if (!(mStartModelOpacity <= 0.0f)) {
            check_movement = true;
        } else if (delete_type != 0) {
            handleFadeoutDelete(DeleteReason::_0);
        } else if (mFadeOutSleepFlags.load() > 0) {
            if (mFadeOutSleepFlags.load() & 1)
                sleep(SleepWakeReason(0));
            if (mFadeOutSleepFlags.load() & 2)
                sleep(SleepWakeReason(1));
            if (mFadeOutSleepFlags.load() & 4)
                sleep(SleepWakeReason(2));
            if (mFadeOutSleepFlags.load() & 8)
                sleep(SleepWakeReason(3));
        } else if (_68c.load() == 1) {
            mMsgTransceiver.sendMessage(*mMsgTransceiver.getId(), MessageType(0x3000010), nullptr, true);
            _68c = 2;
        }
    } else if (mStartModelOpacity < 1.0f) {
        if (_4f8 > 0.0f) {
            check_movement = true;
        } else {
            if (mModel)
                sead::Mathf::chase(&mStartModelOpacity, 1.0f,
                                   VFR::instance()->getIntervalRatio() * (1.0f / 6.0f));
            else
                mStartModelOpacity = 1.0f;
            _68e = true;
        }
    }
    if (check_movement) {
        if (mMapObject && mMapObject->getFlags0().isOn(map::Object::Flag0::_2)) {
            sead::Vector3f home = mHomeMtx.getTranslation();
            if (mFieldBodyGroup)
                home = phys::System::instance()->getStaticCompoundMgr()->getTransformedPos(
                    mFieldBodyGroup, home);
            if (!((home - mMtx.getTranslation()).squaredLength() > 0.5f))
                return;
        }
        _68e = true;
    }
}

bool Actor::deleteEx(DeleteType type, DeleteReason reason, bool* ok) {
    if (!mModel || getState() != State::Calc) {
        if (type == DeleteType::_2 || type == DeleteType::_3) {
            mFadeOutDeleteType.compareExchange(0, s32(type));
            const s32 requested_type = mFadeOutDeleteType;
            if (!deleteLater(reason))
                return false;
            if (mMapObject &&
                (((requested_type == 2 || requested_type == 3) &&
                  mMapObject->getFlags0().isOff(map::Object::Flag0::_400)) ||
                 (getState() != State::Calc &&
                  mMapObject->getFlags0().isOff(map::Object::Flag0::_400)))) {
                mMapObject->setFlags0(map::Object::Flag0::ActorCreated);
                if (auto* mgr = map::PlacementMgr::instance())
                    mgr->sub_71011EB46C(mMapObject);
            }
            return true;
        }
        if (type == DeleteType::_1)
            return deleteLater(reason);
    }
    if (!mFadeOutDeleteType.compareExchange(0, s32(type)))
        return false;
    if (ok)
        *ok = true;
    onPreFadeOutDelete();
    if (type == DeleteType::_2 || type == DeleteType::_3) {
        ActorLinkConstDataAccess accessor;
        if (mMapObject && mMapObject->getLinkData()) {
            mMapObject->getLinkData()->sub_7100D4F6A4(accessor, map::MapLinkDefType::PlacementLOD);
            accessor.wakeUp(SleepWakeReason::_0);
        }
    }
    return true;
}

// NON_MATCHING: transformed-position argument setup and the flag-setting tail differ.
void Actor::updatePlacementObjDistanceFlags() {
    bool near_player = false;
    if (mMapObject && mActorParam->getProfile() != "NPC" && !_687) {
        sead::Vector3f home;
        if (mFieldBodyGroup) {
            const sead::Vector3f original_home = mHomeMtx.getTranslation();
            home = phys::System::instance()->getStaticCompoundMgr()->getTransformedPos(
                mFieldBodyGroup, original_home);
        } else {
            home = mHomeMtx.getTranslation();
        }
        if ((home - mMtx.getTranslation()).squaredLength() > 0.5f &&
            mActorFlags.isOffBit(ActorFlag(0x17)) && mActorParam->getProfile() != "Area" &&
            !mMapObject->checkCreateOrDeleteLinkObjRevival()) {
            sead::Vector3f traverse;
            f32 load_distance = 0.0f;
            mMapObject->getTraversePosAndLoadDistance(&traverse, &load_distance);
            const auto& player = ActorSystem::instance()->getPlayerPos();
            const f32 x = traverse.x - player.x;
            const f32 z = traverse.z - player.z;
            if (x * x + z * z < mDispDistanceSq * 0.5f * 0.5f &&
                !mMapObject->checkYDistance(traverse.y, player.y, -10.0f))
                near_player = true;
        }
    }
    if (near_player)
        mMapObject->setFlags0(map::Object::Flag0::_400000);
    else if (mMapObject->getFlags0().isOff(map::Object::Flag0::_800000))
        mMapObject->resetFlags0(map::Object::Flag0::_400000);
}

// NON_MATCHING: deletion case order and the shared success/flag tail differ.
bool Actor::becomePreActor(DeleteType type, DeleteReason reason) {
    if (!mMapObject || isDeletedOrDeleting())
        return false;
    bool deleted = false;
    if (type == DeleteType::_1) {
        deleted = deleteEx(DeleteType::_3, reason);
    } else if (type == DeleteType::_2) {
        mFadeOutDeleteType.load();
        if (deleteLater(reason)) {
            if (mMapObject) {
                mMapObject->setFlags0(map::Object::Flag0::ActorCreated);
                if (auto* mgr = map::PlacementMgr::instance())
                    mgr->sub_71011EB46C(mMapObject);
            }
            deleted = true;
        }
    } else if (type == DeleteType::_3) {
        if (deleteLater(reason)) {
            mMapObject->setFlags0(map::Object::Flag0::ActorCreated);
            deleted = true;
        }
    } else {
        auto* links = mMapObject->getLinkData();
        if (links && mActorFlags.isOnBit(ActorFlag::_e)) {
            mActorFlags.resetBit(ActorFlag::_e);
            links->incrementGenGroupNumPrepareDelete();
        }
        if (mMapObject->getLinkData() && mMapObject->getLinkData()->mGenGroup) {
            deleted = mMapObject->getLinkData()->deleteEachActorIfDeleteType2_0();
        } else {
            deleteEx(DeleteType::_3, reason);
            deleted = true;
        }
    }
    if (type != DeleteType::_3 && deleted)
        updatePlacementObjDistanceFlags();
    if (_540)
        mMapObject->resetFlags0(map::Object::Flag0::_400000);
    if (reason == DeleteReason(11) && deleted)
        becomePreActor_(true, false);
    return deleted;
}

// NON_MATCHING: the existing atomic bool uses a zero test rather than a bit-zero test.
bool Actor::deleteIfPlacementStuff() {
    if (_687) {
        if (!mMapObject)
            return true;
        if (!isDeletedOrDeleting()) {
            if (deleteEx(DeleteType::_3, DeleteReason(8)))
                updatePlacementObjDistanceFlags();
            if (_540)
                mMapObject->resetFlags0(map::Object::Flag0::_400000);
        }
        auto* links = mMapObject ? mMapObject->getLinkData() : nullptr;
        if (links) {
            const bool deleting = mActorFlags.isOnBit(ActorFlag(0x17));
            const bool counted = mActorFlags.isOnBit(ActorFlag::_e);
            if (deleting && counted) {
                mActorFlags.resetBit(ActorFlag::_e);
                links->incrementGenGroupNumPrepareDelete();
            } else if (!deleting && !counted) {
                mActorFlags.setBit(ActorFlag::_e);
                links->decrementGenGroupNumPrepareDelete();
            }
        }
        return true;
    }
    if (!mMapObject || !mMapObject->checkCreateOrDeleteLinkObjRevival())
        return false;
    const bool delete_link = mMapObject->getLinkData()->checkDeleteLinkObjRevival();
    becomePreActor(DeleteType::_2, DeleteReason(delete_link ? 7 : 6));
    emitSignalsOnDeleteForAreaOrTag();
    auto* links = mMapObject ? mMapObject->getLinkData() : nullptr;
    if (links) {
        const bool deleting = mActorFlags.isOnBit(ActorFlag(0x17));
        const bool counted = mActorFlags.isOnBit(ActorFlag::_e);
        if (deleting && counted) {
            mActorFlags.resetBit(ActorFlag::_e);
            links->incrementGenGroupNumPrepareDelete();
        } else if (!deleting && !counted) {
            mActorFlags.setBit(ActorFlag::_e);
            links->decrementGenGroupNumPrepareDelete();
        }
    }
    mActorFlags.setBit(ActorFlag::_36);
    return true;
}

void Actor::emitSignalsOnDeleteForAreaOrTag() {
    if (!mActorParam || !isAreaOrLinkTagOrOtherTag(mActorParam->getProfile()))
        return;
    emitSignal(map::MapLinkDefType::BasicSig, false);
    emitSignal(map::MapLinkDefType::AxisX, false);
    emitSignal(map::MapLinkDefType::AxisY, false);
    emitSignal(map::MapLinkDefType::AxisZ, false);
    emitSignal(map::MapLinkDefType::NAxisX, false);
    emitSignal(map::MapLinkDefType::NAxisY, false);
    emitSignal(map::MapLinkDefType::NAxisZ, false);
    emitSignal(map::MapLinkDefType::GimmickSuccess, false);
    emitSignal(map::MapLinkDefType::VelocityControl, false);
    emitSignal(map::MapLinkDefType::Remains, false);
}

// NON_MATCHING: the deletion case chain becomes a jump table with a different block order.
bool Actor::handleFadeoutDelete(DeleteReason reason) {
    const s32 requested_type = mFadeOutDeleteType;
    if (requested_type == 4) {
        if (mFadeOutDeleteType.compareExchange(4, 1))
            emitSignalsOrDisappearEffectForDelete(0);
    } else if (requested_type == 5) {
        if (mFadeOutDeleteType.compareExchange(5, 1)) {
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
        }
    } else if (requested_type != 1 && requested_type != 3) {
        if (requested_type != 2)
            return false;
        if (mMapObject && mMapObject->getLinkData())
            mMapObject->getLinkData()->deleteEachActorIfDeleteType2();
        return true;
    }
    const s32 type = mFadeOutDeleteType;
    if (deleteLater(reason) && mMapObject &&
        (((type == 2 || type == 3) && mMapObject->getFlags0().isOff(map::Object::Flag0::_400)) ||
         (getState() != State::Calc && mMapObject->getFlags0().isOff(map::Object::Flag0::_400)))) {
        mMapObject->setFlags0(map::Object::Flag0::ActorCreated);
        if (auto* mgr = map::PlacementMgr::instance())
            mgr->sub_71011EB46C(mMapObject);
    }
    return true;
}

void Actor::deleteIfDeleteType2() {
    if (mFadeOutDeleteType != 2)
        return;
    const s32 type = mFadeOutDeleteType;
    if (!deleteLater(DeleteReason::_0) || !mMapObject)
        return;
    if (((type == 2 || type == 3) && mMapObject->getFlags0().isOff(map::Object::Flag0::_400)) ||
        (getState() != State::Calc && mMapObject->getFlags0().isOff(map::Object::Flag0::_400))) {
        mMapObject->setFlags0(map::Object::Flag0::ActorCreated);
        if (auto* mgr = map::PlacementMgr::instance())
            mgr->sub_71011EB46C(mMapObject);
    }
}

bool Actor::x_34(bool* ok) {
    bool deleted;
    if (getState() == State::Calc) {
        deleted = deleteEx(DeleteType::_2, DeleteReason::_0, ok);
    } else {
        const s32 type = mFadeOutDeleteType;
        deleted = deleteLater(DeleteReason::_0);
        if (deleted && mMapObject &&
            (((type == 2 || type == 3) && mMapObject->getFlags0().isOff(map::Object::Flag0::_400)) ||
             (getState() != State::Calc && mMapObject->getFlags0().isOff(map::Object::Flag0::_400)))) {
            mMapObject->setFlags0(map::Object::Flag0::ActorCreated);
            if (auto* mgr = map::PlacementMgr::instance())
                mgr->sub_71011EB46C(mMapObject);
        }
    }
    updatePlacementObjDistanceFlags();
    return deleted;
}

bool Actor::x_8(bool on) {
    bool changed = false;
    if (auto* physics = mPhysics) {
        if (on) {
            changed = !physics->sub_7100FBAAC8();
        } else if (!physics->sub_7100FBAB68()) {
            physics->sub_7100FBAA3C();
            changed = true;
        }
        if (physics->sub_7100FC0234())
            physics->sub_7100FC01B0();
    }
    changed |= mConstraints.sub_7100D40338();
    if (auto* nav = m45()) {
        nav->sub_7100F75AB8();
        // HavokAI stores request flags in the low two bits of this atomic pointer.
        auto* pending = reinterpret_cast<phys::HavokAI*>(uintptr_t(nav->_20.load()) & ~uintptr_t(3));
        if (pending)
            pending->sub_7100F82C88(nav);
        if (auto* active = nav->_18)
            active->sub_7100F82C88(nav);
    }
    changed |= m47();
    return changed;
}

}  // namespace ksys::act

void sub_71011D75CC(ksys::act::Actor* actor) {
    const bool processing = ksys::MessageDispatcher::instance()->isProcessingOnCurrentThread();
    auto* transceiver = ksys::act::ActorSystem::instance()->sub_7100D5D80C();
    if (processing)
        transceiver->sendMessageOnProcessingThread(*actor->getMesTransceiverId(), ksys::MessageType(0x3000012), nullptr, true);
    else
        transceiver->sendMessage(*actor->getMesTransceiverId(), ksys::MessageType(0x3000012), nullptr, true);
}

void sub_71011D7650(ksys::act::Actor* actor, ksys::act::BaseProc* proc) {
    const bool processing = ksys::MessageDispatcher::instance()->isProcessingOnCurrentThread();
    auto* transceiver = ksys::act::ActorSystem::instance()->sub_7100D5D80C();
    // This message's pointer-sized user-data slot carries the zero-extended actor ID.
    if (processing)
        transceiver->sendMessageOnProcessingThread(*actor->getMesTransceiverId(), ksys::MessageType(0x3000013), reinterpret_cast<void*>(uintptr_t(proc->getId())), true);
    else
        transceiver->sendMessage(*actor->getMesTransceiverId(), ksys::MessageType(0x3000013), reinterpret_cast<void*>(uintptr_t(proc->getId())), true);
}

void sub_71011D76E0(ksys::act::Actor* actor, const ksys::act::ActorLinkConstDataAccess& accessor) {
    const bool processing = ksys::MessageDispatcher::instance()->isProcessingOnCurrentThread();
    auto* transceiver = ksys::act::ActorSystem::instance()->sub_7100D5D80C();
    // The same message protocol accepts an ID obtained through an actor link.
    if (processing)
        transceiver->sendMessageOnProcessingThread(*actor->getMesTransceiverId(), ksys::MessageType(0x3000013), reinterpret_cast<void*>(uintptr_t(accessor.getId())), true);
    else
        transceiver->sendMessage(*actor->getMesTransceiverId(), ksys::MessageType(0x3000013), reinterpret_cast<void*>(uintptr_t(accessor.getId())), true);
}

void ksys::act::Actor::sub_71011CED70(gsys::Model* model) {
    const u32 flags = mStasisFlags.getDirect();
    Unk_710260af28::instance()->sub_7100F1D058(model, flags);
    Unk_710260af28::instance()->sub_7100F1C77C(model, (flags & ~0x7000u) == 0 ? nullptr : &mUnk1);
}

// 0x71011cedc4: the attention info of the actor's model list; false if the actor has no model list.
bool ksys::act::Actor::sub_71011CEDC4(res::ModelList::AttentionInfo* out) {
    if (!mActorParam)
        return false;
    res::ModelList* model_list = mActorParam->getRes().mModelList;
    if (!model_list)
        return false;
    return model_list->getAttentionInfo(out);
}

namespace ksys::act {
// NON_MATCHING: aggregate initialization calls the default material constructors and schedules request stores differently.
void Actor::reactionStuff() {
    if (!mActorFlags.isOnBit(ActorFlag::_9))
        return;
    mActorFlags.resetBit(ActorFlag::_9);
    DamageReactionRequest request{};
    request.mtx = sead::Matrix34f::ident;
    request._34 = 1.0f;
    request._3c = 1.0f;
    request._40 = 1.0f;
    request._44 = 1.0f;
    request._b8 = this;
    request._c0 = 2;
    request._c4 = 6;
    sead::Matrix34f transform;
    sub_7100D36FA0(&transform, this);
    xlink2::HandleELink* stasis_handle = nullptr;
    if (!mActorFlags2.isOn(ActorFlag2::_40)) {
        const auto position = transform.getTranslation();
        request.mtx.setTranslation(position);
        request._90 = 28;
        if (getDamageMgr()) {
            request._54 = std::pow(getDamageMgr()->getStasisBlowPowerRatio(),
                                   Graphics::instance()->getSpecialEffectAWrapMaybe());
            sead::Vector3f direction;
            if (getDamageMgr()->m14(&direction)) {
                direction.normalize();
                sub_7100EBFD08(1.0f, &request, direction, position);
            }
        }
    } else {
        request._90 = 27;
        stasis_handle = ActorSystem::instance()->getStasisMessageSender()->m4(this);
        request.mtx = transform;
    }
    auto* reaction = Reaction::instance();
    if (reaction && reaction->_b0) {
        if (!stasis_handle) {
            reaction->sub_7100EC10B8(&request);
        } else {
            reaction->_a0->sub_7101286BF8(stasis_handle, &request);
            request._c4 &= ~4;
            reaction->sub_7100EC10B8(&request);
            if (auto* xlink = getXLink())
                xlink->sub_7101230968();
        }
    }
}

}  // namespace ksys::act

namespace ksys::act {

void Actor::sub_71011D57A8() {
    if (isDeleting())
        return;
    if (mASList != &as::sNullASListMaybe && mASList)
        mASList->sub_710115C92C();
    mModel->destroyAnimation_();
}

}  // namespace ksys::act

namespace ksys::act {

// NON_MATCHING: pointer-array initialization and loop pointer reloads differ.
bool Actor::sub_71011D00AC(sead::Heap* heap) {
    sead::PtrArray<res::BfRes> resources;
    if (!resources.tryAllocBuffer(mModelResources.size(), heap, -8))
        return false;
    res::Unk_71024f9958::InitArg arg;
    arg.resources = &resources;
    for (s32 i = 0; i < mModelResources.size(); ++i)
        resources.pushBack(mModelResources[i].getModelRes());
    arg.model = mModel;
    arg.heap = heap;
    arg.name = getName();
    mTextureBindings.getBufferPtr()[0]->sub_7100FDD4A8(arg);
    {
        sead::ScopedCurrentHeapSetter heap_setter(heap);
        resources.freeBuffer();
    }
    return true;
}

// 0x71011d4e88: creates the actor's model animation from the model resources, the AS add-res
// entries and the extra model resources of the _5b0 list. The AS add-res retarget model name is
// looked up in the model resource's ResFile; the matched skeleton is handed to Model::createAnimation.
// NON_MATCHING: string temporary stack slots, loop registers and Boolean return tails differ.
bool Actor::sub_71011D4E88(sead::Heap* heap) {
    if (!mModel)
        return true;

    const auto* model_list = mActorParam->getRes().mModelList;
    const sead::SafeString& variation_anim =
        model_list->getControllerInfo().mVariationMatAnim.ref();

    res::ASList* as_list = nullptr;
    if (variation_anim.calcLength() == 0 && !(mActorParam->getProfile() == "Armor") &&
        !hasTag(this, 0x216a3a63)) {
        as_list = mActorParam->getRes().mASList;
        if (as_list->getASDefines().size() == 0 && !_5b0)
            return true;
    } else if (getName().findIndex("Keese") != -1) {
        as_list = mActorParam->getRes().mASList;
        if (as_list->getASDefines().size() == 0 && !_5b0)
            return true;
    }
    as_list = mActorParam->getRes().mASList;

    const s32 num_add_res = as_list->getAddReses().size();
    gsys::ModelResource* model_resources[32];
    nn::g3d::ResSkeleton* skeletons[32];
    memset(skeletons, 0, sizeof(skeletons));

    s32 num_models = 0;
    if (mActorFlags.isOnBit(ActorFlag::_17)) {
        auto* system = OverlayArenaSystem::instance();
        system->nullsub_4271();
        auto* bfres = sead::DynamicCast<res::BfRes>(system->getResHandle().getResource());
        if (bfres) {
            model_resources[0] = bfres->_50;
            num_models = 1;
        }
    }

    u32 skeleton_flags = 0;
    nn::g3d::ResFile* umii_res_file = nullptr;
    for (s32 i = 0; i < _680; ++i) {
        auto* model_res = mModelResources[i].sub_71011FC6AC();
        if (!model_res)
            continue;

        const s32 model_idx = num_models < 0x20 ? num_models : 0;
        model_resources[model_idx] = model_res;

        const s32 add_res_idx = i - _681;
        if (add_res_idx >= 0 && add_res_idx < num_add_res) {
            const auto& add_res = as_list->getAddReses()[num_add_res - 1 - add_res_idx];
            const sead::SafeString retarget = add_res.retarget_model.ref();
            const sead::SafeString anim = add_res.anim.ref();
            if (retarget.cstr()[0] != '\0') {
                nn::g3d::ResModel* res_model = nullptr;
                const bool umii = mActorFlags.isOnBit(ActorFlag::_8) &&
                                  anim.findIndex("UMii_Common_Face_") != -1 &&
                                  anim.findIndex("_Animation") != -1;
                if (umii) {
                    umii_res_file = model_res->getResFile();
                    res_model = umii_res_file->sub_71011D55F4(retarget.cstr());
                    if (!res_model) {
                        umii_res_file = model_resources[0]->getResFile();
                        res_model = umii_res_file->sub_71011D55F4(retarget.cstr());
                    }
                } else {
                    res_model = model_res->getResFile()->sub_71011D55F4(retarget.cstr());
                    if (!res_model)
                        res_model =
                            model_resources[0]->getResFile()->sub_71011D55F4(retarget.cstr());
                }
                if (res_model) {
                    skeleton_flags |= 1u << num_models;
                    skeletons[model_idx] = res_model->pSkeleton.Get();
                }
            }
        }
        ++num_models;
    }

    for (auto* node = _5b0; node; node = node->mNext) {
        if (!node->_0)
            continue;
        const s32 model_idx = num_models < 0x20 ? num_models : 0;
        model_resources[model_idx] = static_cast<res::BfRes*>(node->_0)->_50;
        ++num_models;
    }

    if (num_models < 1)
        return true;

    gsys::ModelAnimation::CreateArg arg;
    sub_71011C9C80(arg);
    if (skeleton_flags != 0)
        arg._8 = skeletons;

    if (auto* tracker = ActorCreator::instance()->getProfiler()) {
        tracker->begin(mDualHeap, 1);
        if (auto* current = ActorCreator::instance()->getProfiler()) {
            current->_10 = arg._8;
            current->_8 = arg._0;
            current->_c = arg._4;
        }
    }

    auto* created = mModel->createAnimation(model_resources, num_models, arg, heap);
    if (auto* tracker = ActorCreator::instance()->getProfiler())
        tracker->end();
    if (!created)
        return false;

    // The UMii skeletons of the animation are renamed to Skeleton_<group> so that they bind to the
    // model's skeletons.
    if (umii_res_file) {
        auto* animation = mModel->getAnimation();
        const s32 count = animation->mSkeletalResources.size();
        for (s32 i = 0; i < count; ++i) {
            const auto& resource = animation->mSkeletalResources[i];
            const auto* skeletal =
                static_cast<const nn::g3d::ResSkeletalAnim*>(resource.resource->resource);
            const sead::SafeString name(skeletal->GetName());
            const s32 idx = name.findIndex("_Grp");
            if (idx < 0)
                continue;
            sead::FixedSafeString<8> group;
            group.copy(sead::SafeString(name.cstr() + idx + 1), 4);
            sead::FormatFixedSafeString<16> skeleton_name("Skeleton_%s", group.cstr());
            auto* res_model = umii_res_file->sub_71011D55F4(skeleton_name.cstr());
            if (res_model)
                animation->mSkeletalResources[i].mSkeleton = res_model->pSkeleton.Get();
        }
    }

    return true;
}

bool Actor::sub_71011D573C(sead::Heap* heap) {
    if (isDelete() || !sub_71011D4E88(heap))
        return false;
    if (mUMiiHylianInfo) {
        mUMiiHylianInfo->sub_71012A504C(mModel->getAnimation());
        mUMiiHylianInfo->sub_71012A5304(mModel->getAnimation(), mTextureCache, nullptr);
    }
    return true;
}

}  // namespace ksys::act

namespace ksys::act {

// 0x7101241f6c: starts a heap free-size measurement for the model animation creation.
void ModelCreationProfiler::begin(sead::Heap* heap, s32 slot) {
    mStartFreeSize = heap->getFreeSize();
    mHeap = heap;
    mSlot = slot;
}

// 0x7101241fb4: ends the measurement and stores the difference in the selected slot.
void ModelCreationProfiler::end() {
    const s32 start = mStartFreeSize;
    const s32 delta = start - mHeap->getFreeSize();
    const s32 slot = mSlot;
    mDeltas[slot < 2u ? slot : 0] = delta;
    mHeap = nullptr;
}

bool Actor::initChemicals(sead::Heap* heap) {
    if (!mActorParam->isDummyParam(res::ActorLink::User::Chemical)) {
        auto* resource = mActorParam->getRes().mChemical;
        if (resource && mPhysics) {
            mChemical = new (heap) ActorChemicals;
            if (!mChemical)
                return false;
            mChemical->init1(mPhysics, &resource->getRoot(), this, heap);
            if (world::Manager::instance() && _6a0)
                mChemical->init2(&_6a0->_10);
        }
    }
    return true;
}

}  // namespace ksys::act
