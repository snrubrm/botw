#include "Game/AI/Action/actionNPCArmorProcessing.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"

namespace uking::action {

NPCArmorProcessing::NPCArmorProcessing(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCArmorProcessing::~NPCArmorProcessing() = default;

bool NPCArmorProcessing::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCArmorProcessing::enter_(ksys::act::ai::InlineParamPack* params) {
    _29 = false;
    ksys::gdt::setFlag_Shop_IsDecide(false);
}

void NPCArmorProcessing::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCArmorProcessing::loadParams_() {
    getDynamicParam(&mArmorProcessingRank_d, "ArmorProcessingRank");
}

void NPCArmorProcessing::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
