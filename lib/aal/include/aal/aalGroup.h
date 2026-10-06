#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <container/seadTreeNode.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>

#include "aal/aalNamedObj.h"

namespace sead {
class Heap;
}

namespace aal {

class GroupDucker;
class GroupLimiter;
class SimpleTimedFader;
class SoundSource;

/// A node of the sound group tree (see GroupMgr): either a SoundGroup (a leaf that owns playing sounds)
/// or a GroupFolder (which forwards the operations to its children).
/// TODO: incomplete. The virtual functions are declared in vtable order (verified against the vtable); the
/// primary base is really a FixedNamedObj<32>, the second base at +0x50 (it holds the tree node) and most
/// members are not modeled yet.
class Group : public NamedObj {
    SEAD_RTTI_BASE(Group)
    friend class GroupFolder;

public:
    ~Group() override;

    /// Stops all the sounds of the group (and of its descendants) with the given fade out time (negative: the
    /// default release time).
    virtual void stopAllSound(f32 fade_time) = 0;
    virtual void pauseAllSound(bool pause, f32 fade_time) = 0;
    virtual void pauseAllSound(sead::BitFlag8 flags, bool pause, f32 fade_time) = 0;
    /// Allows or forbids emitting new sounds in the group.
    virtual void allowEmit(bool allow) = 0;
    virtual void allowEmit(sead::BitFlag8 flags, bool allow) = 0;
    virtual void silence(bool silence, f32 fade_time) = 0;

    virtual void calcActiveSoundLimit();
    virtual void calcRequestSoundLimit();
    virtual s32 calcNumSounds();
    virtual bool isSoundGroup() const = 0;
    virtual bool isGroupFolder() const = 0;
    virtual s32 getStartWaitSoundNum() const = 0;
    // These three are also the virtuals of the second base (a thunk of each is in its vtable).
    virtual bool isOnDucking() const;
    virtual const sead::SafeString& getDuckingSourceName() const;
    virtual void invalidateORNode();
    virtual void initialize(const sead::SafeString& name, sead::Heap* heap);
    virtual void finalize();

    /// The number of ancestors of the group.
    s32 calcTreeDepth() const;
    Group* getParent() const;
    void setDuckingVolumeFloor(f32 floor);

protected:
    // The vtable order of the following virtuals is verified from the vtable (0x7100b7f... 0x24c3cd0).
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
    s32 getStartWaitSoundNum() const override;

    void setReleaseTime(f32 release_time);
    f32 getReleaseTime() const { return mReleaseTime; }
    /// 0x7100b826f8 (declared only): removes the sound source from the playing sounds of the group.
    void removeSound(SoundSource* sound_source);

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

/// A group that only contains other groups: forwards the operations to its children.
class GroupFolder : public Group {
    SEAD_RTTI_OVERRIDE(GroupFolder, Group)
public:
    ~GroupFolder() override = default;

    void stopAllSound(f32 fade_time) override;
    void pauseAllSound(bool pause, f32 fade_time) override;
    void pauseAllSound(sead::BitFlag8 flags, bool pause, f32 fade_time) override;
    void allowEmit(bool allow) override;
    void allowEmit(sead::BitFlag8 flags, bool allow) override;
    void silence(bool silence, f32 fade_time) override;
    bool isSoundGroup() const override;
    bool isGroupFolder() const override;
    s32 getStartWaitSoundNum() const override;

protected:
    bool pushFrontChild_(Group* child) override;
    bool pushBackChild_(Group* child) override;
    bool insertBeforeChild_(Group* child, Group* before) override;
    bool insertAfterChild_(Group* child, Group* after) override;
    void removeChild_(Group* child) override;
};

}  // namespace aal
