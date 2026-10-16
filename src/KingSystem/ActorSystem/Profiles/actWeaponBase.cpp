#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include <gsys/gsysModel.h>
#include <random/seadGlobalRandom.h>
#include <heap/seadHeapMgr.h>
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Ecosystem/ecoLevelSensor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/aiRootAi.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include <prim/seadScopedLock.h>
#include "Game/Actor/actOptionalWeapon.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actGlobalParameter.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBow.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLargeSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSmallSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSpear.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGlobal.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectNpcEquipment.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectEnemyRace.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectShield.h"
#include "KingSystem/Utils/Thread/Message.h"

bool checkIsGetSameGroupActorName(const sead::SafeString& actor_name, bool a1);

namespace ksys::act {

bool WeaponBase::prepareInit_(sead::Heap* heap, PrepareArg& arg) {
    if (!arg._0) {
        mExtraActorHandle.deleteProc();
        spawnExtraActor1();
        spawnExtraActor2();
    }
    return true;
}

void WeaponBase::spawnExtraActor1() {
    sead::SafeString name = m159();
    if (name.isEmpty())
        return;
    auto* heap = sead::HeapMgr::instance()->findContainHeap(this);
    InstParamPack params;
    if (mActorFlags2.isOn(ActorFlag2::_200))
        params->addPlayerControl();
    params->addResourceLane(2);
    ActorCreator::instance()->requestCreateActor(name.cstr(), heap, &mExtraActorHandle, &params,
                                               nullptr, 2);
}

void WeaponBase::spawnExtraActor2() {
    sead::SafeString name = m160();
    if (name.isEmpty())
        return;
    auto* heap = sead::HeapMgr::instance()->findContainHeap(this);
    InstParamPack params;
    if (mActorFlags2.isOn(ActorFlag2::_200))
        params->addPlayerControl();
    ActorCreator::instance()->requestCreateActor(name.cstr(), heap, &mExtraActorHandle, &params,
                                               nullptr, 1);
}

eco::WeaponModifier getRandomWeaponModifier(eco::WeaponModifier modifier,
                                          const sead::SafeString& actor_name) {
    auto* data = InfoData::instance();
    if (!data)
        return eco::WeaponModifier::None;
    const f32 percent = getWeaponCommonSharpWeaponPer(data, actor_name.cstr());
    if (modifier != eco::WeaponModifier::RandomBlue)
        return modifier;
    if (percent <= 0.0f)
        return eco::WeaponModifier::None;
    if (sead::GlobalRandom::instance()->getF32() * 100.0f > percent)
        return eco::WeaponModifier::None;
    return checkIsGetSameGroupActorName(actor_name, true) ? eco::WeaponModifier::Blue :
                                                        eco::WeaponModifier::None;
}

WeaponBase::WeaponBase(const CreateArg& arg) : Actor(arg) {
    _1c0 = 3;
}

// NON_MATCHING: D1 / D0 and their thunks: the original keeps &_840 and &_880 in callee-saved registers across the link resets (we recompute them)
WeaponBase::~WeaponBase() = default;

BaseProc::IsSpecialJobTypeResult WeaponBase::isSpecialJobType_(JobType type) {
    if (_ab0)
        return IsSpecialJobTypeResult::Yes;
    return Actor::isSpecialJobType_(type);
}

bool WeaponBase::canWakeUp_() {
    if (!Actor::canWakeUp_())
        return false;
    auto* parent = sead::DynamicCast<Actor>(_880.getProc(nullptr, nullptr));
    if (parent && !parent->isCalc())
        return false;
    return true;
}

void WeaponBase::onSleepRequested_(SleepWakeReason reason) {
    Actor::onSleepRequested_(reason);
    if (_958.hasProc()) {
        ActorLinkConstDataAccess accessor;
        acquireActor(&_958, &accessor);
        accessor.sleep(reason);
    }
}

void WeaponBase::onWakeUpRequested_(SleepWakeReason reason) {
    Actor::onWakeUpRequested_(reason);
    m215();
    if (_958.hasProc()) {
        ActorLinkConstDataAccess accessor;
        acquireActor(&_958, &accessor);
        accessor.wakeUp(reason);
    }
}

void WeaponBase::onDeleteRequested_(DeleteReason reason) {
    Actor::onDeleteRequested_(reason);
    if (_958.hasProc()) {
        ActorLinkConstDataAccess accessor;
        acquireActor(&_958, &accessor);
        accessor.deleteLater(DeleteReason::_0);
    }
    auto* child = sead::DynamicCast<Actor>(getConnectedCalcChild());
    if (child && !m250(child))
        child->deleteLater(DeleteReason::_0);
}

Actor* WeaponBase::m31() {
    return getParentActor();
}

Actor* WeaponBase::m48() {
    if (hasParentActor_())
        return getParentActor();
    if (_948.hasProc())
        return sead::DynamicCast<Actor>(_948.getProc(nullptr, nullptr));
    return nullptr;
}

void WeaponBase::sub_7100EF3664() {
    if (hasParentActor() && !m189() && (m237(getParentActor()) || m238(getParentActor()))) {
        if (!mExtraActorHandle.isAllocatedOrFailed())
            return;
        if (!m187() && mExtraActorHandle.isProcReady()) {
            auto* proc = mExtraActorHandle.getProc();
            if (auto* optional = sead::DynamicCast<uking::act::OptionalWeapon>(proc)) {
                if (isWeaponType3()) {
                    optional->sub_7100EF1954(getParentActor(), this, "Pod_B");
                } else {
                    optional->clearFadeInCreate();
                    optional->sub_7100EF1954(getParentActor(), this, _9a0);
                }
                _958.acquire(optional, false);
            }
            mExtraActorHandle.releaseAndWakeProc();
        } else if (mExtraActorHandle.hasProcCreationFailed()) {
            mExtraActorHandle.deleteProcIfFailed();
            if (m237(getParentActor()) && !_958.hasProc()) {
                spawnExtraActor1();
                return;
            }
            if (m238(getParentActor()) && !_958.hasProc()) {
                spawnExtraActor2();
                return;
            }
        }
        return;
    }
    if (mExtraActorHandle.isAllocatedOrFailed())
        mExtraActorHandle.deleteProc();
}

void WeaponBase::initMaybe() {
    if (mModel)
        mModel->setMatrix(mMtx);
    if (hasParentActor_()) {
        _920 = _9f4.getDirect() & 4;
        isWeaponType3();
        auto* parent = sead::DynamicCast<Actor>(_938.getProc(nullptr, this));
        if (parent && parent->getState() == State::Sleep)
            sleep(SleepWakeReason::_0);
    }
    _ab0 = 0;
}

void WeaponBase::m117(Unk117* arg) {
    if (auto* optional = sead::DynamicCast<uking::act::OptionalWeapon>(_958.getProc(nullptr, nullptr)))
        optional->x_17(arg);
    if (getConnectedCalcChild()) {
        if (auto* child = sead::DynamicCast<Actor>(getConnectedCalcChild()))
            child->x_17(arg);
    }
}

void WeaponBase::calcMaybe() {
    sub_7100EF345C();
    if (hasParentActor())
        sub_71011DB070();
    else
        sub_71011DB138();
}

void WeaponBase::m70() {
    if (_ab0)
        x_14(false);
    sub_7100EF345C();
    if (m188()) {
        if (auto* chemical = sub_71011D8A44(0)) {
            chemical->sub_7100D8EEE0();
            getRootAi()->setChemicalFlags3cMaybe(1, false);
        }
        deleteLater(DeleteReason::_0);
    }
}

void WeaponBase::updatePositionMaybe() {
    _9f4.reset(8);
    sub_7100EF3664();
}

bool WeaponBase::m86() {
    ActorLinkConstDataAccess accessor;
    acquireActor(&_938, &accessor);
    if (accessor.checkFlag2B())
        return false;
    return Actor::m86();
}

// NON_MATCHING: the common forwarding path changes block layout and register allocation.
int WeaponBase::handleMessage(const Message* message) {
    if (isDelete() || isDeleteRequested())
        return 0;
    MessageType outgoing_type;
    if (message->getType() == 0x3000001) {
        _9f4.set(2);
        mActorFlags2.set(ActorFlag2::_20);
        outgoing_type = static_cast<MessageType>(0x3000001);
    } else if (message->getType() == 0x3000002) {
        _9f4.reset(2);
        mActorFlags2.reset(ActorFlag2::_20);
        outgoing_type = static_cast<MessageType>(0x3000002);
    } else {
        return Actor::handleMessage(message);
    }
    if (_958.hasProcInCalcState()) {
        ActorLinkConstDataAccess accessor;
        acquireActor(&_958, &accessor);
        MessageTransceiverBase& transceiver = getMessageTransceiver();
        transceiver.sendMessageOnProcessingThread(*accessor.getMessageTransceiverId(), outgoing_type,
                                                  nullptr, true);
    }
    return 1;
}

void WeaponBase::m92(phys::RigidBody* body) {
    if (hasParentActor())
        return;
    Actor::m92(body);
}

// NON_MATCHING: the NPC switch (the original zero-extends the index and adds the full field offset per
// case; ours shares the +0x18 of Parameter::ref()).
void WeaponBase::m165(sead::Vector3f* out) {
    if (m153()) {
        m167(out);
        return;
    }

    if (isParentPlayer() || sub_7100EFD8E4(getParentActor())) {
        if (m231()) {
            *out = getParam()->getRes().mGParamList->getSmallSword()->mPlayerEquipRotOffset.ref();
        } else if (m232()) {
            *out = getParam()->getRes().mGParamList->getLargeSword()->mPlayerEquipRotOffset.ref();
        } else if (m233()) {
            *out = getParam()->getRes().mGParamList->getSpear()->mPlayerEquipRotOffset.ref();
        } else if (isWeaponType4()) {
            m248(out);
            *out += getParam()->getRes().mGParamList->getShield()->mPlayerEquipRotOffset.ref();
        } else if (isWeaponType3()) {
            *out = getParam()->getRes().mGParamList->getBow()->mPlayerEquipRotOffset.ref();
        } else {
            *out = sead::Vector3f::zero;
        }
    } else if (isParentNpc()) {
        auto* parent = getParentActor();
        const res::GParamList* list;
        const res::GParamListObjectNpcEquipment* equipment;
        if (!parent || !(list = parent->getParam()->getRes().mGParamList) ||
            !(equipment = list->getNpcEquipment())) {
            *out = sead::Vector3f::zero;
            return;
        }
        const sead::Vector3f* offset;
        switch (_9f8) {
        case 0:
            offset = &equipment->mEquipRotOffset1.ref();
            break;
        case 1:
            offset = &equipment->mEquipRotOffset2.ref();
            break;
        case 2:
            offset = &equipment->mEquipRotOffset3.ref();
            break;
        case 3:
            offset = &equipment->mEquipRotOffset4.ref();
            break;
        default:
            offset = &sead::Vector3f::zero;
            break;
        }
        *out = *offset;
    } else if (m142()) {
        if (getParam()->getRes().mActorLink->hasTag(0x2b533845)) {
            *out = GlobalParameter::instance()->getGlobalParam()->mTreeWeaponEquipRotOffset.ref();
        } else if (m231()) {
            *out = getParam()->getRes().mGParamList->getSmallSword()->mEnemyEquipRotOffset.ref();
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out += accessor.getGParamList()->getEnemyRace()->mWeaponRotOffsetSmallSword.ref();
        } else if (m232()) {
            *out = getParam()->getRes().mGParamList->getLargeSword()->mEnemyEquipRotOffset.ref();
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out += accessor.getGParamList()->getEnemyRace()->mWeaponRotOffsetLargeSword.ref();
        } else if (m233()) {
            *out = getParam()->getRes().mGParamList->getSpear()->mEnemyEquipRotOffset.ref();
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out += accessor.getGParamList()->getEnemyRace()->mWeaponRotOffsetSpear.ref();
        } else if (isWeaponType4()) {
            *out = getParam()->getRes().mGParamList->getShield()->mEnemyEquipRotOffset.ref();
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out += accessor.getGParamList()->getEnemyRace()->mWeaponRotOffsetShield.ref();
        } else if (isWeaponType3()) {
            *out = getParam()->getRes().mGParamList->getBow()->mEnemyEquipRotOffset.ref();
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out += accessor.getGParamList()->getEnemyRace()->mWeaponRotOffsetBow.ref();
        } else {
            *out = sead::Vector3f::zero;
        }
    } else {
        *out = sead::Vector3f::zero;
    }
}

// NON_MATCHING: the NPC switch (the original zero-extends the index and adds the full field offset per
// case; ours shares the +0x18 of Parameter::ref()).
void WeaponBase::m166(sead::Vector3f* out) {
    if (m153()) {
        m168(out);
        return;
    }

    if (isParentPlayer() || sub_7100EFD8E4(getParentActor())) {
        if (m231()) {
            *out = getParam()->getRes().mGParamList->getSmallSword()->mPlayerEquipTransOffset.ref();
        } else if (m232()) {
            *out = getParam()->getRes().mGParamList->getLargeSword()->mPlayerEquipTransOffset.ref();
        } else if (m233()) {
            *out = getParam()->getRes().mGParamList->getSpear()->mPlayerEquipTransOffset.ref();
        } else if (isWeaponType4()) {
            m247(out);
            *out += getParam()->getRes().mGParamList->getShield()->mPlayerEquipTransOffset.ref();
        } else if (isWeaponType3()) {
            *out = getParam()->getRes().mGParamList->getBow()->mPlayerEquipTransOffset.ref();
        } else {
            *out = sead::Vector3f::zero;
        }
    } else if (isParentNpc()) {
        auto* parent = getParentActor();
        const res::GParamList* list;
        const res::GParamListObjectNpcEquipment* equipment;
        if (!parent || !(list = parent->getParam()->getRes().mGParamList) ||
            !(equipment = list->getNpcEquipment())) {
            *out = sead::Vector3f::zero;
        } else {
            const sead::Vector3f* offset;
            switch (_9f8) {
            case 0:
                offset = &equipment->mEquipTransOffset1.ref();
                break;
            case 1:
                offset = &equipment->mEquipTransOffset2.ref();
                break;
            case 2:
                offset = &equipment->mEquipTransOffset3.ref();
                break;
            case 3:
                offset = &equipment->mEquipTransOffset4.ref();
                break;
            default:
                offset = &sead::Vector3f::zero;
                break;
            }
            *out = *offset;
        }
    } else if (m142()) {
        if (getParam()->getRes().mActorLink->hasTag(0x2b533845)) {
            *out = GlobalParameter::instance()->getGlobalParam()->mTreeWeaponEquipTransOffset.ref();
        } else if (m231()) {
            *out = getParam()->getRes().mGParamList->getSmallSword()->mEnemyEquipTransOffset.ref();
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out += accessor.getGParamList()->getEnemyRace()->mWeaponTransOffsetSmallSword.ref();
        } else if (m232()) {
            *out = getParam()->getRes().mGParamList->getLargeSword()->mEnemyEquipTransOffset.ref();
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out += accessor.getGParamList()->getEnemyRace()->mWeaponTransOffsetLargeSword.ref();
        } else if (m233()) {
            *out = getParam()->getRes().mGParamList->getSpear()->mEnemyEquipTransOffset.ref();
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out += accessor.getGParamList()->getEnemyRace()->mWeaponTransOffsetSpear.ref();
        } else if (isWeaponType4()) {
            *out = getParam()->getRes().mGParamList->getShield()->mEnemyEquipTransOffset.ref();
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out += accessor.getGParamList()->getEnemyRace()->mWeaponTransOffsetShield.ref();
        } else if (isWeaponType3()) {
            *out = getParam()->getRes().mGParamList->getBow()->mEnemyEquipTransOffset.ref();
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out += accessor.getGParamList()->getEnemyRace()->mWeaponTransOffsetBow.ref();
        } else {
            *out = sead::Vector3f::zero;
        }
    } else {
        *out = sead::Vector3f::zero;
    }

    sead::Vector3f extra = sead::Vector3f::zero;
    m244(&extra);
    *out += extra;
}

// NON_MATCHING: the original loads out->x / y before the ride-horse offset in each branch; NPC switch as in m165.
void WeaponBase::m167(sead::Vector3f* out) {
    if (isParentPlayer() || sub_7100EFD8E4(getParentActor())) {
        if (m231()) {
            *out = getParam()->getRes().mGParamList->getSmallSword()->mPlayerHoldRotOffset.ref();
            if (m154())
                *out += getParam()->getRes().mGParamList->getSmallSword()->mRideHorsePlayerHoldRotOffset.ref();
        } else if (m232()) {
            *out = getParam()->getRes().mGParamList->getLargeSword()->mPlayerHoldRotOffset.ref();
            if (m154())
                *out += getParam()->getRes().mGParamList->getLargeSword()->mRideHorsePlayerHoldRotOffset.ref();
        } else if (m233()) {
            const bool grab = m155();
            const auto* spear = getParam()->getRes().mGParamList->getSpear();
            if (grab)
                *out = spear->mGrabPlayerHoldRotOffset.ref();
            else
                *out = spear->mPlayerHoldRotOffset.ref();
            if (m154())
                *out += getParam()->getRes().mGParamList->getSpear()->mRideHorsePlayerHoldRotOffset.ref();
        } else if (isWeaponType4()) {
            *out = getParam()->getRes().mGParamList->getShield()->mPlayerHoldRotOffset.ref();
            sead::Vector3f offset;
            m240(&offset);
            *out += offset;
        } else if (isWeaponType3()) {
            *out = getParam()->getRes().mGParamList->getBow()->mPlayerHoldRotOffset.ref();
            sead::Vector3f offset;
            m242(&offset);
            *out += offset;
        } else {
            *out = sead::Vector3f::zero;
        }
        sead::Vector3f squat_offset;
        m246(&squat_offset);
        *out += squat_offset;
        return;
    }

    if (isParentNpc()) {
        auto* parent = getParentActor();
        const res::GParamList* list;
        const res::GParamListObjectNpcEquipment* equipment;
        const sead::Vector3f* offset = &sead::Vector3f::zero;
        if (parent && (list = parent->getParam()->getRes().mGParamList) &&
            (equipment = list->getNpcEquipment())) {
            switch (_9f8) {
            case 0:
                offset = &equipment->mHoldRotOffset1.ref();
                break;
            case 1:
                offset = &equipment->mHoldRotOffset2.ref();
                break;
            case 2:
                offset = &equipment->mHoldRotOffset3.ref();
                break;
            case 3:
                offset = &equipment->mHoldRotOffset4.ref();
                break;
            default:
                break;
            }
        }
        *out = *offset;
        return;
    }

    if (m142()) {
        if (m231()) {
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out = accessor.getGParamList()->getEnemyRace()->mWeaponHoldRotOffsetSmallSword.ref();
        } else if (m232()) {
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out = accessor.getGParamList()->getEnemyRace()->mWeaponHoldRotOffsetLargeSword.ref();
        } else if (m233()) {
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out = accessor.getGParamList()->getEnemyRace()->mWeaponHoldRotOffsetSpear.ref();
        } else if (isWeaponType4()) {
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out = accessor.getGParamList()->getEnemyRace()->mWeaponHoldRotOffsetShield.ref();
        } else if (isWeaponType3()) {
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out = accessor.getGParamList()->getEnemyRace()->mWeaponHoldRotOffsetBow.ref();
        } else {
            *out = sead::Vector3f::zero;
        }
        return;
    }
    *out = sead::Vector3f::zero;
}

// NON_MATCHING: the original loads out->x / y before the ride-horse offset in each branch; NPC switch as in m165.
void WeaponBase::m168(sead::Vector3f* out) {
    if (isParentPlayer() || sub_7100EFD8E4(getParentActor())) {
        if (m231()) {
            *out = getParam()->getRes().mGParamList->getSmallSword()->mPlayerHoldTransOffset.ref();
            if (m154())
                *out += getParam()->getRes().mGParamList->getSmallSword()->mRideHorsePlayerHoldTransOffset.ref();
        } else if (m232()) {
            *out = getParam()->getRes().mGParamList->getLargeSword()->mPlayerHoldTransOffset.ref();
            if (m154())
                *out += getParam()->getRes().mGParamList->getLargeSword()->mRideHorsePlayerHoldTransOffset.ref();
        } else if (m233()) {
            const bool grab = m155();
            const auto* spear = getParam()->getRes().mGParamList->getSpear();
            if (grab)
                *out = spear->mGrabPlayerHoldTransOffset.ref();
            else
                *out = spear->mPlayerHoldTransOffset.ref();
            if (m154())
                *out += getParam()->getRes().mGParamList->getSpear()->mRideHorsePlayerHoldTransOffset.ref();
        } else if (isWeaponType4()) {
            *out = getParam()->getRes().mGParamList->getShield()->mPlayerHoldTransOffset.ref();
            sead::Vector3f offset;
            m241(&offset);
            *out += offset;
        } else if (isWeaponType3()) {
            *out = getParam()->getRes().mGParamList->getBow()->mPlayerHoldTransOffset.ref();
            sead::Vector3f offset;
            m243(&offset);
            *out += offset;
        } else {
            *out = sead::Vector3f::zero;
        }
        sead::Vector3f squat_offset;
        m245(&squat_offset);
        *out += squat_offset;
        return;
    }

    if (isParentNpc()) {
        auto* parent = getParentActor();
        const res::GParamList* list;
        const res::GParamListObjectNpcEquipment* equipment;
        const sead::Vector3f* offset = &sead::Vector3f::zero;
        if (parent && (list = parent->getParam()->getRes().mGParamList) &&
            (equipment = list->getNpcEquipment())) {
            switch (_9f8) {
            case 0:
                offset = &equipment->mHoldTransOffset1.ref();
                break;
            case 1:
                offset = &equipment->mHoldTransOffset2.ref();
                break;
            case 2:
                offset = &equipment->mHoldTransOffset3.ref();
                break;
            case 3:
                offset = &equipment->mHoldTransOffset4.ref();
                break;
            default:
                break;
            }
        }
        *out = *offset;
    } else {
        if (!m142()) {
            *out = sead::Vector3f::zero;
            return;
        }
        if (m231()) {
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out = accessor.getGParamList()->getEnemyRace()->mWeaponHoldTransOffsetSmallSword.ref();
        } else if (m232()) {
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out = accessor.getGParamList()->getEnemyRace()->mWeaponHoldTransOffsetLargeSword.ref();
        } else if (m233()) {
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out = accessor.getGParamList()->getEnemyRace()->mWeaponHoldTransOffsetSpear.ref();
        } else if (isWeaponType4()) {
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out = accessor.getGParamList()->getEnemyRace()->mWeaponHoldTransOffsetShield.ref();
        } else if (isWeaponType3()) {
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            *out = accessor.getGParamList()->getEnemyRace()->mWeaponHoldTransOffsetBow.ref();
        } else {
            *out = sead::Vector3f::zero;
        }
    }

    sead::Vector3f extra = sead::Vector3f::zero;
    m245(&extra);
    *out += extra;
}

// NON_MATCHING: the drop-velocity scaling and the _910 copies are scheduled differently.
bool WeaponBase::m199() {
    mDrawDistanceFlags.set(1);
    sead::Vector3f pos;
    pos.x = mMtx(0, 3);
    pos.y = mMtx(1, 3);
    pos.z = mMtx(2, 3);

    if (_936) {
        if (auto* body = mMainBody.load()) {
            sead::Matrix34f mtx = body->getTransform();
            mtx.setTranslation(_928);
            body->setTransform(mtx, phys::PropagateToLinkedMotions(true));
            setMtx(mtx, false, true);
            pos = mtx.getTranslation();
            if (mPhysics)
                mPhysics->setMtxAndScale(mtx, false, false, mScale.x);
            body->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
            body->setAngularVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
        }
        _936 = false;
    }

    bool result;
    if (!_934) {
        if (!_922) {
            if (_924) {
                f32 speed = sead::Mathf::deg2rad(30.0f);
                if (GlobalParameter::instance() && GlobalParameter::instance()->getGlobalParam())
                    speed = sead::Mathf::deg2rad(
                        GlobalParameter::instance()->getGlobalParam()->mWeaponDropRotSpd.ref());
                sub_7100EE5A14(this, -(sead::Vector3f(0, 1, 0) * speed));
            }
            sub_7100EE5980(this, _910);
            sub_7100EE6AFC();
            const sead::Vector3f vel = _910;
            result = sub_7100EF7208(pos, vel, false);
        } else {
            if (!_935)
                m209(_910);
            else
                sub_7100EE5980(this, _910);
            m207();
            _922 = false;
            _935 = false;
            sub_7100EE6AFC();
            if (isParentPlayer()) {
                sead::Vector3f vel = _910;
                if (auto* body = static_cast<phys::RigidBody*>(m221())) {
                    body->getLinearVelocity(&vel);
                    vel *= 1.0f / 30.0f;
                }
                result = sub_7100EF7208(pos, vel, true);
            } else {
                result = false;
            }
        }
    } else {
        if (auto* body = mMainBody.load()) {
            ActorLinkConstDataAccess accessor;
            acquireActor(&_938, &accessor);
            sead::Matrix34f mtx = accessor.getActorMtx();
            mtx.setTranslation(_928);
            m249(&mtx, this);
            body->setTransform(mtx, phys::PropagateToLinkedMotions(true));
            setMtx(mtx, false, true);
            pos = mtx.getTranslation();
            if (mPhysics)
                mPhysics->setMtxAndScale(mtx, false, false, mScale.x);
            body->setLinearVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
            body->setAngularVelocity(sead::Vector3f::zero, sead::Mathf::epsilon());
        }
        _934 = false;
        if (isMasterSword())
            masterSwordReturnToForest();
        sub_7100EE5980(this, _910);
        sub_7100EE6AFC();
        result = false;
    }

    if (auto* parent = sead::DynamicCast<Actor>(_938.getProc(nullptr, this))) {
        if (auto* weapons = parent->getWeapons())
            weapons->resetBaseProcLinkForActor(this);
    }
    _938.reset();
    _958.reset();
    if (mExtraActorHandle.isAllocatedOrFailed())
        mExtraActorHandle.deleteProc();
    _920 = 0xff;
    return result;
}

// NON_MATCHING: the index search now matches (explicit bounds checks as in PlayerOrEnemy::m147); the
// profile comparisons in the loops are laid out differently.
void WeaponBase::m147(sead::PtrArray<Actor>* actors) {
    const s32 num = actors->size();
    s32 idx = -1;
    for (s32 i = 0; i < num; ++i) {
        if (actors->at(i) == this) {
            idx = i;
            break;
        }
    }
    if (idx < 0)
        return;

    if (isWeaponType0Or1Or2()) {
        for (s32 i = 0; i < num; ++i) {
            auto* weapon = sead::DynamicCast<WeaponBase>(actors->at(i));
            if ((weapon && weapon->getProfile() != "WeaponSmallSword" &&
                 weapon->getProfile() != "WeaponLargeSword" &&
                 weapon->getProfile() != "WeaponLargeSpear") ||
                (actors->at(i) && actors->at(i)->getProfile() == "OptionalWeapon")) {
                if (idx > i) {
                    if (u32(actors->size()) > u32(idx) && u32(actors->size()) > u32(i))
                        actors->swap(idx, i);
                    idx = i;
                }
            }
        }
        return;
    }

    for (s32 i = 0; i < num; ++i) {
        auto* weapon = sead::DynamicCast<WeaponBase>(actors->at(i));
        const bool is_sword = weapon && (weapon->getProfile() == "WeaponSmallSword" ||
                                         weapon->getProfile() == "WeaponLargeSword" ||
                                         weapon->getProfile() == "WeaponLargeSpear");
        if (idx < i && is_sword) {
            if (u32(actors->size()) > u32(idx) && u32(actors->size()) > u32(i))
                actors->swap(idx, i);
            idx = i;
        }
        if (actors->at(i) && actors->at(i)->getProfile() == "OptionalWeapon") {
            const bool type3 = isWeaponType3();
            if (i < idx && type3) {
                if (u32(actors->size()) > u32(idx) && u32(actors->size()) > u32(i))
                    actors->swap(idx, i);
                idx = i;
            }
        }
    }
}

bool WeaponBase::m201() {
    sub_7100EE6AFC();
    auto* actor = sead::DynamicCast<Actor>(_880.getProc(nullptr, nullptr));
    if (!actor)
        return false;
    _938.acquire(actor, false);
    _9f0 = _91c;
    _920 = 0xff;
    _968.copy(_8a0);
    _9a0.copy(_8d8);
    _9f4.set(4);
    return true;
}

void WeaponBase::m169(sead::Vector3f* out) {
    if (getParentActor() && !m153() && (!sub_7100EFD700(getParentActor()) || m159().isEmpty())) {
        *out = sead::Vector3f::zero;
        return;
    }
    if (isWeaponType4() || isWeaponType3()) {
        *out = sead::Vector3f::zero;
        return;
    }
    if (m231()) {
        *out = getParam()->getRes().mGParamList->getSmallSword()->mAffectRotOffsetShield.ref();
    } else if (m232()) {
        *out = getParam()->getRes().mGParamList->getLargeSword()->mAffectRotOffsetShield.ref();
    } else if (m233()) {
        const bool grab = m155();
        const auto* spear = getParam()->getRes().mGParamList->getSpear();
        if (grab)
            *out = spear->mGrabAffectRotOffsetShield.ref();
        else
            *out = spear->mAffectRotOffsetShield.ref();
    } else {
        *out = sead::Vector3f::zero;
    }
}

void WeaponBase::m170(sead::Vector3f* out) {
    if (getParentActor() && !m153() && (!sub_7100EFD700(getParentActor()) || m159().isEmpty())) {
        *out = sead::Vector3f::zero;
        return;
    }
    if (isWeaponType4() || isWeaponType3()) {
        *out = sead::Vector3f::zero;
        return;
    }
    if (m231()) {
        *out = getParam()->getRes().mGParamList->getSmallSword()->mAffectTransOffsetShield.ref();
    } else if (m232()) {
        *out = getParam()->getRes().mGParamList->getLargeSword()->mAffectTransOffsetShield.ref();
    } else if (m233()) {
        const bool grab = m155();
        const auto* spear = getParam()->getRes().mGParamList->getSpear();
        if (grab)
            *out = spear->mGrabAffectTransOffsetShield.ref();
        else
            *out = spear->mAffectTransOffsetShield.ref();
    } else {
        *out = sead::Vector3f::zero;
    }
}

void WeaponBase::m171(sead::Vector3f* out) {
    if (getParentActor() && !m153() && (!sub_7100EFD700(getParentActor()) || m159().isEmpty())) {
        *out = sead::Vector3f::zero;
        return;
    }
    if (isWeaponType4() || isWeaponType3()) {
        *out = sead::Vector3f::zero;
        return;
    }
    if (m231()) {
        *out = getParam()->getRes().mGParamList->getSmallSword()->mAffectRotOffsetBow.ref();
    } else if (m232()) {
        *out = getParam()->getRes().mGParamList->getLargeSword()->mAffectRotOffsetBow.ref();
    } else if (m233()) {
        *out = getParam()->getRes().mGParamList->getSpear()->mAffectRotOffsetBow.ref();
    } else {
        *out = sead::Vector3f::zero;
    }
}

void WeaponBase::m172(sead::Vector3f* out) {
    if (getParentActor() && !m153() && (!sub_7100EFD700(getParentActor()) || m159().isEmpty())) {
        *out = sead::Vector3f::zero;
        return;
    }
    if (isWeaponType4() || isWeaponType3()) {
        *out = sead::Vector3f::zero;
        return;
    }
    if (m231()) {
        *out = getParam()->getRes().mGParamList->getSmallSword()->mAffectTransOffsetBow.ref();
    } else if (m232()) {
        *out = getParam()->getRes().mGParamList->getLargeSword()->mAffectTransOffsetBow.ref();
    } else if (m233()) {
        *out = getParam()->getRes().mGParamList->getSpear()->mAffectTransOffsetBow.ref();
    } else {
        *out = sead::Vector3f::zero;
    }
}

bool WeaponBase::m237(Actor* actor) {
    if (!sub_7100EFD700(actor))
        return false;
    return !m159().isEmpty();
}

bool WeaponBase::m238(Actor* actor) {
    if (!actor)
        return false;
    // NON_MATCHING: the original keeps a dead SafeString("PauseMenuPlayer") object on the stack
    if (actor->getProfile() == "Player" || actor->getProfile() == "PauseMenuPlayer")
        return !m160().isEmpty();
    return false;
}

bool WeaponBase::m173(s32 index, Actor* actor, const char* name, const char* other_name,
                      bool a5, bool a6) {
    const auto lock = sead::makeScopedLock(_840);
    const bool both = a5 && a6;
    if (!both) {
        if (!_920 || _921)
            return false;
        if (!_9f4.isOn(4) && _938.hasProc())
            return false;
    }
    _880.acquire(actor, false);
    _91c = index;
    if (a5) {
        _921 = true;
    } else {
        _920 = 0;
        if (a6)
            _925 = true;
    }
    _8a0.copy(name);
    _8d8.copy(other_name);
    if (!m237(actor) || (_890.hasProc() || both))
        m238(actor);
    return true;
}

void WeaponBase::m180(s32 index, Actor* actor, const char* name, const char* other_name) {
    const auto lock = sead::makeScopedLock(_840);
    _880.acquire(actor, false);
    _91c = index;
    _8a0.copy(name);
    _8d8.copy(other_name);
    _920 = 4;
}

bool WeaponBase::m174() {
    const auto lock = sead::makeScopedLock(_840);
    _880.reset();
    _91c = -1;
    _920 = 1;
    if (_958.hasProc()) {
        if (auto* weapon = sead::DynamicCast<uking::act::OptionalWeapon>(_890.getProc(nullptr, nullptr)))
            weapon->sub_7100EF1ADC();
        _890.reset();
    }
    return true;
}

bool WeaponBase::m178(const sead::Vector3f& pos) {
    const auto lock = sead::makeScopedLock(_840);
    _880.reset();
    _91c = -1;
    _920 = 2;
    _910.set(pos);
    _922 = true;
    _923 = false;
    _924 = 0;
    _935 = 1;
    if (_958.hasProc()) {
        if (auto* weapon = sead::DynamicCast<uking::act::OptionalWeapon>(_958.getProc(nullptr, nullptr)))
            weapon->sub_7100EF1ADC();
        _890.reset();
    }
    return true;
}

bool WeaponBase::m175(const sead::Vector3f& pos, bool a2, bool a3, void* a4, bool a5) {
    const auto lock = sead::makeScopedLock(_840);
    if (_925)
        return false;
    _880.reset();
    _91c = -1;
    _920 = 2;
    _910.set(pos);
    _922 = a3;
    _923 = a5;
    _924 = a2;
    if (_958.hasProc()) {
        if (auto* weapon = sead::DynamicCast<uking::act::OptionalWeapon>(_958.getProc(nullptr, nullptr)))
            weapon->sub_7100EF1ADC();
        _890.reset();
    }
    return true;
}

bool WeaponBase::m177(const sead::Vector3f& target, void* a2) {
    const auto lock = sead::makeScopedLock(_840);
    _880.reset();
    _91c = -1;
    _920 = 2;
    _910.set(sead::Vector3f::zero);
    _922 = false;
    _923 = false;
    _924 = 0;
    _928.set(target);
    _934 = true;
    if (_958.hasProc()) {
        if (auto* weapon = sead::DynamicCast<uking::act::OptionalWeapon>(_958.getProc(nullptr, nullptr)))
            weapon->sub_7100EF1ADC();
        _890.reset();
    }
    return true;
}

void WeaponBase::m179() {
    const auto lock = sead::makeScopedLock(_840);
    _880.reset();
    _91c = -1;
    _920 = 3;
    if (_958.hasProc()) {
        if (auto* weapon = sead::DynamicCast<uking::act::OptionalWeapon>(_890.getProc(nullptr, nullptr)))
            weapon->sub_7100EF1ADC();
        _890.reset();
    }
}

bool WeaponBase::m176(const sead::Vector3f& target, const sead::Vector3f& pos, bool a3, bool a4, void* a5,
                      bool a6) {
    const auto lock = sead::makeScopedLock(_840);
    if (_925)
        return false;
    _880.reset();
    _91c = -1;
    _920 = 2;
    _910.set(pos);
    _922 = a4;
    _923 = a6;
    _924 = a3;
    if (_958.hasProc()) {
        if (auto* weapon = sead::DynamicCast<uking::act::OptionalWeapon>(_958.getProc(nullptr, nullptr)))
            weapon->sub_7100EF1ADC();
        _890.reset();
    }
    _936 = true;
    _928.set(target);
    return true;
}


void WeaponBase::sub_7100EF91B0(bool ready, bool propagate) {
    _ab0 = ready;
    if (propagate) {
        if (auto* optional_weapon = m162())
            optional_weapon->_94c = ready;
    }
}

bool WeaponBase::areExtraActorsReady() const {
    if (m159().isEmpty() && m160().isEmpty())
        return true;

    if (mExtraActorHandle.isAllocatedOrFailed() && !mExtraActorHandle.isProcReady())
        return mExtraActorHandle.hasProcCreationFailed();

    return true;
}

Actor* WeaponBase::getParentActor() {
    return sead::DynamicCast<Actor>(_938.getProc(nullptr, this));
}

// NON_MATCHING: the merged return computes mPodName.ref() as add #0x38 + add #0x18 (target: one add #0x50)
const sead::SafeString& WeaponBase::m159() const {
    if (m231())
        return getParam()->getRes().mGParamList->getSmallSword()->mPodName.ref();
    if (m232())
        return getParam()->getRes().mGParamList->getLargeSword()->mPodName.ref();
    if (m233())
        return getParam()->getRes().mGParamList->getSpear()->mPodName.ref();
    return sead::SafeString::cEmptyString;
}

const sead::SafeString& WeaponBase::m160() const {
    const auto* bow = getParam()->getRes().mGParamList->getBow();
    if (!bow)
        return sead::SafeString::cEmptyString;
    return bow->mQuiverName.ref();
}

const sead::SafeString& WeaponBase::m164() {
    if (m153())
        return _9a0;
    return _968;
}

bool WeaponBase::m182() {
    if (m186() && !m188()) {
        _920 = 0;
        _925 = false;
        return true;
    }
    return false;
}

bool WeaponBase::hasCanPullGiantObjectTag() {
    return getParam()->getRes().mActorLink->hasTag(0x2b533845);
}

void WeaponBase::m207() {
    // C++14 evaluation order: the original evaluates the destination first.
    _948.operator=(_938);
    setFlag(ActorFlag::_2c, true);
}

void WeaponBase::m208() {
    _948.reset();
}

// The return type of this constant-false slot is a guess (bool).
bool WeaponBase::m196(sead::SafeString* out) {
    return false;
}

bool WeaponBase::m197(sead::SafeString* out) {
    return false;
}

bool WeaponBase::m217(sead::SafeString* out) {
    return false;
}

bool WeaponBase::m223(s32* out) {
    return false;
}

bool WeaponBase::m250(Actor* actor) {
    return false;
}

bool WeaponBase::isWeaponType0Or1Or2() const {
    return m231() || m232() || m233();
}

bool WeaponBase::m231() const {
    return getProfile() == "WeaponSmallSword";
}

bool WeaponBase::m232() const {
    return getProfile() == "WeaponLargeSword";
}

bool WeaponBase::m233() const {
    return getProfile() == "WeaponLargeSpear";
}

bool WeaponBase::isWeaponType4() const {
    return getProfile() == "WeaponShield";
}

bool WeaponBase::isWeaponType3() const {
    return getProfile() == "WeaponBow";
}

// NON_MATCHING: parameter-pack and SafeString temporary stack placement differs.
Actor* createWeaponND(const char* name, const sead::Matrix34f& matrix, f32 scale, sead::Heap* heap,
                      bool sleep_after_init, bool nd, s32 life, InstParamPack* params_in) {
    InstParamPack params;
    if (params_in)
        params = *params_in;
    ActorCreator::addScale(params, scale);
    params->add(life, "Life");
    if (nd)
        params->add(true, "@ND");
    auto* actor = ActorCreator::instance()->createActor(name, heap, &params, sleep_after_init, false);
    if (sead::DynamicCast<Actor>(actor)) {
        actor->setMatrix(matrix, nullptr);
    } else {
        if (actor)
            actor->deleteLater(BaseProc::DeleteReason::_0);
        actor = nullptr;
    }
    return actor;
}

void WeaponBase::requestCreateWeaponActor(const char* actor, const sead::Matrix34f& matrix,
                                          f32 scale, sead::Heap* heap,
                                          ksys::act::BaseProcHandle* handle, s32 life,
                                          ksys::act::InstParamPack* params_in, s32 task_lane_id) {
    ksys::act::InstParamPack params;
    if (params_in) {
        params = *params_in;
    }

    ksys::act::ActorCreator::addScale(params, scale);
    params->add(life, "Life");
    params->addMatrix(matrix);
    ksys::act::ActorCreator::instance()->requestCreateActor(actor, heap, handle, &params, nullptr,
                                                            task_lane_id);
}

uking::act::OptionalWeapon* WeaponBase::m162() {
    return sead::DynamicCast<uking::act::OptionalWeapon>(_958.getProc(nullptr, nullptr));
}

uking::act::OptionalWeapon* WeaponBase::m163() {
    return sead::DynamicCast<uking::act::OptionalWeapon>(_958.getProc(nullptr));
}

bool WeaponBase::m154() {
    ActorLinkConstDataAccess accessor;
    acquireActor(&_938, &accessor);
    return accessor.sub_7100D12E64();
}

void* WeaponBase::m221() {
    return nullptr;
}

void WeaponBase::m200() {
    sub_7100EE6AFC();
    _938.reset();
    _958.reset();
    _920 = 0xff;
}

}  // namespace ksys::act

namespace ksys::act::acc {

// inline-only in the original; name is a guess (same helper as in acc::Weapon / acc::Armor: the null test comes
// before the RTTI check).
static BaseProc* getProcIfActor(BaseProc* proc) {
    if (proc && sead::IsDerivedFrom<Actor>(proc))
        return proc;
    return nullptr;
}

inline ksys::act::WeaponBase* WeaponBase::getWeapon() const {
    auto* actor = static_cast<Actor*>(getProcIfActor(mProc));
    return sead::DynamicCast<ksys::act::WeaponBase>(actor);
}

bool WeaponBase::m153() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->m153() : false;
}

bool WeaponBase::isWeaponType0Or1Or2() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->isWeaponType0Or1Or2() : false;
}

bool WeaponBase::isWeaponType3() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->isWeaponType3() : false;
}

void WeaponBase::m167(sead::Vector3f* out) const {
    if (auto* weapon = getWeapon())
        weapon->m167(out);
    else
        *out = sead::Vector3f::zero;
}

void WeaponBase::m168(sead::Vector3f* out) const {
    if (auto* weapon = getWeapon())
        weapon->m168(out);
    else
        *out = sead::Vector3f::zero;
}

void WeaponBase::m169(sead::Vector3f* out) const {
    if (auto* weapon = getWeapon())
        weapon->m169(out);
    else
        *out = sead::Vector3f::zero;
}

void WeaponBase::m170(sead::Vector3f* out) const {
    if (auto* weapon = getWeapon())
        weapon->m170(out);
    else
        *out = sead::Vector3f::zero;
}

void WeaponBase::m171(sead::Vector3f* out) const {
    if (auto* weapon = getWeapon())
        weapon->m171(out);
    else
        *out = sead::Vector3f::zero;
}

void WeaponBase::m172(sead::Vector3f* out) const {
    if (auto* weapon = getWeapon())
        weapon->m172(out);
    else
        *out = sead::Vector3f::zero;
}

bool WeaponBase::m222() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->m222() : false;
}

bool WeaponBase::sub_7100EFA6B8() const {
    auto* weapon = getWeapon();
    if (weapon && !weapon->m159().isEmpty()) {
        if (!weapon->m161())
            return true;
        auto* optional_weapon = weapon->m162();
        return optional_weapon && !optional_weapon->mSpecialJobTypesMaskOverride.isOn(2);
    }
    return false;
}

bool WeaponBase::acquireParentActor(ActorLinkConstDataAccess* out) const {
    auto* weapon = getWeapon();
    return weapon ? ksys::act::acquireActor(&weapon->_938, out) : false;
}

bool WeaponBase::hasParentActor_() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->hasParentActor_() : false;
}

Actor* WeaponBase::getParentActor() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->getParentActor() : nullptr;
}

bool WeaponBase::m188() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->m188() : false;
}

bool WeaponBase::m186() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->m186() : false;
}

bool WeaponBase::m154() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->m154() : false;
}

bool WeaponBase::m155() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->m155() : false;
}

bool WeaponBase::m156() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->m156() : false;
}

bool WeaponBase::m223(s32* out) const {
    auto* weapon = getWeapon();
    if (weapon)
        return weapon->m223(out);
    *out = 0;
    return false;
}

// NON_MATCHING: the original selects `weapon + 0xa00` / null directly on the RTTI result (one csel); ours keeps the null test
// of the cast result and an extra csel
ModelBindInfo* WeaponBase::getBindInfo() const {
    auto* weapon = getWeapon();
    return weapon ? &weapon->_a00 : nullptr;
}

bool WeaponBase::sub_7100EFB338() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->mModelBindInfo != nullptr : false;
}

void WeaponBase::m228(BaseProc* proc) const {
    if (auto* weapon = getWeapon())
        weapon->m228(proc);
}

void WeaponBase::sub_7100EFB53C(gsys::Model* model) const {
    if (auto* weapon = getWeapon())
        weapon->sub_71011C5630(model);
}

bool WeaponBase::sub_7100EFB798() const {
    auto* weapon = getWeapon();
    return weapon ? weapon->_ab0 != 0 : false;
}

}  // namespace ksys::act::acc

namespace ksys::act {
void WeaponBase::onEnterDelete_() {
    Actor::onEnterDelete_();
}
}  // namespace ksys::act
