#include "KingSystem/ActorSystem/actActorUniqueNameSearch.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace ksys::act {

ActorUniqueNameSearch::ActorUniqueNameSearch(const sead::SafeString& unique_name)
    : mUniqueName(unique_name) {}

// NON_MATCHING: the parser result is tested before the returned pointer instead of after it.
void ActorUniqueNameSearch::sub_7100EDCC10(BaseProc* proc) {
    if (!proc)
        return;
    auto* actor = sead::DynamicCast<Actor>(proc);
    if (!actor)
        return;
    const char* unique_name = nullptr;
    if (!actor->getMapObjIter().tryGetParamStringByKey(&unique_name, "UniqueName") || !unique_name)
        return;
    if (mUniqueName == unique_name)
        mLink.acquire(actor, false);
}

}  // namespace ksys::act
