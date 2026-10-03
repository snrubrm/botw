#include "Game/gameMotorcycleMgr.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(MotorcycleMgr)

MotorcycleMgr::MotorcycleMgr() = default;

void MotorcycleMgr::setMotorcycleEnergyIter(ksys::gdt::Manager::ReinitEvent*) {
    mEnergyHandle = ksys::gdt::Manager::instance()->getF32Handle("Motorcycle_Energy");
}

void MotorcycleMgr::clampMotorcycleEnergy() {
    if (!ksys::gdt::Manager::instance()->getF32(mEnergyHandle, &mEnergy)) {
        mEnergy = 1000.0f;
        return;
    }
    mEnergy = sead::Mathf::clamp(mEnergy, 0.0f, 1000.0f);
}

bool MotorcycleMgr::checkIsActorRidingMotorcycle(ksys::act::Actor* actor) {
    auto* ride_info = actor->getPlayerRideInfo();
    if (ride_info && mProcLink.hasProc() && ride_info->_18 == mProcLink)
        return true;
    return false;
}

bool MotorcycleMgr::x(ksys::act::BaseProc* actor) {
    return actor && mProcLink.hasProcById(actor);
}

bool MotorcycleMgr::x_0() {
    return mProcLink.hasProc();
}

bool MotorcycleMgr::hasHavokQueryStarted() const {
    return _17e == 1;
}

bool MotorcycleMgr::sub_710067B63C(sead::Vector3f* pos) {
    if (!mProcLink.hasProc())
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&mProcLink, &accessor);
    const auto& mtx = accessor.getActorMtx();
    pos->x = mtx(0, 3);
    pos->y = mtx(1, 3);
    pos->z = mtx(2, 3);
    return true;
}

bool MotorcycleMgr::sub_710067B6BC(sead::Matrix34f* mtx) {
    if (!mProcLink.hasProc())
        return false;
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&mProcLink, &accessor);
    accessor.sub_7100D11860(mtx);
    return true;
}

void MotorcycleMgr::sub_710067AFB0() {
    if (auto* actor = sead::DynamicCast<ksys::act::Actor>(mProcLink.getProc(nullptr)))
        actor->setFlag(ksys::act::Actor::ActorFlag::_1c, true);
}

void MotorcycleMgr::effectFadeXLink() {
    if (_148.sub_7101241B6C())
        _148.fadeXLink();
}

}  // namespace uking
