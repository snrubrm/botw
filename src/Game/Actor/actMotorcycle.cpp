#include "Game/Actor/actMotorcycle.h"
#include <basis/seadNew.h>
#include "Game/Actor/actRideable.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"

namespace uking::act {

MotorcycleStruct1::MotorcycleStruct1() = default;

ksys::act::BaseProc* Motorcycle::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Motorcycle(arg);
}

// NON_MATCHING: the members are placeholders (ctor and dtor not decompiled)
Motorcycle::~Motorcycle() = default;

bool Motorcycle::shouldUnload(s32* a1) {
    s32 reason = 0;
    return shouldUnloadBecauseOfDistance(&reason);
}

bool Motorcycle::m81(const ksys::Message& message) {
    if (DynamicActor::m81(message))
        return true;
    return _1648->m10(message);
}

Motorcycle::InitResult Motorcycle::init_() {
    searchModelHandles();
    return InitResult::Ok;
}

void Motorcycle::searchModelHandles() {
    _11b0.mWheel_F.search(mModel, "Wheel_F");
    _11b0.mWheel_R.search(mModel, "Wheel_R");
    _11b0.mSwingArm_F.search(mModel, "SwingArm_F");
    _11b0.mSwingArm_R.search(mModel, "SwingArm_R");
    _11b0.mSuspension_F.search(mModel, "Suspension_F");
    _11b0.mSuspension_R.search(mModel, "Suspension_R");
    _11b0.mHandle.search(mModel, "Handle");
    _11b0.mBody_1.search(mModel, "Body_1");
    _11b0.mHead_A.search(mModel, "Head_A");
    _11b0.mSaddle_Root.search(mModel, "Saddle_Root");
    _11b0.mSeat_Front.search(mModel, "Seat_Front");
    _11b0.mSeat_Rear.search(mModel, "Seat_Rear");
    _11b0.mRearCowl_A.search(mModel, "RearCowl_A");
    _11b0.mSeatArm_Front.search(mModel, "SeatArm_Front");
    _11b0.mSeatArm_Rear.search(mModel, "SeatArm_Rear");
    _11b0._350 = 0;
}

void Motorcycle::m88() {
    Actor::m88();
    mPreviousPos += _e5c * (_e58 * 0.1f);
}

void Motorcycle::x_1(sead::Vector3f* center) const {
    _bb8->getCenterOfMassInWorld(center);
}

sead::Vector3f Motorcycle::x_4() const {
    if (!_bb8)
        return {0.0f, 1.0f, 0.0f};
    const sead::Matrix34f mtx = _bb8->getTransform();
    return {mtx(0, 1), mtx(1, 1), mtx(2, 1)};
}

Motorcycle::IsSpecialJobTypeResult Motorcycle::isSpecialJobType_(ksys::act::JobType type) {
    const auto result = DynamicActor::isSpecialJobType_(type);
    return IsSpecialJobTypeResult(_1648->sub_7100E8BB4C(int(result)));
}

void Motorcycle::onPreDeleteStart_(PrepareArg& arg) {
    DynamicActor::onPreDeleteStart_(arg);
}

bool Motorcycle::x_6() const {
    return _f88.isOnBit(11);
}

f32 Motorcycle::x_8() const {
    if (_f10 == 5 || _f10 == 6)
        return _e00 / -35.0f;
    return 0.0f;
}

void Motorcycle::x_11() {
    _f88.set(0x40000);
}

void Motorcycle::x_5() {
    _f88.set(0x800000);
}

void Motorcycle::setAccelMaybe(f32 accel) {
    const f32 prev = _e3c;
    if (accel > 0.0f && prev == 0.0f)
        _10a4 = 1;
    else if (accel == 0.0f && prev == 1.0f)
        _10a4 = 2;
    _e3c = accel;
}

void Motorcycle::crashMaybe(bool crash) {
    _f88.reset(1);
    if (crash) {
        _f88.set(0x4000000);
        x_7();
    } else {
        _f88.reset(0x4000000);
    }
    _df0 = 0;
}

}  // namespace uking::act
