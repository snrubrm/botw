#include "Game/AI/Behavior/behaviorAnimalNeckRotate.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::behavior {

AnimalNeckRotate::AnimalNeckRotate(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

AnimalNeckRotate::~AnimalNeckRotate() = default;

bool AnimalNeckRotate::m6(sead::Heap* heap) {
    return true;
}

void AnimalNeckRotate::m9() {
    if (auto* unit = sub_71007398C0(mActor)) {
        sub_71005DB3EC(mActor);
        unit->sub_7100D8A830(0.0f, false);
        unit->_9c = unit->_98;
        unit->_a4 = unit->_a0;
    }
}

void AnimalNeckRotate::loadParams() {
    getStaticParam(&mLimitAngleLR_s, "LimitAngleLR");
    getStaticParam(&mRotRate_s, "RotRate");
    getStaticParam(&mResetRotRate_s, "ResetRotRate");
    getStaticParam(&mIsUseParentRotOffset_s, "IsUseParentRotOffset");
}

}  // namespace uking::behavior
