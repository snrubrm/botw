#include "Game/AI/AI/aiFlyMoveToTarget.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

FlyMoveToTarget::FlyMoveToTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

FlyMoveToTarget::~FlyMoveToTarget() = default;

bool FlyMoveToTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void FlyMoveToTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _b4 = 0;
    sead::Vector3f target = *mTargetPos_d;
    target.y += *mOffsetHeight_s;
    _60.clear();
    _a4 = false;
    _a8 = 0;
    _ac = 0;
    _98 = target;
    _b0 = 1.0f;
    sub_71003D4414();
}

void FlyMoveToTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void FlyMoveToTarget::loadParams_() {
    getStaticParam(&mMoveFailCount_s, "MoveFailCount");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mOffsetHeight_s, "OffsetHeight");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// NON_MATCHING: the original adds in the other operand order (fadd y, h) with the height loaded first
void FlyMoveToTarget::changeToTargetPosMove() {
    sead::Vector3f target;
    target = *mTargetPos_d;
    target.y += *mOffsetHeight_s;
    _60.clear();
    _60.pushBack(target);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target, "TargetPos", -1);
    changeChild("目標位置移動", &pack);
}

void FlyMoveToTarget::changeToDescend(f32 height) {
    sead::Vector3f position = mActor->getMtx().getTranslation();
    position.y = height;
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(position, "TargetPos", -1);
    pack.addFloat(height, "TargetHeight", -1);
    changeChild("下降", &pack);
}

void FlyMoveToTarget::changeToViaPointMove() {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_60[0], "TargetPos", -1);
    changeChild("経由点移動", &pack);
}

// NON_MATCHING: the original adds in the other operand order (fadd y, h)
void FlyMoveToTarget::changeToMoveFar() {
    const sead::Vector3f& target = *mTargetPos_d;
    sead::Vector3f pos;
    pos.x = target.x;
    pos.y = target.y;
    pos.z = target.z;
    const f32 height = *mOffsetHeight_s;
    pos.y += height;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("遠距離移動", &pack);
}

// NON_MATCHING: the original adds in the other operand order (fadd y, h)
void FlyMoveToTarget::changeToMoveOnNavMesh() {
    const sead::Vector3f& target = *mTargetPos_d;
    sead::Vector3f pos;
    pos.x = target.x;
    pos.y = target.y;
    pos.z = target.z;
    const f32 height = *mOffsetHeight_s;
    pos.y += height;

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("ナビメッシュ移動", &pack);
}

}  // namespace uking::ai
