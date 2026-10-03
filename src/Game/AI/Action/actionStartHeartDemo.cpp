#include "Game/AI/Action/actionStartHeartDemo.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

StartHeartDemo::StartHeartDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StartHeartDemo::~StartHeartDemo() = default;

bool StartHeartDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartHeartDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
}

void StartHeartDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void StartHeartDemo::loadParams_() {}

void StartHeartDemo::calc_() {
    if (isFinished() || isFailed())
        return;
    if (_1c) {
        if (!ui::sub_7100A94AC8())
            setFinished();
    } else {
        ui::sub_7100A94B70(true);
        ui::sub_7100A94B08();
        _1c = true;
    }
}

}  // namespace uking::action
