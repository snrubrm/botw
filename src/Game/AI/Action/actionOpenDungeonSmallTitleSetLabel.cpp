#include "Game/AI/Action/actionOpenDungeonSmallTitleSetLabel.h"
#include "Game/UI/uiUI.h"

namespace uking::action {

OpenDungeonSmallTitleSetLabel::OpenDungeonSmallTitleSetLabel(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

OpenDungeonSmallTitleSetLabel::~OpenDungeonSmallTitleSetLabel() = default;

bool OpenDungeonSmallTitleSetLabel::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenDungeonSmallTitleSetLabel::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
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
