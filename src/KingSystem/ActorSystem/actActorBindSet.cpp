#include "KingSystem/ActorSystem/actActorBindSet.h"
#include "KingSystem/ActorSystem/actActor.h"

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

}  // namespace ksys::act
