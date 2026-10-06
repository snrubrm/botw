#include "aal/aalGroupMgr.h"
#include <basis/seadNew.h>
#include <codec/seadHashCRC32.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "aal/aalGroup.h"
#include "aal/aalGroupLimiter.h"
#include "aal/aalArbiter.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

namespace {
const sead::SafeString sDummyGroupName = "@aalDummy";
const sead::SafeString sDefaultGroupName = "Default";
}  // namespace

// 0x7100bb652c
IGroupFactory::~IGroupFactory() = default;

// 0x7100bb6530 (D0)
GroupFactory::~GroupFactory() = default;

// 0x7100bb64a4
SoundGroup* GroupFactory::createSoundGroup(const sead::SafeString&, sead::Heap* heap) {
    return new (heap) SoundGroup;
}

// 0x7100bb64dc
GroupFolder* GroupFactory::createGroupFolder(const sead::SafeString&, sead::Heap* heap) {
    return new (heap) GroupFolder;
}

// 0x7100bb6514
void GroupFactory::destroyGroup(Group* group) {
    if (group)
        delete group;
}

// 0x7100b804b0
GroupMgr::GroupMgr() : mGroupFactory(&mDefaultGroupFactory) {}

// 0x7100b80520 (D1) / 0x7100b80574 (D0)
GroupMgr::~GroupMgr() {
    if (mInitialized) {
        destroyGroupAll_();
        mGroupHashTable.freeBuffer();
        mInitialized = false;
    }
}

// 0x7100b8071c
void GroupMgr::destroyGroupAll_() {
    if (Arbiter* arbiter = SystemAccessor::getArbiter()) {
        arbiter->detachGroupFromSoundSourceAll();
        arbiter->stopAllSound();
    }
    for (Group& group : mGroups.robustRange()) {
        mGroups.erase(&group);
        mGroupFactory->destroyGroup(&group);
    }
    mGroups.clear();
    mRootGroup = nullptr;
    mDefaultSoundGroup = nullptr;
}

// 0x7100b80910
void GroupMgr::createDefaultGroup_(sead::Heap* heap) {
    if (_9 || mDefaultSoundGroup)
        return;

    if (sDefaultGroupName.getStringTop()[0] != sead::SafeString::cNullChar) {
        if (SoundGroup* group = mGroupFactory->createSoundGroup(sDefaultGroupName, heap)) {
            group->initialize(sDefaultGroupName, heap);
            mDefaultSoundGroup = group;
            if (mRootGroup) {
                mRootGroup->pushBackChild_(group);
                mGroups.pushBack(mDefaultSoundGroup);
                sortGroupsBreadthFirst_();
            }
            return;
        }
    }
    mDefaultSoundGroup = nullptr;
}

// 0x7100b805c0
void GroupMgr::initialize(sead::Heap*, IGroupFactory* factory) {
    if (mInitialized)
        return;
    mGroups.initOffset(Group::getGroupListNodeOffset());
    mGroups.clear();
    mGroupFactory = factory == nullptr ? &mDefaultGroupFactory : factory;
    mInitialized = true;
}

// 0x7100b80ca0
GroupFolder* GroupMgr::findGroupFolder(const sead::SafeString& name) const {
    if (!mInitialized)
        return nullptr;
    Group* group = findGroup(name);
    if (!group)
        return nullptr;
    return sead::DynamicCast<GroupFolder>(group);
}

// 0x7100b80e24
Group* GroupMgr::findGroup(const sead::SafeString& name) const {
    if (!mInitialized)
        return nullptr;

    if (mGroupHashTable.isBufferReady()) {
        const u32 hash = sead::HashCRC32::calcStringHash(name.cstr());
        s32 low = 0;
        s32 high = mGroupHashTable.size();
        while (true) {
            const s32 mid = (low + high) / 2;
            const GroupHashEntry& entry = mGroupHashTable[mid];
            if (entry.hash == hash)
                return entry.group;
            if (entry.hash < hash) {
                if (low == mid)
                    return nullptr;
                low = mid;
            } else {
                if (high == mid)
                    return nullptr;
                high = mid;
            }
        }
    }

    for (Group& group : mGroups) {
        if (group.getObjName().isEqual(name))
            return &group;
    }
    return nullptr;
}

// NON_MATCHING: the original keeps a second null check of the group after the type test.
// 0x7100b80ff8
SoundGroup* GroupMgr::findSoundGroup(const sead::SafeString& name) const {
    if (!mInitialized || name.getStringTop()[0] == sead::SafeString::cNullChar)
        return nullptr;
    Group* group = findGroup(name);
    if (!group)
        return nullptr;
    SoundGroup* sound_group = sead::DynamicCast<SoundGroup>(group);
    return sound_group;
}

// NON_MATCHING: see findSoundGroup.
// 0x7100b810b0
SoundGroup* GroupMgr::findSoundGroupOrDefault(const sead::SafeString& name) const {
    if (mInitialized && name.getStringTop()[0] != sead::SafeString::cNullChar) {
        if (SoundGroup* group = sead::DynamicCast<SoundGroup>(findGroup(name)))
            return group;
    }
    return mDefaultSoundGroup;
}

// 0x7100b8148c
const sead::SafeString& GroupMgr::getDummyGroupName() {
    return sDummyGroupName;
}

// 0x7100b80c60
void GroupMgr::resetDuckingVolume() {
    for (Group& group : mGroups)
        group.mDuckingVolume = 1.0f;
}

// 0x7100b81498
void GroupMgr::pushDescendantsAndSelfGroupArray(sead::PtrArray<Group>* groups, Group* group) {
    if (groups && group) {
        groups->pushBack(group);
        group->pushDescendantGroupArray(groups);
    }
}

// 0x7100b814d8
bool GroupMgr::isUnderAncestorOrSelf(const Group* group, const Group* ancestor) {
    if (group == ancestor)
        return true;
    if (group && ancestor) {
        for (const Group* parent = group->getParent(); parent; parent = parent->getParent()) {
            if (parent == ancestor)
                return true;
        }
    }
    return false;
}

// 0x7100b81528
void GroupMgr::updateActiveSoundLimiterStructure() {
    for (Group& group : mGroups)
        group.mLimiter->updateUpperActiveSoundLimitList();
}

// 0x7100b81584
void GroupMgr::updateRequestSoundLimiterStructure() {
    for (Group& group : mGroups)
        group.mLimiter->updateUpperRequestSoundLimitList();
}

// 0x7100b815e0
void GroupMgr::updateRequestIntervalLimiterStructure() {
    for (Group& group : mGroups)
        group.mLimiter->updateUsingRequestIntervalLimiter();
}

}  // namespace aal
