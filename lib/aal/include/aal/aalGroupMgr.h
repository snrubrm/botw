#pragma once

#include <container/seadBuffer.h>
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

/// An entry of the sorted table of the groups of the GroupMgr.
struct GroupHashEntry {
    bool operator<(const GroupHashEntry& rhs) const { return hash < rhs.hash; }

    u32 hash;
    Group* group;
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
    /// Same as findGroup, but only returns the group if it is a SoundGroup (nullptr for an empty name).
    SoundGroup* findSoundGroup(const sead::SafeString& name) const;
    /// The default sound group if there is no sound group with that name.
    SoundGroup* findSoundGroupOrDefault(const sead::SafeString& name) const;
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
    /// 0x7100b81168: (re)creates the table of the groups sorted by name hash.
    void createGroupHashTable(sead::Heap* heap);
    /// 0x7100b80d38 (declared only): sorts the groups by the depth in the tree.
    void sortGroupsBreadthFirst_();
    void createDefaultGroup_(sead::Heap* heap);

    bool mInitialized = false;
    bool _9 = false;
    /// The root of the group tree.
    Group* mRootGroup = nullptr;
    SoundGroup* mDefaultSoundGroup = nullptr;
    sead::OffsetList<Group> mGroups;
    IGroupFactory* mGroupFactory;
    GroupFactory mDefaultGroupFactory;
    /// The groups sorted by the CRC32 hash of their name (empty if it was not created).
    sead::Buffer<GroupHashEntry> mGroupHashTable;
    SoundParam mDefaultSoundParam;
    u8 _98[8];
    void* _a0 = nullptr;
    s32 _a8 = 0;
};
static_assert(sizeof(GroupMgr) == 0xb0, "aal::GroupMgr size mismatch");

}  // namespace aal
