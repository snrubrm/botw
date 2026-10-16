#include "Game/Actor/Action/actionBowChildArrowRain.h"
#include "Game/Actor/actSiteBoss.h"
#include "Game/Actor/aiUnk_710073fa90.h"
#include <math/seadQuat.h>
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/XLink/xlinkActorUtil.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/System/VFR.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::action {

namespace {
struct Unk_8000054_Payload {
    u8 _0[0x20];
    s32 _20;
};
}  // namespace

// NON_MATCHING: the original emits the zero stores of _d4/_100/_108/_110 before both memsets (0x20..0xd3 and
// the 0x408-byte block at 0x12c); here they end up between / after the memsets.
BowChildArrowRain::BowChildArrowRain(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BowChildArrowRain::~BowChildArrowRain() = default;

bool BowChildArrowRain::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BowChildArrowRain::enter_(ksys::act::ai::InlineParamPack* params) {
    _b8 = 0;
    _bc = 0;
    const s32 id = *mID_d;
    _100.fill(0);
    _c0 = f32(id) * (sead::Mathf::pi() / 2);
    for (auto& state : _12c._3d8)
        state = {false, false};
    _12c._3cc = ksys::Timer(*mToTargetTime_s, *mToTargetTime_s);
    _d0 = false;
    _d1 = false;
    _d2 = false;
    _d8 = *mID_d;
    _c8 = sead::GlobalRandom::instance()->getF32();
    _cc = sead::GlobalRandom::instance()->getF32Range(-5, 5);
}

void BowChildArrowRain::leave_() {
    ksys::act::ai::Action::leave_();
}

void BowChildArrowRain::loadParams_() {
    getStaticParam(&mRainMax_s, "RainMax");
    getStaticParam(&mMoveSpeed_s, "MoveSpeed");
    getStaticParam(&mMoveHeight_s, "MoveHeight");
    getStaticParam(&mWaitTime_s, "WaitTime");
    getStaticParam(&mMoveCountNum_s, "MoveCountNum");
    getStaticParam(&mMoveRange_s, "MoveRange");
    getStaticParam(&mMoveOffsetBase_s, "MoveOffsetBase");
    getStaticParam(&mRotateRate_s, "RotateRate");
    getStaticParam(&mRotateStepMax_s, "RotateStepMax");
    getStaticParam(&mAngleToTarget_s, "AngleToTarget");
    getStaticParam(&mTargetOffsetBase_s, "TargetOffsetBase");
    getStaticParam(&mRainScale_s, "RainScale");
    getStaticParam(&mToTargetTime_s, "ToTargetTime");
    getDynamicParam(&mID_d, "ID");
    getDynamicParam(&mXRotateAngle_d, "XRotateAngle");
    getDynamicParam(&mIsIgnoreHightOffset_d, "IsIgnoreHightOffset");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mMoveTargetPos_d, "MoveTargetPos");
    getDynamicParam(&mParentActor_d, "ParentActor");
}

bool BowChildArrowRain::handleMessage_(const ksys::Message* message) {
    if (!message || message->getBrokerId() != u32(-1))
        return false;
    if (message->getType() != 0x8000054)
        return false;
    if (!message->getUserData())
        return true;

    const auto* data = static_cast<const Unk_8000054_Payload*>(message->getUserData());
    if (!data)
        return true;

    if (data->_20 == 1) {
        _d1 = true;
        return true;
    }

    _b8 = 1;
    _12c._3c0 = ksys::Timer(45.0f, 45.0f);
    playAS("Open", false, 0, 0, -1.0f);
    return true;
}

bool BowChildArrowRain::isChangeable() const {
    return _b8 != 1 && _b8 != 2;
}

void BowChildArrowRain::calc_() {
    sub_710073FA94(&_dc, mActor);
    sead::Vector3f dir = *mTargetPos_d;
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    dir -= pos;
    dir.normalize();
    sead::Matrix33f rotation;
    rotation.makeR({0, -sead::Mathf::piHalf(), 0});
    dir.rotate(rotation);
    sub_71000CD040();

    sead::Vector3f target;
    for (s32 i = 0; i < 5; ++i) {
        if (_100[i] != 0 && --_100[i] == 0) {
            if (sub_71000CD2A8(&target)) {
                sub_71000CD468(target, i);
                _12c._3d8[i] = {false, true};
            } else {
                _100[i] = 20;
            }
        }
    }

    sub_7100740200(&_dc, dir, 0.66f, 0.36f, 0.001f);
    switch (_b8) {
    case 0:
        _c4 += (*mMoveSpeed_s - _c4) * 0.33f;
        sub_71000CD7AC(&target);
        sub_71000CDEEC(target, true);
        break;
    case 1:
        _c4 += (0.04f - _c4) * 0.1f;
        sub_71000CD7AC(&target);
        sub_71000CDEEC(target, true);
        sub_71000CE0C0();
        _12c._3c0.update();
        if (_12c._3c0.value <= sead::Mathf::epsilon()) {
            _120 = target;
            _b8 = 2;
        }
        break;
    case 2:
        sub_71000CDEEC(sead::Vector3f::zero, false);
        sub_71000CE0C0();
        if (!_d1)
            break;
        if (!_d2) {
            _12c._3cc.update();
            if (_12c._3cc.value <= sead::Mathf::epsilon())
                _d2 = true;
        } else if (sub_71000CE328()) {
            setFinished();
        }
        break;
    }
}

void BowChildArrowRain::sub_71000CDEEC(const sead::Vector3f& pos, bool use_pos) {
    auto* body = mActor->getMainBody();
    if (!body)
        return;

    sead::Matrix33f rotation_mtx = _dc;
    sead::Matrix33f rotation;
    rotation.makeR({*mXRotateAngle_d, 0, 0});
    rotation_mtx.setMul(rotation_mtx, rotation);
    sead::Matrix34f mtx(rotation_mtx, pos);
    if (!use_pos)
        mtx.setTranslation(_120);
    body->changePositionAndRotation(mtx);
}

void BowChildArrowRain::sub_71000CD468(const sead::Vector3f& target, int index) {
    if (!mParentActor_d)
        return;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mParentActor_d->getProc(nullptr, nullptr));
    auto* boss = sead::DynamicCast<act::SiteBoss>(actor);
    if (!boss)
        return;

    auto* link = boss->_1560.sub_710066DE24(index + *mID_d * 4 + 4);
    if (link->hasProcInCalcState() || !mActor->getPhysics())
        return;

    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f dir = target;
    dir -= pos;
    dir.normalize();
    sead::Matrix33f rotation;
    ksys::util::sub_71011EFFA8(&rotation, dir, sead::Vector3f::ey, false);
    sead::Vector3f scale = sead::Vector3f::ones;
    scale *= *mRainScale_s;
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    const sead::Matrix34f mtx(rotation, pos);
    sead::Vector3f velocity = dir;
    velocity *= sead::GlobalRandom::instance()->getF32Range(0.4f, 0.8f) * 0.1f;
    accessor.setProperties(mtx, &velocity, nullptr, &scale, false, 2, -1);
}

// NON_MATCHING: float scheduling of the circle offset and of the chase step (the original recomputes the angle
// difference per branch); the start up to the height offset matches.
void BowChildArrowRain::sub_71000CD7AC(sead::Vector3f* pos) {
    const sead::Vector3f center = *mMoveTargetPos_d;
    sead::Vector3f parent_pos = center;
    if (mParentActor_d &&
        sead::DynamicCast<ksys::act::Actor>(mParentActor_d->getProc(nullptr, nullptr))) {
        auto* parent = sead::DynamicCast<ksys::act::Actor>(mParentActor_d->getProc(nullptr, nullptr));
        if (sead::DynamicCast<ksys::act::Actor>(parent))
            parent->getMtx().getTranslation(parent_pos);
    }

    sead::Vector3f axis;
    axis.setCross(parent_pos - center, sead::Vector3f::ey);
    if (axis.equals(sead::Vector3f::zero, sead::Mathf::epsilon()))
        axis = sead::Vector3f::ex;
    axis.normalize();
    sead::Quatf rotation;
    rotation.setAxisRadian(axis, *mAngleToTarget_s);
    sead::Matrix34f rotation_mtx;
    rotation_mtx.fromQuat(rotation);
    f32 height = *mMoveHeight_s;
    if (*mIsIgnoreHightOffset_d)
        height = 0.0f;
    sead::Vector3f offset{0, height, 0};
    offset.rotate(rotation_mtx);
    _114 = center + offset;

    bool far = false;
    if (!*mIsIgnoreHightOffset_d) {
        sead::Vector3f diff = _114 - parent_pos;
        if (diff.x * diff.x + diff.z * diff.z < *mMoveOffsetBase_s * *mMoveOffsetBase_s) {
            diff.normalize();
            _114 += diff * (*mMoveOffsetBase_s + 2.0f);
            far = !*mIsIgnoreHightOffset_d;
        } else {
            far = true;
        }
    }
    f32 radius = far ? *mMoveOffsetBase_s : *mMoveOffsetBase_s * 0.8f;
    radius += _c8;

    const f32 count_angle = *mMoveCountNum_s * sead::Mathf::pi();
    if (count_angle > _bc)
        radius += (count_angle - _bc) / count_angle * *mMoveRange_s;
    const f32 diff = count_angle - _bc;
    _c0 += *mRotateRate_s;
    if (sead::Mathf::abs(diff) <= 0.001f) {
        _bc = count_angle;
    } else {
        const f32 step = *mRotateRate_s * sead::Mathf::abs(diff);
        f32 delta;
        if (step > *mRotateStepMax_s)
            delta = diff < 0 ? -*mRotateStepMax_s : *mRotateStepMax_s;
        else if (step < 0.001f)
            delta = diff < 0 ? -0.001f : 0.001f;
        else
            delta = *mRotateRate_s * diff;
        _bc += delta;
    }

    sead::Matrix33f circle_mtx;
    circle_mtx.makeR({0, _c0, 0});
    sead::Vector3f circle{radius, _cc, 0};
    circle.rotate(circle_mtx);
    sead::Vector3f current;
    mActor->getMtx().getTranslation(current);
    sead::Vector3f dir = _114 + circle - current;
    f32 distance = dir.length();
    if (distance > 0.0f)
        dir *= 1.0f / distance;
    distance = sead::Mathf::min(distance, _c4);
    distance *= ksys::VFR::instance()->getDeltaFrame();
    *pos = current + dir * distance;
}

void BowChildArrowRain::sub_71000CE0C0() {
    if (!mParentActor_d)
        return;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mParentActor_d->getProc(nullptr, nullptr));
    auto* boss = sead::DynamicCast<act::SiteBoss>(actor);
    if (!boss)
        return;

    bool emitted = false;
    for (s32 i = 0; i < 24; ++i) {
        auto* link = boss->_1560.sub_710066DE24(i);
        if (!link->hasProc())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        if (!accessor.isStateCalc() || !_12c._3d8[i].entered)
            continue;

        if (!_d0) {
            _d0 = true;
            for (u32 j = 0; j < u32(*mRainMax_s); ++j)
                _100[j] = 3 * (j + 1);
        }
        auto* shot = &_12c._0[i];
        sub_71000CE750(shot);
        mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000056), shot,
                            true);
        if (!emitted)
            ksys::eft::searchAndEmitSLink(mActor, "Reflect", false);
        emitted = true;
    }
}

void BowChildArrowRain::sub_71000CE750(Unk12c::Shot* shot) {
    shot->has_target = sub_71000CD2A8(&shot->target);
    if (_d2) {
        ++_d4;
        if (u32(_d4) >= 7)
            _d4 -= 6;
    } else {
        _d4 = 0;
    }
    mActor->getMtx().getTranslation(shot->from);
    shot->to = *mTargetPos_d;
    if (_d4 >= 2) {
        const f32 offset_x = *mTargetOffsetBase_s;
        shot->to.x += sead::GlobalRandom::instance()->getF32Range(-offset_x, offset_x);
        const f32 offset_z = *mTargetOffsetBase_s;
        shot->to.z += sead::GlobalRandom::instance()->getF32Range(-offset_z, offset_z);
    }
    shot->to.y += 1.0f;
}

// NON_MATCHING: the original repeats the speed sqrt (dead) after the store; register allocation.
void BowChildArrowRain::sub_71000CD040() {
    if (!mParentActor_d)
        return;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mParentActor_d->getProc(nullptr, nullptr));
    auto* boss = sead::DynamicCast<act::SiteBoss>(actor);
    if (!boss)
        return;

    for (s32 i = 0; i < 24; ++i) {
        auto& state = _12c._3d8[i];
        if (state.entered)
            state.entered = false;
        auto* link = boss->_1560.sub_710066DE24(i);
        if (!link->hasProcInCalcState())
            continue;
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(link, &accessor);
        const sead::Vector3f pos = accessor.getActorMtx().getTranslation();
        const sead::Vector3f velocity = accessor.getVelocity();
        const f32 speed = velocity.length();
        const sead::Vector3f diff = mActor->getMtx().getTranslation() - (pos + velocity);
        const bool inside = diff.squaredLength() < speed * speed;
        if (inside && !state.inside)
            state.entered = true;
        state.inside = inside;
    }
}

// NON_MATCHING: the original keeps &_1560 in a register and adds 0x1e0 after the index (we fold the offsets).
bool BowChildArrowRain::sub_71000CD2A8(sead::Vector3f* pos) {
    if (!mParentActor_d)
        return false;
    auto* actor = sead::DynamicCast<ksys::act::Actor>(mParentActor_d->getProc(nullptr, nullptr));
    auto* boss = sead::DynamicCast<act::SiteBoss>(actor);
    if (!boss)
        return false;

    auto& bound = boss->_1560;
    _d8 = bound.sub_710066DF44(_d8, (*mID_d & 1) ? -1 : 1, *mID_d);
    auto& link = bound._1e0[_d8];
    if (link.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        if (accessor.isStateCalc()) {
            accessor.getActorMtx().getTranslation(*pos);
            return true;
        }
    }
    return false;
}

bool BowChildArrowRain::sub_71000CE328() {
    if (mParentActor_d) {
        auto* actor = sead::DynamicCast<ksys::act::Actor>(mParentActor_d->getProc(nullptr, nullptr));
        if (auto* boss = sead::DynamicCast<act::SiteBoss>(actor)) {
            for (u32 i = 0; i < 24; ++i) {
                if (boss->_1560.sub_710066DE24(i)->hasProcInCalcState())
                    return false;
            }
        }
    }
    return true;
}

}  // namespace uking::action
