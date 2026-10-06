#include "Game/AI/Action/actionCustomDuckingStartAction.h"

#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::action {

namespace {
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

CustomDuckingStartAction::CustomDuckingStartAction(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CustomDuckingStartAction::~CustomDuckingStartAction() = default;

bool CustomDuckingStartAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CustomDuckingStartAction::loadParams_() {
    getDynamicParam(&mVolume_d, "Volume");
    getDynamicParam(&mFadeOutSec_d, "FadeOutSec");
    getDynamicParam(&mFadeInSec_d, "FadeInSec");
    getDynamicParam(&mStartDelaySec_d, "StartDelaySec");
    getDynamicParam(&mTargetGroups_d, "TargetGroups");
    getDynamicParam(&mExceptGroups_d, "ExceptGroups");
}

bool CustomDuckingStartAction::oneShot_() {
    ksys::snd::Unk_710103b704::StartParam param;
    param._0 = mTargetGroups_d;
    param._10 = mExceptGroups_d;
    param._20 = *mVolume_d;
    param._24 = *mFadeOutSec_d;
    param._28 = *mFadeInSec_d;
    param._2c = *mStartDelaySec_d;
    ksys::snd::SoundMgr::instance()->_98->sub_710103CFF4(param);
    return true;
}

}  // namespace uking::action
