#include "KingSystem/ActorSystem/actActorBindSet.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/System/physInstanceSet.h"

namespace ksys::act {

ActorBindEntry::ActorBindEntry() = default;

// NON_MATCHING: the original has a separate `return true` block for the flag 4 shortcut
bool ActorBindEntry::isValid(BaseProc* other_proc) const {
    auto* actor = sead::DynamicCast<Actor>(mLink.getProc(nullptr, other_proc));
    if (!actor || !actor->getModel())
        return false;
    if (!(mFlags & 2) && !mKeyA.isValid())
        return false;
    if (mFlags & 4)
        return true;
    if (mKeyB.isValid())
        return true;
    return false;
}

// NON_MATCHING: register assignment of the arguments / the flag update is a branch in the original
bool ActorBindEntry::set(Actor* actor, const sead::SafeString& bone_a, Actor* other,
                         const sead::SafeString& bone_b, const sead::Matrix34f* mtx, bool flag) {
    mLink.reset();
    mKeyA.remove();
    mKeyB.remove();
    mFlags = 0;
    if (bone_a.isEmpty()) {
        mFlags = 2;
    } else if (!mKeyA.search(actor->getModel(), bone_a)) {
        mLink.reset();
        mKeyA.remove();
        mKeyB.remove();
        return false;
    }
    if (bone_b.isEmpty()) {
        mFlags |= 4;
    } else if (!mKeyB.search(other->getModel(), bone_b)) {
        mLink.reset();
        mKeyA.remove();
        mKeyB.remove();
        return false;
    }
    mLink.acquire(actor, false);
    mMtx = *mtx;
    if (flag)
        mFlags |= 1;
    else
        mFlags &= 0xfe;
    return true;
}

void ActorBindEntry::reset() {
    mLink.reset();
    mKeyA.remove();
    mKeyB.remove();
}

// NON_MATCHING: the original stores the count / pointer before the vtable
ActorBindSet::ActorBindSet(int count, ActorBindEntry* entries) {
    mCount = (count > 0 && entries) ? count : 0;
    mEntries = entries ? entries : nullptr;
}

ActorBindSet::~ActorBindSet() {
    delete[] mEntries;
    mEntries = nullptr;
    mCount = 0;
}

// NON_MATCHING: the original counts down a 64-bit counter and loads the pointer after the count test
void ActorBindSet::resetAll() {
    for (u32 i = 0; i < mCount; ++i)
        mEntries[i].reset();
}

// NON_MATCHING: register allocation / loop shape of the entry walk
bool ActorBindSet::m6(BaseProc* proc) {
    Actor* previous = nullptr;
    auto* entry = mEntries;
    for (u32 n = mCount; n != 0; --n, ++entry) {
        auto* actor = sead::DynamicCast<Actor>(entry->mLink.getProc(nullptr, proc));
        const bool same = actor == previous;
        previous = actor;
        if (same || !actor)
            continue;
        if (actor->getPhysics() && actor->getPhysics()->getFlags().isOn(phys::InstanceSet::Flag::_8))
            return true;
    }
    return false;
}

// NON_MATCHING: register allocation / loop shape of the entry walk
bool ActorBindSet::m7(BaseProc* proc) {
    Actor* previous = nullptr;
    auto* entry = mEntries;
    for (u32 n = mCount; n != 0; --n, ++entry) {
        auto* actor = sead::DynamicCast<Actor>(entry->mLink.getProc(nullptr, proc));
        const bool same = actor == previous;
        previous = actor;
        if (same || !actor)
            continue;
        if (actor->getPhysics() &&
            actor->getPhysics()->getFlags().isOn(phys::InstanceSet::Flag::_10))
            return true;
    }
    return false;
}

// NON_MATCHING: register allocation / loop shape of the entry walk
bool ActorBindSet::m8(BaseProc* proc) {
    Actor* previous = nullptr;
    auto* entry = mEntries;
    for (u32 n = mCount; n != 0; --n, ++entry) {
        auto* actor = sead::DynamicCast<Actor>(entry->mLink.getProc(nullptr, proc));
        const bool same = actor == previous;
        previous = actor;
        if (same || !actor)
            continue;
        if (actor->getPhysics() &&
            actor->getPhysics()->getFlags().isOn(phys::InstanceSet::Flag::DisableDraw))
            return true;
    }
    return false;
}

// NON_MATCHING: register allocation / loop shape of the entry walk
void ActorBindSet::m9(BaseProc* proc) {
    auto* own_physics = static_cast<Actor*>(proc)->getPhysics();
    if (!own_physics)
        return;
    auto* entry = mEntries;
    for (u32 n = mCount; n != 0; --n, ++entry) {
        auto* actor = sead::DynamicCast<Actor>(entry->mLink.getProc(nullptr, proc));
        if (actor && actor->getPhysics()) {
            own_physics->sub_7100FB9BAC(actor->getPhysics());
            return;
        }
    }
}

}  // namespace ksys::act
