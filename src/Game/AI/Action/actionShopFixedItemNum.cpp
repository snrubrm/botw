#include "Game/AI/Action/actionShopFixedItemNum.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

ShopFixedItemNum::ShopFixedItemNum(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ShopFixedItemNum::~ShopFixedItemNum() = default;

bool ShopFixedItemNum::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ShopFixedItemNum::enter_(ksys::act::ai::InlineParamPack* params) {
    ui::sub_7100A98284(*mIsSelectAll_d);
}

void ShopFixedItemNum::leave_() {
    ksys::act::ai::Action::leave_();
}

void ShopFixedItemNum::loadParams_() {
    getDynamicParam(&mIsSelectAll_d, "IsSelectAll");
}

void ShopFixedItemNum::calc_() {
    sub_7100738488(mActor, 0.0f, -sead::Vector3f::ey);
    sub_7100738AA8(mActor, 0.0f);
    if (ksys::gdt::getFlag_Shop_TradeItemNum(false) >= 1)
        setFinished();
}

}  // namespace uking::action
