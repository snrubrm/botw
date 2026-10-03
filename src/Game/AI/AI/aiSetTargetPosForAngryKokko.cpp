#include "Game/AI/AI/aiSetTargetPosForAngryKokko.h"
#include <math/seadMathCalcCommon.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SetTargetPosForAngryKokko::SetTargetPosForAngryKokko(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SetTargetPosForAngryKokko::~SetTargetPosForAngryKokko() = default;

bool SetTargetPosForAngryKokko::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SetTargetPosForAngryKokko::enter_(ksys::act::ai::InlineParamPack* params) {
    _7c = 0;
    sead::Vector3f pos;
    if (!sub_7100568490(&pos))
        mActor->getMtx().getTranslation(pos);

    ksys::act::ai::InlineParamPack child_params;
    child_params.addVec3(pos, "TargetPos", -1);
    changeChild("子アクション", &child_params);
}

void SetTargetPosForAngryKokko::calc_() {
    _70.update();
    if (*mUpdateTargetInterval_s < 0)
        return;

    if (_70.value <= sead::Mathf::epsilon()) {
        sead::Vector3f pos;
        if (sub_7100568490(&pos))
            getCurrentChild()->setDynamicParam(pos, "TargetPos");
    }
}

bool SetTargetPosForAngryKokko::sub_7100568490(sead::Vector3f* pos) {
    if (_7c > *mMaxUpdateNum_s)
        return false;

    sead::Vector3f actor_pos;
    mActor->getMtx().getTranslation(actor_pos);
    ksys::act::ActorConstDataAccess accessor;
    sead::Vector3f target;
    if (ksys::act::acquireActor(mTargetActor_d, &accessor)) {
        if (ksys::act::isEnemyProfile(accessor))
            target = accessor.getField44C_Vec3();
        else
            accessor.getActorMtx().getTranslation(target);
    } else {
        sead::Vector3f front;
        mActor->getMtx().getBase(front, 2);
        target = actor_pos + front;
    }
    target.y += *mHeightOffset_s;

    sead::Vector3f dir = target - actor_pos;
    dir.normalize();

    sead::Vector3f result = target + dir * *mAddLength_s;
    const f32 range = *mRandRange_s;
    if (sead::GlobalRandom::instance()->getF32() < *mRandRate_s) {
        result.x += sead::GlobalRandom::instance()->getF32Range(-range, range);
        result.z += sead::GlobalRandom::instance()->getF32Range(-range, range);
    }
    *pos = result;

    const f32 interval = *mUpdateTargetInterval_s + 0.5f;
    _70 = ksys::Timer(interval, interval);
    ++_7c;
    return true;
}

void SetTargetPosForAngryKokko::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SetTargetPosForAngryKokko::loadParams_() {
    getStaticParam(&mUpdateTargetInterval_s, "UpdateTargetInterval");
    getStaticParam(&mMaxUpdateNum_s, "MaxUpdateNum");
    getStaticParam(&mAddLength_s, "AddLength");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getStaticParam(&mRandRange_s, "RandRange");
    getStaticParam(&mRandRate_s, "RandRate");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
