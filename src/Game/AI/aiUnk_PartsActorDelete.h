#pragma once

#include <prim/seadSafeString.h>
#include "Game/Actor/actUnk_7100d3cd74.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

// inline-only in the original; name is a guess: the same sequence is inlined four times into LynelRoot::~LynelRoot and
// MoveRemainsElectric::~MoveRemainsElectric (and once per WeakPoint key elsewhere): deletes the actor linked under `name` in the
// actor's parts list and removes the entry.
inline void deleteActorParts(uking::act::Unk_7100d3cd74* parts, const sead::SafeString& name) {
    auto& link = parts->getActorPartsActor(name);
    if (link.hasProc()) {
        ksys::act::ActorConstDataAccess accessor;
        ksys::act::acquireActor(&link, &accessor);
        accessor.deleteLater(ksys::act::BaseProc::DeleteReason::_0);
    }
    parts->sub_7100D3CFEC(name);
}
