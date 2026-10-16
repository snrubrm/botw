#include "Game/UI/uiOnUiActorMgr.h"
#include "KingSystem/ActorSystem/actLodState.h"
#include <gsys/gsysModel.h>
#include "Game/Actor/actWeapon.h"
#include "Game/Actor/actPauseMenuPlayer.h"
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

}  // namespace uking::ui
