#include "Game/AI/AI/aiMoveToCameraFrontXZ.h"
#include <cmath>
#include <gsys/gsysModel.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100D8C538.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/System/CameraMgr.h"
#include "KingSystem/Utils/MathUtil.h"
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

void MoveToCameraFrontXZ::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
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
