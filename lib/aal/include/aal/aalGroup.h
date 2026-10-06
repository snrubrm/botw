#pragma once

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>

#include "aal/aalNamedObj.h"

namespace aal {

/// A node of the sound group tree (see GroupMgr): either a SoundGroup (a leaf that owns playing sounds)
/// or a GroupFolder (which forwards the operations to its children).
/// TODO: incomplete. Only the virtual functions up to `silence` are declared (the vtable slots follow
/// the original); the other bases (the tree node, ...) and the members are not modeled yet.
class Group : public NamedObj {
    SEAD_RTTI_BASE(Group)
public:
    /// Stops all the sounds of the group (and of its descendants) with the given fade out time (negative: the
    /// default release time).
    virtual void stopAllSound(f32 fade_time) = 0;
    virtual void pauseAllSound(bool pause, f32 fade_time) = 0;
    virtual void pauseAllSound(sead::BitFlag8 flags, bool pause, f32 fade_time) = 0;
    /// Allows or forbids emitting new sounds in the group.
    virtual void allowEmit(bool allow) = 0;
    virtual void allowEmit(sead::BitFlag8 flags, bool allow) = 0;
    virtual void silence(bool silence, f32 fade_time) = 0;
};

/// A group that only contains other groups.
class GroupFolder : public Group {
    SEAD_RTTI_OVERRIDE(GroupFolder, Group)
};

}  // namespace aal
