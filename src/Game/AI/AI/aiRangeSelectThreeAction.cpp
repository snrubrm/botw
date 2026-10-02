#include "Game/AI/AI/aiRangeSelectThreeAction.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"

namespace uking::ai {

RangeSelectThreeAction::RangeSelectThreeAction(const InitArg& arg) : RangeSelectAction(arg) {}

RangeSelectThreeAction::~RangeSelectThreeAction() = default;

void RangeSelectThreeAction::loadParams_() {
    RangeSelectAction::loadParams_();
    getStaticParam(&mNearDist_s, "NearDist");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mBaseDist_s, "BaseDist");
}

void RangeSelectThreeAction::m34() {
    const f32 weapon_range = sub_7100539F84();
    const f32 base_dist = *mBaseDist_s;
    const f32 dist = m35();
    const f32 near_dist = weapon_range + (base_dist + *mNearDist_s);
    const f32 far_dist = weapon_range + (base_dist + *mFarDist_s);
    if (dist < near_dist) {
        if (getCurrentChild() && isCurrentChild("近距離"))
            return;
        ksys::act::ai::InlineParamPack params;
        params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("近距離", &params);
        return;
    }

    auto* child = getCurrentChild();
    if (dist < far_dist) {
        if (child && isCurrentChild("中距離"))
            return;
        ksys::act::ai::InlineParamPack params;
        params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("中距離", &params);
    } else {
        if (child && isCurrentChild("遠距離"))
            return;
        ksys::act::ai::InlineParamPack params;
        params.addVec3(*mTargetPos_d, "TargetPos", -1);
        changeChild("遠距離", &params);
    }
}

}  // namespace uking::ai
