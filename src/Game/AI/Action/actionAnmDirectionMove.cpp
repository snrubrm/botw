#include "Game/AI/Action/actionAnmDirectionMove.h"

namespace uking::action {

AnmDirectionMove::AnmDirectionMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmDirectionMove::~AnmDirectionMove() = default;

bool AnmDirectionMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the original keeps the two arms as branches (fmov constants joined by a phi) where ours selects with fcsel
void AnmDirectionMove::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!mASName_s.isEmpty())
        playAS(mASName_s.cstr(), false, 0, 0, -1.0f);
    if (*mIsChangeable_s)
        mFlags.set(Flag::Changeable);
    _68 = 1.0f;
    if (*mDirection_s == 1) {
        _5c = 1.0f;
        _60 = 0.0f;
        _64 = 0.0f;
    } else {
        _5c = 0.0f;
        _60 = 0.0f;
        _64 = 1.0f;
    }
}

void AnmDirectionMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmDirectionMove::loadParams_() {
    getStaticParam(&mDirection_s, "Direction");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mUsereachableCheck_s, "UsereachableCheck");
    getStaticParam(&mASName_s, "ASName");
}

void AnmDirectionMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
