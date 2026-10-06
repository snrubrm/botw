#pragma once

#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadSafeString.h>
#include "aal/aalSoundParam.h"

namespace sead {
class Heap;
}

namespace aal {

class Group;
class GroupFolder;
class SoundGroup;

/// Creates and destroys the groups of the GroupMgr.
class IGroupFactory {
public:
    virtual ~IGroupFactory();
    virtual SoundGroup* createSoundGroup(const sead::SafeString& name, sead::Heap* heap) = 0;
    virtual GroupFolder* createGroupFolder(const sead::SafeString& name, sead::Heap* heap) = 0;
    virtual void destroyGroup(Group* group) = 0;
};

/// The default group factory.
class GroupFactory : public IGroupFactory {
public:
    ~GroupFactory() override;
    SoundGroup* createSoundGroup(const sead::SafeString& name, sead::Heap* heap) override;
    GroupFolder* createGroupFolder(const sead::SafeString& name, sead::Heap* heap) override;
    void destroyGroup(Group* group) override;
};

/// Owns the sound group tree and finds groups by name.
/// TODO: incomplete.
class GroupMgr : public sead::hostio::Node {
public:
    GroupMgr();
    virtual ~GroupMgr();

    /// Uses the default group factory if `factory` is null.
    void initialize(sead::Heap* heap, IGroupFactory* factory);

    /// Finds a group (a SoundGroup or a GroupFolder) by name; nullptr if there is none.
    Group* findGroup(const sead::SafeString& name) const;
    /// Same as findGroup, but only returns the group if it is a GroupFolder.
    GroupFolder* findGroupFolder(const sead::SafeString& name) const;
    /// 0x7100b8148c: the name of the placeholder group (a child that is inserted after is not moved).
    static const sead::SafeString& getDummyGroupName();

    /// Sets the ducking volume of all groups back to 1.
    void resetDuckingVolume();
    void updateActiveSoundLimiterStructure();
    void updateRequestSoundLimiterStructure();
    void updateRequestIntervalLimiterStructure();

    /// Adds the group and all its descendants to the array (nothing is added if the array is full).
    static void pushDescendantsAndSelfGroupArray(sead::PtrArray<Group>* groups, Group* group);
    /// Whether `ancestor` is the group itself or one of its ancestors.
    static bool isUnderAncestorOrSelf(const Group* group, const Group* ancestor);

private:
    void destroyGroupAll_();

    bool mInitialized = false;
    bool _9 = false;
    void* _10 = nullptr;
    void* _18 = nullptr;
    sead::OffsetList<Group> mGroups;
    IGroupFactory* mGroupFactory;
    GroupFactory mDefaultGroupFactory;
    s32 mGroupHashTableSize = 0;
    void* mGroupHashTable = nullptr;
    SoundParam mDefaultSoundParam;
    u8 _98[8];
    void* _a0 = nullptr;
    s32 _a8 = 0;
};
static_assert(sizeof(GroupMgr) == 0xb0, "aal::GroupMgr size mismatch");

}  // namespace aal
