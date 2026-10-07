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

bool Unk_SoundInstance::sub_710104ACF8(map::Object* object) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    if (!object || object->getHashId() == 0xffffffff || _0.isFull())
        return false;
    auto* entry = _0.emplaceBack(object->getHashId());
    if (!entry)
        return false;
    if (auto* manager = SoundMgr::instance()->_a8)
        _494 = manager->sub_710104B7D0();
    return true;
}

// NON_MATCHING: the actor ID and pool-pointer loads use swapped registers.
bool Unk_SoundInstance::sub_710104B1D8(act::Actor* actor) {
    if (!actor)
        return false;
    auto* object = actor->getMapObject();
    if (!object) {
        for (auto id : _220) {
            if (id == actor->getId())
                return true;
        }
    } else if (object->getHashId() != 0xffffffff) {
        for (auto id : _0) {
            if (id == object->getHashId())
                return true;
        }
    }
    return false;
}

// NON_MATCHING: the compiler merges empty-pool exits and returns map-path results directly.
bool Unk_SoundInstance::sub_710104AFC0(act::Actor* actor) {
    auto* object = actor->getMapObject();
    if (!object) {
        const u32 actor_id = actor->getId();
        mCS.lock();
        bool found = false;
        for (s32 i = 0; i < _220.size(); ++i) {
            if (*_220[i] == actor_id) {
                --_488;
                if (auto* manager = SoundMgr::instance()->_a8)
                    _494 = manager->sub_710104B7D0();
                found = true;
                break;
            }
        }
        mCS.unlock();
        return found;
    } else {
        const u32 hash_id = object->getHashId();
        if (hash_id == 0xffffffff)
            return false;
        mCS.lock();
        for (s32 i = 0; i < _0.size(); ++i) {
            if (*_0[i] == hash_id) {
                --_488;
                if (auto* manager = SoundMgr::instance()->_a8)
                    _494 = manager->sub_710104B7D0();
                mCS.unlock();
                return true;
            }
        }
        mCS.unlock();
    }
    return false;
}

bool Unk_SoundInstance::sub_710104AE6C(int id) {
    sead::ScopedLock<sead::CriticalSection> lock(&mCS);
    for (s32 i = 0; i < _220.size(); ++i) {
        if (*_220[i] == id) {
            _220.erase(i);
            --_488;
            if (auto* manager = SoundMgr::instance()->_a8)
                _494 = manager->sub_710104B7D0();
            return true;
        }
    }
    return false;
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
