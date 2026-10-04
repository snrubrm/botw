#include "Game/AI/Action/actionOpenDungeonSmallTitle.h"
#include "Game/UI/uiUI.h"

namespace uking::action {

OpenDungeonSmallTitle::OpenDungeonSmallTitle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenDungeonSmallTitle::~OpenDungeonSmallTitle() = default;

bool OpenDungeonSmallTitle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenDungeonSmallTitle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenDungeonSmallTitle::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenDungeonSmallTitle::loadParams_() {
    getStaticParam(&mMstxt_s, "Mstxt");
    getDynamicParam(&mSubMstxt_d, "SubMstxt");
}

void OpenDungeonSmallTitle::calc_() {
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
