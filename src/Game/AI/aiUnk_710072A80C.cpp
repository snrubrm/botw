#include "Game/AI/aiUnk_710072A80C.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectSwarm.h"

void sub_710072A80C(ksys::act::Actor* actor, ksys::act::BaseProcHandle* handle,
                    ksys::act::InstParamPack* params) {
    auto* swarm = actor->getParam()->getRes().mGParamList->getSwarm();
    if (swarm->mDeadActorName.ref().isEmpty())
        return;
    ksys::act::ActorCreator::instance()->requestCreateActor(
        swarm->mDeadActorName.ref().cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(),
        handle, params, nullptr, 1);
}
