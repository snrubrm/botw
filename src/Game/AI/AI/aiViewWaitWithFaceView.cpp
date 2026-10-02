#include "Game/AI/AI/aiViewWaitWithFaceView.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::ai {

ViewWaitWithFaceView::ViewWaitWithFaceView(const InitArg& arg) : ViewWait(arg) {}

ViewWaitWithFaceView::~ViewWaitWithFaceView() = default;

bool ViewWaitWithFaceView::init_(sead::Heap* heap) {
    return ViewWait::init_(heap);
}

void ViewWaitWithFaceView::enter_(ksys::act::ai::InlineParamPack* params) {
    ViewWait::enter_(params);
}

void ViewWaitWithFaceView::calc_() {
    const bool use_simple_offset = *mUseSimpleOffset_s;
    auto* actor = mActor;
    const auto& target_pos = m34();
    if (use_simple_offset)
        sub_71005DB1D8(actor, target_pos);
    else
        sub_71005DB068(actor, target_pos);
    ViewWait::calc_();
}

void ViewWaitWithFaceView::leave_() {
    sub_71005DB3EC(mActor);
}

void ViewWaitWithFaceView::loadParams_() {
    ViewWait::loadParams_();
    getStaticParam(&mUseSimpleOffset_s, "UseSimpleOffset");
}

}  // namespace uking::ai
