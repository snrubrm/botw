#include "KingSystem/Sound/sndSound.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/XLink/xlinkXLink.h"
#include <xlink2/xlink2UserInstanceSLink.h>
#include "KingSystem/Sound/sndBgmMgr.h"
#include <prim/seadScopedLock.h>
#include "KingSystem/Utils/InitTimeInfo.h"

namespace {
// Set up by the TU's 52-byte static initialiser.
ksys::util::InitConstants sInitConstants;
ksys::util::InitTimeInfo sInitTimeInfo;
}  // namespace

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

// NON_MATCHING: the two _18 stores are merged after the branches (the original keeps one per branch).
void Unk_7102502410::Entry::sub_7101049778() {
    if (!mUserInstance || !mAssetInfoReader || (mAssetInfoReader->_18 & 1))
        return;
    const char* name = mUserInstance->getUserName();
    if (!name)
        return;
    auto* resource_mgr = SoundMgr::instance()->_60;
    if (!mAssetInfoReader->sub_7101057258(name, nullptr))
        return;
    if (mAssetInfoReader->_18 & 1) {
        mUserInstance->setAssetInfoReader(mAssetInfoReader);
        _18 = 2;
    } else {
        resource_mgr->sub_7101059354(mAssetInfoReader);
        mAssetInfoReader = nullptr;
        _18 = 0;
    }
}

bool Unk_7102502410::Entry::sub_7101049824() {
    if (!mUserInstance)
        return false;
    const char* name = mUserInstance->getUserName();
    if (!name || _18 != 0)
        return false;
    auto* resource_mgr = SoundMgr::instance()->_60;
    mAssetInfoReader = new (resource_mgr->mHeap, 8) Unk_7102502950;
    if (resource_mgr->loadBars(name, mAssetInfoReader, resource_mgr->mHeap, false, false, nullptr)) {
        _18 = 1;
        return true;
    }
    resource_mgr->sub_7101059354(mAssetInfoReader);
    mAssetInfoReader = nullptr;
    return false;
}

// NON_MATCHING: the two loop offsets are kept in swapped registers.
void Unk_7102502410::sub_7101049AF8(const sead::Buffer<const char*>& names, Unk_710105E3D0Arg* defs,
                                    sead::Heap* heap) {
    if (mEntries.isBufferReady())
        return;
    mEntries.tryAllocBuffer(names.size(), heap);
    for (s32 i = 0; i < names.size(); ++i) {
        if (!names[i])
            continue;
        Entry& entry = mEntries[i];
        entry.mUserInstance = sub_710105E3D0(names[i], heap, nullptr, nullptr, defs);
        if (entry.mUserInstance)
            entry.mUserInstance->sleep();
    }
}

// NON_MATCHING: the found entry is null-checked again before the lock (the original goes straight on).
Unk_7102502410::Entry* Unk_7102502410::sub_7101049CEC(const sead::SafeString& name) {
    if (name.isEmpty() || !mEntries.isBufferReady())
        return nullptr;
    Entry* found = nullptr;
    for (s32 i = 0; i < mEntries.size(); ++i) {
        Entry& entry = mEntries[i];
        if (entry.mUserInstance && name == entry.mUserInstance->getUserName()) {
            found = &entry;
            break;
        }
    }
    if (!found)
        return nullptr;

    auto lock = sead::makeScopedLock(found->mCS);
    if (found->mRefCount == 0) {
        if (found->mUserInstance)
            found->mUserInstance->setIsActive(true);
        found->sub_7101049824();
    }
    ++found->mRefCount;
    return found;
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

void Unk_7102502430::sub_710104A098(Unk_7102502410* owner, const sead::SafeString& name) {
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

void Unk_7102502430::sub_710104A1B8() {
    if (!_10.isEmpty() && !mHandle.isActive()) {
        sub_710104A108();
        if (mOwner && !_98) {
            _98 = mOwner->sub_7101049CEC(_10);
            if (_98)
                _68 = 1;
        }
        _10.clear();
    }
    if (_68 && _98 && _98->_18 == 2) {
        if (!mName.isEmpty()) {
            if (auto* user_instance = _98->mUserInstance) {
                m4(user_instance);
                mHandle = user_instance->searchAndEmit(mName.cstr());
                m5(user_instance, &mHandle);
            }
        }
        _68 = 0;
    }
}

void Unk_7102502430::sub_710104A308(const sead::SafeString& name) {
    mHandle.fadeIfLoopSound();
    _10.clear();
    _68 = 0;
    if (_98) {
        const char* user_name = _98->mUserInstance ? _98->mUserInstance->getUserName() : nullptr;
        if (name == user_name) {
            if (_98->_18 != 2) {
                _68 = 1;
                return;
            }
            if (_98 && !mName.isEmpty()) {
                if (auto* user_instance = _98->mUserInstance) {
                    m4(user_instance);
                    mHandle = user_instance->searchAndEmit(mName.cstr());
                    m5(user_instance, &mHandle);
                }
            }
            return;
        }
    }
    _10 = name;
}

void Unk_7102502430::sub_710104A5E8() {
    if (!_98 || _98->_18 != 2)
        return;
    mHandle.fadeIfLoopSound();
    _10.clear();
    _68 = 0;
    if (_98 && !mName.isEmpty()) {
        if (auto* user_instance = _98->mUserInstance) {
            m4(user_instance);
            mHandle = user_instance->searchAndEmit(mName.cstr());
            m5(user_instance, &mHandle);
        }
    }
}

void Unk_7102502430::sub_710104A76C(s32 frame) {
    mHandle.fade(frame);
    _10.clear();
    _68 = 0;
}

bool Unk_7102502430::sub_710104A2E8() const {
    return _98 && _98->_18 == 2;
}

bool Unk_7102502430::sub_710104A858() const {
    if (mHandle.isActive())
        return true;
    if (!_10.isEmpty())
        return true;
    return _68 != 0;
}

bool Unk_7102502430::sub_710104A8AC() const {
    if (_98)
        return false;
    return _10.isEmpty();
}

xlink2::UserInstanceSLink* Unk_7102502430::getUserInstance() const {
    if (_98)
        return _98->mUserInstance;
    return nullptr;
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
