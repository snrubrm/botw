#include "Game/AI/Action/actionGanonStunRecover.h"
#include "Game/Actor/actLastBoss.h"

namespace uking::action {

GanonStunRecover::GanonStunRecover(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonStunRecover::~GanonStunRecover() = default;

bool GanonStunRecover::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonStunRecover::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void GanonStunRecover::leave_() {
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
        boss->stunEnd();
        boss->_14e8.resetBit(3);
    }
}

void GanonStunRecover::loadParams_() {}

void GanonStunRecover::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
