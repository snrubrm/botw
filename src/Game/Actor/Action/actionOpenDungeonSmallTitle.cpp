#include "Game/Actor/Action/actionOpenDungeonSmallTitle.h"
#include "Game/Scene/gameStageInfo.h"
#include "Game/Scene/gameScene.h"
#include "Game/UI/uiUI.h"

namespace uking::action {

OpenDungeonSmallTitle::OpenDungeonSmallTitle(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenDungeonSmallTitle::~OpenDungeonSmallTitle() = default;

bool OpenDungeonSmallTitle::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenDungeonSmallTitle::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* ui = ui::UI::instance();
    if (!ui) {
        setFailed();
        return;
    }
    sead::FixedSafeString<256> label(uking::StageInfo::getCurrentMapName());
    sead::FixedSafeString<256> secondary_label(uking::StageInfo::getCurrentMapName());
    ui->sub_71010A6800(mMstxt_s, label, mSubMstxt_d, secondary_label);
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
