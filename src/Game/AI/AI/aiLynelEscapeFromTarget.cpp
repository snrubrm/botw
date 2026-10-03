#include "Game/AI/AI/aiLynelEscapeFromTarget.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LynelEscapeFromTarget::LynelEscapeFromTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelEscapeFromTarget::~LynelEscapeFromTarget() = default;

bool LynelEscapeFromTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelEscapeFromTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    const s32 time = *mKeepTime_s;
    _60 = time;
    _64 = _68 = time;
    sead::Vector3f pos;
    if (sub_7100490F58(&pos))
        changeToEscapeMove(pos);
    else
        changeToCannotEscape();
}

void LynelEscapeFromTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelEscapeFromTarget::loadParams_() {
    getStaticParam(&mKeepTime_s, "KeepTime");
    getStaticParam(&mSpaceDistMin_s, "SpaceDistMin");
    getStaticParam(&mSpaceDist_s, "SpaceDist");
    getStaticParam(&mMoveDistMin_s, "MoveDistMin");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
