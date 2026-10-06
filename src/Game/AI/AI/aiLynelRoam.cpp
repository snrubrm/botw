#include "Game/AI/AI/aiLynelRoam.h"
#include <random/seadGlobalRandom.h>
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

LynelRoam::LynelRoam(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelRoam::~LynelRoam() = default;

bool LynelRoam::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

bool LynelRoam::sub_7100498398(sead::Vector3f* out) {
    const f32 x = mActor->getMtx().m[0][3];
    const f32 z = mActor->getMtx().m[2][3];
    sead::Vector3f direction;
    sub_71000891C8(&direction, mActor);
    const f32 angle = sead::GlobalRandom::instance()->getF32() * (2.0f * sead::Mathf::pi() / 3);
    sead::Vector3f ray = direction;
    ksys::util::sub_71011EF010(&ray, angle);
    sead::Vector3f hit;
    for (int i = 0; i < 3; ++i) {
        if (sub_710072FD28(mActor, ray, &hit, -1, *mTargetDistMax_s, -1.0f, -1.0f, -1.0f)) {
            *out = hit;
            return true;
        }
        if (sead::Vector2f(hit.x - x, hit.z - z).squaredLength() >=
            *mTargetDistMin_s * *mTargetDistMin_s) {
            *out = hit;
            return true;
        }
        ksys::util::sub_71011EF010(&ray, 2.0f * sead::Mathf::pi() / 3);
    }
    return false;
}

// NON_MATCHING: scheduling of the random-number conversions and constants (the original converts the first
// draw before the third getU32 call) and stack slots of the ray / hit.
bool LynelRoam::sub_710049951C(sead::Vector3f* out, const sead::Vector3f& direction) {
    auto* random = sead::GlobalRandom::instance();
    const f32 randoms[3] = {random->getF32(), random->getF32(), random->getF32()};
    const f32 offsets[3] = {0.0f, 0.7853982f, -0.7853982f};
    sead::Vector3f hit;
    for (int i = 0; i < 3; ++i) {
        sead::Vector3f ray = direction;
        ksys::util::sub_71011EF010(&ray, randoms[i] * 0.34906584f - 0.17453292f + offsets[i]);
        if (sub_710072FD28(mActor, ray, &hit, -1, *mTargetDistMax_s,
                           *mTargetDistMax_s - *mTargetDistMin_s, -1.0f, -1.0f)) {
            *out = hit;
            return true;
        }
    }
    return false;
}

// NON_MATCHING: timer load scheduling and vector stack placement differ.
void LynelRoam::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 time = *mNoSpAttackMoveTime_s;
    _b0 = time;
    _b4 = _b8 = time;
    _c8.reset(sead::GlobalRandom::instance()->getS32Range(*mFreeIntervalMin_s,
                                                      *mFreeIntervalMax_s));
    _bc.reset(*mNoMoveTime_s);
    sead::Vector3f position;
    if (!sub_7100498398(&position)) {
        sead::Vector3f direction;
        sub_71000891C8(&direction, mActor);
        if (!sub_710049951C(&position, direction)) {
            changeChild("待機");
            return;
        }
    }
    changeToMove(position);
}

void LynelRoam::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelRoam::loadParams_() {
    getStaticParam(&mFreeIntervalMin_s, "FreeIntervalMin");
    getStaticParam(&mFreeIntervalMax_s, "FreeIntervalMax");
    getStaticParam(&mFreePer_s, "FreePer");
    getStaticParam(&mMoveIntervalMin_s, "MoveIntervalMin");
    getStaticParam(&mMoveIntervalMax_s, "MoveIntervalMax");
    getStaticParam(&mNoMoveTime_s, "NoMoveTime");
    getStaticParam(&mNoSpAttackMoveTime_s, "NoSpAttackMoveTime");
    getStaticParam(&mSpAttackServiceTime_s, "SpAttackServiceTime");
    getStaticParam(&mRepathTime_s, "RepathTime");
    getStaticParam(&mTerritory_s, "Territory");
    getStaticParam(&mTargetDistMin_s, "TargetDistMin");
    getStaticParam(&mTargetDistMax_s, "TargetDistMax");
    getStaticParam(&mSpAttackServiceDist_s, "SpAttackServiceDist");
    getStaticParam(&mSpAttackServiceAngle_s, "SpAttackServiceAngle");
    getDynamicParam(&mCentralPos_d, "CentralPos");
}

void LynelRoam::changeToMove(const sead::Vector3f& pos) {
    if (!isCurrentChild("移動")) {
        const s32 min = *mMoveIntervalMin_s;
        const s32 max = *mMoveIntervalMax_s;
        const s32 time = sead::GlobalRandom::instance()->getS32Range(min, max);
        _e0 = ksys::Timer(time, time);
    }

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("移動", &pack);
}

}  // namespace uking::ai
