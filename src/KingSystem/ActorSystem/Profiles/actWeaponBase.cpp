#include "KingSystem/ActorSystem/Profiles/actWeaponBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Actor/actOptionalWeapon.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectBow.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLargeSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSmallSword.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSpear.h"

namespace ksys::act {

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

}  // namespace ksys::act
