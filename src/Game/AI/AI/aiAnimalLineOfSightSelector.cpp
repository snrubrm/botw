#include "Game/AI/AI/aiAnimalLineOfSightSelector.h"
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
