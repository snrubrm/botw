#include "Game/AI/AI/aiViewChaseSound.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ViewChaseSound::ViewChaseSound(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ViewChaseSound::~ViewChaseSound() = default;

bool ViewChaseSound::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ViewChaseSound::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ViewChaseSound::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ViewChaseSound::loadParams_() {
    getStaticParam(&mTurnDir_s, "TurnDir");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

// 0x71005e39e8
void ViewChaseSound::sub_71005E39E8() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos = *mTargetPos_d;
    somePositionCalc(&pos, pos, -sead::Vector3f::ey, 10.0f);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("回転", &pack);
}

// 0x71005e4150
void ViewChaseSound::sub_71005E4150() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos = *mTargetPos_d;
    somePositionCalc(&pos, pos, -sead::Vector3f::ey, 10.0f);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("追跡", &pack);
}

// 0x71005e4268
void ViewChaseSound::sub_71005E4268() {
    ksys::act::ai::InlineParamPack pack;
    sead::Vector3f pos = *mTargetPos_d;
    somePositionCalc(&pos, pos, -sead::Vector3f::ey, 10.0f);
    pack.addVec3(pos, "TargetPos", -1);
    changeChild("直線追跡", &pack);
}

}  // namespace uking::ai
