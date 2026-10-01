#include "Game/AI/AI/aiLastBossSwordWhirlSlash.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

LastBossSwordWhirlSlash::LastBossSwordWhirlSlash(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossSwordWhirlSlash::~LastBossSwordWhirlSlash() = default;

bool LastBossSwordWhirlSlash::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossSwordWhirlSlash::enter_(ksys::act::ai::InlineParamPack* params) {
    if (*mIsNoCharge_d) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("溜め無し攻撃", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("溜め", &pack);
    }
}

void LastBossSwordWhirlSlash::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossSwordWhirlSlash::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mIsNoCharge_d, "IsNoCharge");
}

void LastBossSwordWhirlSlash::calc_() {
    auto* child = getCurrentChild();
    child->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (child->isFailed()) {
        setFailed();
    } else if (child->isFinished()) {
        if (isCurrentChild("溜め")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(*mTargetPos_d, "TargetPos", -1);
            changeChild("攻撃", &pack);
        } else {
            setFinished();
        }
    }
}

}  // namespace uking::ai
