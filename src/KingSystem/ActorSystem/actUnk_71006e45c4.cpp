#include "KingSystem/ActorSystem/actUnk_71006e45c4.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace ksys::act {

Unk_71006e45c4::Unk_71006e45c4() {
    mFlags |= 1;
}

bool Unk_71006e45c4::m4() {
    return mFlags & 1;
}

bool Unk_71006e45c4::m9() {
    if (mFlags & 0x100)
        return true;
    return mActor->getActorFlags2().isOn(Actor::ActorFlag2::_40);
}

bool Unk_71006e45c4::m15() {
    return mFlags >> 1 & 1;
}

bool Unk_71006e45c4::m16() {
    return mFlags >> 9 & 1;
}

}  // namespace ksys::act
