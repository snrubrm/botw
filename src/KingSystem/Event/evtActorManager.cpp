#include "KingSystem/Event/evtActorManager.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Event/evtAction.h"
#include "KingSystem/Event/evtActorBase.h"
#include "KingSystem/Event/evtQuery.h"

namespace ksys::evt {

// 0x7100da2938 (CSV evt::actorActionHandler)
void ActorManager::actionHandler(const evfl::ActionArg& arg, evfl::ActionDoneHandler handler) {
    static_cast<ActionBase*>(arg.action_user_data)->sub_7100DA70A8(arg, handler);
}

// 0x7100da2950 (CSV evt::actorQueryHandler)
int ActorManager::queryHandler(const evfl::QueryArg& arg) {
    auto* query = static_cast<Query*>(arg.query_user_data);
    if (!sead::DynamicCast<act::Actor>(query->mActor->mLink.getProc(nullptr)))
        return 0;

    if (query->mIsSystemQuery)
        return callEventSystemQueryHandler(arg);
    return query->sub_7100DAEBA8(arg);
}

}  // namespace ksys::evt
