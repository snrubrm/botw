#include "Game/Actor/AI/aiHorseNotRidden.h"
#include <random/seadGlobalRandom.h>
#include <limits>
#include "Game/Actor/actRideable.h"
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectHorse.h"
#include "Game/Actor/actHorseBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

HorseNotRidden::HorseNotRidden(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseNotRidden::~HorseNotRidden() {
    if (_128.isConnected())
        ksys::gdt::Manager::instance()->removeReinitCallback(_128);
}

bool HorseNotRidden::init_(sead::Heap* heap) {
    auto* horse = sead::DynamicCast<act::HorseBase>(mActor);
    if (horse && horse->x() == 9) {
        auto* gdm = ksys::gdt::Manager::instance();
        _198 = gdm->getBoolHandle("AnimalMaster_Appearance");
        ksys::gdt::Manager::instance()->addReinitCallback(_128);
    }
    return true;
}

void HorseNotRidden::setAnimalMasterAppearanceFlagIdx(ksys::gdt::Manager::ReinitEvent* event) {
    _198 = ksys::gdt::Manager::instance()->getBoolHandle("AnimalMaster_Appearance");
}

// NON_MATCHING: awareness flag selection and child/ride-state branches use different scheduling.
void HorseNotRidden::enter_(ksys::act::ai::InlineParamPack* params) {
    _1a9.makeAllZero();
    if (mActor->getParam()->getRes().mGParamList->getHorse()->mIsDecoy.ref()) {
        _1a9.setBit(Flag(Flag::_4));
        changeChild("待機(静止)");
        return;
    }
    _c0.sub_710071EE1C();
    _1a9.changeBit(Flag(Flag::_0), act::sub_7100E815C8(mActor->getAwareness()));
    _120 = -1;
    _f0 = std::numeric_limits<f32>::infinity();
    _108 = std::numeric_limits<f32>::infinity();
    const f32 nan = std::numeric_limits<f32>::quiet_NaN();
    _10c.set(nan, nan, nan);
    _19c.set(0.0f, 0.0f, 0.0f);
    auto* rideable = mActor->getHorseOptionsMaybe();
    if (*mParams.mChildSelectAtFirst_d == 0) {
        changeChild("逃走");
        _1a9.setBit(Flag(Flag::_1));
        return;
    }
    if (*mParams.mChildSelectAtFirst_d == 1) {
        changeChild("ダメージリアクション");
        return;
    }
    if (rideable && rideable->sub_7100E8BFF4()) {
        if (auto* horse = sead::DynamicCast<act::HorseBase>(mActor)) {
            horse->sub_7100E6BEC0(true);
            _1a9.setBit(Flag(Flag::_5));
        }
        changeChild("待機(静止)");
        return;
    }
    if (mActor->get1a0() || (mActor->getMapObject() &&
        mActor->getMapObject()->getFlags0().isOn(ksys::map::Object::Flag0::_20000))) {
        changeChild("待機(静止)");
        return;
    }
    if (rideable && rideable->Unk_7100e8b2b8::_c.load() == 1) {
        const act::Rideable::Gear gear = rideable->_18._b ? rideable->_18._b : rideable->_18._9;
        if (int(gear) != 0) {
            changeChild("待機(静止)");
            return;
        }
    }
    changeChild("うろつく");
}

void HorseNotRidden::leave_() {
    ksys::act::ai::Ai::leave_();
}

// NON_MATCHING: the original switch is a jump table over 0x3800001..0x380001f (a fourth case we cannot see; ours is a
// compare chain), it reads both actors' x / z before BaseProcLink::acquire (ours subtracts first), and copies the
// 12-byte payload as z, then x/y (ours: three floats).
bool HorseNotRidden::handleMessage_(const ksys::Message* message) {
    switch (message->getType()) {
    case 0x3800001: {
        if (auto* horse = sead::DynamicCast<act::HorseBase>(mActor))
            horse->sub_7100E6C094(true);
        auto* target = static_cast<ksys::act::Actor*>(message->getUserData());
        const sead::Vector2f diff{mActor->getMtx().m[0][3] - target->getMtx().m[0][3],
                                  mActor->getMtx().m[2][3] - target->getMtx().m[2][3]};
        _f8.acquire(target, false);
        _f0 = *mParams.mCallDelayFrames_s + diff.length() / 11.0f;
        return true;
    }
    case 0x3800010:
        _10c = *static_cast<const sead::Vector3f*>(message->getUserData());
        _108 = sead::GlobalRandom::instance()->getF32Range(*mParams.mEscapeDelayFramesMin_s,
                                                           *mParams.mEscapeDelayFramesMax_s);
        return true;
    case 0x3800011:
        return true;
    default:
        return false;
    }
}

void HorseNotRidden::loadParams_() {
    getStaticParam(&mParams.mEscapeCountThreshold_s, "EscapeCountThreshold");
    getStaticParam(&mParams.mNearHorseAssociationDistance_s, "NearHorseAssociationDistance");
    getStaticParam(&mParams.mEscapeDelayFramesMin_s, "EscapeDelayFramesMin");
    getStaticParam(&mParams.mEscapeDelayFramesMax_s, "EscapeDelayFramesMax");
    getStaticParam(&mParams.mCallDelayFrames_s, "CallDelayFrames");
    getStaticParam(&mParams.mAttackFrontDistance_s, "AttackFrontDistance");
    getStaticParam(&mParams.mAttackFrontAngleCos_s, "AttackFrontAngleCos");
    getStaticParam(&mParams.mAttackBackDistance_s, "AttackBackDistance");
    getStaticParam(&mParams.mAttackBackAngleCos_s, "AttackBackAngleCos");
    getStaticParam(&mParams.mAttackDefinitelyDistance_s, "AttackDefinitelyDistance");
    getStaticParam(&mParams.mAttackIntervalFrames_s, "AttackIntervalFrames");
    getStaticParam(&mParams.mMoveAttackCLOSDistanceByRadius_s, "MoveAttackCLOSDistanceByRadius");
    getStaticParam(&mParams.mCarriedItemCosThresholdForEat_s, "CarriedItemCosThresholdForEat");
    getStaticParam(&mParams.mStaggerVelocityThreshold_s, "StaggerVelocityThreshold");
    getStaticParam(&mParams.mCarriedItemPosRTYOffset_s, "CarriedItemPosRTYOffset");
    getStaticParam(&mParams.mCarriedItemPosRTYWidth_s, "CarriedItemPosRTYWidth");
    getDynamicParam(&mParams.mChildSelectAtFirst_d, "ChildSelectAtFirst");
}

}  // namespace uking::ai
