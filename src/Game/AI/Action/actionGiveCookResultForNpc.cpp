#include "Game/AI/Action/actionGiveCookResultForNpc.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

GiveCookResultForNpc::GiveCookResultForNpc(const InitArg& arg) : ksys::act::ai::Action(arg) {}

GiveCookResultForNpc::~GiveCookResultForNpc() = default;

bool GiveCookResultForNpc::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: the literal comparison retains temporary SafeString storage.
bool GiveCookResultForNpc::oneShot_() {
    for (s32 i = 0; i < *mCount_d; ++i) {
        if (mCookEffectType_d == "AllOK")
            ui::sub_7100A9E540(mPorchItemName_d);
        else
            ui::pouchDeleteCookResultFromFlow(mPorchItemName_d, sub_710018B630());
    }
    return true;
}

void GiveCookResultForNpc::loadParams_() {
    getDynamicParam(&mCount_d, "Count");
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
    getDynamicParam(&mCookEffectType_d, "CookEffectType");
}

}  // namespace uking::action
