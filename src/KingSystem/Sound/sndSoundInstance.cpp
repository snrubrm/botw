#include "KingSystem/Sound/sndMgr.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include <prim/seadScopedLock.h>

namespace ksys::snd {

Unk_SoundInstance::Unk_SoundInstance(s32 id) : _48c(id) {}

Unk_SoundInstance::~Unk_SoundInstance() = default;

bool Unk_SoundInstance::sub_710104ACB4() {
    if (!_490)
        return false;
    if (_440 >= 0.0f) {
        if (!_0.isEmpty())
            return true;
        return !_220.isEmpty();
    }
    return false;
}

void Unk_SoundInstance::sub_710104ABE8() {
    if (!_491) {
        _491 = true;
        _488 = 0;
    }
}

bool Unk_SoundInstance::sub_710104ADB8(int id) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (_220.isFull())
        return false;
    auto* entry = _220.emplaceBack(id);
    if (!entry)
        return false;
    if (auto* manager = SoundMgr::instance()->_a8)
        _494 = manager->sub_710104B7D0();
    return true;
}

// NON_MATCHING: actor ID and array-pointer loads use swapped registers in the non-map path.
f32 Unk_SoundInstance::sub_710104AC00(ksys::act::Actor* actor) {
    if (actor) {
        auto* object = actor->getMapObject();
        if (!object) {
            if (_490 && _440 >= 0.0f) {
                for (auto id : _220) {
                    if (id == actor->getId())
                        return 1.0f - _440;
                }
            }
        } else if (_490 && _440 >= 0.0f) {
            if ((!_0.isEmpty() || !_220.isEmpty()) && object->getHashId() != 0xffffffff) {
                for (auto id : _0) {
                    if (id == object->getHashId())
                        return 1.0f - _440;
                }
            }
        }
    }
    return -1.0f;
}

}  // namespace ksys::snd
