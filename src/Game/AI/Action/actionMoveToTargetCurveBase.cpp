#include "Game/AI/Action/actionMoveToTargetCurveBase.h"
#include <algorithm>
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

MoveToTargetCurveBase::MoveToTargetCurveBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoveToTargetCurveBase::~MoveToTargetCurveBase() = default;

bool MoveToTargetCurveBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoveToTargetCurveBase::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = ksys::Timer(0, 0, 1.0f / 30.0f);
    _60 = 0;
    _64 = 0;
    auto* actor = mActor;
    sead::Vector3f target = sead::Vector3f::zero;
    m34(&target);
    actor->getMtx().getTranslation(_44);

    const sead::Vector3f to_target(target.x - _44.x, 0, target.z - _44.z);
    sead::Vector3f axis;
    ksys::util::sub_71011EEB08(&axis, &_54, sead::Vector3f::ex, to_target, sead::Vector3f::ey);
    _54 *= axis.y;

    const f32 dist = std::sqrt((_44.x - target.x) * (_44.x - target.x) +
                               (_44.z - target.z) * (_44.z - target.z));
    const f32 dy = target.y - _44.y;
    const f32 height = sead::Mathf::clampMin(m35(&_44, &target), 0.0f);
    sead::Vector3f gravity;
    ksys::act::sub_7100EE5B84(&gravity, actor);
    _50 = gravity.y;
    const f32 speed = std::sqrt(height * (_50 * -2.0f));
    _5c = speed;
    f32 numerator;
    f32 denominator;
    if (dy >= sead::Mathf::epsilon() || dy <= -sead::Mathf::epsilon()) {
        numerator = dist * (speed - std::sqrt(speed * speed + dy * (gravity.y + gravity.y)));
        denominator = dy;
    } else {
        numerator = -(dist * _50);
        denominator = speed;
    }
    _58 = numerator / (denominator + denominator);
    m32();
}

void MoveToTargetCurveBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void MoveToTargetCurveBase::loadParams_() {
    getStaticParam(&mMaxHeight_s, "MaxHeight");
    getStaticParam(&mTimeScale_s, "TimeScale");
    getStaticParam(&mIsDebugDrawTargetPos_s, "IsDebugDrawTargetPos");
}

void MoveToTargetCurveBase::calc_() {
    sead::Vector3f gravity;
    ksys::act::sub_7100EE5B84(&gravity, mActor);
    const f32 duration = _5c / gravity.y;
    const f32 time_scale = *mTimeScale_s;
    _64 = _38.value;
    _38.update();
    const f32 time = _38.value;
    const f32 scale = std::max(time_scale - (1.0f - time_scale) * time / duration, 1.0f);
    _60 = _60 + (time - _64) * scale;
    const f32 dist = _58 * _60;
    const f32 dx = std::cos(_54) * dist;
    const f32 dz = dist * std::sin(_54);
    const f32 dy = gravity.y * (_60 * _60) * 0.5f + _60 * _5c;
    sead::Vector3f pos = _44;
    pos.x += dx;
    pos.y += dy;
    pos.z -= dz;
    sead::Vector3f target = sead::Vector3f::zero;
    m34(&target);
    const f32 remaining = std::sqrt((_44.x - target.x) * (_44.x - target.x) +
                                    (_44.z - target.z) * (_44.z - target.z));
    m33(remaining, &pos);
}

f32 MoveToTargetCurveBase::m35(const sead::Vector3f* from, const sead::Vector3f* to) {
    const f32 dy = to->y - from->y;
    const f32 height = *mMaxHeight_s;
    return height > dy ? height : dy + 5.0f;
}

}  // namespace uking::action
