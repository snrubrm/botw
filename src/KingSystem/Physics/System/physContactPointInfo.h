#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadSafeArray.h>
#include <cstddef>
#include <math/seadVector.h>
#include <prim/seadBitFlag.h>
#include <prim/seadDelegate.h>
#include <prim/seadNamable.h>
#include <prim/seadSafeString.h>
#include <thread/seadAtomic.h>
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Physics/physLayerMaskBuilder.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

struct ContactPoint;

class ContactPointInfoBase : public sead::INamable {
public:
    using Points = sead::Buffer<ContactPoint*>;

    // FIXME: parameter names
    ContactPointInfoBase(const sead::SafeString& name, int a, int b, int c)
        : sead::INamable(name), _2c(a), _30(b), _34(c) {}
    virtual ~ContactPointInfoBase() = default;
    virtual void freePoints() = 0;

    u32 get30() const { return _30; }
    void set30(u32 value) { _30 = value; }

    // TODO: rename
    bool testContactPointDistance(float distance) const { return get30() == 0 || distance <= 0; }

    u32 get34() const { return _34; }
    void set34(u32 value) { _34 = value; }

    bool isLayerSubscribed(ContactLayer layer) const {
        const auto type = getContactLayerType(layer);
        return mSubscribedLayers[int(type)].isOnBit(getContactLayerBaseRelativeValue(layer));
    }

    // Inline (BeamMove::m33 clears EntityPlayer / EntityNPC this way); written like
    // CollisionInfoBase::disableLayer.
    void unsubscribeLayer(ContactLayer layer) {
        mSubscribedLayers[int(getContactLayerType(layer))].resetBit(
            getContactLayerBaseRelativeValue(layer));
    }

    // Inline-only in the original (AmiiboMgr::init sets five layers this way; the name is a guess):
    // adds the layer to the subscribed mask and clears it from mask 2.
    void subscribeLayer(ContactLayer layer) {
        const u32 mask = makeContactLayerMask(layer);
        const auto type = getContactLayerType(layer);
        mSubscribedLayers[int(type)].set(mask);
        mLayerMask2[int(type)].reset(mask);
    }

    // TODO: rename
    bool isLayerInMask2(ContactLayer layer) const {
        const auto type = getContactLayerType(layer);
        return mLayerMask2[int(type)].isOnBit(getContactLayerBaseRelativeValue(layer));
    }

    // Inline-only in the original (StopTimerObserver::enter_ stores -1 over both words with one 64-bit
    // store; the name is a guess).
    void setAllLayerMask2() {
        for (int i = 0; i < NumContactLayerTypes; ++i)
            mLayerMask2[i].setDirect(0xffffffff);
    }

    // Inline-only in the original (EventDisableContactIdle::init_ stores -1 over both subscribed words;
    // the name is a guess).
    void subscribeAllLayers() {
        for (int i = 0; i < NumContactLayerTypes; ++i)
            mSubscribedLayers[i].makeAllOne();
    }

    void setLayerMasks(const LayerMaskBuilder& builder) {
        for (int i = 0; i < NumContactLayerTypes; ++i) {
            mSubscribedLayers[i] = builder.getMasks()[i].layers;
            mLayerMask2[i] = builder.getMasks()[i].layers2;
        }
    }

public:
    // For internal use by the physics system.

    sead::Atomic<int>& getNumContactPoints() { return mNumContactPoints; }

    bool isLinked() const { return mListNode.isLinked(); }

    static constexpr size_t getListNodeOffset() {
        return offsetof(ContactPointInfoBase, mListNode);
    }

protected:
    friend class ContactMgr;

    sead::Atomic<int> mNumContactPoints;
    sead::SafeArray<sead::BitFlag32, 2> mSubscribedLayers;
    // TODO: rename
    sead::SafeArray<sead::BitFlag32, 2> mLayerMask2;
    u32 _2c{};
    u32 _30{};
    u32 _34{};
    sead::ListNode mListNode{};
};

class ContactPointInfo : public ContactPointInfoBase {
public:
    enum class ShouldDisableContact : bool {
        Yes = true,
        No = false,
    };

    /// Contact data passed to ContactCallback. The vector and collision-mask pointers are borrowed
    /// for the duration of the callback; copy their values if they are needed afterwards.
    struct Event {
        /// The other rigid body in the contact, rather than the body receiving the callback.
        RigidBody* body;
        const sead::Vector3f* position;
        const sead::Vector3f* separating_normal;
        const RigidBody::CollisionMasks* collision_masks;
    };

    class Iterator {
    public:
        enum class IsEnd : bool { Yes = true };

        enum class Point {
            BodyA,
            BodyB,
            Midpoint,
        };

        Iterator(const Points& points, int count);
        Iterator(const Points& points, int count, IsEnd is_end);

        // Skips invalid points like the constructor (inlined in FixableLiftable::calc_: the index is
        // stored after each increment and points with flag bit 0 at +0x68 are skipped).
        Iterator& operator++() {
            while (++mIdx != mPointsNum) {
                if (!mPoints[mIdx]->flags.isOn(ContactPoint::Flag::Invalid))
                    break;
            }
            return *this;
        }

        virtual void getPointPosition(sead::Vector3f* out, Point point) const;
        virtual sead::Vector3f getPointPosition(Point point) const;

        // Inline-only in the original (emptiness test in sub_7100738E70, where
        // the begin iterator is compared with its own point count); the name is a guess.
        bool isEnd() const { return mIdx == mPointsNum; }

        const ContactPoint* getPoint() const { return mPoints[mIdx]; }
        const ContactPoint* operator*() const { return getPoint(); }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.mIdx == rhs.mIdx;
        }
        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) {
            return !operator==(lhs, rhs);
        }

    private:
        int mIdx = 0;
        const ContactPoint* const* mPoints = nullptr;
        int mPointsNum = 0;
        const ContactPoint* const* mPointsStart = nullptr;
    };

    /// The output parameter starts at ShouldDisableContact::No. Set it to Yes to request that the
    /// physical contact be disabled, independently of the return value.
    ///
    /// When called by ContactMgr::registerContactPoint, return false to skip recording the point,
    /// or true to allow recording (subject to available storage). ContactListener's manifold
    /// callback ignores the return value and only checks the ShouldDisableContact output.
    using ContactCallback = sead::IDelegate2R<ShouldDisableContact*, const Event&, bool>;

    static ContactPointInfo* make(sead::Heap* heap, int num, const sead::SafeString& name, int a,
                                  int b, int c);
    static void free(ContactPointInfo* instance);

    ContactPointInfo(const sead::SafeString& name, int a, int b, int c);
    ~ContactPointInfo() override;
    void freePoints() override;
    virtual void allocPoints(sead::Heap* heap, int num);

    ContactCallback* getContactCallback() const { return mContactCallback; }
    void setContactCallback(ContactCallback* cb) { mContactCallback = cb; }

    auto begin() const { return Iterator(mPoints, mNumContactPoints); }
    auto end() const { return Iterator(mPoints, mNumContactPoints, Iterator::IsEnd::Yes); }

protected:
    friend class ContactMgr;

    Points mPoints;
    ContactCallback* mContactCallback{};
};
KSYS_CHECK_SIZE_NX150(ContactPointInfo, 0x60);

}  // namespace ksys::phys
