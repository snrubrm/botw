#include "Game/AI/AI/aiEscapeFromTargetFront.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

EscapeFromTargetFront::EscapeFromTargetFront(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EscapeFromTargetFront::~EscapeFromTargetFront() = default;

bool EscapeFromTargetFront::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EscapeFromTargetFront::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = 0;
    const int dir = m34();
    const sead::Vector3f& target_pos = sub_71005D9330(mActor);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(target_pos, "TargetPos", -1);
    pack.addInt(dir, "RotDir", -1);
    changeChild("回転移動", &pack);
}

void EscapeFromTargetFront::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EscapeFromTargetFront::loadParams_() {
    getStaticParam(&mMaxTime_s, "MaxTime");
    getStaticParam(&mMinTime_s, "MinTime");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mUseCameraFrontByTargetPlayer_s, "UseCameraFrontByTargetPlayer");
}

// NON_MATCHING: the target keeps branches for the 1/-1/0 result (select here) and swaps d8/d9
int EscapeFromTargetFront::m34() {
    sead::Vector3f front;
    sub_71003C8338(&front);
    const sead::Vector3f& target_pos = sub_71005D9330(mActor);
    sead::Vector3f dir = mActor->getMtx().getTranslation() - target_pos;
    dir.y = 0;
    dir.normalize();
    const f32 cross = dir.x * front.z - dir.z * front.x;
    if (cross > 0.0871557f)
        return 1;
    if (cross < -0.0871557f)
        return -1;
    return 0;
}

}  // namespace uking::ai
