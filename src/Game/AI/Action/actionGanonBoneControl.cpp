#include "Game/AI/Action/actionGanonBoneControl.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "Game/AI/aiUnk_71007368A4.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

GanonBoneControl::GanonBoneControl(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GanonBoneControl::~GanonBoneControl() = default;

bool GanonBoneControl::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void GanonBoneControl::loadParams_() {
    getDynamicParam(&mIsBattleModeOn_d, "IsBattleModeOn");
}

bool GanonBoneControl::oneShot_() {
    sub_7100739918(mActor);
    const sead::Vector3f& pos = getPlayerPosition();
    sub_71005DB068(mActor, pos);
    if (*mIsBattleModeOn_d)
        sub_71005D7444(mActor, pos, true, true);
    return true;
}

}  // namespace uking::action
