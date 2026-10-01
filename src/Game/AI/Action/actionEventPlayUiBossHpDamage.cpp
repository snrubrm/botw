#include "Game/AI/Action/actionEventPlayUiBossHpDamage.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

EventPlayUiBossHpDamage::EventPlayUiBossHpDamage(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventPlayUiBossHpDamage::~EventPlayUiBossHpDamage() = default;

bool EventPlayUiBossHpDamage::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventPlayUiBossHpDamage::enter_(ksys::act::ai::InlineParamPack* params) {
    float num_cleared = ksys::gdt::getFlag_Clear_RemainsWind() ? 1.0f : 0.0f;
    if (ksys::gdt::getFlag_Clear_RemainsWater())
        num_cleared += 1.0f;
    if (ksys::gdt::getFlag_Clear_RemainsFire())
        num_cleared += 1.0f;
    if (ksys::gdt::getFlag_Clear_RemainsElectric())
        num_cleared += 1.0f;
    ksys::gdt::setFlag_DispBossGaugeRate_Demo(1.0f - num_cleared * 0.125f);
}

void EventPlayUiBossHpDamage::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventPlayUiBossHpDamage::loadParams_() {
    getDynamicParam(&mClipIndex_d, "ClipIndex");
}

void EventPlayUiBossHpDamage::calc_() {
    setFinished();
}

}  // namespace uking::action
