#include "Game/AI/AI/aiHorseNotRidden.h"
#include <random/seadGlobalRandom.h>
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

void HorseNotRidden::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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
