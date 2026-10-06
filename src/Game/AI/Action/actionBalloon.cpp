#include "Game/AI/Action/actionBalloon.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

Balloon::Balloon(const InitArg& arg) : BalloonBase(arg) {}

Balloon::~Balloon() {
    if (_118.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(&_118, &accessor))
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    _110 = nullptr;
}

bool Balloon::init_(sead::Heap* heap) {
    return BalloonBase::init_(heap);
}

void Balloon::enter_(ksys::act::ai::InlineParamPack* params) {
    BalloonBase::enter_(params);
}

void Balloon::leave_() {
    BalloonBase::leave_();
}

void Balloon::loadParams_() {
    BalloonBase::loadParams_();
    getStaticParam(&mLength_s, "Length");
    getStaticParam(&mRopeActorName_s, "RopeActorName");
    getMapUnitParam(&mRopeHungActOffset_m, "RopeHungActOffset");
}

void Balloon::calc_() {
    BalloonBase::calc_();
}

}  // namespace uking::action
