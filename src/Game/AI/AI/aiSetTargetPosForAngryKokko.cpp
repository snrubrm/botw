#include "Game/AI/AI/aiSetTargetPosForAngryKokko.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

SetTargetPosForAngryKokko::SetTargetPosForAngryKokko(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SetTargetPosForAngryKokko::~SetTargetPosForAngryKokko() = default;

bool SetTargetPosForAngryKokko::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SetTargetPosForAngryKokko::enter_(ksys::act::ai::InlineParamPack* params) {
    _7c = 0;
    sead::Vector3f pos;
    if (!sub_7100568490(&pos))
        mActor->getMtx().getTranslation(pos);

    ksys::act::ai::InlineParamPack child_params;
    child_params.addVec3(pos, "TargetPos", -1);
    changeChild("子アクション", &child_params);
}

void SetTargetPosForAngryKokko::calc_() {
    _70.update();
    if (*mUpdateTargetInterval_s < 0)
        return;

    if (_70.value <= sead::Mathf::epsilon()) {
        sead::Vector3f pos;
        if (sub_7100568490(&pos))
            getCurrentChild()->setDynamicParam(pos, "TargetPos");
    }
}

void SetTargetPosForAngryKokko::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SetTargetPosForAngryKokko::loadParams_() {
    getStaticParam(&mUpdateTargetInterval_s, "UpdateTargetInterval");
    getStaticParam(&mMaxUpdateNum_s, "MaxUpdateNum");
    getStaticParam(&mAddLength_s, "AddLength");
    getStaticParam(&mHeightOffset_s, "HeightOffset");
    getStaticParam(&mRandRange_s, "RandRange");
    getStaticParam(&mRandRate_s, "RandRate");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

}  // namespace uking::ai
