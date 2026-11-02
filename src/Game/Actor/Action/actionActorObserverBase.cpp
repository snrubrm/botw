#include "Game/Actor/Action/actionActorObserverBase.h"
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actAreaActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actAiActionBase.h"
#include "KingSystem/Utils/Thread/Message.h"

ActorObserverBase::ActorObserverBase(ksys::act::ai::ActionBase* owner) : mOwner(owner) {}

void ActorObserverBase::sub_7100E28168() {
    enter();
    _10 = false;
}

void ActorObserverBase::enter() {
    ksys::act::ActorLinkConstDataAccess accessor;
    if (getAreaCol(&accessor, -1) < 0 && mOwner) {
        auto* actor = mOwner->getActor();
        if (actor) {
            sead::FixedSafeString<64> name;
            sead::FixedSafeString<64> unique_name;
            ksys::act::getPlacementNameAndUniqueName(mOwner->getActor(), &name, &unique_name);
            const auto& mtx = actor->getMtx();
            sead::FormatFixedSafeString<128> message("このアクタの座標(%f,%f,%f)", mtx(0, 3),
                                                     mtx(1, 3), mtx(2, 3));
        }
    }
}

void ActorObserverBase::sub_7100E282AC() {
    calc();
    m2();
    calc2();
    m5();
}

// NON_MATCHING: stack layout (the MessageType temporary sits above the accessor in the original) and
// register allocation of the accessor address / payload loop counter.
void ActorObserverBase::calc() {
    if (_10 && !_11)
        return;

    if (!mOwner)
        return;

    ksys::act::ActorLinkConstDataAccess accessor;
    for (int idx = getAreaCol(&accessor, -1); idx >= 0; idx = getAreaCol(&accessor, idx)) {
        if (!accessor.hasProc())
            continue;

        auto* payloads = m6();
        if (!payloads)
            continue;

        const auto* id = accessor.getMessageTransceiverId();
        for (auto& payload : *payloads)
            mOwner->sendMessage(*id, ksys::MessageType(0x4800001), &payload);
    }
    _10 = true;
    _11 = false;
}

bool ActorObserverBase::sub_7100E289C0(const ksys::Message* message) {
    if (!message)
        return true;

    if (message->getType() == 0x4800002) {
        _11 = true;
        return true;
    }
    return false;
}

bool ActorObserverBase::m3(const CollisionIterator& it) {
    return false;
}

bool ActorObserverBase::m4(const ContactIterator& it) {
    return false;
}

bool ActorObserverBase::m7(const CollisionIterator& it) {
    return true;
}

bool ActorObserverBase::m8(const ContactIterator& it) {
    return true;
}

// NON_MATCHING: clang keeps a widened iterator and lowers the loop exits through a dispatcher.
int ActorObserverBase::getAreaCol(ksys::act::ActorLinkConstDataAccess* accessor, int idx) {
    if (!accessor || !mOwner || !mOwner->getActor())
        return -1;
    auto* object = mOwner->getActor()->getMapObject();
    if (!object || !object->getLinkData())
        return -1;
    auto* links = object->getLinkData();
    const s32 count = links->mLinksOther.links.size();
    // The native index increment wraps in 32 bits; the wider loop avoids signed overflow.
    const s32 start = idx < 0 ? 0 : s32(u32(idx) + 1);
    for (s64 i = start; i < count; ++i) {
        auto& link = links->mLinksOther.links[s32(i)];
        if (link.type != ksys::map::MapLinkDefType::AreaCol || !link.other_obj)
            continue;
        link.other_obj->getActorWithAccessor(*accessor);
        if (sead::IsDerivedFrom<ksys::act::Area>(accessor->getProc()))
            return s32(i);
        accessor->acquire(nullptr);
    }
    return -1;
}
// NON_MATCHING: virtual callback loads move after iterator construction; stack/register allocation differs.
bool ActorObserverBase::m13(const CollisionIterator& it, int area_idx) {
    ksys::act::acc::AreaActor area;
    for (int idx = getAreaCol(&area, -1); idx >= 0 && idx < area_idx;
         idx = getAreaCol(&area, idx)) {
        if (!area.hasProc() || area.isDeletedOrDeleting())
            continue;
        if (auto* info = area.getField848()) {
            bool found;
            {
                CollisionIterator begin(info);
                CollisionIterator end;
                found = m9(it, begin, end);
            }
            if (found)
                return true;
        }
        if (auto* info = area.getField850()) {
            auto begin = info->begin();
            auto end = info->end();
            if (m10(it, begin, end))
                return true;
        }
    }
    return false;
}

// NON_MATCHING: virtual callback loads move after iterator construction; stack/register allocation differs.
bool ActorObserverBase::m14(const ContactIterator& it, int area_idx) {
    ksys::act::acc::AreaActor area;
    for (int idx = getAreaCol(&area, -1); idx >= 0 && idx < area_idx;
         idx = getAreaCol(&area, idx)) {
        if (!area.hasProc() || area.isDeletedOrDeleting())
            continue;
        if (auto* info = area.getField848()) {
            bool found;
            {
                CollisionIterator begin(info);
                CollisionIterator end;
                found = m12(it, begin, end);
            }
            if (found)
                return true;
        }
        if (auto* info = area.getField850()) {
            auto begin = info->begin();
            auto end = info->end();
            if (m11(it, begin, end))
                return true;
        }
    }
    return false;
}
// NON_MATCHING: clang uses different exit flags and branches while releasing the iterators.
void ActorObserverBase::calc2() {
    ksys::act::acc::AreaActor area;
    for (int idx = getAreaCol(&area, -1); idx >= 0; idx = getAreaCol(&area, idx)) {
        if (!area.hasProc() || area.isDeletedOrDeleting())
            continue;

        auto* collision = area.getField848();
        if (collision) {
            CollisionIterator begin(collision);
            CollisionIterator current(begin);
            for (; *current; ++current) {
                if (m7(current) && !m9(current, begin, current) && !m13(current, idx) && m3(current))
                    return;
            }
        }

        auto* contacts = area.getField850();
        if (!contacts)
            continue;
        auto begin = contacts->begin();
        if (collision) {
            CollisionIterator collision_begin(collision);
            CollisionIterator collision_end;
            auto current = begin;
            auto end = contacts->end();
            for (; current != end; ++current) {
                if (m8(current) && !m12(current, collision_begin, collision_end) &&
                    !m11(current, begin, current) && !m14(current, idx) && m4(current))
                    return;
            }
        } else {
            auto current = begin;
            auto end = contacts->end();
            for (; current != end; ++current) {
                if (m8(current) && !m11(current, begin, current) && !m14(current, idx) && m4(current))
                    return;
            }
        }
    }
}
