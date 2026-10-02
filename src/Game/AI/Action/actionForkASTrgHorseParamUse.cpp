#include "Game/AI/Action/actionForkASTrgHorseParamUse.h"
#include "Game/Actor/actEnemy.h"
#include "Game/AI/aiUnk_71005D6D10.h"

namespace uking::action {

ForkASTrgHorseParamUse::ForkASTrgHorseParamUse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgHorseParamUse::~ForkASTrgHorseParamUse() = default;

bool ForkASTrgHorseParamUse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgHorseParamUse::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
}

void ForkASTrgHorseParamUse::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgHorseParamUse::loadParams_() {}

void ForkASTrgHorseParamUse::calc_() {
    if (!sub_71005DD780(mActor, 0x49, nullptr, 0, 0))
        return;
    if (auto* enemy = sead::DynamicCast<act::Enemy>(mActor))
        enemy->_e84.set(0x2000);
}

}  // namespace uking::action
