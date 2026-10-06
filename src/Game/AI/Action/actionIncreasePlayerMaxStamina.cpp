#include "Game/AI/Action/actionIncreasePlayerMaxStamina.h"
#include "Game/AI/aiUnk_710073BB28.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerLink.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ui {
// 0x7100a9b4a4 (uiManagerFacade.cpp)
void updateStaminaAndMax(f32 stamina, f32 max_stamina, f32 a2);
}  // namespace uking::ui

namespace uking::action {

IncreasePlayerMaxStamina::IncreasePlayerMaxStamina(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

IncreasePlayerMaxStamina::~IncreasePlayerMaxStamina() = default;

bool IncreasePlayerMaxStamina::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void IncreasePlayerMaxStamina::enter_(ksys::act::ai::InlineParamPack* params) {
    if (!ksys::act::PlayerInfo::instance()) {
        setFailed();
        return;
    }

    const s32 value = *mValue_d;
    const bool is_move_center = *mIsMoveCenter_d;
    using ksys::act::PlayerInfo;
    const f32 max_stamina = f32(s32(PlayerInfo::instance()->getStaminaMax()) + value * 200);
    PlayerInfo::instance()->setStaminaMax(max_stamina);
    if (auto* player = PlayerInfo::instance()->getPlayer()) {
        if (auto* link = player->m129())
            link->m377();
    }
    auto* info = PlayerInfo::instance();
    info->setStaminaCurrentMax(info->getMaxStaminaFromPlayerActor());
    sub_710073BB28(value >= 0, is_move_center);
    ui::updateStaminaAndMax(PlayerInfo::instance()->getStaminaCurrentMax(),
                            PlayerInfo::instance()->getMaxStaminaFromPlayerActor(), 2000.0f);
}

void IncreasePlayerMaxStamina::leave_() {
    ksys::act::ai::Action::leave_();
}

void IncreasePlayerMaxStamina::loadParams_() {
    getDynamicParam(&mValue_d, "Value");
    getDynamicParam(&mIsMoveCenter_d, "IsMoveCenter");
}

void IncreasePlayerMaxStamina::calc_() {
    if (isFinished())
        return;
    if (isFailed())
        return;
    if (sub_710073BB54())
        setFinished();
}

}  // namespace uking::action
