#include "Game/AI/AI/aiStalPartCatch.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "Game/Actor/actEnemy.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace uking::ai {

StalPartCatch::StalPartCatch(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

StalPartCatch::~StalPartCatch() = default;

bool StalPartCatch::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void StalPartCatch::enter_(ksys::act::ai::InlineParamPack* params) {
    if (auto* enemy = sub_7100724D7C(mActor)) {
        ksys::act::ActorConstDataAccess accessor;
        auto& head = sub_7100725588(enemy);
        if (head.hasProc()) {
            ksys::act::acquireActor(&head, &accessor);
            if (accessor.isStateCalc()) {
                changeChild("頭拾い");
                return;
            }
        }

        auto& arm = sub_71007255A0(enemy);
        if (arm.hasProc()) {
            ksys::act::acquireActor(&arm, &accessor);
            if (accessor.isStateCalc()) {
                auto* actor = sead::DynamicCast<ksys::act::Actor>(arm.getProc(nullptr, nullptr));
                auto* weapon = sead::DynamicCast<act::Weapon>(actor);
                if (weapon && !weapon->hasParentActor()) {
                    changeChild("腕拾い");
                    return;
                }
            }
        }
    }
    setFailed();
}

void StalPartCatch::calc_() {
    if (isFinished() || isFailed())
        return;

    auto* child = getCurrentChild();
    if (child->isFinished())
        setFinished();
    else if (child->isFailed())
        setFailed();
}

void StalPartCatch::leave_() {
    ksys::act::ai::Ai::leave_();
}

void StalPartCatch::loadParams_() {}

bool StalPartCatch::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool StalPartCatch::isFinished() const {
    return ksys::act::ai::Ai::isFinished() || getCurrentChild()->isFinished();
}

}  // namespace uking::ai
