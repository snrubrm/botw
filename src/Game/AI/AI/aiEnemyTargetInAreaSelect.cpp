#include "Game/AI/AI/aiEnemyTargetInAreaSelect.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

EnemyTargetInAreaSelect::EnemyTargetInAreaSelect(const InitArg& arg) : TargetInAreaSelect(arg) {}

EnemyTargetInAreaSelect::~EnemyTargetInAreaSelect() = default;

bool EnemyTargetInAreaSelect::init_(sead::Heap* heap) {
    return TargetInAreaSelect::init_(heap);
}

// NON_MATCHING: FP register numbering of the centre offset / mtx row loads, and the original ends
// with fccmp + b.hi instead of two setcc; the arithmetic is identical
bool EnemyTargetInAreaSelect::m34() {
    bool in_area = false;
    if (auto* link = sub_71005D9050(mActor)) {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(link, &accessor)) {
            const sead::Matrix34f& target_mtx = accessor.getActorMtx();
            sead::Vector3f center;
            center.setMul(mActor->getMtx(), *mCentOffset_s);
            const f32 target_y = target_mtx.m[1][3];

            bool outside_xz = false;
            if (*mLengthXZ_s > 0.0f) {
                const f32 dx = target_mtx.m[0][3] - center.x;
                const f32 dz = target_mtx.m[2][3] - center.z;
                outside_xz = sead::Mathf::sqrt(dx * dx + dz * dz) >= *mLengthXZ_s;
            }
            if (!outside_xz) {
                if (*mLengthMaxY_s <= *mLengthMinY_s) {
                    in_area = true;
                } else {
                    const f32 dy = target_y - center.y;
                    if (dy < *mLengthMaxY_s && dy > *mLengthMinY_s)
                        in_area = true;
                }
            }
        }
    }
    return in_area;
}

void EnemyTargetInAreaSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    TargetInAreaSelect::enter_(params);
}

void EnemyTargetInAreaSelect::calc_() {
    TargetInAreaSelect::calc_();
}

void EnemyTargetInAreaSelect::leave_() {
    TargetInAreaSelect::leave_();
}

void EnemyTargetInAreaSelect::loadParams_() {
    TargetInAreaSelect::loadParams_();
    getStaticParam(&mLengthXZ_s, "LengthXZ");
    getStaticParam(&mLengthMaxY_s, "LengthMaxY");
    getStaticParam(&mLengthMinY_s, "LengthMinY");
    getStaticParam(&mCentOffset_s, "CentOffset");
}

}  // namespace uking::ai
