#include "Game/AI/AI/aiReflectableEscape.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

ReflectableEscape::ReflectableEscape(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ReflectableEscape::~ReflectableEscape() = default;

bool ReflectableEscape::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ReflectableEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    _64 = ksys::Timer(*mEscapeTimer_s, *mEscapeTimer_s);
    sub_710053C804(&_58, *mTargetPos_d, *mEscapeDist_s);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(_58, "TargetPos", -1);
    changeChild("移動", &pack);
}

void ReflectableEscape::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ReflectableEscape::loadParams_() {
    getStaticParam(&mEscapeDist_s, "EscapeDist");
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mEscapeTimer_s, "EscapeTimer");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
