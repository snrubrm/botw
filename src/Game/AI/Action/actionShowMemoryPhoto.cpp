#include "Game/AI/Action/actionShowMemoryPhoto.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

ShowMemoryPhoto::ShowMemoryPhoto(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShowMemoryPhoto::~ShowMemoryPhoto() = default;

bool ShowMemoryPhoto::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ShowMemoryPhoto::oneShot_() {
    if (mPhotoNo_d)
        ui::sub_7100A9F048(*mPhotoNo_d);
    return ksys::act::ai::Action::oneShot_();
}

void ShowMemoryPhoto::loadParams_() {
    getDynamicParam(&mPhotoNo_d, "PhotoNo");
}

}  // namespace uking::action
