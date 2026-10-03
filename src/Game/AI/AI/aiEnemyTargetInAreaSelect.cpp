#include "Game/AI/AI/aiEnemyTargetInAreaSelect.h"
#include <cmath>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

EnemyTargetInAreaSelect::EnemyTargetInAreaSelect(const InitArg& arg) : TargetInAreaSelect(arg) {}

EnemyTargetInAreaSelect::~EnemyTargetInAreaSelect() = default;

bool EnemyTargetInAreaSelect::init_(sead::Heap* heap) {
    return TargetInAreaSelect::init_(heap);
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

// NON_MATCHING: same loads / math; the original combines `dy < max && dy > min` with fccmp + branch and keeps
// the Vector3f in s10 / s11 / s9 (register numbering) where we get cset + and
bool EnemyTargetInAreaSelect::m34() {
    auto* link = sub_71005D9050(mActor);
    if (!link)
        return false;
    ksys::act::ActorConstDataAccess accessor;
    if (!ksys::act::acquireActor(link, &accessor))
        return false;
    const auto& target_mtx = accessor.getActorMtx();
    const auto& actor_mtx = mActor->getMtx();
    const sead::Vector3f& offset = *mCentOffset_s;
    const f32 y = actor_mtx(1, 3) + (offset.x * actor_mtx(1, 0) + offset.y * actor_mtx(1, 1) +
                                     offset.z * actor_mtx(1, 2));
    const f32 dy = target_mtx(1, 3) - y;
    if (*mLengthXZ_s > 0) {
        const f32 z = actor_mtx(2, 3) + (offset.x * actor_mtx(2, 0) + offset.y * actor_mtx(2, 1) +
                                         offset.z * actor_mtx(2, 2));
        const f32 x = actor_mtx(0, 3) + (offset.x * actor_mtx(0, 0) + offset.y * actor_mtx(0, 1) +
                                         offset.z * actor_mtx(0, 2));
        const f32 dz = target_mtx(2, 3) - z;
        const f32 dx = target_mtx(0, 3) - x;
        if (std::sqrt(dx * dx + dz * dz) >= *mLengthXZ_s)
            return false;
    }
    if (!(*mLengthMaxY_s > *mLengthMinY_s))
        return true;
    if (dy < *mLengthMaxY_s && !(dy <= *mLengthMinY_s))
        return true;
    return false;
}

void EnemyTargetInAreaSelect::loadParams_() {
    TargetInAreaSelect::loadParams_();
    getStaticParam(&mLengthXZ_s, "LengthXZ");
    getStaticParam(&mLengthMaxY_s, "LengthMaxY");
    getStaticParam(&mLengthMinY_s, "LengthMinY");
    getStaticParam(&mCentOffset_s, "CentOffset");
}

}  // namespace uking::ai
