#include "Game/Actor/actMotorcycle.h"
#include "Game/Actor/actMotorcycleUtil.h"
#include <basis/seadNew.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include <random/seadGlobalRandom.h>
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
#include <xlink2/xlink2HandleSLink.h>
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Physics/System/physInstanceSet.h"
#include "KingSystem/Physics/System/physRayCastBodyQuery.h"

namespace uking::act {

// 0x71023618c8
static const char* const sUnk_71023618c8[] = {
    "ThisIsError", "ThrottleOn", "ThrottleOff", "DonutStartThrottleOn", "WheelieLaunch", "Jump",
};
// 0x7101e79334 / 0x7101e7931c
static const f32 sUnk_7101e79334[] = {0.0f, 0.85f, 0.3f, 0.9f, 0.9f, 0.9f};
static const f32 sUnk_7101e7931c[] = {0.0f, 0.3f, 0.0f, 0.3f, 0.5f, 0.4f};

// inline-only in the original; name is a guess: the part of sub_710007DAB8 / sub_710007D034 that fades the
// throttle sound layer in for the sound selected by _10a4 (unless it is 0 or 2).
static inline void startThrottleFader(Motorcycle* motorcycle) {
    switch (motorcycle->_10a4) {
    case 0:
    case 2:
        break;
    default:
        motorcycle->_10c0.setValueImmediate(0.0f);
        motorcycle->_10c0.moveTo(1.0f, sUnk_7101e7931c[motorcycle->_10a4]);
        break;
    }
}

// NON_MATCHING: the 24 leading floats (Unk0) are stored as paired `stp w, w` as in the original, but the
// scheduler orders / register-allocates those constant stores differently; the 0x184-0x190 stores are
// merged differently (the original merges `_184` with `_188` and stores `_18c` / `_190` singly)
MotorcycleStruct0::MotorcycleStruct0(ksys::act::Actor* actor) {
    _188 = sead::GlobalRandom::instance()->getF32Range(1.0f, 2.0f);
    _18c = sead::GlobalRandom::instance()->getF32Range(0.7f, 1.0f);
    _194 = false;
    _195 = false;
    _196 = false;
    _197 = false;
    _198 = false;
    _199 = false;
    _19a = false;
    _19b = false;
    _19c = false;
    _19d = false;
    _19e = false;
    _1a0 = 0;
    _1a8 = actor;
    _0._60.x = _0._18;
    _0._54 = 0.0f;
    _0._4 = -1.0f;
    _150.setCurveType(aal::FadeCurveType::Sqrt);
}

void MotorcycleStruct0::sub_710006C270() {
    f32 rate = _0._4;
    if (rate < 0.0f) {
        rate = 1000.0f /
               (_1a8->getParam()->getRes().mGParamList->getMotorcycle()->mFullEnergyLastSec.ref() *
                30.0f);
        _0._4 = rate;
    }
    if (_0._48 > 0.0f) {
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

// NON_MATCHING: everything matches except the order of the zero stores of the xlink2::Handle block
// (0xf88-0x1038, the original interleaves the BitFlag / first handle stores differently), the
// merging of the stores at 0x1080-0x10b8 and the register allocation of the 0x1184-0x118c floats
Motorcycle::Motorcycle(const CreateArg& arg) : DynamicActor(arg) {
    _1c0 = 3;
    _f88.reset(0x700004405007);
    _f88.set(0x5007);
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
        wheel->_13c = false;
        wheel->_13d = false;
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
        wheel->_13c = false;
        wheel->_13d = false;
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

void Motorcycle::sub_710007F8F8() {
    _1058.moveTo(0.0f, 0.0f);
    _1058.setCurveType(aal::FadeCurveType::Sin);
}

void Motorcycle::sub_7100071998() {
    _1058.setValueImmediate(0.0f);
    _1050 = 0.83f;
    _fb0.fade();
    _fc0.fade();
    _fd0.fade();
    sub_71012412E4(this, 0x30, 1.0f, false);
    sub_71012412E4(this, 0x31, 1.0f, false);
    xlinkEventOn(this, 0x3c, 1, false);
}

// NON_MATCHING: same instructions; the original computes `&_f88` in both predecessors of the
// "wheel is on the ground" block and keeps the zero result in s9 across the sub_710006FBF8 call
void Motorcycle::x_17() {
    f32 speed;
    if (_dd8->_13d) {
        const sead::Matrix34f& mtx = _dd8->_24;
        const sead::Vector3f up{mtx(0, 1), mtx(1, 1), mtx(2, 1)};
        const f32 dot = up.dot(_dd8->_5c);
        const f32 length = _dd8->_5c.length();
        speed = dot > 0.0f ? length : -length;
    } else {
        speed = _e58;
    }

    const bool boost = _e3c > 0.5f || _f10 == 5;

    bool launching;
    if (_dd0->_13d || _dd8->_13d) {
        _f88.reset(0x200000000);
        _1080 = 0.25f;
        launching = false;
    } else if (!boost) {
        _f88.set(0x200000000);
        launching = false;
    } else if (!_f88.isOnBit(33)) {
        _1080 -= ksys::VFR::instance()->getDeltaTime();
        launching = false;
    } else {
        _1080 = 0.25f;
        launching = true;
    }

    f32 result = 0.0f;
    _d78.sub_710006FBF8(!_f88.isOnAll(0x2000020000) && _e40 > 0.0f);

    if (MotorcycleMgr::instance()->mEnergy == 0.0f) {
        _d78._24 = false;
        if (!_d78._22)
            _d78._30.setValueImmediate(0.0f);
        _d78._30.calc();
        _d78._20 = false;
        _d78._18 = 0.0f;
    } else {
        const f32 kmh = sead::Mathf::max(speed * 3.6f, 0.0f);
        if (launching) {
            const f32 s = sead::Mathf::clamp(10000.0f / _d78._0, -1.0f, 1.0f);
            _d78._20 = true;
            _d78._14 = 2.0f * sead::Mathf::asin(s) / sead::Mathf::pi();
            _d78.sub_710006F97C(kmh, true);
            _d78._24 = false;
        } else {
            _d78.sub_710006F97C(kmh, boost);
            if (_d78._24) {
                const f32 limit = _f10 != 4 ? 0.5f : 1.25f;
                const f32 abs_speed = _e58 > 0.0f ? _e58 : -_e58;
                if ((!(abs_speed < limit) || !(_e3c > 0.1f) || !_f88.isOnAll(0x2000020000) ||
                     !(_e4c > 0.9f) || !_dd0->_13d || !_dd8->_13d) &&
                    _dd8->_13d && !_f88.isOnBit(25)) {
                    xlinkSearchAndEmit(this, "Launch", 2, nullptr);
                }
            }
        }

        if (_f10 != 4) {
            if (_dd8->_13d || !(_e3c > 0.0f) || _f88.isOnBit(33)) {
                result = _d78._18;
            } else if (_1080 > 0.0f) {
                result = 200.0f;
                if (!_f88.isOnBit(30))
                    _bc8._19d = true;
            }
        }
    }
    _bc8._0._48 = result;
}

// NON_MATCHING: same instructions; the original keeps `&_f88` in a register from the start (x20)
// and tests `(flags & 0x14000) == 0x14000` as and + cmp where ours emits mvn + and + cbnz
void Motorcycle::x_18() {
    const auto param = [this]() { return getParam()->getRes().mGParamList->getMotorcycle(); };
    bool drifting = false;
    if (_e3c > 0.0f) {
        const f32 steer_abs = sead::Mathf::abs(_b90._8);
        if (steer_abs > param()->mDriftAllowSteerRate.ref())
            _f88.set(0x8000);
        else
            _f88.reset(0x8000);
        drifting = sead::Mathf::abs(_b90._8) > param()->mDriftAllowSteerRate.ref() && _e40 > 0.0f;
    } else {
        _f88.reset(0x8000);
    }
    if (drifting)
        _f88.set(0x10000);
    else
        _f88.reset(0x10000);

    if (!_f88.isOnBit(17)) {
        if (_f88.isOnAll(0x14000) && param()->mDriftAllowSpeedKPH.ref() < _e58 * 3.6f &&
            MotorcycleMgr::instance()->mEnergy > 0.0f) {
            _f88.set(0x20000);
            _f18.setValueImmediate(0.0f);
            _f40.setValueImmediate(0.0f);
            _f40.moveTo(1.0f, 0.5f);
            _f68 = 0.1125f;
            _f6c = _b90._8;
            _f88.set(0x2000000000);
            _10a4 = 1;
        }
    } else {
        if (_f68 > 0.0f) {
            _f68 -= ksys::VFR::instance()->getDeltaTime();
            if (_f68 <= 0.0f)
                _f18.moveTo(1.0f, 0.5f);
        }
        if (_e40 == 0.0f)
            _f88.reset(0x2000000000);
        if (_e58 * 3.6f < param()->mDriftAbortSpeedKPH.ref() || _e3c < 1.0f ||
            sead::Mathf::abs(_b90._8) < param()->mDriftAbortSteerRate.ref() ||
            _b90._8 * _f6c < 0.0f || !(MotorcycleMgr::instance()->mEnergy > 0.0f)) {
            _f88.reset(0x2000020000);
            _f18.moveTo(0.0f, 0.25f);
            _f40.moveTo(0.0f, 0.25f);
        }
        if (!_f88.isOnBit(14)) {
            _f88.reset(0x2000020000);
            _f18.setValueImmediate(0.0f);
            _f40.setValueImmediate(0.0f);
            _f68 = -1.0f;
        }
    }
    _d78._21 = _f88.isOnBit(17);
    _f18.calc();
    _f40.calc();
    _bc8._196 = _f88.isOnBit(17);
}

// NON_MATCHING: the original loads the two target speeds in separate branches (we select the address
// first and load once)
void MotorcycleStruct3::sub_710006FBF8(bool flag) {
    if (_22) {
        if (!flag && _30.getValue() > 0.5f) {
            const auto* param = _28->getParam()->getRes().mGParamList->getMotorcycle();
            f32 speed;
            if (_21)
                speed = param->mSlowDriftTargetSpeedKPH2.ref();
            else
                speed = param->mSlowModeTargetSpeedKPH2.ref();
            _14 = 2.0f * sead::Mathf::asin(sead::Mathf::clamp(speed / _0, -1.0f, 1.0f)) /
                  sead::Mathf::pi();
        }
    } else if (flag) {
        _30.setValueImmediate(0.0f);
        _30.moveTo(1.0f, _28->getParam()->getRes().mGParamList->getMotorcycle()->mSlowModeTransitionSec.ref());
    }
    _22 = flag;
}

// NON_MATCHING: the original selects between the value addresses of the two target speeds; we select
// between the parameter objects (+0x18 folded into the load) and schedule the `_14 * pi` product later
void MotorcycleStruct3::sub_710006F97C(f32 speed, bool flag) {
    _24 = false;
    const f32 squared = speed > 0.0f ? speed * speed : -(speed * speed);
    if (!_22)
        _30.setValueImmediate(0.0f);
    _30.calc();
    if (!flag) {
        _20 = false;
        _18 = 0.0f;
        return;
    }

    if (!_20) {
        const f32 s = sead::Mathf::clamp(squared / _0, -1.0f, 1.0f);
        _20 = true;
        _14 = 2.0f * sead::Mathf::asin(s) / sead::Mathf::pi();
        if (_14 < 0.01f)
            _24 = true;
    }

    _14 += ksys::VFR::instance()->getDeltaTime() / _4;
    _14 = sead::Mathf::clamp(_14, 0.0f, 1.0f);

    f32 value = _0;
    if (_22) {
        const auto* param = _28->getParam()->getRes().mGParamList->getMotorcycle();
        const f32& target = _21 ? param->mSlowDriftTargetSpeedKPH2.ref() :
                                  param->mSlowModeTargetSpeedKPH2.ref();
        value = _30.getValue() * target + (1.0f - _30.getValue()) * value;
    }
    f32 capped = value;
    if (_23) {
        const auto* param = _28->getParam()->getRes().mGParamList->getMotorcycle();
        const f32 limit = param->mWeaponThrowModeSpeedKPH2.ref();
        if (capped > limit)
            capped = limit;
    }
    capped *= sead::Mathf::sin(_14 * sead::Mathf::pi() * 0.5f);
    if (_21)
        capped *= _28->getParam()->getRes().mGParamList->getMotorcycle()->mDriftSpeedRate.ref();
    _1c = capped;
    _18 = (_1c - squared) * 0.25f;
    _18 = sead::Mathf::clamp(_18, 0.001f, _8);
}

// NON_MATCHING: the compares of _10a4 against 0 / 2 / 4 are turned into a jump table here; the original
// keeps the compare chain (== 4, then (x | 2) == 2) and also fades the handle without the second
// validity test
void Motorcycle::sub_710007DAB8() {
    if (_10a4 != 0) {
        if (_10a8.getEvent() && _10a8.getEvent()->getCreateId() == _10a8.getCreateId()) {
            if (sUnk_7101e79334[_10a4] < _10b8) {
                _10a4 = 0;
                return;
            }
            _10a8.fade();
        }

        Unk_71012419b4 handle;
        xlinkSearchAndEmit(this, sUnk_71023618c8[_10a4], 2, &handle);
        if (handle.sub_7101241AD8(1)) {
            _10a8 = handle.mSLink;
            _10b8 = sUnk_7101e79334[_10a4];
        }
        if (_10a4 == 1) {
            if (_bc8._0._60.x > 2000.0f) {
                _bc8._150.setValueImmediate(0.0f);
                _bc8._150.moveTo(1.0f, 0.03f);
                _10a4 = 0;
                return;
            }
        } else if (_10a4 == 4) {
            _10a4 = 0;
            return;
        }
        startThrottleFader(this);
    }
    _10a4 = 0;
}

bool Unk_71023618f8::invoke(ksys::phys::ContactPointInfo::ShouldDisableContact* disable,
                            const ksys::phys::ContactPointInfo::Event& event) {
    if (auto* user_tag = event.body->getUserTag()) {
        if (auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(user_tag)) {
            ksys::act::ActorConstDataAccess accessor;
            tag->acquireActor(&accessor);
            if (accessor.hasTag(ksys::act::tags::IsDisableContactMotorcycle)) {
                *disable = ksys::phys::ContactPointInfo::ShouldDisableContact::Yes;
                return false;
            }
        }
    }
    if (event.body->getContactLayer() == ksys::phys::ContactLayer::EntityRagdoll) {
        if (auto* user_tag = event.body->getUserTag()) {
            if (auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(user_tag)) {
                ksys::act::ActorConstDataAccess accessor;
                tag->acquireActor(&accessor);
                if (!accessor.isPlayerProfile()) {
                    *disable = ksys::phys::ContactPointInfo::ShouldDisableContact::Yes;
                    return false;
                }
                if (accessor.isPlayerProfile() && event.body->getHkBodyName() == "RollingBody") {
                    *disable = ksys::phys::ContactPointInfo::ShouldDisableContact::Yes;
                    return false;
                }
            }
        }
    }
    return true;
}

// NON_MATCHING: the original evaluates `y_axis.dot(up)` before the cross product's length() (a local would
// reproduce it) and loads `mtx(1, 2)` before the sqrt call and keeps it across it (d9)
void Motorcycle::sub_710007D034() {
    const f32 delta = getParam()
                          ->getRes()
                          .mGParamList->getMotorcycle()
                          ->mWheelieLaunchRiseDegDelta.ref();
    _df8 = delta;
    _dfc = delta;
    _df0 = 0;

    const sead::Matrix34f& mtx = getMtx();
    const sead::Vector3f x_axis{mtx(0, 0), mtx(1, 0), mtx(2, 0)};
    const sead::Vector3f y_axis{mtx(0, 1), mtx(1, 1), mtx(2, 1)};
    const sead::Vector3f side = x_axis.cross(sead::Vector3f::ey);
    const sead::Vector3f up = side.cross(x_axis);
    const f32 angle = sead::Mathf::atan2(y_axis.cross(up).length(), y_axis.dot(up));
    _e00 = mtx(1, 2) > 0.0f ? angle * 57.29578f : -(angle * 57.29578f);

    const f32 kmh = _e58 * 3.6f;
    _d78._14 = 2.0f * sead::Mathf::asin(sead::Mathf::clamp(3025.0f / _d78._0, -1.0f, 1.0f)) /
               sead::Mathf::pi();
    _d78._20 = true;
    _d78.sub_710006F97C(kmh, true);
    _f10 = 5;
    _d78._24 = false;
    _e80 = 2.0f;
    xlinkSearchAndEmit(this, "WheelieLaunch", 0, nullptr);
    _10a4 = 4;
    xlinkSearchAndEmit(this, "WheelieLaunchWind", 2, nullptr);
    startThrottleFader(this);
    _bc8._199 = true;
    _e88 = getParam()->getRes().mGParamList->getMotorcycle()->mWheelieLastSecInMidAir.ref();
    _f88.set(8);
}

f32 getMotorcycleEnergy() {
    return MotorcycleMgr::instance()->mEnergy;
}

// NON_MATCHING: everything matches except the block layout of the timer update / reset (the original
// computes `&_1640` in both predecessors and falls from the reset block into the final compare)
bool Motorcycle::x_31() {
    if (mPhysics) {
        bool hit;
        {
            ksys::phys::RayCastBodyQuery query(mPhysics->get188(0), ksys::phys::GroundHit::HitAll);
            query.setNormalCheckingMode(ksys::phys::RayCast::NormalCheckingMode::DoNotCheck);
            query.enableLayer(ksys::phys::ContactLayer::EntityGroundObject);
            query.enableLayer(ksys::phys::ContactLayer::EntityGround);
            query.enableLayer(ksys::phys::ContactLayer::EntityGroundRough);
            query.enableLayer(ksys::phys::ContactLayer::EntityTree);
            query.enableLayer(ksys::phys::ContactLayer::EntityAirWall);

            sead::Vector3f start;
            sead::Vector3f end;
            sead::Matrix34f mtx;
            _bb8->getCenterOfMassInWorld(&end);
            _bb8->getTransform(&mtx);
            sead::Vector3f x, y;
            mtx.getBase(x, 0);
            mtx.getBase(y, 1);
            end -= y * 0.1f;
            x *= 0.05f;
            y *= 0.3f;

            _dd0->_0->getPosition(&start);
            start += x + y;
            query.setStartAndEnd(start, end);
            query.worldRayCast(ksys::phys::ContactLayerType::Entity);
            if (query.hasHit()) {
                hit = true;
            } else {
                _dd8->_0->getPosition(&start);
                start += y - x;
                query.setStartAndEnd(start, end);
                query.worldRayCast(ksys::phys::ContactLayerType::Entity);
                hit = query.hasHit();
            }
        }
        if (!hit)
            _1640 = 0.0f;
        else
            ksys::Timer::update(&_1640, 1.0f);
    } else {
        _1640 = 0.0f;
    }
    if (_1640 > 30.0f) {
        _f88.set(0x800000000);
        return true;
    }
    return false;
}

bool Motorcycle::isAnyWheelOnMaterial(ksys::phys::Material material) const {
    const ksys::phys::Material front = _dd0->_110;
    if (int(front) == int(material))
        return true;
    const ksys::phys::Material rear = _dd8->_110;
    return int(rear) == int(material);
}

bool Motorcycle::isWheelConstraintActiveMaybe() const {
    if (_de0->_18 && (_de0->_50 & 1) && _de0->_18->sub_7100F6C658())
        return true;
    if (_de8->_18 && (_de8->_50 & 1) && _de8->_18->sub_7100F6C658())
        return true;
    return false;
}

// NON_MATCHING: only the stack slot of the second SafeString temporary (the "SweepCollision" literal is at
// sp+0x18 in the original, sp+0x8 here)
bool Motorcycle::collisionStuff(ksys::phys::RigidBody* body) {
    if (auto* info = body->getContactPointInfo()) {
        for (auto it = info->begin(), end = info->end(); it != end; ++it) {
            auto* other = (*it)->body_b;
            if (!other)
                continue;
            auto* tag = sead::DynamicCast<ksys::act::PhysicsUserTag>(other->getUserTag());
            if (!tag)
                continue;
            ksys::act::ActorConstDataAccess accessor;
            tag->acquireActor(&accessor);
            if (other->getContactLayer() == ksys::phys::ContactLayer::EntityPlayer &&
                accessor.isPlayerProfile() && other->getHkBodyName() == "Cleaning")
                return true;
            if (accessor.getProfile() == "SweepCollision")
                return true;
        }
    }
    return false;
}

bool Motorcycle::deleteIfColliding() {
    if (!isDeleteRequested()) {
        if (collisionStuff(_bb8) || collisionStuff(_dd0->_0) || collisionStuff(_dd8->_0)) {
            deleteLater(DeleteReason::_0);
            return true;
        }
    }
    return false;
}

bool Motorcycle::sub_710007A478() const {
    return _e3c > 0.0f && MotorcycleMgr::instance()->mEnergy > 0.0f;
}

f32 Motorcycle::sub_710007AB7C() const {
    if (!_f88.isOnBit(17))
        return 0.0f;
    return (_f18.getValue() + _f40.getValue()) * 0.5f;
}

bool Motorcycle::sub_710007C00C() const {
    if (!_d78._24)
        return false;
    if (sead::Mathf::abs(_e58) < 0.5f && _e3c > 0.1f && !_f88.isOnAll(0x2000020000) && _e4c > 0.9f &&
        _dd0->_13d && _dd8->_13d)
        return false;
    return MotorcycleMgr::instance()->mEnergy > 0.0f;
}

void Motorcycle::m70() {
    if (_f80) {
        mActorFlags2.reset(ActorFlag2::_20);
        if (!_f88.isOnBit(20)) {
            _f88.set(0x100000);
            _bb8->changeMotionType(ksys::phys::MotionType::Fixed);
            _dd0->_0->changeMotionType(ksys::phys::MotionType::Fixed);
            _dd8->_0->changeMotionType(ksys::phys::MotionType::Fixed);
        }
    }
    _1648->_10 &= ~0x38u;
    _de0->_18->sub_7100F6C64C(10000000.0f);
    _de8->_18->sub_7100F6C64C(10000000.0f);
    if ((_de0->_50 & 1) || (_de8->_50 & 1)) {
        _de0->sub_7100F6A074();
        _de8->sub_7100F6A074();
        _f88.set(0x40000000000);
    }
    if (!isDeleteRequested()) {
        if (collisionStuff(_bb8) || collisionStuff(_dd0->_0) || collisionStuff(_dd8->_0))
            deleteLater(DeleteReason::_0);
    }
}

void Motorcycle::m44() {
    sead::Matrix34f mtx;
    _bb8->getTransform(&mtx);
    const sead::Vector3f pos = mtx.getTranslation();
    sead::Vector3f velocity;
    _bb8->getLinearVelocity(&velocity);
    velocity.y = 0.0f;
    if (!pos.isNan()) {
        sead::Vector3f direction;
        {
            auto* nav = _1650;
            auto lock = sead::makeScopedLock(nav->_1e0);
            direction.set(nav->_248);
        }
        _1650->sub_7100F76380(pos, direction, velocity, direction);
    }
}

// NON_MATCHING: only the stack slot of the core-number temporary (it shares the slot of the transform in the
// original)
void Motorcycle::applyPitchDamping() {
    sead::Vector3f damping;
    const sead::Vector3f angular_velocity = _bb8->getAngularVelocity();
    sead::Vector3f axis;
    const sead::Matrix34f mtx = _bb8->getTransform();
    mtx.getBase(axis, 0);
    innerProductTimesA3(&damping, angular_velocity, axis);
    damping *= -getParam()->getRes().mGParamList->getMotorcycle()->mPitchDampingCoefficient.ref();
    damping *= ksys::VFR::instance()->getDeltaFrame();
    addAngularVelocity(_bb8, damping.x, damping.y, damping.z);
}

// NON_MATCHING: operand order of the first fadd of the length and the store grouping of the velocity
void Motorcycle::applyDragMaybe() {
    sead::Vector3f velocity =
        _bb8->getLinearVelocity() + sead::Vector3f(0.010255f, -0.666032f, 0.09355f);
    const f32 factor = velocity.length() * -0.432f;
    velocity *= factor * ksys::VFR::instance()->getDeltaFrame();
    _bb8->applyLinearImpulse(velocity);
}

}  // namespace uking::act
