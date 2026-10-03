#include "Game/AI/Action/actionPlayerDamage.h"
#include <cstring>
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "Game/gameUnk_71008ba8d8.h"

namespace uking::action {

PlayerDamage::PlayerDamage(const InitArg& arg) : PlayerAction(arg) {
    std::memset(&mBaseInitSpeedNSword_s, 0, 0x80);
}

void PlayerDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
}

void PlayerDamage::leave_() {
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
}

void PlayerDamage::loadParams_() {
    getStaticParam(&mBaseInitSpeedNSword_s, "BaseInitSpeedNSword");
    getStaticParam(&mBaseInitSpeedLSword_s, "BaseInitSpeedLSword");
    getStaticParam(&mBaseInitSpeedSpear_s, "BaseInitSpeedSpear");
    getStaticParam(&mBaseInitSpeedOther_s, "BaseInitSpeedOther");
    getStaticParam(&mAddSpeedNSword_s, "AddSpeedNSword");
    getStaticParam(&mAddSpeedLSword_s, "AddSpeedLSword");
    getStaticParam(&mAddSpeedSpear_s, "AddSpeedSpear");
    getStaticParam(&mAddSpeedOther_s, "AddSpeedOther");
    getStaticParam(&mMaxSpeedNSword_s, "MaxSpeedNSword");
    getStaticParam(&mMaxSpeedLSword_s, "MaxSpeedLSword");
    getStaticParam(&mMaxSpeedSpear_s, "MaxSpeedSpear");
    getStaticParam(&mMaxSpeedOther_s, "MaxSpeedOther");
    getStaticParam(&mDecSpeedNSword_s, "DecSpeedNSword");
    getStaticParam(&mDecSpeedLSword_s, "DecSpeedLSword");
    getStaticParam(&mDecSpeedSpear_s, "DecSpeedSpear");
    getStaticParam(&mDecSpeedOther_s, "DecSpeedOther");
}

void PlayerDamage::calc_() {
    if (!static_cast<ksys::act::Player*>(mActor)->stillAlive())
        callPlayerGameOverDemo(mActor);
    static_cast<ksys::act::Player*>(mActor)->_20bc.chase(0.0f,
                                                         static_cast<ksys::act::Player*>(mActor)->_1800);
    m32();
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
}

bool PlayerDamage::isChangeable() const {
    return _1c;
}

}  // namespace uking::action
