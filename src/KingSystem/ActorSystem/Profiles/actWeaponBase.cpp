#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include <prim/seadScopedLock.h>
#include "Game/Actor/actOptionalWeapon.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBow.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLargeSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSmallSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSpear.h"

namespace ksys::act {

// NON_MATCHING: D1 / D0 and their thunks: the original keeps &_840 and &_880 in callee-saved registers across the link resets (we recompute them)
WeaponBase::~WeaponBase() = default;

bool WeaponBase::m86() {
    ActorConstDataAccess accessor;
    acquireActor(&_938, &accessor);
    if (accessor.checkFlag2B())
        return false;
    return Actor::m86();
}

void WeaponBase::m92(phys::RigidBody* body) {
    if (hasParentActor())
        return;
    Actor::m92(body);
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

// NON_MATCHING: x0/x1 materialised in the other order for the BaseProcLink copy
void WeaponBase::m207() {
    _948 = _938;
    setFlag(ActorFlag::_2c, true);
}

void WeaponBase::m208() {
    _948.reset();
}

// The return types of these constant-false slots are guesses (bool).
bool WeaponBase::m196() {
    return false;
}

bool WeaponBase::m197() {
    return false;
}

bool WeaponBase::m217() {
    return false;
}

bool WeaponBase::m223() {
    return false;
}

bool WeaponBase::m250() {
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

Actor* WeaponBase::m162() {
    return sead::DynamicCast<uking::act::OptionalWeapon>(_958.getProc(nullptr, nullptr));
}

Actor* WeaponBase::m163() {
    return sead::DynamicCast<uking::act::OptionalWeapon>(_958.getProc(nullptr));
}

bool WeaponBase::m154() {
    ActorConstDataAccess accessor;
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