#include "Game/AI/AI/aiNushiWarp.h"
#include <math/seadMatrix.h>
#include <random/seadGlobalRandom.h>
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapRail.h"

namespace uking::ai {

NushiWarp::NushiWarp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NushiWarp::~NushiWarp() = default;

bool NushiWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: in the farthest-point loop the original stores target.x after updating max_dist
void NushiWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    const sead::Vector3f player_pos = getPlayerPosition();
    sead::Vector3f target = sead::Vector3f::zero;

    ksys::map::Rail* rail = nullptr;
    if (mActor) {
        if (auto* object = mActor->getMapObject()) {
            if (auto** rails = object->getRails())
                rail = rails[0];
        }
    }
    if (!rail) {
        setFailed();
        return;
    }

    const int num_points = rail->getNumPoints();
    f32 max_dist = 0.0f;
    for (int i = 0; i < num_points; ++i) {
        const sead::Vector3f& point = rail->getPointTranslate(i);
        const f32 dx = point.x - player_pos.x;
        const f32 dz = point.z - player_pos.z;
        const f32 dist = dx * dx + dz * dz;
        if (dist > max_dist) {
            max_dist = dist;
            target = point;
        }
    }
    if (target.x == 0.0f && target.y == 0.0f && target.z == 0.0f) {
        const sead::Vector3f& translate = mActor->getMapObject()->getTranslate();
        target = {translate.x, translate.y, translate.z};
    }

    sead::Vector3f dir = player_pos - target;
    dir.normalize();
    const s32 sign = (sead::GlobalRandom::instance()->getU32() & 2) - 1;
    const f32 angle = sign * sead::Mathf::piHalf();
    sead::Matrix34f rot;
    rot.makeR({0.0f, angle, 0.0f});
    sead::Vector3f front;
    front.setRotated(rot, dir);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    pack.addVec3(front, "TargetFoward", -1);
    changeChild("ワープ", &pack);
}

void NushiWarp::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return;

    if (child->isFinished())
        setFinished();
    else
        setFailed();
}

void NushiWarp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NushiWarp::loadParams_() {}

}  // namespace uking::ai
