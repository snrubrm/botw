#include "Game/AI/Action/actionSiteBossSwordChemicalPlus.h"
#include "Game/Actor/actSiteBoss.h"

namespace uking::action {

SiteBossSwordChemicalPlus::SiteBossSwordChemicalPlus(const InitArg& arg)
    : ActionWithPosAngReduce(arg) {}

SiteBossSwordChemicalPlus::~SiteBossSwordChemicalPlus() = default;

bool SiteBossSwordChemicalPlus::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void SiteBossSwordChemicalPlus::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
    _30 = 0x100;
    _32 = false;
    if (auto* boss = sead::DynamicCast<act::SiteBoss>(mActor)) {
        if (!boss->_1558.isOnBit(0))
            _32 = true;
    }
    if (_32)
        playAS("Chemical_Plus", false, 0, 0, -1.0f);
    else
        playAS("Chemical_Change_Sword", false, 0, 0, -1.0f);
}

void SiteBossSwordChemicalPlus::leave_() {
    ActionWithPosAngReduce::leave_();
}

void SiteBossSwordChemicalPlus::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void SiteBossSwordChemicalPlus::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
