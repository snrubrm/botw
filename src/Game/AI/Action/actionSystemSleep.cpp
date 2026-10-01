#include "Game/AI/Action/actionSystemSleep.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

SystemSleep::SystemSleep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SystemSleep::~SystemSleep() = default;

bool SystemSleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SystemSleep::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
}

void SystemSleep::leave_() {
    ksys::act::ai::Action::leave_();
}

void SystemSleep::loadParams_() {}

void SystemSleep::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
