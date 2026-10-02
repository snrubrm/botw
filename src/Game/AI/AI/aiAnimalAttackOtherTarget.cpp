#include "Game/AI/AI/aiAnimalAttackOtherTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

AnimalAttackOtherTarget::AnimalAttackOtherTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalAttackOtherTarget::~AnimalAttackOtherTarget() = default;

bool AnimalAttackOtherTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

// NON_MATCHING: the original branches straight to two copies of the accessor destructor instead of
// keeping the result in a register across one
void AnimalAttackOtherTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = false;
    if (sub_71005D94AC(mActor).hasProc()) {
        auto& target = sub_71005D94AC(mActor);
        bool invalid = false;
        if (ksys::act::isNPCProfile(&target)) {
            ksys::act::ActorConstDataAccess accessor;
            invalid = ksys::act::acquireActor(&target, &accessor) && accessor.sub_7100022FD0();
        }
        if (!invalid) {
            changeChild("戦闘行動");
            return;
        }
    }
    setFailed();
    changeChild("待機");
}

void AnimalAttackOtherTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalAttackOtherTarget::loadParams_() {}

}  // namespace uking::ai
