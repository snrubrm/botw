#include "Game/Actor/Action/actionOpenDungeonSmallTitleSetLabel.h"
#include "Game/UI/uiUI.h"

namespace uking::action {

OpenDungeonSmallTitleSetLabel::OpenDungeonSmallTitleSetLabel(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OpenDungeonSmallTitleSetLabel::~OpenDungeonSmallTitleSetLabel() = default;

bool OpenDungeonSmallTitleSetLabel::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenDungeonSmallTitleSetLabel::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* ui = ui::UI::instance();
    if (!ui || mLabelName_d.isEmpty()) {
        setFailed();
        return;
    }
    sead::FixedSafeString<256> label(mLabelName_d);
    sead::FixedSafeString<256> secondary_label(mLabelName_d);
    ui->sub_71010A6800(mMstxt_s, label, mSubMstxt_d, secondary_label);
}

void OpenDungeonSmallTitleSetLabel::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenDungeonSmallTitleSetLabel::loadParams_() {
    getStaticParam(&mMstxt_s, "Mstxt");
    getDynamicParam(&mSubMstxt_d, "SubMstxt");
    getDynamicParam(&mLabelName_d, "LabelName");
}

void OpenDungeonSmallTitleSetLabel::calc_() {
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
