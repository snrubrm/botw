#include "Game/Actor/AI/aiNewRangeSelect.h"
#include "Game/Actor/aiUnk_71007320F0.h"

namespace uking::ai {

NewRangeSelect::NewRangeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NewRangeSelect::~NewRangeSelect() = default;

bool NewRangeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NewRangeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71004BC154(params);
}

void NewRangeSelect::sub_71004BC154(ksys::act::ai::InlineParamPack* params) {
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

void NewRangeSelect::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed())
        return;

    if (child->isChangeable() && *mIsSelectEveryFrame_s)
        sub_71004BC154(nullptr);
}

void NewRangeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NewRangeSelect::loadParams_() {
    getStaticParam(&mWeaponIdx_s, "WeaponIdx");
    getStaticParam(&mFarDist_s, "FarDist");
    getStaticParam(&mIsSelectEveryFrame_s, "IsSelectEveryFrame");
}

f32 NewRangeSelect::m38() {
    return 0.0f;
}

f32 NewRangeSelect::m34() {
    return *mFarDist_s + sub_71007320F0(mActor, *mWeaponIdx_s);
}

}  // namespace uking::ai
