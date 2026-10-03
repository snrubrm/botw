#include "Game/AI/Action/actionNPCBuyItem.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCBuyItem::NPCBuyItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCBuyItem::~NPCBuyItem() = default;

bool NPCBuyItem::oneShot_() {
    ui::sub_7100A98358();
    return ksys::act::ai::Action::oneShot_();
}

}  // namespace uking::action
