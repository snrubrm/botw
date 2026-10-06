#include "Game/AI/AI/aiAnimalLineOfSightSelector.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actWolfLink.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AnimalLineOfSightSelector::AnimalLineOfSightSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalLineOfSightSelector::~AnimalLineOfSightSelector() = default;

bool AnimalLineOfSightSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalLineOfSightSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AnimalLineOfSightSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalLineOfSightSelector::loadParams_() {
    getStaticParam(&mStartGear_s, "StartGear");
    getStaticParam(&mMinGear_s, "MinGear");
    getStaticParam(&mMaxGear_s, "MaxGear");
    getStaticParam(&mGearUpRestrictionFrames_s, "GearUpRestrictionFrames");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnimalLineOfSightSelector::gearDown() {
    const s32 gear = s32(sead::MathCalcCommon<f64>::clamp2(f64(*mMinGear_s), f64(_70 - 1), f64(*mMaxGear_s)));
    if (gear == _70)
        return;
    if (auto* wolf = sead::DynamicCast<act::WolfLink>(mActor))
        wolf->_1698 |= 0x100;
    _70 = gear;
    changeToGear(gear);
}

void AnimalLineOfSightSelector::gearUp() {
    const s32 gear = s32(sead::MathCalcCommon<f64>::clamp2(f64(*mMinGear_s), f64(_70 + 1), f64(*mMaxGear_s)));
    if (gear == _70)
        return;
    if (gear == *mMaxGear_s) {
        if (auto* wolf = sead::DynamicCast<act::WolfLink>(mActor))
            wolf->_1698 &= ~0x100;
    }
    _70 = gear;
    changeToGear(gear);
}

void AnimalLineOfSightSelector::changeToGear(s32 gear) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    switch (gear) {
    case 1:
        changeChild("Gear1", &pack);
        break;
    case 2:
        changeChild("Gear2", &pack);
        break;
    case 3:
        changeChild("Gear3", &pack);
        break;
    case 4:
        changeChild("Gear4", &pack);
        break;
    }
    _6c = true;
    _60 = ksys::Timer(*mGearUpRestrictionFrames_s, *mGearUpRestrictionFrames_s);
}

}  // namespace uking::ai
