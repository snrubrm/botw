#include "Game/Actor/actMotorcycle.h"
#include <basis/seadNew.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include "Game/Actor/actRideable.h"
#include "Game/gameMaskController.h"
#include "Game/gameMotorcycleMgr.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectMotorcycle.h"
#include "KingSystem/System/VFR.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actTag.h"
#include "KingSystem/Physics/System/physNavMeshCharacter.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Physics/Constraint/physConstraint.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Utils/SafeDelete.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::act {

void MotorcycleStruct0::sub_710006C270() {
    f32 rate = _4;
    if (rate < 0.0f) {
        rate = 1000.0f /
               (_1a8->getParam()->getRes().mGParamList->getMotorcycle()->mFullEnergyLastSec.ref() *
                30.0f);
        _4 = rate;
    }
    if (_48 > 0.0f) {
        auto* mgr = MotorcycleMgr::instance();
        mgr->mEnergy -= rate * ksys::VFR::instance()->getDeltaFrame();
        mgr->mEnergy = sead::Mathf::clampMin(mgr->mEnergy, 0.0f);
    }
    if (!(MotorcycleMgr::instance()->mEnergy > 0.0f))
        _19e = true;
}

MotorcycleStruct1::MotorcycleStruct1() = default;
MotorcycleStruct1::~MotorcycleStruct1() = default;

MotorcycleUserTag::~MotorcycleUserTag() = default;

void MotorcycleUserTag::onImpulse(ksys::phys::RigidBody* body_a, ksys::phys::RigidBody* body_b,
                                  f32 impulse_a) {
    Entry* entry = nullptr;
    for (auto& e : mEntries) {
        if (e.body == body_a)
            entry = &e;
    }
    if (!entry)
        return;

    if (impulse_a >= 100.0f) {
        if (auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(body_b->getUserTag())) {
            ksys::act::ActorConstDataAccess accessor;
            tag->acquireActor(&accessor);
            if (accessor.hasTag(ksys::act::tags::TeamForestGiant) ||
                accessor.hasTag(ksys::act::tags::TeamGolem)) {
                entry->hit_by_giant_or_golem = true;
            }
        }
    }

    entry->impulse = sead::Mathf::max(impulse_a, entry->impulse);
    entry->updated = true;
}

ksys::act::BaseProc* Motorcycle::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) Motorcycle(arg);
}

Motorcycle::~Motorcycle() {
    if (_1648)
        ksys::util::safeDelete(_1648);
    if (_1650)
        ksys::util::safeDelete(_1650);
}

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

void Motorcycle::m117(ksys::act::Unk117* arg) {
    if (!_1648->sub_7100E8B780(arg))
        _f80 = true;
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

void Motorcycle::m76(ksys::VFR::ScopedDeltaSetter* setter) {
    DynamicActor::m76(setter);
    if (_1128) {
        _1128 = false;
        x_3(_112c);
    }
    if (sead::DynamicCast<ksys::act::Player>(getConnectedCalcChild()))
        sub_71008BBDC8();
    sub_7100071CB0();
}

void Motorcycle::updateMtxFromPhysics() {
    sead::Vector3f velocity;
    sead::Matrix34f mtx;
    if (auto* controller = getCharacterController()) {
        controller->sub_7100F5F598(&velocity);
        mVelocity = velocity * (1.0f / 30.0f);
        controller->sub_7100F635BC(&velocity);
        mAngVelocity = velocity * (1.0f / 30.0f);
        controller->sub_7100F626E8(&mtx);
    } else {
        auto* body = mMainBody.load();
        if (!body)
            return;
        body->getLinearVelocity(&velocity);
        mVelocity = velocity * (1.0f / 30.0f);
        body->getAngularVelocity(&velocity);
        mAngVelocity = velocity * (1.0f / 30.0f);
        body->getTransform(&mtx);
    }
    mMtx = mtx;
    nullsub_4648();
}

void Motorcycle::setMtx(const sead::Matrix34f& mtx, bool a2, bool a3) {
    Actor::setMtx(mtx, a2, a3);
    x_12(mtx);

    _bb8->setLinearVelocity(sead::Vector3f::zero);
    _bb8->setAngularVelocity(sead::Vector3f::zero);
    _dd0->_0->setLinearVelocity(sead::Vector3f::zero);
    _dd0->_0->setAngularVelocity(sead::Vector3f::zero);
    _dd8->_0->setLinearVelocity(sead::Vector3f::zero);
    _dd8->_0->setAngularVelocity(sead::Vector3f::zero);

    _11b0._388 = _dd0->_0->getPosition();
    _11b0._394 = _dd8->_0->getPosition();
    _1608.set(0.0f, 0.0f, 0.0f);

    _e6c = mtx(1, 3);
    _e70 = mtx(1, 3);
    _ec4 = 10;
    const sead::Vector3f translation = mtx.getTranslation();
    _ed4 = translation;
    _ec8 = translation;
}

// NON_MATCHING: the last branch keeps `body == nullptr` in a register (cset) across the call; we test the
// pointer again
void Motorcycle::x_12(const sead::Matrix34f& mtx) {
    if (auto* wheel = _dd0) {
        const sead::Vector3f pos = mtx.getTranslation() + mtx.getBase(0) * 0.0f +
                                   mtx.getBase(1) * 0.474f + mtx.getBase(2) * 1.41f;
        sead::Matrix34f wheel_mtx = mtx;
        wheel_mtx.setTranslation(pos);
        wheel->_0->setTransform(wheel_mtx);
        wheel->_128 = 0;
        wheel->_130.set(0.0f, 0.0f, 0.0f);
        wheel->_13c = 0;
        if (wheel->_148->_50 & 1)
            wheel->_148->sub_7100F6A074();
        if (wheel->_150->_50 & 1)
            wheel->_150->sub_7100F6A074();
    }
    if (auto* wheel = _dd8) {
        const sead::Vector3f pos = mtx.getTranslation() + mtx.getBase(0) * 0.0f +
                                   mtx.getBase(1) * 0.474f - mtx.getBase(2) * 0.7762f;
        sead::Matrix34f wheel_mtx = mtx;
        wheel_mtx.setTranslation(pos);
        wheel->_0->setTransform(wheel_mtx);
        wheel->_128 = 0;
        wheel->_130.set(0.0f, 0.0f, 0.0f);
        wheel->_13c = 0;
        if (wheel->_148->_50 & 1)
            wheel->_148->sub_7100F6A074();
        if (wheel->_150->_50 & 1)
            wheel->_150->sub_7100F6A074();
    }
    sub_71000715D8(&_e04, &_e10);
    sub_71000717B8(&_e1c, &_e28);
    _f88.reset(0x80);
}

void Motorcycle::x_7() {
    auto* body = _bb8;
    const bool has_wheel0 = _dd0 && _dd0->_0;
    const bool has_wheel1 = _dd8 && _dd8->_0;
    if (body)
        body->setContactNone();
    if (has_wheel0) {
        _dd0->_0->setContactNone();
        _dd0->_0->enableContactLayer(ksys::phys::ContactLayer::EntityRope);
        _dd0->_0->enableContactLayer(ksys::phys::ContactLayer::EntitySmallObject);
    }
    if (has_wheel1) {
        _dd8->_0->setContactNone();
        _dd8->_0->enableContactLayer(ksys::phys::ContactLayer::EntityRope);
        _dd8->_0->enableContactLayer(ksys::phys::ContactLayer::EntitySmallObject);
    }

    if (_f88.isOnBit(44)) {
        if (body)
            _bb8->setContactAll();
        if (has_wheel0)
            _dd0->_0->setContactAll();
        if (has_wheel1)
            _dd8->_0->setContactAll();
    } else if (_f88.isOnBit(22)) {
        if (body)
            _bb8->setContactAll();
        if (has_wheel0)
            _dd0->_0->setContactAll();
        if (has_wheel1)
            _dd8->_0->setContactAll();
    } else if (_f88.isOnBit(26)) {
        if (body) {
            _bb8->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
            _bb8->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
        }
        if (has_wheel0) {
            _dd0->_0->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
            _dd0->_0->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
        }
        if (has_wheel1) {
            _dd8->_0->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
            _dd8->_0->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
        }
    } else {
        const bool no_body = body == nullptr;
        if (_f88.isOnBit(45) && !no_body)
            _bb8->enableContactLayer(ksys::phys::ContactLayer::EntityPlayer);
        if (_f88.isOnBit(46) && !no_body)
            _bb8->enableContactLayer(ksys::phys::ContactLayer::EntityRagdoll);
    }
}

void Motorcycle::sub_7100077830() {
    if (_f88.isOnBit(20))
        return;
    _f88.set(0x100000);
    _bb8->changeMotionType(ksys::phys::MotionType::Fixed);
    _dd0->_0->changeMotionType(ksys::phys::MotionType::Fixed);
    _dd8->_0->changeMotionType(ksys::phys::MotionType::Fixed);
}

// NON_MATCHING: the three fadds of `start` have their operands swapped (`prod + pos` in the original)
void Motorcycle::sub_7100071CB0() {
    _f88.reset(0x1000000);
    if (!mPhysics)
        return;

    ksys::phys::RayCastBodyQuery query(mPhysics->get188(0), ksys::phys::GroundHit::HitAll);
    query.enableLayer(ksys::phys::ContactLayer::EntityGround);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
    query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityObject);
    query.enableLayer(ksys::phys::ContactLayer::EntityTree);

    sead::Vector3f up, forward;
    const sead::Vector3f pos = _bb8->getPosition();
    _bb8->getTransform().getBase(up, 1);
    _bb8->getTransform().getBase(forward, 2);
    const sead::Vector3f start = pos + up * 1.2f;
    query.setStartAndDisplacementScaled(start, forward, 2.0f);
    if (query.worldRayCast(ksys::phys::ContactLayerType::Entity))
        _f88.set(0x1000000);
}

void Motorcycle::sub_71000769B4() {
    if ((_eec - _bb8->getInertiaLocal()).squaredLength() > 0.1f)
        _bb8->setInertiaLocal(_eec);
    if ((_ef8 - _dd0->_0->getInertiaLocal()).squaredLength() > 0.1f)
        _dd0->_0->setInertiaLocal(_ef8);
    if ((_f04 - _dd8->_0->getInertiaLocal()).squaredLength() > 0.1f)
        _dd8->_0->setInertiaLocal(_f04);
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
