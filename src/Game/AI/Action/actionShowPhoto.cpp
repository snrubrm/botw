#include "Game/AI/Action/actionShowPhoto.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

ShowPhoto::ShowPhoto(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShowPhoto::~ShowPhoto() = default;

bool ShowPhoto::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool ShowPhoto::oneShot_() {
    if (!mActorName_d.isEmpty())
        ui::sub_7100A9F08C(mActorName_d);
    return ksys::act::ai::Action::oneShot_();
}

void ShowPhoto::loadParams_() {
    getDynamicParam(&mActorName_d, "ActorName");
}

}  // namespace uking::action
