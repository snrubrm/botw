#include "Game/AI/Action/actionPlayerPullSword.h"

#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorWeapons.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Event/evtManager.h"
#include "Game/gameRoot4.h"
#include "Game/gameRumble.h"
#include "Game/gameUnk_710246d058.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

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

// NON_MATCHING: state predicates and actor loads produce different block order and register allocation.
void PlayerPullSword::calc_() {
    if (ksys::act::PlayerInfo::instance()->getLifeFromPlayerActor() == 0 && _68 != 10) {
        _68 = 10;
        static_cast<ksys::act::Player*>(mActor)->_cf0.set(0x100);
        static_cast<ksys::act::Player*>(mActor)->_c48.set(1);
        mActor->getASList()->sub_710115BC28("MasterSwordDead", -1);
        static_cast<ksys::act::Player*>(mActor)->releaseWeapon(3);
    }
    mActor->getASList()->x_2(0x42, 0x21, true, false);
    if (_68 != 0 && _68 != 6 && _68 != 7 && _68 != 8 && _68 != 9 && _68 != 10) {
        sub_7100807630();
        if (!static_cast<ksys::act::Player*>(mActor)->_17d0->playerCheckController(0)) {
            static_cast<ksys::act::Player*>(mActor)->_c48.set(0x4000000);
            _68 = 7;
            mActor->getASList()->sub_710115BC28("Demo300_0-C02-Link-A-0", -1);
            static_cast<ksys::act::Player*>(mActor)->releaseWeapon(3);
        }
    }
    if (!(static_cast<ksys::act::Player*>(mActor)->_1844.value <= sead::Mathf::epsilon()))
        static_cast<ksys::act::Player*>(mActor)->_1844.update();
    if (_68 == 0) {
        static_cast<ksys::act::Player*>(mActor)->_c44.set(0x10000000);
        if (static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(14)) {
            static_cast<ksys::act::Player*>(mActor)->_c48.reset(0x4000000);
            _68 = 8;
        }
    } else {
        static_cast<ksys::act::Player*>(mActor)->_c44.reset(0x10000000);
        static_cast<ksys::act::Player*>(mActor)->_c44.set(0x20000000);
    }
    if (_68 != 0 && _68 != 6 && _68 != 7)
        static_cast<ksys::act::Player*>(mActor)->_1cb0 = 14;
    switch (_68) {
    case 0:
        static_cast<ksys::act::Player*>(mActor)->_1cb0 = 14;
        if (!static_cast<ksys::act::Player*>(mActor)->_17d0->controllerCheckPressedMaybe(0))
            return;
        uking::ui::sub_7100A95F5C(14);
        if (!ksys::gdt::getFlag_Get_MasterSword_FirstFailure(false) &&
            ksys::act::PlayerInfo::instance()->getLifeFromPlayerActor() == 1) {
            _68 = 9;
            static_cast<ksys::act::Player*>(mActor)->_c48.set(0x4000000);
            auto* actor = mActor;
            actor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0);
            actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0);
            static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(2, 2);
        } else {
            _68 = 1;
            mActor->getASList()->sub_710115BC28("Demo300_0-C01-Link-A-1", -1);
            sub_71008077FC();
        }
        break;
    case 1:
        if (!mActor->getASList()->x_4(0, 0)) return;
        Rumble::instance()->sub_7100897FE4(1, 1);
        _68 = 2;
        mActor->getASList()->sub_710115BC28("Demo300_0-C01-Link-A-2", -1);
        break;
    case 2:
        if (!mActor->getASList()->x_4(0, 0)) return;
        Rumble::instance()->sub_7100897FE4(1, 1);
        _68 = 3;
        mActor->getASList()->sub_710115BC28("Demo300_0-C01-Link-A-3", -1);
        break;
    case 3:
        if (!mActor->getASList()->x_4(0, 0)) return;
        Rumble::instance()->sub_7100897FE4(1, 1);
        _68 = 4;
        mActor->getASList()->sub_710115BC28("Demo300_0-C01-Link-A-4", -1);
        break;
    case 4:
        if (!mActor->getASList()->x_4(0, 0)) return;
        Rumble::instance()->sub_7100897FE4(1, 1);
        _68 = 5;
        mActor->getASList()->sub_710115BC28("Demo300_0-C01-Link-A-5", -1);
        break;
    case 5:
        if (!mActor->getASList()->x_4(0, 0)) return;
        Rumble::instance()->sub_7100897FE4(2, 1);
        _68 = 6;
        // Fall through.
    case 6:
        setFinished();
        break;
    case 7:
        if (!mActor->getASList()->x_4(0, 0)) return;
        // Fall through.
    case 8:
        setFailed();
        break;
    case 9:
        if (static_cast<ksys::act::Player*>(mActor)->_1844.value <= sead::Mathf::epsilon())
            setFailed();
        break;
    case 10:
        static_cast<ksys::act::Player*>(mActor)->_c48.set(0x4000000);
        setFailed();
        break;
    }
}

bool PlayerPullSword::isChangeable() const {
    return false;
}

// NON_MATCHING: signed state loads replace the target's zero-extended loads in interval switches.
void PlayerPullSword::sub_7100807630() {
    static_cast<ksys::act::Player*>(mActor)->_1850.update();
    const f32 time = static_cast<ksys::act::Player*>(mActor)->_1850.value;
    f32 interval = 0;
    switch (_68) {
    case 1: interval = *mLifeDecInterval1_s; break;
    case 2: interval = *mLifeDecInterval2_s; break;
    case 3: interval = *mLifeDecInterval3_s; break;
    case 4: interval = *mLifeDecInterval4_s; break;
    case 5: interval = *mLifeDecInterval5_s; break;
    }
    if (!(time >= interval))
        return;
    if (!ksys::gdt::getFlag_Get_MasterSword_FirstFailure(false) &&
        ksys::act::PlayerInfo::instance()->getLifeFromPlayerActor() == 2 &&
        !static_cast<ksys::act::Player*>(mActor)->_17f0) {
        _68 = 9;
        static_cast<ksys::act::Player*>(mActor)->_c48.set(0x4000000);
        auto* actor = mActor;
        actor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0);
        actor->getASList()->x_3(1, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0);
        static_cast<ksys::act::Player*>(mActor)->_1844 = ksys::Timer(2, 2);
    }
    static_cast<ksys::act::Player*>(mActor)->_c50.set(0x100000000);
    auto* player = static_cast<ksys::act::Player*>(mActor);
    interval = 0;
    switch (_68) {
    case 1: interval = *mLifeDecInterval1_s; break;
    case 2: interval = *mLifeDecInterval2_s; break;
    case 3: interval = *mLifeDecInterval3_s; break;
    case 4: interval = *mLifeDecInterval4_s; break;
    case 5: interval = *mLifeDecInterval5_s; break;
    }
    player->_1850.value = time - interval;
    player->_1850.previous_value = time - interval;
}

}  // namespace uking::action
