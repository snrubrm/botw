#include "Game/Actor/Action/actionOpenDungeonTitleSetLabel.h"
#include "Game/UI/uiUI.h"

namespace uking::action {

OpenDungeonTitleSetLabel::OpenDungeonTitleSetLabel(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OpenDungeonTitleSetLabel::~OpenDungeonTitleSetLabel() = default;

bool OpenDungeonTitleSetLabel::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenDungeonTitleSetLabel::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* ui = ui::UI::instance();
    if (!ui || mLabelName_d.isEmpty()) {
        setFailed();
        return;
    }
    sead::FixedSafeString<256> label(mLabelName_d);
    sead::FixedSafeString<256> secondary_label(mLabelName_d);
    ui->sub_71010A7774(mMstxt_s, label, mSubMstxt_d, secondary_label, true);
}

void OpenDungeonTitleSetLabel::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenDungeonTitleSetLabel::loadParams_() {
    getStaticParam(&mMstxt_s, "Mstxt");
    getDynamicParam(&mSubMstxt_d, "SubMstxt");
    getDynamicParam(&mLabelName_d, "LabelName");
}

void OpenDungeonTitleSetLabel::calc_() {
    if (isFinishedOrFailed())
        return;
    auto* ui = ui::UI::instance();
    if (!ui) {
        setFailed();
        return;
    }
    if (ui->sub_71010A5CFC())
        setFinished();
}

}  // namespace uking::action
