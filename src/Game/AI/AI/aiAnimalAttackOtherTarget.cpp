#include "Game/AI/AI/aiAnimalAttackOtherTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
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

// NON_MATCHING: same as enter_ (the original destroys the accessor separately on each side of the
// sub_7100022FD0 test instead of keeping the result in a register across the destructor; an inline
// helper with separate returns and an if-with-initializer did not change that)
void AnimalAttackOtherTarget::calc_() {
    if (hasAttackInfo(mActor))
        _38 = true;

    if (!sub_71005D94AC(mActor).hasProc()) {
        setFailed();
        return;
    }

    if (isChangeable()) {
        auto& target = sub_71005D94AC(mActor);
        if (ksys::act::isNPCProfile(&target)) {
            bool ok = false;
            {
                ksys::act::ActorConstDataAccess accessor;
                if (ksys::act::acquireActor(&target, &accessor) && accessor.sub_7100022FD0())
                    ok = true;
            }
            if (ok && isCurrentChild("戦闘行動")) {
                if (_38)
                    changeChild("攻撃後");
                else
                    changeChild("待機");
                return;
            }
        }
    }

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (!isCurrentChild("攻撃後"))
            setFinished();
        changeChild("待機");
    }
}

void AnimalAttackOtherTarget::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AnimalAttackOtherTarget::loadParams_() {}

}  // namespace uking::ai
