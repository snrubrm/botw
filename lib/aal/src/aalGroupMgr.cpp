#include "aal/aalGroupMgr.h"
#include <basis/seadNew.h>
#include "aal/aalGroup.h"
#include "aal/aalGroupLimiter.h"
#include "aal/aalArbiter.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

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
        if (mGroupHashTable) {
            delete[] static_cast<u8*>(mGroupHashTable);
            mGroupHashTable = nullptr;
            mGroupHashTableSize = 0;
        }
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
    _10 = nullptr;
    _18 = nullptr;
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
