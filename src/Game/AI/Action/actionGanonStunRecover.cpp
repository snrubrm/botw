#include "Game/AI/Action/actionGanonStunRecover.h"
#include "Game/Actor/actLastBoss.h"

namespace uking::action {

GanonStunRecover::GanonStunRecover(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonStunRecover::~GanonStunRecover() = default;

bool GanonStunRecover::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonStunRecover::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("Down_End", false, 0, 0, -1.0f);
    if (auto* boss = sead::DynamicCast<act::LastBoss>(mActor)) {
        boss->stunEnd();
        const auto* life = boss->getLife();
        if (!life || *life != 0)
            boss->_14e8.setBit(3);
        else
            setFinished();
    }
    _1c = false;
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
