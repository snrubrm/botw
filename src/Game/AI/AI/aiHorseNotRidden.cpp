#include "Game/AI/AI/aiHorseNotRidden.h"
#include "Game/Actor/actHorseBase.h"

namespace uking::ai {

HorseNotRidden::HorseNotRidden(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

// NON_MATCHING: the original calls gdt::Manager::removeReinitCallback(_128) first when the slot is
// connected (sead's Slot::mConnectedToDelegateEvent is private in our sead headers)
HorseNotRidden::~HorseNotRidden() = default;

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
