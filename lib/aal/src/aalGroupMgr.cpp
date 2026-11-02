#include "aal/aalGroupMgr.h"
#include <basis/seadNew.h>
#include <codec/seadHashCRC32.h>
#include <prim/seadRuntimeTypeInfo.h>
#include "aal/aalGroup.h"
#include "aal/aalActiveSoundLimiter.h"
#include "aal/aalRequestIntervalLimiter.h"
#include "aal/aalRequestSoundLimiter.h"
#include "aal/aalSoundSource.h"
#include "aal/aalGroupLimiter.h"
#include "aal/aalArbiter.h"
#include "aal/aalSystemAccessor.h"

namespace aal {

// 0x7100b81af4
void GroupMgr::setupWithResourceDefaultSoundParam_(Group* group, const GroupReader::GroupParam::DefaultSoundParam& param) {
    SoundParam sound_param(group->mDefaultParam);
    sound_param.setVolume(param.volume);
    sound_param.setPitch(param.pitch);
    sound_param.setLfe(param.lfe);
    sound_param.setLpf(param.lpf);
    sound_param.setBiquadFilter(param.biquadType, param.biquadValue);
    sound_param.setAngleIdx(param.angleIdx);
    sound_param.setSpread(param.spread);
    sound_param.setDeviceVolume(DeviceType::TV, param.tvVolume);
    sound_param.setBusVolume(BusType::Main, param.busVolume[0]);
    sound_param.setBusVolume(BusType::AuxA, param.busVolume[1]);
    sound_param.setBusVolume(BusType::AuxB, param.busVolume[2]);
    sound_param.setBusVolume(BusType::AuxC, param.busVolume[3]);
    group->setDefaultParam(sound_param);
}

// NON_MATCHING: stack stores for limiter settings are scheduled differently.
// 0x7100b81bdc
void GroupMgr::setupWithResourceGroupLimiterParam_(Group* group, const GroupReader::GroupParam::GroupLimiterParam& param, sead::Heap* heap) {
    GroupLimiter* limiter = group->mLimiter;
    if (!limiter)
        return;

    ActiveSoundLimiter* active = LimiterUtil::createActiveSoundLimiter(static_cast<ActiveSoundLimiterType>(param.activeType), heap);
    if (active) {
        auto* sources = new (heap) sead::OffsetList<SoundSource>;
        if (sources) {
            sources->initOffset(offsetof(SoundSource, mGroupNode));
            group->mLimiter->setActiveSoundLimiter(active, sources);
            ActiveSoundLimiter::Settings settings{param.activeLimit, {u8(param.activeFlag != 0), 0}};
            active->setup(settings);
        } else {
            delete active;
        }
    }
    limiter->_58 = param.activeType;
    if (param.requestEnabled) {
        auto* request = new (heap) RequestSoundLimiter;
        if (request) {
            auto* sources = new (heap) sead::OffsetList<SoundSource>;
            if (sources) {
                sources->initOffset(offsetof(SoundSource, mGroupNode));
                group->mLimiter->setRequestSoundLimiter(request, sources);
                RequestSoundLimiter::Settings settings;
                settings.mLimitNum = param.requestLimit;
                settings.mField1 = param.requestField1;
                settings.mField2 = param.requestField2;
                settings.mField3 = param.requestField3;
                settings.mField4 = param.requestField4;
                settings.mFlag = false;
                request->setup(settings);
            } else {
                delete request;
            }
        }
    }
    limiter->_5c = param.requestEnabled != 0;
    if (param.intervalEnabled) {
        auto* interval = new (heap) RequestIntervalLimiter;
        if (interval) {
            group->mLimiter->setRequestIntervalLimiter(interval);
            RequestIntervalLimiter::Settings settings{param.interval};
            interval->setup(settings);
        }
    }
    limiter->_5d = param.intervalEnabled != 0;
}

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

// NON_MATCHING: the original handles the first element before the loop (without the index clamp), and does not
// share one heap sort with the other table (the sort of sead::Buffer is expanded here too, differently scheduled).
// 0x7100b81168
void GroupMgr::createGroupHashTable(sead::Heap* heap) {
    mGroupHashTable.freeBuffer();
    const s32 num = mGroups.size();
    if (num < 1)
        return;
    if (!mGroupHashTable.tryAllocBuffer(num, heap, 8))
        return;
    s32 i = 0;
    for (Group& group : mGroups) {
        GroupHashEntry& entry = mGroupHashTable[i];
        entry.hash = sead::HashCRC32::calcStringHash(group.getObjName().cstr());
        entry.group = &group;
        ++i;
    }
    mGroupHashTable.heapSort(0, num - 1);
}

// 0x7100b80d38
void GroupMgr::sortGroupsBreadthFirst_() {
    if (!mInitialized)
        return;
    mGroups.insertionSort([](const Group* lhs, const Group* rhs) {
        if (!lhs || !rhs)
            return false;
        return lhs->calcTreeDepth() > rhs->calcTreeDepth();
    });
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
