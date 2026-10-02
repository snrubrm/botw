#include "Game/AI/Action/actionEmitElectricWaterBall.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

EmitElectricWaterBall::EmitElectricWaterBall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EmitElectricWaterBall::~EmitElectricWaterBall() = default;

bool EmitElectricWaterBall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EmitElectricWaterBall::enter_(ksys::act::ai::InlineParamPack* params) {
    if (_30.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_30, &accessor);
        if (accessor.isStateSleep())
            accessor.setProperties(mActor->getMtx(), nullptr, nullptr, nullptr, false, 0, -1);
    }
    setFinished();
}

void EmitElectricWaterBall::leave_() {
    ksys::act::ai::Action::leave_();
}

void EmitElectricWaterBall::loadParams_() {
    getStaticParam(&mActorName_s, "ActorName");
}

void EmitElectricWaterBall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
