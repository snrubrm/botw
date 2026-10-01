#include "Game/AI/AI/aiRangeSelect.h"

namespace uking::ai {

RangeSelect::RangeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

RangeSelect::~RangeSelect() = default;

bool RangeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RangeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71004BC154(params);
}

void RangeSelect::sub_71004BC154(ksys::act::ai::InlineParamPack* params) {
    if (m38() < m34() || m35()) {
        if (getCurrentChild() && isCurrentChild("近距離"))
            return;
        m36();
        changeChild("近距離", params);
    } else {
        if (getCurrentChild() && isCurrentChild("遠距離"))
            return;
        m37();
        changeChild("遠距離", params);
    }
}

void RangeSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        return;

    if (child->isChangeable() && *mIsSelectEveryFrame_s)
        sub_71004BC154(nullptr);
}

void RangeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RangeSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mIsSelectEveryFrame_s, "IsSelectEveryFrame");
}

f32 RangeSelect::m38() {
    return 0.0f;
}

}  // namespace uking::ai
