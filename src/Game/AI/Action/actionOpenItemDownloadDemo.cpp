#include "Game/AI/Action/actionOpenItemDownloadDemo.h"

#include <container/seadSafeArray.h>
#include "Game/UI/uiUtils.h"

namespace uking::ui {
// 0x7100a9ecbc / 0x7100a9ec04 (placeholder names; the second is declared only).
bool sub_7100A9ECBC();
bool sub_7100A9EC04(s32 type, bool a2, bool a3, bool a4, bool a5);
}  // namespace uking::ui

namespace uking::action {

OpenItemDownloadDemo::OpenItemDownloadDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenItemDownloadDemo::~OpenItemDownloadDemo() = default;

bool OpenItemDownloadDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenItemDownloadDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    _40 = false;
}

void OpenItemDownloadDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenItemDownloadDemo::loadParams_() {
    getDynamicParam(&mItemType_d, "ItemType");
    getDynamicParam(&mIsEquip_d, "IsEquip");
    getDynamicParam(&mIsPowerUp_d, "IsPowerUp");
    getDynamicParam(&mIsPlayerClose_d, "IsPlayerClose");
}

// NON_MATCHING: the original selects the element ADDRESS (`csel x8, base + idx * 4, base`) and loads once; ours selects the
// index (SafeArray::operator[]) and loads after the bool params.
void OpenItemDownloadDemo::calc_() {
    if (isFinished() || isFailed())
        return;
    if (_40) {
        if (!ui::sub_7100A9ECBC())
            return;
        setFinished();
    } else {
        static sead::SafeArray<s32, 6> sItemTypes = {{0, 2, 3, 4, 5, 6}};
        bool opened = false;
        if (u32(*mItemType_d) <= 5) {
            ui::createAndLoadScreenIfNeededImpl(31, nullptr);
            opened = ui::sub_7100A9EC04(sItemTypes[*mItemType_d], *mIsEquip_d, *mIsPowerUp_d, *mIsPlayerClose_d, false);
        }
        if (opened) {
            _40 = true;
            return;
        }
        setFailed();
    }
    mFlags.set(Flag::Changeable);
}

}  // namespace uking::action
