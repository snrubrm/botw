#include "Game/AI/AI/aiTargetPosOffset.h"
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::ai {

TargetPosOffset::TargetPosOffset(const InitArg& arg) : TargetPosAI(arg) {}

TargetPosOffset::~TargetPosOffset() = default;

bool TargetPosOffset::init_(sead::Heap* heap) {
    return TargetPosAI::init_(heap);
}

void TargetPosOffset::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetPosAI::enter_(params);
}

void TargetPosOffset::calc_() {
    TargetPosAI::calc_();
}

void TargetPosOffset::leave_() {
    TargetPosAI::leave_();
}

void TargetPosOffset::loadParams_() {
    TargetPosAI::loadParams_();
    getStaticParam(&mDir_s, "Dir");
    getStaticParam(&mOffset_s, "Offset");
    getStaticParam(&mMinDist_s, "MinDist");
    getStaticParam(&mSideDist_s, "SideDist");
    getStaticParam(&mIsRandSide_s, "IsRandSide");
}

// NON_MATCHING: regalloc (my_pos.x/z registers swapped, commuted fmul/fadd operands)
void TargetPosOffset::m35(sead::Vector3f* pos) {
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

    f32 offset = sead::Mathf::max(*mMinDist_s, dist + *mOffset_s);
    offset *= *mDir_s;
    dir *= offset;
    pos->x = my_pos.x + dir.x + side.x;
    pos->y = my_pos.y + diff.y + side.y;
    pos->z = my_pos.z + dir.z + side.z;
}

}  // namespace uking::ai
