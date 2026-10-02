#include "Game/AI/AI/aiSleepSelect.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

SleepSelect::SleepSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SleepSelect::~SleepSelect() = default;

bool SleepSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SleepSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71005DD798(mActor, 19, nullptr, 0, 0)) {
        changeChild("睡眠中", params);
        return;
    }
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor)) {
        if (enemy->_e84.isOnBit(8)) {
            changeChild("睡眠中", params);
            return;
        }
    }
    changeChild("活動中", params);
}

void SleepSelect::calc_() {}

void SleepSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SleepSelect::loadParams_() {}

}  // namespace uking::ai
