#include "Game/AI/Action/actionChangeScene.h"
#include "Game/gameScene.h"
#include "KingSystem/Event/evtManager.h"
#include "KingSystem/System/StageInfo.h"

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
    if (isFinished() || isFailed())
        return;

    const auto* manager = ksys::evt::Manager::instance();
    if (manager->_1d2f4_bytes[0] & 0x20) {
        setFinished();
        return;
    }
    if (manager->_1d174 & 0x40) {
        GameScene::sub_71007B7D78();
        return;
    }

    // NON_MATCHING: the original materializes the 0 argument as `mov x0, xzr` (64-bit) while the 1 / 2
    // cases use `orr w0` like ours: the declaration of gameSceneSetFadeType seen by this call site takes a
    // 64-bit argument, although the definition is mangled as (int) — the same width mismatch that leaves
    // gameSceneSetFadeType itself m (`and x1, x0, #0xffffffff` there).
    if (*mFadeType_d == 0)
        gameSceneSetFadeType(0);
    else if (*mFadeType_d == 1)
        gameSceneSetFadeType(1);
    else if (*mFadeType_d == 2)
        gameSceneSetFadeType(2);

    initWarpEventFlow(mWarpDestMapName_d, mWarpDestPosName_d);
    ksys::StageInfo::sub_7100ED8C64(mWarpDestMapName_d, mWarpDestPosName_d, _48, false);
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
