#include "Game/AI/Action/actionSmallDamageDirectPreTargetBone.h"
#include <math/seadMathCalcCommon.h>
#include "Game/AI/aiUnk_710072BA90.h"
#include "Game/Damage/dmgDamageManager.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Utils/MathUtil.h"

namespace uking::action {

SmallDamageDirectPreTargetBone::SmallDamageDirectPreTargetBone(const InitArg& arg)
    : SmallDamage(arg) {}

SmallDamageDirectPreTargetBone::~SmallDamageDirectPreTargetBone() = default;

// NON_MATCHING: scheduling / register naming of the first (hit position - actor position) step; the original stores
// the zero y component before the subtractions and keeps x in s9 / z in s8.
void SmallDamageDirectPreTargetBone::m38() {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;
    if (*mIsSetHitPosSelecter_s) {
        if (auto* manager = sub_710072BA90(mActor)) {
            sead::Vector3f hit_pos;
            if (manager->getPosition(&hit_pos)) {
                sead::Vector3f dir;
                dir.set(hit_pos);
                dir.x -= mActor->getMtx().m[0][3];
                dir.y = 0.0f;
                dir.z -= mActor->getMtx().m[2][3];
                dir.normalize();
                const auto& mtx = mActor->getMtx();
                const sead::Vector3f world = dir;
                dir.x = world.x * mtx(0, 0) + world.y * mtx(1, 0) + world.z * mtx(2, 0);
                dir.y = world.x * mtx(0, 1) + world.y * mtx(1, 1) + world.z * mtx(2, 1);
                dir.z = world.x * mtx(0, 2) + world.y * mtx(1, 2) + world.z * mtx(2, 2);
                sead::Vector3f axis;
                f32 angle;
                ksys::util::sub_71011EEB08(&axis, &angle, dir, sead::Vector3f::ez, sead::Vector3f::ey);
                as_list->x_6(9, 0, sead::Mathf::rad2deg(axis.y * angle));
            }
        }
    }
    as_list->sub_710115B140(mASName_s.cstr(), 0, *mPreTargetBone_s, 0, 0);
}

void SmallDamageDirectPreTargetBone::loadParams_() {
    TakeHitImpactForce::loadParams_();
    getStaticParam(&mPreTargetBone_s, "PreTargetBone");
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mIsSetHitPosSelecter_s, "IsSetHitPosSelecter");
}

}  // namespace uking::action
