#include "Game/AI/AI/aiSimpleLiftableDLC.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

SimpleLiftableDLC::SimpleLiftableDLC(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleLiftableDLC::~SimpleLiftableDLC() = default;

bool SimpleLiftableDLC::init_(sead::Heap* heap) {
    _40.x();
    _80.x();
    return true;
}

void SimpleLiftableDLC::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::disableAttClient(mActor, "Grab");
    _d0 = false;
    _80.x();
    sub_710056EA38();
}

void SimpleLiftableDLC::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleLiftableDLC::loadParams_() {
    getStaticParam(&mScaleToLiftUp_s, "ScaleToLiftUp");
}

}  // namespace uking::ai
