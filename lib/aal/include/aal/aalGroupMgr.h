#pragma once

#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <prim/seadSafeString.h>

namespace aal {

class Group;
class GroupFolder;

/// Owns the sound group tree and finds groups by name.
/// TODO: incomplete (the object has a vtable at +0 and an initialized flag at +8).
class GroupMgr {
public:
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
    u8 _0[0x20];
    sead::OffsetList<Group> mGroups;
};

}  // namespace aal
