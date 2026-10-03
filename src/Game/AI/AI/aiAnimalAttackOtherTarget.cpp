#include "Game/AI/AI/aiAnimalAttackOtherTarget.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::ai {

namespace {
// inline-only in the original; name is a guess. Evidence: enter_ and calc_ contain the same sequence and only
// this form (separate `return true` / `return false` exits, so the accessor destructor is emitted on each
// side of the test) reproduces their code.
bool checkNpc(ksys::act::BaseProcLink* target) {
    {
        ksys::act::ActorConstDataAccess accessor;
        if (ksys::act::acquireActor(target, &accessor) && accessor.sub_7100022FD0())
            return true;
    }
    return false;
}
}  // namespace

AnimalAttackOtherTarget::AnimalAttackOtherTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AnimalAttackOtherTarget::~AnimalAttackOtherTarget() = default;

bool AnimalAttackOtherTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AnimalAttackOtherTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _38 = false;
    if (sub_71005D94AC(mActor).hasProc()) {
        auto& target = sub_71005D94AC(mActor);
        bool invalid = false;
        if (ksys::act::isNPCProfile(&target))
            invalid = checkNpc(&target);
        if (!invalid) {
            changeChild("戦闘行動");
            return;
        }
    }
    setFailed();
    changeChild("待機");
}

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
            if (checkNpc(&target) && isCurrentChild("戦闘行動")) {
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
