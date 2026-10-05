#include "Game/AI/AI/aiPlayerGrab.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/gameUnk_710246d058.h"

namespace uking::ai {

PlayerGrab::PlayerGrab(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerGrab::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerGrab::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerGrab::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerGrab::calc_() {
    if (handlePendingChildChange())
        return;
    static_cast<ksys::act::Player*>(mActor)->sub_710086B834();
    if (static_cast<ksys::act::Player*>(mActor)->_1cb0 != -1 &&
        static_cast<ksys::act::Player*>(mActor)->get17d0()->controllerCheckPressedMaybe(0)) {
        const s32 type = static_cast<ksys::act::Player*>(mActor)->_1cb0;
        if (type >= 22 && type <= 25) {
            ui::sub_7100A95F5C(type);
            static_cast<ksys::act::Player*>(mActor)->sub_710086BCF8();
        }
    }
    if (isCurrentChild("置き") &&
        static_cast<ksys::act::Player*>(mActor)->get17d0()->controllerCheckPressedMaybe(17))
        _38 = true;
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("準備")) {
            if (!getCurrentChild()->isFailed())
                changeChild("持上げ", nullptr);
        } else if (isCurrentChild("置き")) {
            if (_38)
                changeChild("しゃがみ", nullptr);
            else if (_39)
                changeChild("風の加護ジャンプ溜め", nullptr);
            else
                changeChild("立ち上がり", nullptr);
        }
    }
}

void PlayerGrab::loadParams_() {}

bool PlayerGrab::isFinished() const {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("投げ") || isCurrentChild("立ち上がり"))
            return true;
        if (getCurrentChild()->isFailed()) {
            if (isCurrentChild("準備") || isCurrentChild("持上げ"))
                return true;
        } else if (getCurrentChild()->isFinished()) {
            if (isCurrentChild("持上げ"))
                return true;
        }
    }
    return false;
}

bool PlayerGrab::isChangeable() const {
    if (getCurrentChild()->isChangeable()) {
        if (isCurrentChild("投げ") || isCurrentChild("立ち上がり"))
            return true;
    }
    return false;
}

}  // namespace uking::ai
