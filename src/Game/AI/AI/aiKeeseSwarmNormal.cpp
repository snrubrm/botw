#include "Game/AI/AI/aiKeeseSwarmNormal.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

KeeseSwarmNormal::KeeseSwarmNormal(const InitArg& arg) : EnemyNormal(arg) {}

KeeseSwarmNormal::~KeeseSwarmNormal() = default;

bool KeeseSwarmNormal::init_(sead::Heap* heap) {
    return EnemyNormal::init_(heap);
}

void KeeseSwarmNormal::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNormal::enter_(params);
}

void KeeseSwarmNormal::calc_() {
    EnemyNormal::calc_();
}

void KeeseSwarmNormal::leave_() {
    EnemyNormal::leave_();
}

void KeeseSwarmNormal::loadParams_() {
    EnemyNormal::loadParams_();
}

bool KeeseSwarmNormal::m45(const sead::Vector3f& target_pos, ksys::act::BaseProcLink& target,
                           bool skip_own_pos) {
    if (!skip_own_pos && sub_71005D9F70(mActor))
        return true;
    if (target.hasProcInCalcState() && !m46(target_pos, target))
        return true;
    return false;
}

bool KeeseSwarmNormal::m46(const sead::Vector3f& pos, ksys::act::BaseProcLink& target) {
    sead::Vector3f center;
    m48(&center);
    const f32 area = sub_71003A234C(&target);
    const f32 area_sq = area * area;

    const bool has_target = target.hasProc();
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(&target, &accessor);
    const auto& mtx = accessor.getActorMtx();

    const f32 dx = center.x - pos.x;
    const f32 dz = center.z - pos.z;
    if (!(dx * dx + dz * dz < area_sq))
        return false;
    if (has_target) {
        const sead::Vector2f target_xz(mtx.m[0][3], mtx.m[2][3]);
        if (!((sead::Vector2f(center.x, center.z) - target_xz).squaredLength() < area_sq))
            return false;
    }
    return !sub_71005D9F4C(pos);
}

}  // namespace uking::ai
