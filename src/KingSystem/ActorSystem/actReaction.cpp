#include "KingSystem/ActorSystem/actReaction.h"

namespace ksys::act {
Reaction* Reaction::sInstance;

void Reaction::Unk1::sub_7100EC66FC(Actor* actor) {
    _110 = 2;
}

f32 Reaction::Unk1::sub_7100EC877C() const {
    return 0.7f;
}

s32 Reaction::Unk1::sub_7100EC87A4() const {
    return 7;
}

s8 Reaction::Unk1::sub_7100EC89BC() const {
    return 5;
}
}  // namespace ksys::act
