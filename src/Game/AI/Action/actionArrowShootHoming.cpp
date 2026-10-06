#include "Game/AI/Action/actionArrowShootHoming.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

ArrowShootHoming::ArrowShootHoming(const InitArg& arg) : ArrowShootMove(arg) {}

ArrowShootHoming::~ArrowShootHoming() = default;

void ArrowShootHoming::enter_(ksys::act::ai::InlineParamPack* params) {
    ArrowShootMove::enter_(params);
}

void ArrowShootHoming::loadParams_() {
    ArrowShootMove::loadParams_();
    getStaticParam(&mSubAngMax_s, "SubAngMax");
    getStaticParam(&mHomingRate_s, "HomingRate");
    getStaticParam(&mNearDist_s, "NearDist");
    getDynamicParam(&mTargetActor_d, "TargetActor");
    getDynamicParam(&mHomingTargetPos_d, "HomingTargetPos");
}

void ArrowShootHoming::calc_() {
    ArrowShootMove::calc_();
}

bool ArrowShootHoming::sub_71000A21E8() {
    if (auto* bullet = sead::DynamicCast<ksys::act::Bullet>(mActor)) {
        if (bullet->_ba0.hasProc() && ksys::act::isPlayerProfile(&bullet->_ba0)) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&bullet->_ba0, &accessor);
            bool moving = false;
            if (accessor.sub_7100D12E64()) {
                const sead::Vector3f velocity = accessor.getVelocity();
                moving = velocity.length() >= 0.1f;
            }
            return moving;
        }
    }
    return false;
}

}  // namespace uking::action
