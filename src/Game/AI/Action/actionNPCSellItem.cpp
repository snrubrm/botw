#include "Game/AI/Action/actionNPCSellItem.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

NPCSellItem::NPCSellItem(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCSellItem::~NPCSellItem() = default;

bool NPCSellItem::oneShot_() {
    ui::sub_7100A98340();
    return ksys::act::ai::Action::oneShot_();
}

}  // namespace uking::action
