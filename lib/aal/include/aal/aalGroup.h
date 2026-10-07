#pragma once

#include <basis/seadTypes.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <thread/seadCriticalSection.h>
#include <prim/seadScopedLock.h>
#include <container/seadTreeNode.h>
#include <hostio/seadHostIONode.h>
#include <prim/seadBitFlag.h>
#include <prim/seadRuntimeTypeInfo.h>

#include "aal/aalNamedObj.h"
#include "aal/aalSoundParam.h"

namespace sead {
class Heap;
}

namespace aal {

class GroupDucker;
class GroupLimiter;
class SimpleTimedFader;
class SoundSource;

/// The interface of a group that can be a source of ducking (the second base of Group, at +0x50).
class IDuckingSource {
public:
    virtual ~IDuckingSource() = default;
    virtual bool isOnDucking() const = 0;
    virtual void invalidateORNode() = 0;
    virtual const sead::SafeString& getDuckingSourceName() const = 0;
};

/// A node of the sound group tree (see GroupMgr): either a SoundGroup (a leaf that owns playing sounds)
/// or a GroupFolder (which forwards the operations to its children).
/// TODO: incomplete. The virtual functions are declared in vtable order (verified against the vtable) and most
/// members are not modeled yet.
class Group : public FixedNamedObj<32>,
              public IDuckingSource,
              public sead::TTreeNode<Group*>,
              public sead::hostio::Node {
    SEAD_RTTI_BASE(Group)
    friend class GroupFolder;
    friend class GroupMgr;
    friend class GroupLimiter;
    friend class GroupDucker;

public:
    Group();
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
    virtual void calcNumSounds();
    virtual bool isSoundGroup() const = 0;
    virtual bool isGroupFolder() const = 0;
    virtual s32 getStartWaitSoundNum() const = 0;
    // These three are also the virtuals of the second base (a thunk of each is in its vtable).
    bool isOnDucking() const override;
    const sead::SafeString& getDuckingSourceName() const override;
    void invalidateORNode() override;
    virtual void initialize(const sead::SafeString& name, sead::Heap* heap);
    virtual void finalize();

    /// The number of ancestors of the group.
    /// 0x7100b7fc30 (declared only): pushes the descendants of the group into the array.
    void pushDescendantGroupArray(sead::PtrArray<Group>* groups);
    s32 calcTreeDepth() const;
    Group* getParent() const;
    GroupLimiter* getLimiter() const { return mLimiter; }
    void setDuckingVolumeFloor(f32 floor);
    void setDefaultParam(const SoundParam& param);

protected:
    // The vtable order of the following virtuals is verified from the vtable (0x7100b7f... 0x24c3cd0).
    virtual bool pushFrontChild_(Group* child) = 0;
    virtual bool pushBackChild_(Group* child) = 0;
    virtual bool insertBeforeChild_(Group* child, Group* before) = 0;
    virtual bool insertAfterChild_(Group* child, Group* after) = 0;
    virtual void removeChild_(Group* child) = 0;
    virtual void calcSilence_();

    /// 0x7100b7fc6c: pushes the group and its descendants.
    void pushDescendantGroupArrayChild_(sead::PtrArray<Group>* groups);
    void calcInit_();
    void calcParam_();
    void calcDucker_();
    void aggregateDuckingVolumeFromDucker_(f32 volume);
    void calcDuckingVolume_();

public:
    static constexpr s32 getGroupListNodeOffset() { return 0x168; }

    const SoundParam* getAggregatedParam() const { return mAggregatedParam; }
    f32 getDuckingVolume() const { return mDuckingVolume; }

protected:
    sead::TTreeNode<Group*>& treeNode() { return *this; }
    const sead::TTreeNode<Group*>& treeNode() const { return *this; }

    bool mInitialized;
    GroupDucker* mDucker;
    void* _98;
    SoundParam mDefaultParam;
    SoundParam mCurrentParam;
    /// The parameters of the group (the volume is the aggregation of the group's own volume, the ducking...).
    SoundParam* mAggregatedParam;
    void* mParamBuffer;
    /// The ducking volume: the product / minimum (by mDuckingMode) of the ducking volumes of the ducker and the
    /// parent, clamped to at least mDuckingVolumeFloor.
    f32 mDuckingVolume;
    f32 mDuckingVolumeFloor;
    /// 0: the volumes are multiplied, 1: the minimum is taken.
    u32 mDuckingMode;
    u32 _13c;
    /// Whether the default parameters differ from the initial parameters.
    bool mHasDefaultParam;
    GroupLimiter* mLimiter;
    /// Sound counters of the group (calcNumSounds adds them to the parent's counters): the first one is also the
    /// ducking count (isOnDucking), and mNumSounds is the sum of the first, third and fourth.
    s32 mDuckingCount;
    s32 _154;
    s32 _158;
    s32 _15c;
    s32 mNumSounds;
    u8 _164[4];
    /// The node in the group list of the GroupMgr.
    sead::ListNode mGroupListNode;
};
static_assert(sizeof(Group) == 0x178, "aal::Group size mismatch");

/// A leaf of the sound group tree: owns the playing sound sources of the group.
class SoundGroup : public Group {
    SEAD_RTTI_OVERRIDE(SoundGroup, Group)
public:
    SoundGroup();
    ~SoundGroup() override;

    void stopAllSound(f32 fade_time) override;
    void pauseAllSound(bool pause, f32 fade_time) override;
    void pauseAllSound(sead::BitFlag8 flags, bool pause, f32 fade_time) override;

    void initialize(const sead::SafeString& name, sead::Heap* heap) override;
    void finalize() override;

    void allowEmit(bool allow) override;
    void allowEmit(sead::BitFlag8 flags, bool allow) override;
    void silence(bool silence, f32 fade_time) override;
    bool isSoundGroup() const override;
    bool isGroupFolder() const override;
    void calcActiveSoundLimit() override;
    s32 getStartWaitSoundNum() const override;

    void setReleaseTime(f32 release_time);
    /// Registers the sound source in the group (and the limiters); false if it is limited.
    bool addSound(SoundSource* sound_source);
    void addToPlayingSoundSources(SoundSource* sound_source);
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
    void calcNumSounds() override;

    f32 mReleaseTime;
    /// One bit per emit permission (all set by default).
    sead::BitFlag8 mEmitFlags;
    SimpleTimedFader* mSilenceFader;
    sead::OffsetList<SoundSource> mPlayingSoundSources;
    sead::CriticalSection mCS;
};

/// A group that only contains other groups: forwards the operations to its children.
class GroupFolder : public Group {
    SEAD_RTTI_OVERRIDE(GroupFolder, Group)
public:
    GroupFolder();
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
