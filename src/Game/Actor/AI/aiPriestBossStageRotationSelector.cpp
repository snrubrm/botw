#include "Game/Actor/AI/aiPriestBossStageRotationSelector.h"
#include "Game/Actor/aiUnk_7102450fa8.h"

namespace uking::ai {

PriestBossStageRotationSelector::PriestBossStageRotationSelector(const InitArg& arg)
    : PriestBoss(arg) {}

PriestBossStageRotationSelector::~PriestBossStageRotationSelector() = default;

bool PriestBossStageRotationSelector::init_(sead::Heap* heap) {
    return PriestBoss::init_(heap);
}

void PriestBossStageRotationSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBoss::enter_(params);
    auto* unit = sub_7100505BE4();
    if (!unit)
        return;

    _40 = unit->_78.isOnBit(Unk_7102450fa8::Flag(Unk_7102450fa8::Flag::_6));
    _41 = _40;
    if (_40)
        changeChild("回転あり");
    else
        changeChild("回転なし");
}

void PriestBossStageRotationSelector::calc_() {
    auto* unit = sub_7100505BE4();
    if (!unit)
        return;

    _41 = _40;
    _40 = unit->_78.isOnBit(Unk_7102450fa8::Flag(Unk_7102450fa8::Flag::_6));
    if (_40 != _41)
        if (_40)
        changeChild("回転あり");
    else
        changeChild("回転なし");
}

void PriestBossStageRotationSelector::leave_() {
    PriestBoss::leave_();
}

void PriestBossStageRotationSelector::loadParams_() {
    PriestBoss::loadParams_();
}

}  // namespace uking::ai
