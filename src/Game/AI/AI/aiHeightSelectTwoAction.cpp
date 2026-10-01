#include "Game/AI/AI/aiHeightSelectTwoAction.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

HeightSelectTwoAction::HeightSelectTwoAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

HeightSelectTwoAction::~HeightSelectTwoAction() = default;

void HeightSelectTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    _58 = ksys::Timer(*mSelectCheckInterval_s, *mSelectCheckInterval_s);

    bool in_range = false;
    if (mActor) {
        const f32 height = mTargetPos_d->y - mActor->getMtx().m[1][3];
        in_range = !(height < *mHeightMin_s) && !(height > *mHeightMax_s);
    }

    if (in_range) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("レンジ内", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("レンジ外", &pack);
    }
}

void HeightSelectTwoAction::calc_() {
    if (getCurrentChild()->isFinished()) {
        setFinished();
        return;
    }
    if (getCurrentChild()->isFailed()) {
        setFailed();
        return;
    }

    getCurrentChild()->setDynamicParam(*mTargetPos_d, "TargetPos");
    if (!(_58.value <= sead::Mathf::epsilon()))
        _58.update();

    if (getCurrentChild()->isChangeable() && *mSelectCheckInterval_s >= 0 &&
        _58.value <= sead::Mathf::epsilon()) {
        sub_710042E7CC();
    }
}

void HeightSelectTwoAction::sub_710042E7CC() {
    bool in_range = false;
    if (mActor) {
        const f32 height = mTargetPos_d->y - mActor->getMtx().m[1][3];
        in_range = !(height < *mHeightMin_s) && !(height > *mHeightMax_s);
    }

    if (in_range) {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("レンジ内", &pack);
    } else {
        ksys::act::ai::InlineParamPack pack;
        pack.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("レンジ外", &pack);
    }
}

bool HeightSelectTwoAction::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool HeightSelectTwoAction::isFinished() const {
    return getCurrentChild()->isFinished();
}

void HeightSelectTwoAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void HeightSelectTwoAction::loadParams_() {
    getStaticParam(&mSelectCheckInterval_s, "SelectCheckInterval");
    getStaticParam(&mHeightMin_s, "HeightMin");
    getStaticParam(&mHeightMax_s, "HeightMax");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

}  // namespace uking::ai
