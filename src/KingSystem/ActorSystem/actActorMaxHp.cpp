#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGeneral.h"

namespace ksys::act {

// In its own translation unit like in the original (0x71011daf40 getMaxLife tail-calls it at
// 0x7100edd1d8); in actActor.cpp clang would inline it into getMaxLife.
s32 Actor::getMaxHp_() {
    const auto* gparamlist = mActorParam->getRes().mGParamList;
    if (!gparamlist)
        return 1;
    const auto* general = gparamlist->getGeneral();
    if (!general)
        return 1;
    return general->mLife.ref();
}

}  // namespace ksys::act
