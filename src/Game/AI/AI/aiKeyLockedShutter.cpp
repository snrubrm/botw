#include "Game/AI/AI/aiKeyLockedShutter.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/gameScene.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::ai {

KeyLockedShutter::KeyLockedShutter(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KeyLockedShutter::~KeyLockedShutter() = default;

void KeyLockedShutter::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* actor = mActor;
    if (actor->checkLinkBasicSig() || actor->isWaitRevivalForUsed())
        changeChild("プリオープン");
    else
        changeChild("クローズ待機");
    _38.x();
    ksys::act::disableAttClient(actor, "Open");
}

// NON_MATCHING: regalloc (address of _38 kept in x20 in the original)
void KeyLockedShutter::calc_() {
    auto* actor = mActor;
    auto* child = getCurrentChild();
    const s32 num_keys = ksys::gdt::getSmallKeyNum(GameScene::getCurrentMapName());

    if (num_keys >= 1 && isCurrentChild("クローズ待機"))
        ksys::act::enableAttClient(actor, "Open");
    else
        ksys::act::disableAttClient(actor, "Open");

    if (isCurrentChild("クローズ待機")) {
        if (child->isChangeable() && num_keys >= 1 && _38._30) {
            _38.x();
            ksys::gdt::incrementSmallKeyNum(GameScene::getCurrentMapName(), -1);
            changeChild("オープン");
            return;
        }
    }
    if (isCurrentChild("オープン") && child->isFinished()) {
        changeChild("オープン待機");
    } else if (isCurrentChild("プリオープン") && (child->isFinished() || child->isFinished())) {
        changeChild("オープン待機");
    }
}

void KeyLockedShutter::loadParams_() {}

bool KeyLockedShutter::handleMessage_(const ksys::Message& message) {
    if (isCurrentChild("クローズ待機") &&
        ksys::gdt::getSmallKeyNum(GameScene::getCurrentMapName()) >= 1 && _38.m2(message)) {
        return true;
    }
    return false;
}

}  // namespace uking::ai
