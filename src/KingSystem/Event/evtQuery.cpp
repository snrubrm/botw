#include "KingSystem/Event/evtQuery.h"
#include <evfl/ResActor.h>
#include <prim/seadSafeString.h>
#include "KingSystem/ActorSystem/actAiClassDef.h"

namespace ksys::evt {

SystemQueryHandler sEventSystemQueryHandler;

// 0x7100e49998
void setEventSystemQueryHandler(SystemQueryHandler handler) {
    sEventSystemQueryHandler = handler;
}

// 0x7100e499a8
int callEventSystemQueryHandler(const evfl::QueryArg& arg) {
    if (sEventSystemQueryHandler)
        return sEventSystemQueryHandler(arg);
    return 0;
}

// 0x7100daeb2c (CSV evt::Query::ctor)
Query::Query(const evfl::ResQuery* res, ActorBase* actor) : mActor(actor), mRes(res) {
    if (AIClassDef::instance()->isSystemQuery(res->name.Get()->data()))
        mIsSystemQuery = true;
}

}  // namespace ksys::evt
