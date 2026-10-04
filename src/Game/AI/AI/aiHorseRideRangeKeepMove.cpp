#include "Game/AI/AI/aiHorseRideRangeKeepMove.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

HorseRideRangeKeepMove::HorseRideRangeKeepMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HorseRideRangeKeepMove::~HorseRideRangeKeepMove() = default;

bool HorseRideRangeKeepMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void HorseRideRangeKeepMove::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!sub_71005D8F28(mActor)) {
        setFailed();
        return;
    }
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
    changeChild("指令", &pack);
}

void HorseRideRangeKeepMove::calc_() {
    if (!sub_71005D8F28(mActor)) {
        setFailed();
        return;
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("指令")) {
            ksys::act::ai::InlineParamPack pack;
            pack.addVec3(sub_71005D9330(mActor), "TargetPos", -1);
            changeChild("待機", &pack);
        } else if (child->isFinished()) {
            setFinished();
        } else {
            setFailed();
        }
    } else if (child->isChangeable()) {
        const sead::Vector3f pos = mActor->getMtx().getTranslation();
        if ((sub_71005D9330(mActor) - pos).length() > *mBaseDist_s + *mOutDist_s)
            setFailed();
    }

    child->setDynamicParam(sub_71005D9330(mActor), "TargetPos");
}

void HorseRideRangeKeepMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HorseRideRangeKeepMove::loadParams_() {
    getStaticParam(&mOutDist_s, "OutDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
}

}  // namespace uking::ai
