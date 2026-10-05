#include "Game/AI/AI/aiLynelDirSelect.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LynelDirSelect::LynelDirSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelDirSelect::~LynelDirSelect() = default;

bool LynelDirSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelDirSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(*mTargetPos_d, "TargetPos", -1);
    switch (sub_7100490308()) {
    case 0:
        changeChild("前", &pack);
        break;
    case 1:
        changeChild("後", &pack);
        break;
    case 2:
        changeChild("左", &pack);
        break;
    case 3:
        changeChild("右", &pack);
        break;
    default:
        break;
    }
}

bool LynelDirSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool LynelDirSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

void LynelDirSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelDirSelect::loadParams_() {
    getStaticParam(&mBasePosOffsetFront_s, "BasePosOffsetFront");
    getStaticParam(&mBasePosOffsetBack_s, "BasePosOffsetBack");
    getStaticParam(&mFrontAngle_s, "FrontAngle");
    getStaticParam(&mBackAngle_s, "BackAngle");
    getStaticParam(&mIsCheckOnlyXZ_s, "IsCheckOnlyXZ");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void LynelDirSelect::calc_() {
    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
}

void LynelDirSelect::m34() {}

}  // namespace uking::ai
