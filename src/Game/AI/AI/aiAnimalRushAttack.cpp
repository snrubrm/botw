#include "Game/AI/AI/aiAnimalRushAttack.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

AnimalRushAttack::AnimalRushAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalRushAttack::~AnimalRushAttack() = default;

bool AnimalRushAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalRushAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* controller = mActor->getCharacterController();
    mActor->m45();
    if (!controller) {
        setFailed();
        return;
    }

    if (!sub_710030CB64(true))
        setFailed();
    const s32 time = *mUpdateTargetPosTime_s;
    if (time < 0)
        _50 = ksys::Timer(1.0f, 1.0f, 0.0f);
    else
        _50 = ksys::Timer(f32(time), f32(time));
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_5c, "TargetPos", -1);
    changeChild("突進", &pack);
}

void AnimalRushAttack::calc_() {
    if (!isFinished() && !isFailed()) {
        if (!(_50.value <= sead::Mathf::epsilon())) {
            sub_710030CB64(false);
            getCurrentChild()->setDynamicParam(_5c, "TargetPos");
            _50.update();
        }
        auto* child = getCurrentChild();
        if (child->isFinished() || child->isFailed()) {
            if (getCurrentChild()->isFinished())
                setFinished();
            else
                setFailed();
        } else {
            child->isChangeable();
        }
    }
}

bool AnimalRushAttack::sub_710030CB64(bool force) {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sead::Vector3f dir{mTargetPos_d->x - pos.x, 0.0f, mTargetPos_d->z - pos.z};
    dir.normalize();
    const sead::Vector3f goal = *mTargetPos_d + dir * *mAttackPosOffsetLength_s;
    sead::Vector3f out;
    if (sub_710072FAB0(mActor, goal, &out, -1, -1.0f, -1.0f)) {
        _5c = goal;
        return true;
    }

    const sead::Vector3f result = out;
    const f32 out_dist =
        (pos.x - result.x) * (pos.x - result.x) + (pos.z - result.z) * (pos.z - result.z);
    const f32 target_dist = (pos.x - mTargetPos_d->x) * (pos.x - mTargetPos_d->x) +
                            (pos.z - mTargetPos_d->z) * (pos.z - mTargetPos_d->z);
    const bool closer = !(out_dist < target_dist);
    if (closer || force)
        _5c = result;
    return closer;
}

}  // namespace uking::ai
