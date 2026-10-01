#include "Game/AI/Action/actionOpenItemCategory.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

OpenItemCategory::OpenItemCategory(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenItemCategory::~OpenItemCategory() = default;

bool OpenItemCategory::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool OpenItemCategory::oneShot_() {
    ksys::gdt::setFlag_IsOpenItemCategory(true, *mCategory_d);
    return true;
}

void OpenItemCategory::loadParams_() {
    getDynamicParam(&mCategory_d, "Category");
}

}  // namespace uking::action
