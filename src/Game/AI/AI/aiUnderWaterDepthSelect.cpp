#include "Game/AI/AI/aiUnderWaterDepthSelect.h"
#include "Game/AI/aiUnk_71007377D4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

UnderWaterDepthSelect::UnderWaterDepthSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

UnderWaterDepthSelect::~UnderWaterDepthSelect() = default;

bool UnderWaterDepthSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void UnderWaterDepthSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sead::Vector3f pos;
    mActor->getMtx().getTranslation(pos);
    sead::Vector3f deep = pos;
    deep.y -= *mDeepDepth_s;
    if (!mActor->get68f() || sub_710072E928(pos, deep, nullptr, nullptr, nullptr, 0.0f))
        changeChild("浅瀬", params);
    else
        changeChild("深瀬", params);
}

void UnderWaterDepthSelect::calc_() {
    if (*mOnEnterOnly_s)
        return;

    bool is_deep;
    {
        sead::Vector3f pos;
        mActor->getMtx().getTranslation(pos);
        sead::Vector3f deep = pos;
        deep.y -= *mDeepDepth_s;
        is_deep = mActor->get68f() && !sub_710072E928(pos, deep, nullptr, nullptr, nullptr, 0.0f);
    }

    if (*mForceDeepChange_s && is_deep && !isCurrentChild("深瀬")) {
        changeChild("深瀬");
    } else if (getCurrentChild()->isChangeable()) {
        if (is_deep) {
            if (!isCurrentChild("深瀬"))
                changeChild("深瀬");
        } else {
            if (!isCurrentChild("浅瀬"))
                changeChild("浅瀬");
        }
    }
}

void UnderWaterDepthSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void UnderWaterDepthSelect::loadParams_() {
    getStaticParam(&mDeepDepth_s, "DeepDepth");
    getStaticParam(&mOnEnterOnly_s, "OnEnterOnly");
    getStaticParam(&mForceDeepChange_s, "ForceDeepChange");
}

}  // namespace uking::ai
