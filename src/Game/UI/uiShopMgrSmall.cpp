#include "Game/UI/uiShopMgr.h"
#include "Game/gameHorseMgr.h"

namespace uking::ui {

// 0x7100984ee0
void UiShopMgr::sub_7100984EE0() {
    if (auto* mgr = HorseMgr::instance())
        mgr->sub_7100E875EC();
}

// 0x71009854fc
bool UiShopMgr::sub_71009854FC(ksys::act::BaseProc* proc) {
    return _140.acquire(proc, false);
}

// 0x7100985508
void UiShopMgr::sub_7100985508() {
    _140.reset();
}

}  // namespace uking::ui
