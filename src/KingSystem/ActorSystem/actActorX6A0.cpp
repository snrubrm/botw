#include "KingSystem/ActorSystem/actActorX6A0.h"
#include "KingSystem/Physics/System/physRayCastForRequest.h"

namespace ksys::act {

ActorX6A0::ActorX6A0() {
    // 2026-10-07: these assignments follow the original VFRValue constructor call.
    _74 = 23.0f;
    _50.value = 23.0f;
    _50.prev_value = 23.0f;
    _44 = sead::Vector3f::ez;
    _40 = 0;
    _79 = 0;
    _6c = 0.0f;
    _70 = 0.0f;
    _5c = {0.0f, 0.0f, 0.0f};
    _7a = true;
    _7b = false;
}

ActorX6A0::~ActorX6A0() {
    sub_71010F21E0();
}

void ActorX6A0::sub_71010F21E0() {
    if (_38) {
        _38->release();
        _38 = nullptr;
    }
}

void ActorX6A0::sub_71010F21C4() {
    _79 = 0;
    _10._24 = false;
    _7a = true;
    _5c = {0.0f, 0.0f, 0.0f};
}

void* ActorX6A0::sub_71010F2848() {
    return &_40;
}

}  // namespace ksys::act
