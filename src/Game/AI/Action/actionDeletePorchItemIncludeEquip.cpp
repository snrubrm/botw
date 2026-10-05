#include "Game/AI/Action/actionDeletePorchItemIncludeEquip.h"
#include "Game/Actor/actPlayerCreateMgr.h"
#include "Game/UI/uiPauseMenuDataMgr.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::action {

DeletePorchItemIncludeEquip::DeletePorchItemIncludeEquip(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DeletePorchItemIncludeEquip::~DeletePorchItemIncludeEquip() = default;

bool DeletePorchItemIncludeEquip::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DeletePorchItemIncludeEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = false;
    const s32 requested_count = *mDeleteNum_d;
    if (requested_count == 0) {
        _38 = true;
        return;
    }
    if (auto* manager = ui::PauseMenuDataMgr::instance()) {
        const s32 count = requested_count > 0 ? -requested_count : requested_count;
        if (manager->checkAddOrRemoveItem(mPorchItemName_d, count, true)) {
            _38 = true;
            _39 = true;
            manager->increasePouchNum(mPorchItemName_d, count, &_39, nullptr);
        }
    }
}

void DeletePorchItemIncludeEquip::leave_() {
    ksys::act::ai::Action::leave_();
}

void DeletePorchItemIncludeEquip::loadParams_() {
    getDynamicParam(&mDeleteNum_d, "DeleteNum");
    getDynamicParam(&mPorchItemName_d, "PorchItemName");
}

void DeletePorchItemIncludeEquip::calc_() {
    if (!_38) {
        setFailed();
        return;
    }
    if (_39) {
        if (!act::CreatePlayerEquipActorMgr::instance()->areAllWeaponActorsReady())
            return;
        if (auto* player = ksys::act::PlayerInfo::instance()->getPlayer())
            player->setC98Locked(0x20);
    }
    setFinished();
}

}  // namespace uking::action
