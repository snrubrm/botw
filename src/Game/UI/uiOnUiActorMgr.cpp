#include "Game/UI/uiOnUiActorMgr.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include <gsys/gsysModel.h>
#include <layer/aglLayer.h>
#include <layer/aglRenderer.h>
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/actPauseMenuPlayer.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerArmors.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::ui {

OnUiActorMgr* OnUiActorMgr::sInstance = nullptr;

void OnUiActorMgr::sub_7100906F08(ksys::act::Actor* actor) {
    if (!mActor)
        mActor = actor;
}

bool OnUiActorMgr::sub_710090AB4C() const {
    return !mArmors || mArmors->hasNoPartBeingCreated();
}

// 0x710090aa30
uking::act::Weapon* OnUiActorMgr::sub_710090AA30(s32 idx) {
    if (idx > 2)
        return nullptr;
    auto& handle = _60[idx];
    if (handle.isProcReady()) {
        auto* proc = handle.releaseAndWakeProc();
        if (auto* weapon = sead::DynamicCast<uking::act::Weapon>(proc)) {
            weapon->_cec = 2;
            if (auto* model = weapon->getModel())
                model->bind(_98);
            if (auto* lod = weapon->getLodState())
                lod->mFlags26.set(1);
            weapon->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000);
            return weapon;
        }
        proc->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    } else if (handle.hasProcCreationFailed()) {
        handle.deleteProcIfFailed();
    }
    return nullptr;
}

// 0x710090ab60
ksys::act::Actor* OnUiActorMgr::getActor() const {
    return mActor;
}

// 0x7100906e70
void OnUiActorMgr::sub_7100906E70() {
    if (mArmors) {
        delete mArmors;
        mArmors = nullptr;
    }
    if (mActor) {
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        mActor = nullptr;
    }
    if (_50.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_50, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
        _50.reset();
    }
    _1f4.makeAllZero();
}

// 0x71009079ec
void OnUiActorMgr::sub_71009079EC(bool on) {
    if (auto* player = static_cast<uking::act::PauseMenuPlayer*>(mActor)) {
        player->_c34 = on;
        if (!on)
            player->_c38 = 0;
    }
    if (on)
        _1f4.set(8);
    else
        _1f4.reset(8);
}

// 0x71009070d0
void OnUiActorMgr::x_4() {
    const s32 hot = ksys::gdt::getFlag_Item_HotLevelAdd(false);
    const s32 cold = ksys::gdt::getFlag_Item_ColdResistLevelAdd(false);
    const s32 burn = ksys::gdt::getFlag_Item_BurnLevelAdd(false);
    if (hot >= 1) {
        if (auto* player = static_cast<uking::act::PauseMenuPlayer*>(mActor)) {
            player->sub_71006E9E24();
            player->_c3c = hot;
        }
    } else if (cold >= 1) {
        if (auto* player = static_cast<uking::act::PauseMenuPlayer*>(mActor)) {
            player->sub_71006E9E24();
            player->_c40 = cold;
        }
    } else if (burn >= 1) {
        if (auto* player = static_cast<uking::act::PauseMenuPlayer*>(mActor)) {
            player->sub_71006E9E24();
            player->_c44 = burn;
        }
    } else if (auto* player = static_cast<uking::act::PauseMenuPlayer*>(mActor)) {
        player->sub_71006E9E24();
    }
}

// 0x7100907b24
void OnUiActorMgr::sub_7100907B24(const f32* value) {
    if (mActor && mActor->getChemicalStuff()) {
        auto* chemical = mActor->getChemicalStuff();
        chemical->_170 = *value;
    }
}

// 0x7100907190 (placeholder name): copies the player's heat state to the pause menu player and sets
// the pause menu player's burn threshold.
void OnUiActorMgr::sub_7100907190() {
    if (!mActor)
        return;

    auto* info = act::PlayerInfo::instance();
    if (!info)
        return;
    auto* player = info->getPlayer();
    if (!player)
        return;

    auto* pause_player = static_cast<uking::act::PauseMenuPlayer*>(mActor);
    pause_player->_c35 = !player->m306();

    auto* chemical = player->getChemicalStuff();
    if (!chemical)
        return;

    const f32 heat = chemical->_170;
    if (mActor && mActor->getChemicalStuff())
        mActor->getChemicalStuff()->_170 = heat;

    const bool is_hot = !(chemical->_c & 0x1000000) && chemical->_190 > 0.0f;
    auto* threshold_target = static_cast<uking::act::PauseMenuPlayer*>(mActor);
    threshold_target->_c48 = is_hot ? 0 : chemical->sub_7100D914C0();
}

// 0x7100907b74 (placeholder name): sets the pause menu player's heat resist level
void OnUiActorMgr::sub_7100907B74(const s32* value) {
    auto* player = static_cast<uking::act::PauseMenuPlayer*>(mActor);
    if (player) {
        player->sub_71006E9E24();
        player->_c3c = *value;
    }
}

// 0x7100907ba8 (placeholder name): sets the pause menu player's cold resist level
void OnUiActorMgr::sub_7100907BA8(const s32* value) {
    auto* player = static_cast<uking::act::PauseMenuPlayer*>(mActor);
    if (player) {
        player->sub_71006E9E24();
        player->_c40 = *value;
    }
}

// 0x7100907bdc (placeholder name): sets the pause menu player's burn resist level
void OnUiActorMgr::sub_7100907BDC(const s32* value) {
    auto* player = static_cast<uking::act::PauseMenuPlayer*>(mActor);
    if (player) {
        player->sub_71006E9E24();
        player->_c44 = *value;
    }
}

// 0x7100907c10 (placeholder name): sets the pause menu player's _c35 flag
void OnUiActorMgr::sub_7100907C10() {
    auto* player = static_cast<uking::act::PauseMenuPlayer*>(mActor);
    if (player)
        player->_c35 = true;
}

// 0x7100907c24 (placeholder name): updates the pause menu player's resist state
void OnUiActorMgr::sub_7100907C24() {
    auto* player = static_cast<uking::act::PauseMenuPlayer*>(mActor);
    if (player)
        player->sub_71006E9E24();
}

// 0x7100907c34
void OnUiActorMgr::sub_7100907C34(const s32* index) {
    if (!mActor)
        return;
    static_cast<uking::act::PauseMenuPlayer*>(mActor)->_c38 = *index;
    _198.sendMessage(*mActor->getMesTransceiverId(),
                     static_cast<ksys::MessageType>(0x8000091), nullptr, true);
}

// 0x7100907914
void OnUiActorMgr::sub_7100907914(bool on) {
    if (!on) {
        _1f4.set(0x20);
        if (_50.hasProc()) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ksys::act::acquireActor(&_50, &accessor);
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason::_0);
        }
        if (auto* layer = agl::lyr::Renderer::instance()->getLayer(10))
            layer->sub_7100B60D60(false);
    } else {
        if (auto* layer = agl::lyr::Renderer::instance()->getLayer(10))
            layer->sub_7100B60D60(true);
    }
}

}  // namespace uking::ui
