#include "Game/Actor/Player/AI/aiPlayerAttack.h"
#include "Game/gameUnk_710246d058.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/AS/ASList.h"

namespace uking::ai {

PlayerAttack::PlayerAttack(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool PlayerAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: flag loads and child-selection branch joins differ.
void PlayerAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    if (handlePendingChildChange())
        return;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    if (player->_c50.isOnBit(41)) {
        changeChild("ふいうち", nullptr);
        return;
    }
    if (player->_c40.isOnBit(9)) {
        player->_c40.resetBit(9);
        changeChild("ジャスト後攻撃", nullptr);
        return;
    }
    if (player->_1fa8 > 1.0f) {
        changeChild("ダッシュ攻撃", nullptr);
        return;
    }
    if (player->x_51() && u8(player->sub_7100892F1C()) != 0) {
        changeChild(player->_d24 == 1 ? "大剣回転斬り" : "回転斬り", nullptr);
        return;
    }
    if (player->get17d0()->controllerCheckPressedMaybe(5) && player->_c40.isOnBit(3)) {
        changeChild("ガード攻撃", nullptr);
        return;
    }
    if (player->_d24 == 1 && !player->m227() && !player->sub_71008736E4()) {
        changeChild(player->sub_7100892724() ? "大剣回転斬り" : "小攻撃", nullptr);
        return;
    }
    changeChild(player->sub_7100892724() ? "回転斬り" : "小攻撃", nullptr);
}

void PlayerAttack::loadParams_() {}

bool PlayerAttack::isFinished() const {
    if (isCurrentChild("小攻撃") || isCurrentChild("大攻撃")) {
        if (static_cast<uking::act::PlayerBase*>(mActor)->m224())
            return true;
    }
    if (isCurrentChild("ガード攻撃")) {
        if (static_cast<uking::act::PlayerBase*>(mActor)->_c40.isOnBit(9))
            return false;
    }
    if (isCurrentChild("大剣回転斬り") &&
        static_cast<uking::act::PlayerBase*>(mActor)->get17d0()->controllerCheckPressedMaybe(14) &&
        mActor->getASList()->x_1(0, 0) == "CutChargeLswordSpin") {
        return true;
    }
    auto* child = getCurrentChild();
    if (!child->isFinished() && !child->isFailed())
        return false;
    return true;
}

bool PlayerAttack::isChangeable() const {
    if (isCurrentChild("ガード攻撃")) {
        if (static_cast<uking::act::PlayerBase*>(mActor)->_c40.isOnBit(9))
            return false;
    }
    return getCurrentChild()->isChangeable();
}

}  // namespace uking::ai
