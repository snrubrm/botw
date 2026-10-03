#include "Game/gameMotorcycleMgr.h"
#include <math/seadMathCalcCommon.h>
#include "Game/Actor/actHorseRideInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleShape.h"
#include "KingSystem/Physics/RigidBody/Shape/Capsule/physCapsuleRigidBody.h"
#include "KingSystem/Physics/System/physHavokAI.h"

namespace uking {

SEAD_SINGLETON_DISPOSER_IMPL(MotorcycleMgr)

MotorcycleMgr::MotorcycleMgr() : _148() {}

// NON_MATCHING: register allocation / scheduling (the constant 1.0f and 1 swap registers; the
// capsule parameter stores are scheduled differently)
void MotorcycleMgr::init(sead::Heap* heap) {
    mEnergyHandle = ksys::gdt::Manager::instance()->getF32Handle("Motorcycle_Energy");
    ksys::gdt::Manager::instance()->addReinitCallback(mSlot);

    _c8 = 0;
    _17e = 0;
    _178 = 0;
    mEnergy = 1000.0f;

    ksys::phys::CapsuleParam param;
    param.contact_layer = ksys::phys::ContactLayer::EntityObject;
    param.motion_type = ksys::phys::MotionType::Fixed;
    param.vertex_a = {0.0f, 0.97f, -0.9f};
    param.vertex_b = {0.0f, 0.97f, 1.0f};
    param.radius = 0.97f;
    param.name = "MotorcycleShapeCast";
    _d0 = ksys::phys::CapsuleRigidBody::make(&param, heap);
}

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

MotorcycleMgr::~MotorcycleMgr() {
    delete _d0;
    if (mProcHandle.isAllocatedOrFailed())
        mProcHandle.deleteProc();
    if (_d8)
        ksys::phys::HavokAI::instance()->destroyQuery(_d8);
    if (auto* gdt_mgr = ksys::gdt::Manager::instance())
        gdt_mgr->removeReinitCallback(mSlot);

    if (_168.getEvent() && _168.getEvent()->getCreateId() == _168.getCreateId()) {
        _168.fade();
        _168.reset();
    }
    if (_148.sub_7101241B6C()) {
        if (_148.mELink.getEvent() &&
            _148.mELink.getEvent()->getCreateId() == _148.mELink.getCreateId()) {
            _148.mELink.fade();
            _148.mELink.reset();
        }
        if (_148.mSLink.getEvent() &&
            _148.mSLink.getEvent()->getCreateId() == _148.mSLink.getCreateId()) {
            _148.mSLink.fade();
            _148.mSLink.reset();
        }
        _148.fadeXLink();
    }
}

}  // namespace uking
