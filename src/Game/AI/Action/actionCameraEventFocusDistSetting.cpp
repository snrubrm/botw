#include "Game/AI/Action/actionCameraEventFocusDistSetting.h"
#include <math/seadMathCalcCommon.h>
#include "KingSystem/Event/evtManager.h"

namespace uking::action {

CameraEventFocusDistSetting::CameraEventFocusDistSetting(const InitArg& arg)
    : ksys::act::ai::Action(arg), Unk_7102459708(this) {}

CameraEventFocusDistSetting::~CameraEventFocusDistSetting() = default;

void CameraEventFocusDistSetting::loadParams_() {
    getDynamicParam_2(&mClipIndex_d, "ClipIndex");
    getDynamicParam_2(&mFocusDistStart_d, "FocusDistStart");
    getDynamicParam_2(&mFocusDistEnd_d, "FocusDistEnd");
}

// NON_MATCHING: the original computes &camera->_860 before the second EventMgr call (scheduling)
void CameraEventFocusDistSetting::calc_() {
    auto* camera = getCamera();
    if (!camera)
        return;

    auto* event_mgr = ksys::evt::Manager::instance();
    if (!event_mgr)
        return;

    const f32 duration = event_mgr->sub_7100DB1174(*mClipIndex_d);
    if (duration == 0)
        return;

    const f32 t = sead::Mathf::clamp(event_mgr->sub_7100DB1138(*mClipIndex_d) / duration, 0.0f, 1.0f);
    camera->_860.sub_710079C0DC(0, *mFocusDistStart_d + t * (*mFocusDistEnd_d - *mFocusDistStart_d));
}

}  // namespace uking::action
