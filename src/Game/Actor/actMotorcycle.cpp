#include "Game/Actor/actMotorcycle.h"
#include <basis/seadNew.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
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

void Motorcycle::setLeftStickX(f32 x) {
    _b90.sub_71002C8918(x);
    _b9c.motorcycleStickControlStuff(x);
    _bb4 = x;
}

void Motorcycle::setLeftStickY(f32 y) {
    _ba8.motorcycleStickControlStuff(y);
}

void Motorcycle::sub_7100077830() {
    if (_f88.isOnBit(20))
        return;
    _f88.set(0x100000);
    _bb8->changeMotionType(ksys::phys::MotionType::Fixed);
    _dd0->_0->changeMotionType(ksys::phys::MotionType::Fixed);
    _dd8->_0->changeMotionType(ksys::phys::MotionType::Fixed);
}

void Motorcycle::sub_7100072204() {
    if (!_f88.isOnBit(20))
        return;
    _f88.reset(0x100000);
    _bb8->changeMotionType(ksys::phys::MotionType::Dynamic);
    _dd0->_0->changeMotionType(ksys::phys::MotionType::Dynamic);
    _dd8->_0->changeMotionType(ksys::phys::MotionType::Dynamic);
}

void Motorcycle::sub_710007A798(const sead::Vector3f& direction) {
    _f88.set(0x10000000);
    _f70.x = direction.x;
    _f70.y = direction.y;
    _f70.z = direction.z;
    if (_f70.y != 0.0f) {
        _f70.y = 0.0f;
        _f70.normalize();
    }
}

f32 Motorcycle::sub_710007A4A8() const {
    if (_f88.isOnAll(0x2000020000))
        return 0.0f;
    return _e4c;
}

bool Motorcycle::sub_710007A6E8() const {
    return _f88.isOnBit(25) && _f88.isOn(0x300);
}

void Motorcycle::sub_710007A74C(f32 value) {
    sead::ScopedLock<sead::CriticalSection> lock(&_10e8);
    _1128 = true;
    _112c = value;
}

void Motorcycle::sub_710007A928() {
    _f88.set(0x100000000000);
    x_7();
}

void Motorcycle::sub_710007A938() {
    _f88.reset(0x100000000000);
    x_7();
}

f32 Motorcycle::sub_710007A958() const {
    return sead::Mathf::clamp(_e74 / 42.5f, -1.0f, 1.0f) * 20.0f;
}

f32 Motorcycle::sub_710007A994() const {
    return sead::Mathf::clamp(_e78 / -45.0f, -1.0f, 1.0f);
}

f32 Motorcycle::sub_710007ABA4() const {
    if (_f10 == 1 || _f10 == 3)
        return _ba8._8;
    return 0.0f;
}

sead::Vector3f Motorcycle::sub_710007F868() const {
    sead::Vector3f center;
    _bb8->getCenterOfMassInWorld(&center);
    return center;
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
