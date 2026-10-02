#include "Game/Actor/actRideable.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::act {

Unk_7100e8b2b8::Unk_7100e8b2b8() = default;

Unk_7100e8b2b8::~Unk_7100e8b2b8() = default;

ksys::act::Actor* Unk_7100e8b2b8::sub_7100E8B644() {
    return sead::DynamicCast<ksys::act::Actor>(_20.getProc(nullptr, nullptr));
}

ksys::act::Actor* Unk_7100e8b2b8::sub_7100E8B6E0() {
    return sead::DynamicCast<ksys::act::Actor>(_20.getProc(nullptr, mActor));
}

}  // namespace uking::act
