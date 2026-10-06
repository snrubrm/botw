#include "Game/AI/Query/queryCheckItemShopSelect.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckItemShopSelect::CheckItemShopSelect(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckItemShopSelect::~CheckItemShopSelect() = default;

int CheckItemShopSelect::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm != nullptr) {
        s32 screen_type = -1;
        if (gdm->getParam().get().getS32(&screen_type, "Shop_ScreenType")) {
            switch (screen_type) {
            case 0:
                return 2;
            case 1:
                return 0;
            case 2:
                return 1;
            }
        }
    }
    return 2;
}

void CheckItemShopSelect::loadParams(const evfl::QueryArg& arg) {}

void CheckItemShopSelect::loadParams() {}

}  // namespace uking::query
