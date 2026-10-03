#include "Game/AI/Action/actionTriggerAllPartsSleep.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "Game/Actor/actEnemy.h"

namespace uking::action {

TriggerAllPartsSleep::TriggerAllPartsSleep(const InitArg& arg) : ksys::act::ai::Action(arg) {}

TriggerAllPartsSleep::~TriggerAllPartsSleep() = default;

bool TriggerAllPartsSleep::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void TriggerAllPartsSleep::loadParams_() {}

bool TriggerAllPartsSleep::oneShot_() {
    // NON_MATCHING: regalloc (the original computes the begin node before the end sentinel and keeps the sentinel in
    // the register of the Enemy pointer)
    if (auto* enemy = sead::DynamicCast<uking::act::Enemy>(mActor)) {
        auto& list = enemy->_1128.mList;
        for (auto it = list.begin(); it != list.end(); ++it) {
            ksys::act::ActorConstDataAccess accessor;
            ksys::act::acquireActor(&(*it)->mLink, &accessor);
            accessor.sleep(ksys::act::BaseProc::SleepWakeReason(0));
        }
    }
    return true;
}

}  // namespace uking::action
