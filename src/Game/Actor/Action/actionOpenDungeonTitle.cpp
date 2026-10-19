#include "Game/Actor/Action/actionOpenDungeonTitle.h"
#include "Game/Scene/gameStageInfo.h"
#include "Game/Scene/gameScene.h"
#include "Game/UI/uiUI.h"

namespace uking::action {

OpenDungeonTitle::OpenDungeonTitle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenDungeonTitle::~OpenDungeonTitle() = default;

bool OpenDungeonTitle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenDungeonTitle::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* ui = ui::UI::instance();
    if (!ui) {
        setFailed();
        return;
    }
    sead::FixedSafeString<256> label(uking::StageInfo::getCurrentMapName());
    sead::FixedSafeString<256> secondary_label(uking::StageInfo::getCurrentMapName());
    ui->sub_71010A7774(mMstxt_s, label, mSubMstxt_d, secondary_label, true);
}

void OpenDungeonTitle::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenDungeonTitle::loadParams_() {
    getStaticParam(&mMstxt_s, "Mstxt");
    getDynamicParam(&mSubMstxt_d, "SubMstxt");
}

void OpenDungeonTitle::calc_() {
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
