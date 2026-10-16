#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include <xlink2/xlink2UserInstanceSLink.h>
#include <prim/seadScopedLock.h>

namespace ksys::snd {

Unk_7102502410::Unk_7102502410() = default;

Unk_7102502410::~Unk_7102502410() {
    sub_710104993C();
}

void Unk_7102502410::sub_710104993C() {
    if (!mEntries.isBufferReady())
        return;
    for (s32 i = 0; i < mEntries.size(); ++i)
        mEntries[i].finalize();
    mEntries.freeBuffer();
}

void Unk_7102502410::sub_7101049C60() {
    for (s32 i = 0; i < mEntries.size(); ++i) {
        Entry& entry = mEntries[i];
        entry.sub_7101049778();
        if (entry.mRefCount > 0) {
            if (auto* user_instance = entry.mUserInstance) {
                user_instance->preCalc();
                user_instance->postCalc();
            }
        }
    }
}

Unk_7102502430::Unk_7102502430() = default;

Unk_7102502430::~Unk_7102502430() {
    sub_710104A0D4();
}

void Unk_7102502430::sub_710104A098(void* owner, const sead::SafeString& name) {
    if (mIsSet)
        return;
    mOwner = owner;
    mName = name;
    mIsSet = true;
}

void Unk_7102502430::sub_710104A0D4() {
    if (!mIsSet)
        return;
    sub_710104A108();
    mOwner = nullptr;
    mIsSet = false;
}

void Unk_7102502430::sub_710104A108() {
    if (!mOwner)
        return;
    Unk_7102502410::Entry* entry = _98;
    if (!entry)
        return;
    {
        auto lock = sead::makeScopedLock(entry->mCS);
        if (--entry->mRefCount == 0) {
            if (entry->mAssetInfoReader) {
                SoundMgr::instance()->_60->sub_7101059354(entry->mAssetInfoReader);
                if (entry->mUserInstance)
                    entry->mUserInstance->setAssetInfoReader(nullptr);
                entry->mAssetInfoReader = nullptr;
                entry->_18 = 0;
            }
            if (entry->mUserInstance)
                entry->mUserInstance->sleep();
        }
    }
    _98 = nullptr;
}

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

bool Unk_SoundInstance::sub_710104B10C(act::Actor* actor) {
    if (!actor || actor->getXLink()->_bc >= u32(_494))
        return false;
    auto* object = actor->getMapObject();
    if (!object) {
        const u32 actor_id = actor->getId();
        for (auto id : _220) {
            if (id == actor_id) {
                auto lock = sead::makeScopedLock(mCS);
                ++_488;
                return true;
            }
        }
    } else if (object->getHashId() != 0xffffffff) {
        for (auto id : _0) {
            if (id == object->getHashId()) {
                auto lock = sead::makeScopedLock(mCS);
                ++_488;
                return true;
            }
        }
    }
    return false;
}

bool Unk_SoundInstance::sub_710104B1D8(act::Actor* actor) {
    if (!actor)
        return false;
    auto* object = actor->getMapObject();
    if (!object) {
        const u32 actor_id = actor->getId();
        for (auto id : _220) {
            if (id == actor_id)
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

f32 Unk_SoundInstance::sub_710104AC00(ksys::act::Actor* actor) {
    if (actor) {
        auto* object = actor->getMapObject();
        if (!object) {
            if (_490 && _440 >= 0.0f) {
                const u32 actor_id = actor->getId();
                for (auto id : _220) {
                    if (id == actor_id)
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
