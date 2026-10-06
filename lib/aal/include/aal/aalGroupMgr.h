#pragma once

#include <prim/seadSafeString.h>

namespace aal {

class Group;
class GroupFolder;

/// Owns the sound group tree and finds groups by name.
class GroupMgr {
public:
    /// Finds a group (a SoundGroup or a GroupFolder) by name; nullptr if there is none.
    Group* findGroup(const sead::SafeString& name) const;
    /// Same as findGroup, but only returns the group if it is a GroupFolder.
    GroupFolder* findGroupFolder(const sead::SafeString& name) const;
    /// 0x7100b8148c: the name of the placeholder group (a child that is inserted after is not moved).
    static const sead::SafeString& getDummyGroupName();
};

}  // namespace aal
