#include "Game/AI/Action/actionHorseRideTurnCommand.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

HorseRideTurnCommand::HorseRideTurnCommand(const InitArg& arg) : HorseRideCommand(arg) {}

HorseRideTurnCommand::~HorseRideTurnCommand() = default;

bool HorseRideTurnCommand::init_(sead::Heap* heap) {
    return HorseRideCommand::init_(heap);
}

void HorseRideTurnCommand::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseRideCommand::enter_(params);
}

void HorseRideTurnCommand::leave_() {
    HorseRideCommand::leave_();
}

void HorseRideTurnCommand::loadParams_() {
    HorseRideCommand::loadParams_();
}

void HorseRideTurnCommand::calc_() {
    HorseRideCommand::calc_();
}

bool HorseRideTurnCommand::m32(ksys::act::Actor* actor) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f dir = *mTargetPos_d - pos;
    dir.normalize();
    {
        sead::ScopedLock<sead::CriticalSection> lock(&_58.mLock);
        _58._58 = dir;
    }
    return _58.sub_710070DC38(actor, true);
}

}  // namespace uking::action
