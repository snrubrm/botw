#include "Game/AI/Action/actionArrowShootHoming.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actBullet.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::action {

ArrowShootHoming::ArrowShootHoming(const InitArg& arg) : ArrowShootMove(arg) {}

ArrowShootHoming::~ArrowShootHoming() = default;

void ArrowShootHoming::enter_(ksys::act::ai::InlineParamPack* params) {
    ArrowShootMove::enter_(params);
    mTail._178 = _e4.x;
    mTail._17c = _e4.y;
    mTail._180 = _e4.z;
    mTail._1b4 = 0;
    if (mTargetActor_d->hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(mTargetActor_d, &accessor);
        const sead::Matrix34f target_mtx = accessor.getActorMtx();
        sead::Matrix34f inverse;
        inverse.setInverse(target_mtx);
        sead::Matrix34f mtx = mActor->getMtx();
        mtx.setTranslation(*mHomingTargetPos_d);
        mTail._184.setMul(inverse, mtx);
    }
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
