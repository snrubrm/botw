#include "Game/AI/Action/actionEmitElectricWaterBall.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorChemicals.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::action {

EmitElectricWaterBall::EmitElectricWaterBall(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EmitElectricWaterBall::~EmitElectricWaterBall() {
    if (_30.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&_30, &accessor);
        if (accessor.hasProc() && accessor.isStateSleep())
            accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
}

// NON_MATCHING: the short-circuit fallback naturally emits a tail call.
bool EmitElectricWaterBall::init_(sead::Heap* heap) {
    return sub_71001058D0() || sub_71005D6D10();
}

// NON_MATCHING: temporary parameter values and strings use different stack slots.
bool EmitElectricWaterBall::sub_71001058D0() {
    ksys::act::InstParamPack params;
    params->add(0, "AttackPower");
    params->add(1.0f, "ScaleTime");
    params->add(0.0f, "Range");
    ksys::act::ActorCreator::addScale(params, 1.0f);
    params->addMatrix(mActor->getMtx());

    auto* actor = sead::DynamicCast<ksys::act::Actor>(
        ksys::act::ActorCreator::instance()->createActor(
            "ElectricWaterBall", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
            &params, false, false));
    if (!actor)
        return false;

    if (auto* chemical = actor->sub_71011D8A44(0)) {
        if (auto* container = mActor->getChemicalContainer()) {
            chemical->_190 = 1.0f;
            chemical->sub_7100D8EAB4(container->_68);
        }
    }
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(actor)) {
        bullet->sub_71000048BC(mActor);
        bullet->sub_710000497C(mActor);
    }
    _30.acquire(actor, false);
    actor->sleep(ksys::act::BaseProc::SleepWakeReason::_0);
    return true;
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
