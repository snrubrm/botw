#include "KingSystem/ActorSystem/Profiles/actPlayerArmors.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace ksys::act {

void PlayerArmors::sub_7100E31B9C(Unk117* arg) {
    for (int i = 0; i < 6; ++i) {
        if (auto* actor = sead::DynamicCast<Actor>(_10(i).getProc(nullptr, nullptr)))
            actor->x_17(arg);
    }
}

sead::BitFlag16* PlayerArmors::sub_7100E2F61C() {
    return &_134;
}

}  // namespace ksys::act
