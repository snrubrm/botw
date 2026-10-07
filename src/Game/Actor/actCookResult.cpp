#include "Game/Actor/actCookResult.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include <basis/seadNew.h>

namespace uking::act {

CookResult::CookResult(const CreateArg& arg) : Item(arg) {
    _bb0.actor_name.copy(mName);
}

ksys::act::BaseProc* CookResult::construct(const CreateArg& arg, sead::Heap* heap) {
    return new (heap, std::nothrow) CookResult(arg);
}

// NON_MATCHING: the tail (life_recover through is_crit, 0x210-0x225) is a 21-byte
// word copy in the original (u64 at 0x210 and 0x218, unaligned u64 at 0x21d); scalar field
// stores do not reproduce it (verified with scratch probes). See the session log.
bool copyCookResultToCookItem(const ksys::act::ActorConstDataAccess& accessor, CookItem& result) {    ksys::act::Actor* actor = static_cast<ksys::act::Actor*>(accessor.getProc());
    if (!actor || !actor->checkDerivedRuntimeTypeInfo(ksys::act::Actor::getRuntimeTypeInfoStatic()))
        actor = nullptr;
    if (!sead::IsDerivedFrom<CookResult>(actor))
        return false;
    const CookItem& item = static_cast<CookResult*>(actor)->_bb0;
    result.actor_name = item.actor_name;
    result.ingredients = item.ingredients;
    result.life_recover = item.life_recover;
    result.effect_time = item.effect_time;
    result.sell_price = item.sell_price;
    result.effect_id = item.effect_id;
    result.vitality_boost = item.vitality_boost;
    result.is_crit = item.is_crit;
    return true;
}

}  // namespace uking::act
