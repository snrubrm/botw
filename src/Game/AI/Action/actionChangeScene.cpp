#include "Game/AI/Action/actionChangeScene.h"

namespace uking::action {

ChangeScene::ChangeScene(const InitArg& arg) : ChangeSceneBase(arg) {}

// Empty-statement body as in upstream's GameDataFlagSelector::~GameDataFlagSelector() (96101229):
// the original keeps the vtable store that a defaulted destructor drops.
ChangeScene::~ChangeScene() {
    ;
}

bool ChangeScene::init_(sead::Heap* heap) {
    return ChangeSceneBase::init_(heap);
}

void ChangeScene::enter_(ksys::act::ai::InlineParamPack* params) {
    ChangeSceneBase::enter_(params);
}

void ChangeScene::leave_() {
    ChangeSceneBase::leave_();
}

void ChangeScene::loadParams_() {
    ChangeSceneBase::loadParams_();
    getDynamicParam(&mFadeType_d, "FadeType");
    getDynamicParam(&mWarpDestMapName_d, "WarpDestMapName");
    getDynamicParam(&mWarpDestPosName_d, "WarpDestPosName");
}

void ChangeScene::calc_() {
    ChangeSceneBase::calc_();
}

}  // namespace uking::action
