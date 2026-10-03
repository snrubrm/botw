#include "Game/AI/Action/actionLevelFlyRise.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actCCAccessor.h"

namespace uking::action {

LevelFlyRise::LevelFlyRise(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LevelFlyRise::~LevelFlyRise() = default;

bool LevelFlyRise::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LevelFlyRise::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LevelFlyRise::leave_() {
    _9c.resetMotionType(mActor->getCharacterController());
}

void LevelFlyRise::loadParams_() {
    getStaticParam(&mHeight_s, "Height");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mASName_s, "ASName");
}

void LevelFlyRise::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
