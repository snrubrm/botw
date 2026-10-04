#include "KingSystem/ActorSystem/Profiles/actPlayerArmors.h"
#include "Game/Actor/actArmorBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

namespace ksys::act {

void PlayerArmors::sub_7100E31B9C(Unk117* arg) {
    for (int i = 0; i < 6; ++i) {
        if (auto* actor = sead::DynamicCast<Actor>(_10(i).getProc(nullptr, nullptr)))
            actor->x_17(arg);
    }
}

void PlayerArmors::sleep(BaseProc::SleepWakeReason reason) {
    for (int i = 0; i < 6; ++i) {
        if (_10(i).hasProc()) {
            ActorConstDataAccess accessor;
            acquireActor(&_10(i), &accessor);
            accessor.sleep(reason);
        }
    }
}

bool PlayerArmors::sub_7100E2F428() {
    bool result = false;
    if (_10(1).hasProc()) {
        acc::Armor accessor;
        acquireActor(&_10(1), &accessor);
        result = accessor.getArmorUpperDisableSelfMantle();
    }
    return result;
}

bool PlayerArmors::sub_7100E2F358() {
    bool result = false;
    if (_10(0).hasProc()) {
        acc::Armor accessor;
        acquireActor(&_10(0), &accessor);
        result = accessor.sub_7100E2BF44();
    }
    return result;
}

sead::BitFlag16* PlayerArmors::sub_7100E2F61C() {
    return &_134;
}

}  // namespace ksys::act
