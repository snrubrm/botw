#include "KingSystem/Event/evtEventFlowBinder.h"
#include "KingSystem/Event/evtActorBase.h"

namespace ksys::evt {

// NON_MATCHING: binder-copy scheduling and loop register allocation differ.
long bindActors(evfl::FlowchartContext& context, EventActorBinder binder) {
    u8 any_ok = 0;
    u8 any_failed = 0;
    for (auto it = context.GetObjs().begin(); it != context.GetObjs().end(); ++it) {
        bool ok;
        bool failed;
        auto binder_ = binder;
        ok = false;
        failed = false;
        auto& bindings = it->GetActBinder().GetBindings();
        for (auto b = bindings.begin(); b != bindings.end(); ++b) {
            if (b->IsUsed() && !b->IsInitialized()) {
                binder_.bind(b, b->GetActor());
                (b->IsInitialized() ? ok : failed) = true;
            }
        }
        if (ok)
            any_ok = 1;
        if (failed)
            any_failed = 1;
    }
    return (int(any_failed) << 8) | int(any_ok);
}

// NON_MATCHING: binder-copy member and vtable stores are ordered differently.
long bindActorActions(evfl::FlowchartContext& context, EventActionBinder binder) {
    u8 any_ok = 0;
    u8 any_failed = 0;
    for (auto it = context.GetObjs().begin(); it != context.GetObjs().end(); ++it) {
        bool ok;
        bool failed;
        auto binder_ = binder;
        ok = false;
        failed = false;
        auto& bindings = it->GetActBinder().GetBindings();
        for (auto b = bindings.begin(); b != bindings.end(); ++b) {
            if (!b->IsUsed() || !b->IsInitialized())
                continue;
            const auto* actor = b->GetActor();
            for (auto a = b->GetActions().begin(); a != b->GetActions().end(); ++a) {
                binder_.bind(a, a->res_action, actor, static_cast<ActorBase*>(b->GetUserData()));
                (a->handler ? ok : failed) = true;
            }
        }
        if (ok)
            any_ok = 1;
        if (failed)
            any_failed = 1;
    }
    return (int(any_failed) << 8) | int(any_ok);
}

// NON_MATCHING: binder-copy member and vtable stores are ordered differently.
long bindActorQueries(evfl::FlowchartContext& context, EventQueryBinder binder) {
    u8 any_ok = 0;
    u8 any_failed = 0;
    for (auto it = context.GetObjs().begin(); it != context.GetObjs().end(); ++it) {
        bool ok;
        bool failed;
        auto binder_ = binder;
        ok = false;
        failed = false;
        auto& bindings = it->GetActBinder().GetBindings();
        for (auto b = bindings.begin(); b != bindings.end(); ++b) {
            if (!b->IsUsed() || !b->IsInitialized())
                continue;
            const auto* actor = b->GetActor();
            for (auto a = b->GetQueries().begin(); a != b->GetQueries().end(); ++a) {
                binder_.bind(a, a->res_query, actor, static_cast<ActorBase*>(b->GetUserData()));
                (a->handler ? ok : failed) = true;
            }
        }
        if (ok)
            any_ok = 1;
        if (failed)
            any_failed = 1;
    }
    return (int(any_failed) << 8) | int(any_ok);
}

}  // namespace ksys::evt
