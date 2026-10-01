#include "Game/AI/AI/aiRangeSelectTwoAction.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

RangeSelectTwoAction::RangeSelectTwoAction(const InitArg& arg) : RangeSelectAction(arg) {}

RangeSelectTwoAction::~RangeSelectTwoAction() = default;

void RangeSelectTwoAction::loadParams_() {
    RangeSelectAction::loadParams_();
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
}

void RangeSelectTwoAction::m34() {
    const bool is_far = m36();
    auto* child = getCurrentChild();
    if (is_far) {
        if (child && isCurrentChild("遠距離"))
            return;
        ksys::act::ai::InlineParamPack params;
        params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("遠距離", &params);
    } else {
        if (child && isCurrentChild("近距離"))
            return;
        ksys::act::ai::InlineParamPack params;
        params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("近距離", &params);
    }
}

bool RangeSelectTwoAction::m36() {
    const f32 weapon_range = sub_7100539F84();
    const f32 base_dist = *mBaseDist_s;
    return m35() > weapon_range + (base_dist + *mFarDist_s);
}

}  // namespace uking::ai
