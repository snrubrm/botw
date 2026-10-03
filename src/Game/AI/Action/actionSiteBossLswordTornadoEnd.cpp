#include "Game/AI/Action/actionSiteBossLswordTornadoEnd.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::action {

SiteBossLswordTornadoEnd::SiteBossLswordTornadoEnd(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossLswordTornadoEnd::~SiteBossLswordTornadoEnd() = default;

bool SiteBossLswordTornadoEnd::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SiteBossLswordTornadoEnd::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.reset(Flag::Changeable);
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        boss->x_1(true, true, false);
        playAS("Chemical_Loop", false, 3, 0, -1.0f);
        act::SiteBoss::x_2(boss, mActor);
    }
}

void SiteBossLswordTornadoEnd::leave_() {
    ksys::act::ai::Action::leave_();
}

void SiteBossLswordTornadoEnd::loadParams_() {
    getStaticParam(&mIsUseTornadoAttack_s, "IsUseTornadoAttack");
    getDynamicParam(&mAttackActor_d, "AttackActor");
}

void SiteBossLswordTornadoEnd::calc_() {
    if (isFinishedAS(0, 0))
        setFinished();
}

}  // namespace uking::action
