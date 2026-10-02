#include "Game/AI/Action/actionActorObserver.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"

ActorObserver::ActorObserver(ksys::act::ai::ActionBase* owner) : ActorObserverBase(owner) {}

bool ActorObserver::m3(const CollisionIterator& it) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::getCollidedActorMaybe(&accessor, (*it)->bodies[1]);
    return m15(accessor);
}

bool ActorObserver::m4(const ContactIterator& it) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::getCollidedActorMaybe(&accessor, (*it)->body_b);
    return m15(accessor);
}

bool ActorObserver::m7(const CollisionIterator& it) {
    if (m16((*it)->bodies[1]))
        return false;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::getCollidedActorMaybe(&accessor, (*it)->bodies[1]);
    return accessor.hasProc();
}

bool ActorObserver::m8(const ContactIterator& it) {
    if (m16((*it)->body_b))
        return false;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::getCollidedActorMaybe(&accessor, (*it)->body_b);
    return accessor.hasProc();
}

bool ActorObserver::m9(const CollisionIterator& it, const CollisionIterator& begin,
                       const CollisionIterator& end) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::getCollidedActorMaybe(&accessor, (*it)->bodies[1]);
    return sub_7100E27D7C(accessor, begin, end);
}

bool ActorObserver::sub_7100E27D7C(const ksys::act::ActorLinkConstDataAccess& accessor,
                                   const CollisionIterator& begin, const CollisionIterator& end) {
    for (auto it = begin; it != end; ++it) {
        if (m16((*it)->bodies[1]))
            continue;

        {
            ksys::act::ActorConstDataAccess body_accessor;
            ksys::act::getCollidedActorMaybe(&body_accessor, (*it)->bodies[1]);
            if (!body_accessor.hasProc())
                continue;
        }

        ksys::act::ActorConstDataAccess body_accessor;
        ksys::act::getCollidedActorMaybe(&body_accessor, (*it)->bodies[1]);
        if (accessor.getProc() == body_accessor.getProc())
            return true;
    }
    return false;
}

bool ActorObserver::m10(const CollisionIterator& it, const ContactIterator& begin,
                        const ContactIterator& end) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::getCollidedActorMaybe(&accessor, (*it)->bodies[1]);
    return sub_7100E27F0C(accessor, begin, end);
}

bool ActorObserver::sub_7100E27F0C(const ksys::act::ActorLinkConstDataAccess& accessor,
                                   const ContactIterator& begin, const ContactIterator& end) {
    for (auto it = begin; it != end; ++it) {
        if (m16((*it)->body_b))
            continue;

        {
            ksys::act::ActorConstDataAccess body_accessor;
            ksys::act::getCollidedActorMaybe(&body_accessor, (*it)->body_b);
            if (!body_accessor.hasProc())
                continue;
        }

        ksys::act::ActorConstDataAccess body_accessor;
        ksys::act::getCollidedActorMaybe(&body_accessor, (*it)->body_b);
        if (accessor.getProc() == body_accessor.getProc())
            return true;
    }
    return false;
}

bool ActorObserver::m11(const ContactIterator& it, const ContactIterator& begin,
                        const ContactIterator& end) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::getCollidedActorMaybe(&accessor, (*it)->body_b);
    return sub_7100E27F0C(accessor, begin, end);
}

bool ActorObserver::m12(const ContactIterator& it, const CollisionIterator& begin,
                        const CollisionIterator& end) {
    ksys::act::ActorConstDataAccess accessor;
    ksys::act::getCollidedActorMaybe(&accessor, (*it)->body_b);
    return sub_7100E27D7C(accessor, begin, end);
}

bool ActorObserver::m16(ksys::phys::RigidBody* body) {
    if (!body)
        return false;
    return ksys::act::sub_7100EE9A14(body);
}
