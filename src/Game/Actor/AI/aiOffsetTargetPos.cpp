#include "Game/Actor/AI/aiOffsetTargetPos.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

OffsetTargetPos::OffsetTargetPos(const InitArg& arg) : TargetActorPos(arg) {}

OffsetTargetPos::~OffsetTargetPos() = default;

bool OffsetTargetPos::init_(sead::Heap* heap) {
    return TargetActorPos::init_(heap);
}

void OffsetTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetActorPos::enter_(params);
}

void OffsetTargetPos::calc_() {
    TargetActorPos::calc_();
}

void OffsetTargetPos::leave_() {
    TargetActorPos::leave_();
}

void OffsetTargetPos::loadParams_() {
    TargetActorPos::loadParams_();
    getStaticParam(&mDir_s, "Dir");
    getStaticParam(&mOffset_s, "Offset");
    getStaticParam(&mMinDist_s, "MinDist");
    getStaticParam(&mSideDist_s, "SideDist");
    getStaticParam(&mIsRandSide_s, "IsRandSide");
}

// NON_MATCHING: two commuted fmul/fadd operands near the end (regalloc)
void OffsetTargetPos::m35(sead::Vector3f* pos) {
    sead::Vector3f diff;
    m36(&diff);
    const sead::Vector3f my_pos = mActor->getMtx().getTranslation();
    diff -= my_pos;

    sead::Vector3f dir(diff.x, 0.0f, diff.z);
    const f32 dist = dir.normalize();

    sead::Vector3f side = sead::Vector3f::zero;
    if (*mSideDist_s != 0.0f) {
        side.set(*mSideDist_s, 0.0f, 0.0f);
        ksys::util::sub_71011EF010(&side, std::atan2(dir.x, dir.z));
        if (*mIsRandSide_s) {
            const s32 sign = (sead::GlobalRandom::instance()->getU32() & 2) - 1;
            side *= sign;
        }
    }

    dir *= sead::Mathf::max(*mMinDist_s, dist + *mOffset_s) * *mDir_s;
    dir.y = diff.y;
    pos->setAdd(my_pos + dir, side);
}

}  // namespace uking::ai
