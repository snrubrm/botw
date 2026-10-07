#include "Game/UI/uiScreens.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ui {

// 0x71010ae9e8
bool ScreenMessage3D::sub_71010AE9E8(ksys::act::Actor* actor) {
    if (!isOpened())
        return false;
    for (u32 i = 0; i < 4; ++i) {
        auto* entry = i < _300.size() ? _300.at(i) : nullptr;
        if (entry->m38.hasProcById(actor))
            return true;
    }
    return false;
}

}  // namespace uking::ui
