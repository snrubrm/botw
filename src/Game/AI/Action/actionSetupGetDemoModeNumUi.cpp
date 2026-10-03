#include "Game/AI/Action/actionSetupGetDemoModeNumUi.h"
#include "Game/UI/uiUtils.h"

namespace uking::action {

SetupGetDemoModeNumUi::SetupGetDemoModeNumUi(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetupGetDemoModeNumUi::~SetupGetDemoModeNumUi() = default;

bool SetupGetDemoModeNumUi::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetupGetDemoModeNumUi::loadParams_() {
    getDynamicParam(&mNumUiType_d, "NumUiType");
    getDynamicParam(&mAddNum_d, "AddNum");
}

bool SetupGetDemoModeNumUi::oneShot_() {
    switch (*mNumUiType_d) {
    case 0:
        ui::sub_7100A97550(*mAddNum_d);
        break;
    case 1:
        ui::sub_7100A970DC(*mAddNum_d);
        break;
    case 2:
        ui::sub_7100A97C6C(*mAddNum_d, 0);
        break;
    case 3:
        ui::sub_7100A97C6C(*mAddNum_d, 1);
        break;
    case 4:
        ui::sub_7100A97C6C(*mAddNum_d, 2);
        break;
    case 5:
        ui::sub_7100A97C6C(*mAddNum_d, 3);
        break;
    }
    return true;
}

}  // namespace uking::action
