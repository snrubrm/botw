#include "Game/AI/Action/actionSiteBossLswordTornadoAttack.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::action {

SiteBossLswordTornadoAttack::SiteBossLswordTornadoAttack(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

SiteBossLswordTornadoAttack::~SiteBossLswordTornadoAttack() = default;

bool SiteBossLswordTornadoAttack::init_(sead::Heap* heap) {
    _58.sub_710073E730(heap, 2, mActor);
    return true;
}

void SiteBossLswordTornadoAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    _4c.reset(*mEndTime_s);
    _58._8 = *mVacuumAcc_s;
    _58._c = *mVacuumMaxSpeed_s;
    _58._10 = *mVacuumBaseWeight_s;
    _48 = false;
    mFlags.reset(Flag::Changeable);
}

void SiteBossLswordTornadoAttack::leave_() {
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->getActorPartsActor("DrawingFlame").hasProc()) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&enemy->getActorPartsActor("DrawingFlame"), &accessor);
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
    }
    sub_7100739918(mActor);
}

void SiteBossLswordTornadoAttack::loadParams_() {
    getStaticParam(&mEndTime_s, "EndTime");
    getStaticParam(&mVacuumAcc_s, "VacuumAcc");
    getStaticParam(&mVacuumMaxSpeed_s, "VacuumMaxSpeed");
    getStaticParam(&mVacuumAngle_s, "VacuumAngle");
    getStaticParam(&mVacuumBaseWeight_s, "VacuumBaseWeight");
}

void SiteBossLswordTornadoAttack::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
