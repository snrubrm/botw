#include "Game/AI/aiUnk_710001A69C.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"

// NON_MATCHING: the first cast (BaseProc -> Actor) compiles to a csel here, the original branches (the null
// check jumps to its own `mov x20, xzr` block before the RTTI guard is touched).
bool sub_710001A69C(const ksys::act::ActorConstDataAccess* accessor, u32 flags) {
    auto* proc = accessor->getProc();
    if (proc && !sead::IsDerivedFrom<ksys::act::Actor>(proc))
        proc = nullptr;
    auto* actor = static_cast<ksys::act::Actor*>(proc);
    auto* enemy = sead::DynamicCast<uking::act::Enemy>(actor);
    return enemy && enemy->_e84.isOn(flags);
}
