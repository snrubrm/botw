#include "Game/Actor/Action/actionOpenEnduranceFloorNumber.h"
#include "Game/UI/uiUI.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::action {

OpenEnduranceFloorNumber::OpenEnduranceFloorNumber(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OpenEnduranceFloorNumber::~OpenEnduranceFloorNumber() = default;

bool OpenEnduranceFloorNumber::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenEnduranceFloorNumber::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* ui = ui::UI::instance();
    if (!ui || mLabelName_d.isEmpty()) {
        setFailed();
        return;
    }
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm) {
        setFailed();
        mFlags.set(Flag::Changeable);
        return;
    }
    s32 floor = 0;
    gdm->getParam().get().getS32(&floor, mGameDataIntFloorNum_d);
    sead::FixedSafeString<256> label(mLabelName_d);
    sead::FixedSafeString<256> floor_label("");
    floor_label.format("%s%d", mLabelName_d.cstr(), floor);
    ui->sub_71010A6800(mMstxt_s, label, mSubMstxt_d, floor_label);
}

void OpenEnduranceFloorNumber::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenEnduranceFloorNumber::loadParams_() {
    getStaticParam(&mMstxt_s, "Mstxt");
    getDynamicParam(&mSubMstxt_d, "SubMstxt");
    getDynamicParam(&mLabelName_d, "LabelName");
    getDynamicParam(&mGameDataIntFloorNum_d, "GameDataIntFloorNum");
}

void OpenEnduranceFloorNumber::calc_() {
    if (isFinishedOrFailed())
        return;
    auto* ui = ui::UI::instance();
    if (!ui) {
        setFailed();
        return;
    }
    if (ui->sub_71010A5E64())
        setFinished();
}

}  // namespace uking::action
