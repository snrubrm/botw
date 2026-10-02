#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include "KingSystem/Physics/System/physCollisionInfo.h"
#include "KingSystem/Physics/System/physContactPointInfo.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {
class Message;
}  // namespace ksys

namespace ksys::act {
class ActorConstDataAccess;
class ActorLinkConstDataAccess;
namespace ai {
class ActionBase;
}  // namespace ai
}  // namespace ksys::act

// vtable 0x71024e5380
//
// Observer of the actors that are inside the areas linked to the owner action's actor through
// AreaCol map links (class names from the CSV; the classes have no RTTI). The functions live in
// TU 0x7100e2814c-0x7100e29070 (ActorObserver's own functions are in the TU before it). Embedded
// as the second base (at +0x20) of AreaTagAction (ActorObserver) and AreaFireObserveBase
// (Unk_71024e5408).
//
// The virtual functions are called for each body colliding with an area (CollisionInfo of the area
// actor) or each contact point of an area (ContactPointInfo); the "other" body of the pair is the
// one whose actor is observed.
class ActorObserverBase {
public:
    // Iterator over the colliding bodies of a CollisionInfo. It holds the info's lock while it
    // exists: constructing (or copying) an iterator locks the info, destroying it unlocks it.
    class CollisionIterator {
    public:
        CollisionIterator() = default;
        explicit CollisionIterator(ksys::phys::CollisionInfo* info)
            : mInfo(info), mBodies(info->getCollidingBodies().front()) {
            mInfo->lock();
        }
        CollisionIterator(const CollisionIterator& other)
            : mInfo(other.mInfo), mBodies(other.mBodies) {
            if (mInfo)
                mInfo->lock();
        }
        ~CollisionIterator() {
            if (mInfo)
                mInfo->unlock();
        }

        CollisionIterator& operator++() {
            mBodies = mInfo->getCollidingBodies().next(mBodies);
            return *this;
        }

        ksys::phys::CollidingBodies* operator*() const { return mBodies; }

        friend bool operator==(const CollisionIterator& lhs, const CollisionIterator& rhs) {
            return lhs.mBodies == rhs.mBodies;
        }
        friend bool operator!=(const CollisionIterator& lhs, const CollisionIterator& rhs) {
            return !operator==(lhs, rhs);
        }

    private:
        ksys::phys::CollisionInfo* mInfo = nullptr;
        ksys::phys::CollidingBodies* mBodies = nullptr;
    };

    using ContactIterator = ksys::phys::ContactPointInfo::Iterator;

    // User data of the message (type 0x4800001) that calc() sends to every observed actor for each
    // entry of the buffer returned by m6().
    struct Payload {
        u32 _0;
        bool _4;
    };

    explicit ActorObserverBase(ksys::act::ai::ActionBase* owner);
    virtual ~ActorObserverBase() {}

    virtual void m2() {}
    // m3/m4/m7/m8 are emitted after the TU's other functions in the original, like inline
    // functions emitted with the vtable (whose key function would then be m13). They are defined
    // out of line here so that the vtable is emitted while m13/m14 are not decompiled.
    virtual bool m3(const CollisionIterator& it);
    virtual bool m4(const ContactIterator& it);
    virtual void m5() {}
    virtual sead::Buffer<Payload>* m6() { return nullptr; }
    virtual bool m7(const CollisionIterator& it);
    virtual bool m8(const ContactIterator& it);
    virtual bool m9(const CollisionIterator& it, const CollisionIterator& begin,
                    const CollisionIterator& end) {
        return false;
    }
    virtual bool m10(const CollisionIterator& it, const ContactIterator& begin,
                     const ContactIterator& end) {
        return false;
    }
    virtual bool m11(const ContactIterator& it, const ContactIterator& begin,
                     const ContactIterator& end) {
        return false;
    }
    virtual bool m12(const ContactIterator& it, const CollisionIterator& begin,
                     const CollisionIterator& end) {
        return false;
    }
    // 0x7100e28a1c / 0x7100e28ba8 (declared only): need the area actor's CollisionInfo /
    // ContactPointInfo accessors (AreaActor TU, not decompiled yet).
    virtual bool m13(const CollisionIterator& it, int area_idx);
    virtual bool m14(const ContactIterator& it, int area_idx);

    // Called by the owner's enter_ / calc_ / handleMessage_.
    void sub_7100E28168();
    void sub_7100E282AC();
    bool sub_7100E289C0(const ksys::Message* message);

    void enter();
    void calc();
    // 0x7100e283ec (declared only): needs the AreaActor accessors (see m13).
    void calc2();
    // 0x7100e28878 (declared only): finds the next AreaCol link of the owner's actor after link
    // `idx` (-1: from the start) whose object is an Area actor (needs the Area class RTTI), acquires
    // the area into `accessor` and returns the link index (-1 if none).
    int getAreaCol(ksys::act::ActorConstDataAccess* accessor, int idx);

protected:
    ksys::act::ai::ActionBase* mOwner;
    bool _10 = false;
    bool _11 = false;
};
