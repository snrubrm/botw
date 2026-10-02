#include "Game/AI/Action/actionGerudoQueenWakeBoardReady.h"
#include "KingSystem/XLink/xlinkActorUtil.h"

namespace uking::action {

GerudoQueenWakeBoardReady::GerudoQueenWakeBoardReady(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

GerudoQueenWakeBoardReady::~GerudoQueenWakeBoardReady() = default;

bool GerudoQueenWakeBoardReady::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GerudoQueenWakeBoardReady::enter_(ksys::act::ai::InlineParamPack* params) {
    _20 = ksys::eft::searchAndEmitELink(mActor, "SafetyZone");
    playAS("WakeBoarding", false, 0, 0, -1.0f);
}

void GerudoQueenWakeBoardReady::leave_() {
    ksys::act::ai::Action::leave_();
}

void GerudoQueenWakeBoardReady::loadParams_() {}

void GerudoQueenWakeBoardReady::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
