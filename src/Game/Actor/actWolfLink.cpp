#include "Game/Actor/actWolfLink.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actBoneControl.h"

namespace uking::act {

// NON_MATCHING: the message listener members at 0x1620/0x1638 are not typed yet
WolfLink::~WolfLink() = default;

bool WolfLink::shouldUnload(s32* a1) {
    s32 reason = 0;
    const bool unload = Enemy::shouldUnload(&reason);
    if (unload)
        uking::ui::showInfoOverlay(0x28);
    *a1 = reason;
    return unload;
}

void WolfLink::sub_71002F4B3C() {
    if (auto* bone_control = mBoneControl) {
        if (auto* controller = bone_control->_0) {
            controller->_8 = controller->_c;
            controller->_10._9c = controller->_10._98;
            controller->sub_7100D85774();
            _1698 &= ~8;
        }
    }
}

}  // namespace uking::act
