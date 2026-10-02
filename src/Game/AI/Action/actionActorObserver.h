#pragma once

#include "Game/AI/Action/actionActorObserverBase.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class ActorLinkConstDataAccess;
}  // namespace ksys::act

namespace ksys::phys {
class RigidBody;
}  // namespace ksys::phys

// vtable 0x71024e52e8 (TU 0x7100e27b08-0x7100e2814c)
class ActorObserver : public ActorObserverBase {
public:
    explicit ActorObserver(ksys::act::ai::ActionBase* owner);

    bool m3(const CollisionIterator& it) override;
    bool m4(const ContactIterator& it) override;
    bool m7(const CollisionIterator& it) override;
    bool m8(const ContactIterator& it) override;
    bool m9(const CollisionIterator& it, const CollisionIterator& begin,
            const CollisionIterator& end) override;
    bool m10(const CollisionIterator& it, const ContactIterator& begin,
             const ContactIterator& end) override;
    bool m11(const ContactIterator& it, const ContactIterator& begin,
             const ContactIterator& end) override;
    bool m12(const ContactIterator& it, const CollisionIterator& begin,
             const CollisionIterator& end) override;
    // Whether the observed actor `accessor` is accepted.
    virtual bool m15(const ksys::act::ActorConstDataAccess& accessor) { return false; }
    // Whether `body` is to be ignored.
    virtual bool m16(ksys::phys::RigidBody* body);

    // Whether one of the bodies in [begin, end) belongs to the actor of `accessor`.
    bool sub_7100E27D7C(const ksys::act::ActorLinkConstDataAccess& accessor,
                        const CollisionIterator& begin, const CollisionIterator& end);
    bool sub_7100E27F0C(const ksys::act::ActorLinkConstDataAccess& accessor,
                        const ContactIterator& begin, const ContactIterator& end);
};
KSYS_CHECK_SIZE_NX150(ActorObserver, 0x18);
