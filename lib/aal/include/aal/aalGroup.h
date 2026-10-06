#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <container/seadTreeNode.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>

#include "aal/aalNamedObj.h"

namespace aal {

class GroupDucker;
class GroupLimiter;
class SimpleTimedFader;
class SoundSource;

/// A node of the sound group tree (see GroupMgr): either a SoundGroup (a leaf that owns playing sounds)
/// or a GroupFolder (which forwards the operations to its children).
/// TODO: incomplete. Only the virtual functions up to `silence` are declared in vtable order (the other virtuals
/// below are in an unverified order); the second base at +0x50 (it holds the tree node) and most members are not
/// modeled yet.
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

    // The vtable positions of the following virtuals are not verified.
    virtual bool isSoundGroup() const = 0;
    virtual bool isGroupFolder() const = 0;
    virtual bool isOnDucking() const;
    virtual const sead::SafeString& getDuckingSourceName() const;
    virtual void invalidateORNode();
    virtual void calcActiveSoundLimit();
    virtual void calcRequestSoundLimit();

    /// The number of ancestors of the group.
    s32 calcTreeDepth() const;
    Group* getParent() const;
    void setDuckingVolumeFloor(f32 floor);

protected:
    virtual bool pushFrontChild_(Group* child) = 0;
    virtual bool pushBackChild_(Group* child) = 0;
    virtual bool insertBeforeChild_(Group* child, Group* before) = 0;
    virtual bool insertAfterChild_(Group* child, Group* after) = 0;
    virtual void removeChild_(Group* child) = 0;
    virtual void calcSilence_();

    void calcInit_();
    void calcDucker_();
    void aggregateDuckingVolumeFromDucker_(f32 volume);
    void calcDuckingVolume_();

    u8 _18[0x58 - 0x18];
    sead::TTreeNode<Group*> mTreeNode;
    u8 _80[0x90 - 0x80];
    GroupDucker* mDucker;
    u8 _98[0x130 - 0x98];
    /// The ducking volume: the product / minimum (by mDuckingMode) of the ducking volumes of the ducker and the
    /// parent, clamped to at least mDuckingVolumeFloor.
    f32 mDuckingVolume;
    f32 mDuckingVolumeFloor;
    /// 0: the volumes are multiplied, 1: the minimum is taken.
    u32 mDuckingMode;
    u8 _13c[0x148 - 0x13c];
    GroupLimiter* mLimiter;
    s32 mDuckingCount;
    s32 _154;
    void* _158;
    u32 _160;
    u8 _164[0x178 - 0x164];
};
static_assert(sizeof(Group) == 0x178, "aal::Group size mismatch");

/// A leaf of the sound group tree: owns the playing sound sources of the group.
class SoundGroup : public Group {
public:
    void allowEmit(bool allow) override;
    void allowEmit(sead::BitFlag8 flags, bool allow) override;
    void silence(bool silence, f32 fade_time) override;
    bool isSoundGroup() const override;
    bool isGroupFolder() const override;
    void calcActiveSoundLimit() override;

    void setReleaseTime(f32 release_time);

protected:
    bool pushFrontChild_(Group* child) override;
    bool pushBackChild_(Group* child) override;
    bool insertBeforeChild_(Group* child, Group* before) override;
    bool insertAfterChild_(Group* child, Group* after) override;
    void removeChild_(Group* child) override;
    void calcSilence_() override;

    f32 mReleaseTime;
    /// One bit per emit permission (all set by default).
    sead::BitFlag8 mEmitFlags;
    SimpleTimedFader* mSilenceFader;
    sead::OffsetList<SoundSource> mPlayingSoundSources;
};

/// A group that only contains other groups.
class GroupFolder : public Group {
    SEAD_RTTI_OVERRIDE(GroupFolder, Group)
};

}  // namespace aal
