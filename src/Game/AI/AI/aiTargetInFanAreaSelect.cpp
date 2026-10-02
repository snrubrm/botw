#include "Game/AI/AI/aiTargetInFanAreaSelect.h"
#include <cmath>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

TargetInFanAreaSelect::TargetInFanAreaSelect(const InitArg& arg) : TargetInAreaSelect(arg) {}

TargetInFanAreaSelect::~TargetInFanAreaSelect() = default;

bool TargetInFanAreaSelect::init_(sead::Heap* heap) {
    return TargetInAreaSelect::init_(heap);
}

void TargetInFanAreaSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetInAreaSelect::enter_(params);
}

void TargetInFanAreaSelect::calc_() {
    TargetInAreaSelect::calc_();
}

void TargetInFanAreaSelect::leave_() {
    TargetInAreaSelect::leave_();
}

void TargetInFanAreaSelect::loadParams_() {
    TargetInAreaSelect::loadParams_();
    getStaticParam(&mNearYMax_s, "NearYMax");
    getStaticParam(&mNearYMin_s, "NearYMin");
    getStaticParam(&mFarYMax_s, "FarYMax");
    getStaticParam(&mFarYMin_s, "FarYMin");
    getStaticParam(&mXZRange_s, "XZRange");
    getStaticParam(&mAngle_s, "Angle");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

bool TargetInFanAreaSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool TargetInFanAreaSelect::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

bool TargetInFanAreaSelect::isChangeable() const {
    return ksys::act::ai::Ai::isChangeable() || getCurrentChild()->isChangeable();
}

bool TargetInFanAreaSelect::m34() {
    sead::Vector3f pos;
    m37(&pos);
    sead::Vector3f diff = *mTargetPos_d;
    diff -= pos;
    sead::Vector3f dir;
    m38(&dir);

    sead::Vector3f xz_dir{diff.x, 0.0f, diff.z};
    const f32 dist = xz_dir.normalize();
    if (!(xz_dir.dot(dir) >= std::cos(*mAngle_s)))
        return false;

    if (dist > *mXZRange_s)
        return false;

    const f32 rate = dist / *mXZRange_s;
    if (diff.y < *mNearYMin_s + rate * (*mFarYMin_s - *mNearYMin_s) ||
        *mNearYMax_s + rate * (*mFarYMax_s - *mNearYMax_s) < diff.y) {
        return false;
    }
    return true;
}

void TargetInFanAreaSelect::m35(ksys::act::ai::InlineParamPack* params) {
    params->addVec3(*mTargetPos_d, "TargetPos", -1);
}

void TargetInFanAreaSelect::m36(ksys::act::ai::InlineParamPack* params) {
    params->addVec3(*mTargetPos_d, "TargetPos", -1);
}

void TargetInFanAreaSelect::m37(sead::Vector3f* out) {
    mActor->getMtx().getTranslation(*out);
}

void TargetInFanAreaSelect::m38(sead::Vector3f* out) {
    mActor->getMtx().getBase(*out, 2);
}

}  // namespace uking::ai
