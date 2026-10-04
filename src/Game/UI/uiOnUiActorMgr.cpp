#include "Game/UI/uiOnUiActorMgr.h"

namespace uking::ui {

OnUiActorMgr* OnUiActorMgr::sInstance = nullptr;

// 0x710090ab60
ksys::act::Actor* OnUiActorMgr::getActor() const {
    return mActor;
}

}  // namespace uking::ui
