#include "KingSystem/ActorSystem/actActorBindSet.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>
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
// NON_MATCHING: instruction scheduling only: the bone index of `mKeyA` is loaded before the branch on flag 4 (the
// original loads it in each branch, after the virtual call target)
bool ActorBindEntry::sub_7101255A0C(BaseProc* proc) {
    if (!(mFlags & 1))
        return false;
    auto* actor = sead::DynamicCast<Actor>(mLink.getProc(nullptr, proc));
    const bool valid = isValid(proc);
    if (!actor || !valid)
        return false;
    sead::Matrix34f local;
    sead::Vector3f scale = actor->mScale;
    if (mFlags & 2) {
        local = actor->mMtx;
    } else {
        auto* unit = actor->mModel->getUnits().unsafeAt(mKeyA.getKey().model_unit_index)->mModelUnit;
        if (mFlags & 4) {
            const sead::Vector3f ones = sead::Vector3f::ones;
            const f32 inv_x = ones.x / scale.x;
            const f32 inv_y = ones.y / scale.y;
            const f32 inv_z = ones.z / scale.z;
            unit->getBoneWorldMatrix(&local, mKeyA.getKey().bone_index);
            local.scaleBases(inv_x, inv_y, inv_z);
        } else {
            unit->getBoneLocalMatrix(&local, &scale, mKeyA.getKey().bone_index);
        }
    }
    local.setMul(local, mMtx);
    auto* child = static_cast<Actor*>(proc);
    if (!(mFlags & 4)) {
        child->mModel->setBoneLocalMatrix(mKeyB.getKey(), local, scale);
    } else {
        child->mMtx = local;
        child->nullsub_4648();
        child->mScale = scale;
        child->mModel->setMatrix(local);
        child->mModel->setScale(scale);
    }
    return true;
}

bool ActorBindEntry::sub_7101255D50(BaseProc* proc) {
    if (mFlags & 1)
        return false;
    auto* actor = sead::DynamicCast<Actor>(mLink.getProc(nullptr, proc));
    const bool valid = isValid(proc);
    if (!actor || !valid)
        return false;
    sead::Matrix34f local;
    const sead::Vector3f scale = actor->mScale;
    if (mFlags & 2) {
        local = actor->mMtx;
    } else {
        const sead::Vector3f ones = sead::Vector3f::ones;
        const f32 inv_x = ones.x / scale.x;
        const f32 inv_y = ones.y / scale.y;
        const f32 inv_z = ones.z / scale.z;
        auto* unit = actor->mModel->getUnits().unsafeAt(mKeyA.getKey().model_unit_index)->mModelUnit;
        unit->getBoneWorldMatrix(&local, mKeyA.getKey().bone_index);
        local.scaleBases(inv_x, inv_y, inv_z);
    }
    local.setMul(local, mMtx);
    auto* child = static_cast<Actor*>(proc);
    if (!(mFlags & 4)) {
        child->mModel->setBoneWorldMatrix(mKeyB.getKey(), local);
    } else {
        child->mMtx = local;
        child->nullsub_4648();
        child->mScale = scale;
        child->mModel->setMatrix(local);
        child->mModel->setScale(scale);
    }
    return true;
}

ActorBindSet::ActorBindSet(int count, ActorBindEntry* entries) {
    mCount = (count > 0 && entries) ? count : 0;
    mEntries = entries ? entries : nullptr;
}

// NON_MATCHING: the original stores the ActorBind vtable with a post-increment (`str x8, [x19], #8`)
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

// NON_MATCHING: register allocation (the original keeps the cursor index in the 64-bit register of its argument and
// the limit / flag on the stack)
ActorBindSet::Cursor ActorBindSet::bindAll(Actor* actor, Actor* other, Cursor cursor, bool flag) {
    const s32 num_units = other->getModel()->getUnits().size();
    const u32 limit = mCount;
    for (s32 i = 0; i < num_units; ++i) {
        auto* unit = other->getModel()->getUnits().unsafeAt(i)->mModelUnit;
        const s32 num_bones = unit->getBoneNum();
        for (s32 j = 0; j < num_bones; ++j) {
            auto* entry = &cursor.entries[cursor.index];
            if (entry->set(actor, unit->getBoneName(j), other, unit->getBoneName(j), &sead::Matrix34f::ident,
                           flag)) {
                ++cursor.index;
                if (u32(cursor.index) == limit)
                    return cursor;
            } else {
                cursor.entries[cursor.index].reset();
            }
        }
    }
    return cursor;
}

}  // namespace ksys::act
