#pragma once

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace evfl {
struct QueryArg;
struct ResQuery;
}  // namespace evfl

namespace ksys::evt {

class ActorBase;

using SystemQueryHandler = int (*)(const evfl::QueryArg& arg);

// 0x7100e49998 (CSV evt::setEventSystemQueryHandler): sets the handler of system queries (see
// ActorManager::queryHandler); 0x7100e499a8 calls it (returns 0 if it is not set)
void setEventSystemQueryHandler(SystemQueryHandler handler);
int callEventSystemQueryHandler(const evfl::QueryArg& arg);

// The query of an event actor (CSV evt::Query; created by ukingEventMgr::makeQuery 0x71008ac66c, 0x20 bytes).
class Query {
public:
    SEAD_RTTI_BASE(Query)

    Query(const evfl::ResQuery* res, ActorBase* actor);
    virtual ~Query() = default;

    // 0x7100daeba8 (declaration only): runs a non-system query
    int sub_7100DAEBA8(const evfl::QueryArg& arg);

    /* 0x08 */ ActorBase* mActor;
    /* 0x10 */ const evfl::ResQuery* mRes;
    /* 0x18 */ bool mIsSystemQuery = false;
};

}  // namespace ksys::evt
