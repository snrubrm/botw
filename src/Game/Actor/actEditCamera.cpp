#include "Game/Actor/actEditCamera.h"
#include <basis/seadNew.h>

namespace uking::act {

EditCamera::EditCamera(const CreateArg& arg) : Actor(arg) {}

ksys::act::BaseProc* EditCamera::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) EditCamera(arg);
}

ksys::act::BaseProc::InitResult EditCamera::init_() {
    _1c0 = 5;
    return InitResult::Ok;
}

void EditCamera::onJobPush2_(ksys::act::JobType type) {
    if (type == ksys::act::JobType::Calc1)
        m107();
}

EditCamera::CameraNames* EditCamera::sub_71007917BC() {
    return &_840._40;
}

int EditCamera::getCalcTiming() {
    return 1;
}

}  // namespace uking::act
