#include "Game/Actor/AI/aiMoveToCameraFrontXZ.h"
#include <cmath>
#include <geom/seadGeometry.h>
#include <gsys/gsysModel.h>
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "Game/Actor/aiUnk_7100D8C538.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Camera/CameraMgr.h"
#include "KingSystem/Utils/MathUtil.h"
#include "KingSystem/System/Timer.h"
#include "Game/Actor/aiUnk_71007320F0.h"
#include "Game/Actor/aiUnk_71007377D4.h"
#include "Game/Actor/actCameraUtil.h"

namespace ksys {
// Source namespace inferred from the CameraMgr helper family; declarations only.
f32 sub_7100D8C888();
f32 sub_7100D8C8FC();
}  // namespace ksys

namespace uking::ai {

MoveToCameraFrontXZ::MoveToCameraFrontXZ(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoveToCameraFrontXZ::~MoveToCameraFrontXZ() = default;

bool MoveToCameraFrontXZ::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: stack layout and operand scheduling differ from the original.
void MoveToCameraFrontXZ::enter_(ksys::act::ai::InlineParamPack* params) {
    _80 = 0;
    _84 = 0;
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    _88 = pos;
    sub_71004B33BC(&_88);

    // Move straight unless the player is near the line from the actor to the destination, between the two.
    const auto& player = sub_71005D9330(mActor);
    const sead::Vector2f point(player.x, player.z);
    sead::Vector2f dir(_88.x - pos.x, _88.z - pos.z);
    const sead::Line2f line(sead::Vector2f(pos.x, pos.z), dir);
    if (sead::Geometry::calcSquaredDistancePointToLine(point, line, nullptr) > *mAvoidPlayerDist_s + 0.1f ||
        (_88 - pos).dot(sub_71005D9330(mActor) - pos) < 0.0f) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(_88, "TargetPos", -1);
        changeChild("移動", &pack);
    } else {
        changeToAvoidPlayerMove(pos, _88);
    }
}

// NON_MATCHING: stack slot of `pos`, the line direction store (packed into one register) and some fsub scheduling
void MoveToCameraFrontXZ::calc_() {
    const sead::Vector3f pos = mActor->getMtx().getTranslation();
    sub_71004B33BC(&_88);

    // Whether the player is far enough from the actor's position and closer to the camera than it.
    const auto isPlayerInFront = [&] {
        const auto& player = sub_71005D9330(mActor);
        const f32 dx = player.x - pos.x;
        const f32 dz = player.z - pos.z;
        if (dx * dx + dz * dz <= *mMinDistFromPlayer_s * *mMinDistFromPlayer_s)
            return false;
        sead::Vector3f camera;
        ksys::sub_7100D8C6AC(&camera);
        const auto& player2 = sub_71005D9330(mActor);
        const f32 px = camera.x - player2.x;
        const f32 pz = camera.z - player2.z;
        const f32 ax = camera.x - pos.x;
        const f32 az = camera.z - pos.z;
        if (px * px + pz * pz >= ax * ax + az * az)
            return false;
        return true;
    };
    const auto isReachable = [this] {
        auto* actor = mActor;
        const auto& player = sub_71005D9330(actor);
        return sub_710072CB78(actor, player, nullptr,
                              *mReachableRadius_s + sub_71007320F0(mActor, *mWeaponIdx_s), -1);
    };
    // Whether the player is close to the line from the actor's position towards the destination.
    const auto distanceToLine = [&] {
        const auto& player = sub_71005D9330(mActor);
        const sead::Vector2f point(player.x, player.z);
        const sead::Line2f line(sead::Vector2f(pos.x, pos.z), sead::Vector2f(_88.x - pos.x, _88.z - pos.z));
        return sead::Geometry::calcSquaredDistancePointToLine(point, line, nullptr);
    };
    const auto isPlayerAhead = [&] {
        const auto& player = sub_71005D9330(mActor);
        return (_88 - pos).dot(player - pos) < 0.0f;
    };

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        const bool moving = isCurrentChild("移動");
        const bool finished = child->isFinished();
        if (moving) {
            if (finished) {
                setFinished();
                return;
            }
        } else if (finished) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(_88, "TargetPos", -1);
            changeChild("移動", &pack);
            return;
        }
        if (*mIsSuccessByLineReachable_s && isPlayerInFront() && isReachable())
            setFinished();
        else
            setFailed();
        return;
    }

    if (child->isChangeable()) {
        if (!sub_71004B4180(1.0f, pos)) {
            if (isCurrentChild("移動") && _84 < *mReverseCount_s) {
                if (sub_71004B42F0()) {
                    _80 = 0;
                } else {
                    ksys::Timer::update(&_80, 1.0f);
                    if (_80 > f32(*mReverseTimer_s)) {
                        _80 = 0;
                        ++_84;
                        changeChild("反転");
                        return;
                    }
                }
            }
        } else if (sub_71004B4180(0.6f, pos) && isPlayerInFront()) {
            const auto& player = sub_71005D9330(mActor);
            const f32 dx = player.x - pos.x;
            const f32 dz = player.z - pos.z;
            const f32 dist = *mDistFromPlayer_s * 0.8f;
            if (dx * dx + dz * dz >= dist * dist && (!*mIsSuccessByLineReachable_s || isReachable()))
                setFinished();
        }

        if (isCurrentChild("移動")) {
            if (distanceToLine() <= *mAvoidPlayerDist_s && !isPlayerAhead()) {
                changeToAvoidPlayerMove(pos, _88);
                return;
            }
        } else if (isCurrentChild("プレイヤー回避移動")) {
            if (distanceToLine() > *mAvoidPlayerDist_s + 0.1f || isPlayerAhead()) {
                ksys::act::ai::InlineParamPack pack;
                pack.addVec3(_88, "TargetPos", -1);
                changeChild("移動", &pack);
                return;
            }
        }
    }

    if (isCurrentChild("移動")) {
        getCurrentChild()->setDynamicParam(_88, "TargetPos");
    } else if (isCurrentChild("プレイヤー回避移動")) {
        sead::Vector3f target;
        sub_71004B43E4(&target, pos, _88);
        getCurrentChild()->setDynamicParam(target, "TargetPos");
    }
}

void MoveToCameraFrontXZ::changeToAvoidPlayerMove(const sead::Vector3f& a, const sead::Vector3f& b) {
    sead::Vector3f pos;
    sub_71004B43E4(&pos, a, b);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("プレイヤー回避移動", &pack);
}

void MoveToCameraFrontXZ::sub_71004B43E4(sead::Vector3f* out, const sead::Vector3f& a, const sead::Vector3f& b) {
    const sead::Vector3f& player = sub_71005D9330(mActor);
    sead::Vector3f to_b = b;
    to_b -= player;
    to_b.normalize();
    sead::Vector3f to_a = a;
    to_a -= player;
    sead::Vector3f dir;
    ksys::util::sub_71011EFA00(&dir, to_a, to_b);
    dir.normalize();
    out->setScaleAdd(*mAvoidPlayerDist_s, dir, player);
}

// NON_MATCHING: the original multiplies the field of view by 0.5 right after the call (before the camera position
// query); ours sinks the multiplication to its use and keeps the constant in a callee-saved register
bool MoveToCameraFrontXZ::sub_71004B4180(f32 scale, const sead::Vector3f& pos) {
    if (!sub_71005D8FBC(mActor))
        return true;
    sead::Vector3f direction;
    ksys::sub_7100D8C7FC(&direction);
    direction.y = 0;
    direction.normalize();
    const f32 fovy = ksys::sub_7100D8C888();
    const f32 half_angle = sub_7100924C08(fovy, ksys::sub_7100D8C8FC()) * 0.5f;
    sead::Vector3f camera_pos;
    ksys::sub_7100D8C6AC(&camera_pos);
    sead::Vector3f to_pos(pos.x - camera_pos.x, 0, pos.z - camera_pos.z);
    to_pos.normalize();
    return to_pos.dot(direction) >= std::cos(half_angle * scale);
}

bool MoveToCameraFrontXZ::sub_71004B42F0() {
    auto* model = mActor->getModel();
    if (!model)
        return false;
    sead::BoundSphere3f bounds;
    model->getBounding(&bounds);
    sead::Vector3f center;
    center.setMul(mActor->getMtx(), bounds.getCenter());
    return visibilityCheckMaybe(center, bounds.getRadius());
}

void MoveToCameraFrontXZ::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoveToCameraFrontXZ::loadParams_() {
    getStaticParam(&mReverseTimer_s, "ReverseTimer");
    getStaticParam(&mReverseCount_s, "ReverseCount");
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mDistFromPlayer_s, "DistFromPlayer");
    getStaticParam(&mMinDistFromPlayer_s, "MinDistFromPlayer");
    getStaticParam(&mAvoidPlayerDist_s, "AvoidPlayerDist");
    getStaticParam(&mAddLineCheckNavRadius_s, "AddLineCheckNavRadius");
    getStaticParam(&mReachableRadius_s, "ReachableRadius");
    getStaticParam(&mIsSuccessByLineReachable_s, "IsSuccessByLineReachable");
}

}  // namespace uking::ai
