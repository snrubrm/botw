#include "Game/AI/Query/queryWhatCurrentItem.h"
#include <evfl/Query.h>
#include "Game/gameRuneMgr.h"

namespace uking::query {

WhatCurrentItem::WhatCurrentItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

WhatCurrentItem::~WhatCurrentItem() = default;

int WhatCurrentItem::doQuery() {
    auto* mgr = RuneMgr::instance();
    if (!mgr)
        return 0;

    const s32 item = mgr->getCurrentItem();
    const u32 flags = mgr->_90;
    if (flags & 0x20)
        return 8;
    if (item == 0)
        return 1;
    if (item == 1)
        return 2;
    if (flags & 0x10) {
        switch (item) {
        case 2:
            return 3;
        case 3:
            return 4;
        case 4:
            return 5;
        case 5:
            return 6;
        case 6:
            return 0;
        case 7:
            return 7;
        }
    }
    return 0;
}

void WhatCurrentItem::loadParams(const evfl::QueryArg& arg) {}

void WhatCurrentItem::loadParams() {}

}  // namespace uking::query
