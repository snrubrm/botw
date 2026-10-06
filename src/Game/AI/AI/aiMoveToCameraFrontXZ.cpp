#include "Game/AI/AI/aiMoveToCameraFrontXZ.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/Utils/MathUtil.h"

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
