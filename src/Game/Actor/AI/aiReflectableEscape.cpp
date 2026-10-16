#include "Game/Actor/AI/aiReflectableEscape.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ReflectableEscape::ReflectableEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReflectableEscape::~ReflectableEscape() = default;

bool ReflectableEscape::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReflectableEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    _64 = ksys::Timer(*mEscapeTimer_s, *mEscapeTimer_s);
    sub_710053C804(&_58, *mTargetPos_d, *mEscapeDist_s);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_58, "TargetPos", -1);
    changeChild("移動", &pack);
}

void ReflectableEscape::sub_710053C804(sead::Vector3f* out, const sead::Vector3f& target, f32 dist) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();

    sead::Vector3f dir = pos - target;
    dir.y = 0;
    dir.normalize();
    if (dir.x == 0 && dir.y == 0 && dir.z == 0) {
        mActor->getMtx().getBase(dir, 2);
        dir.normalize();
        dir.negate();
    }

    const f32 length = (pos - target).length();
    *out = pos + dir * (length > dist * 2 ? -dist : dist);
}

void ReflectableEscape::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ReflectableEscape::loadParams_() {
    getStaticParam(&mEscapeDist_s, "EscapeDist");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mEscapeTimer_s, "EscapeTimer");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// 0x710053d0b8
// NON_MATCHING: register allocation (the original keeps the normalised front x / z in integer registers).
bool ReflectableEscape::sub_710053D0B8() {
    const auto& mtx = mActor->getMtx();
    sead::Vector3f front = mtx.getBase(2);
    front.y = 0.0f;
    const f32 x = mtx(0, 3);
    const f32 z = mtx(2, 3);
    front.normalize();
    sead::Vector3f to_target(mTargetPos_d->x - x, 0.0f, mTargetPos_d->z - z);
    to_target.normalize();
    const f32 min_cos = sead::Mathf::cos(sead::Mathf::deg2rad(60.0f));
    if (!(front.dot(to_target) >= min_cos))
        return false;
    sead::Vector3f to_escape(_58.x - x, 0.0f, _58.z - z);
    to_escape.normalize();
    return to_target.dot(to_escape) >= min_cos;
}

}  // namespace uking::ai
