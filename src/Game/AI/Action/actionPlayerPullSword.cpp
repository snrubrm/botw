#include "Game/AI/Action/actionPlayerPullSword.h"

#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Event/evtManager.h"
#include "Game/gameRoot4.h"

namespace uking::action {

PlayerPullSword::PlayerPullSword(const InitArg& arg) : PlayerAction(arg) {}

void PlayerPullSword::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cf4.set(0x80);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    player->_20bc.value = 0;
    player->_20bc.prev_value = 0;
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    _68 = 0;
    static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(0, 0);
    static_cast<ksys::act::Player*>(mActor)->_1850 = ksys::Timer(0, 0, 1);
    const auto* life = mActor->getLife();
    const s32 max_life = life ? *life : 1;
    const s32 consumed_life = static_cast<ksys::act::Player*>(mActor)->m321();
    static_cast<ksys::act::Player*>(mActor)->_17f0 = max_life - consumed_life >= *mSuccessLife_s;
    ksys::act::PlayerInfo::instance()->saveLifeInfoForSwordPull();
    static_cast<ksys::act::Player*>(mActor)->_1ffc = 0;
    Root4::instance()->sub_71008BCF44(Root4::FlagIdx::_1, true);
}

void PlayerPullSword::leave_() {
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x10000000);
    static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x20000000);
    if (_68 != 6) {
        static_cast<ksys::act::Player*>(mActor)->releaseWeapon(3);
        mActor->getWeapons()->mWeapons[3]._10 = true;
    }
    mActor->getASList()->sub_710115C11C();
    if (!(ksys::evt::Manager::instance()->_1d2f4 & 0x40))
        Root4::instance()->sub_71008BCFA0(Root4::FlagIdx::_1);
}

void PlayerPullSword::loadParams_() {
    getStaticParam(&mLifeDecInterval1_s, "LifeDecInterval1");
    getStaticParam(&mLifeDecInterval2_s, "LifeDecInterval2");
    getStaticParam(&mLifeDecInterval3_s, "LifeDecInterval3");
    getStaticParam(&mLifeDecInterval4_s, "LifeDecInterval4");
    getStaticParam(&mLifeDecInterval5_s, "LifeDecInterval5");
    getStaticParam(&mInterruptInterval_s, "InterruptInterval");
    getStaticParam(&mSuccessLife_s, "SuccessLife");
}

void PlayerPullSword::calc_() {
    PlayerAction::calc_();
}

bool PlayerPullSword::isChangeable() const {
    return false;
}

}  // namespace uking::action
