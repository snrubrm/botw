#include "Game/UI/uiScreens.h"
#include "Game/UI/euiLayoutEx.h"
#include "Game/UI/euiAnimator.h"
#include "Game/UI/euiTagProcessor.h"
#include "Game/UI/euiButton.h"
#include "Game/UI/uiUtils.h"
#include "Game/UI/uiUI.h"

namespace uking::ui {

// 0x710109ed94
// NON_MATCHING: store scheduling only (all stores/calls match: base ctor, the five member
// stores, both vtable pairs, the merged 8-byte _314 zero and the non-tail memset). Ours emits
// mErrorCode second-to-last (after the +0x108 pair) instead of second, keeps the chained _314
// zero after the memset instead of before it, and does not swap the _308/_310 order. Six source
// shapes tried (all-NSDMI, value-init array, full-body, split NSDMI/body, mem-init); the
// scheduler packs differently in each and none reproduces the exact interleaving.
ScreenErrorViewer::ScreenErrorViewer() : Screen() {
    _314 = _318 = 0;
}

ScreenErrorViewer::~ScreenErrorViewer() = default;

// 0x710109ff50
bool ScreenErrorViewer::isEnableControl() const {
    return true;
}

void ScreenErrorViewer::sub_710109EE10(s32 error_code) {
    if (u32(error_code) - 1000000 < 9000000)
        mErrorCode = error_code;
}

// NON_MATCHING: the original keeps `5 : 4` as separate blocks (branch) where ours selects with csinc
// 0x710109fe34
void ScreenErrorViewer::m101() {
    if (mId == 0x61) {
        ksys::ui::sub_7100EDC638(false);
        s32 mode;
        switch (_314) {
        case 1:
            mode = (mErrorCode | 2) == 0x17a716 ? 5 : 4;
            break;
        case 2:
            mode = _31d ? 6 : 7;
            break;
        default:
            mode = 3;
            break;
        }
        UI::instance()->_a4 = mode;
    }
}

// 0x710109fd90
void ScreenErrorViewer::m107(eui::AnimButton* button) {
    if (_314 == 2)
        _31d = _320._348 == button;
    _320._340->setFlag10(false);
    _320._348->setFlag10(false);
    _320._350->setFlag10(false);
    close(-1);
}

// 0x710109fe14
void ScreenErrorViewer::sub_710109FE14() {
    if (_314 == 0)
        UI::instance()->_a4 = 2;
}

// 0x710109ff58
const char* ScreenErrorViewer::getLayoutName_() const {
    return "ErrorViewer_00";
}

}  // namespace uking::ui
