#include "Game/AI/Action/actionStartLifeUpDemo.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

StartLifeUpDemo::StartLifeUpDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StartLifeUpDemo::~StartLifeUpDemo() = default;

bool StartLifeUpDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartLifeUpDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    _1c = false;
}

void StartLifeUpDemo::loadParams_() {}

void StartLifeUpDemo::calc_() {
    if (_1c) {
        ui::sub_7100A94B08();
        ui::sub_7100A94D54();
        setFinished();
    } else {
        ui::sub_7100A94B70(true);
        _1c = true;
    }
}

}  // namespace uking::action
