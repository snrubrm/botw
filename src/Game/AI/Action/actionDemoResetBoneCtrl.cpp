#include "Game/AI/Action/actionDemoResetBoneCtrl.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::action {

DemoResetBoneCtrl::DemoResetBoneCtrl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoResetBoneCtrl::~DemoResetBoneCtrl() = default;

bool DemoResetBoneCtrl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool DemoResetBoneCtrl::oneShot_() {
    auto* control = mActor->sub_71011D89F8();
    if (!control)
        return false;
    switch (*mResetTarget_d) {
    case 0:
        control->sub_7100D85644();
        break;
    case 1:
        control->_10.sub_7100D86BD8();
        break;
    case 2:
        control->_e8.sub_7100D839A8();
        break;
    }
    return true;
}

void DemoResetBoneCtrl::loadParams_() {
    getDynamicParam(&mResetTarget_d, "ResetTarget");
}

}  // namespace uking::action
