#include "Game/AI/aiUnk_710073CDFC.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceDrop.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectGeneral.h"

s32 sub_710073CDFC(ksys::act::Actor* actor, ksys::act::BaseProcLink* link) {
    if (!link->hasProc())
        return -1;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    const auto* general = accessor.getGParamList()->getGeneral();
    if (general->mChangeDropTableName.ref().isEmpty())
        return -1;
    return actor->getParam()->getRes().mDropTable->findTableIndex(
        general->mChangeDropTableName.ref());
}
