#include "Game/AI/AI/aiHorseNotRidden.h"
#include "Game/Actor/actHorseBase.h"

namespace uking::ai {

// NON_MATCHING: the address of _c0 is computed before the memset of the parameters (register
// allocation)
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
    getStaticParam(&mEscapeCountThreshold_s, "EscapeCountThreshold");
    getStaticParam(&mNearHorseAssociationDistance_s, "NearHorseAssociationDistance");
    getStaticParam(&mEscapeDelayFramesMin_s, "EscapeDelayFramesMin");
    getStaticParam(&mEscapeDelayFramesMax_s, "EscapeDelayFramesMax");
    getStaticParam(&mCallDelayFrames_s, "CallDelayFrames");
    getStaticParam(&mAttackFrontDistance_s, "AttackFrontDistance");
    getStaticParam(&mAttackFrontAngleCos_s, "AttackFrontAngleCos");
    getStaticParam(&mAttackBackDistance_s, "AttackBackDistance");
    getStaticParam(&mAttackBackAngleCos_s, "AttackBackAngleCos");
    getStaticParam(&mAttackDefinitelyDistance_s, "AttackDefinitelyDistance");
    getStaticParam(&mAttackIntervalFrames_s, "AttackIntervalFrames");
    getStaticParam(&mMoveAttackCLOSDistanceByRadius_s, "MoveAttackCLOSDistanceByRadius");
    getStaticParam(&mCarriedItemCosThresholdForEat_s, "CarriedItemCosThresholdForEat");
    getStaticParam(&mStaggerVelocityThreshold_s, "StaggerVelocityThreshold");
    getStaticParam(&mCarriedItemPosRTYOffset_s, "CarriedItemPosRTYOffset");
    getStaticParam(&mCarriedItemPosRTYWidth_s, "CarriedItemPosRTYWidth");
    getDynamicParam(&mChildSelectAtFirst_d, "ChildSelectAtFirst");
}

}  // namespace uking::ai
