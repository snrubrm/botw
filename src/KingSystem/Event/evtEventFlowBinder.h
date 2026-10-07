#pragma once

#include <evfl/Flowchart.h>

namespace ksys::evt {
class ActorBase;
class EventActorSet;

class EventActorBinder {
public:
    explicit EventActorBinder(EventActorSet* actors) : mActors(actors) {}
    virtual ~EventActorBinder() = default;
    void bind(evfl::ActorBinding* binding, const evfl::ResActor* actor);
private:
    EventActorSet* mActors;
};

class EventActionBinder {
public:
    explicit EventActionBinder(EventActorSet* actors) : mActors(actors) {}
    virtual ~EventActionBinder() = default;
    void bind(evfl::ActorBinding::Action* binding, const evfl::ResAction* action,
              const evfl::ResActor* actor, ActorBase* instance);
private:
    EventActorSet* mActors;
};

class EventQueryBinder {
public:
    explicit EventQueryBinder(EventActorSet* actors) : mActors(actors) {}
    virtual ~EventQueryBinder() = default;
    void bind(evfl::ActorBinding::Query* binding, const evfl::ResQuery* query,
              const evfl::ResActor* actor, ActorBase* instance);
private:
    EventActorSet* mActors;
};

long bindActors(evfl::FlowchartContext& context, EventActorBinder binder);
long bindActorActions(evfl::FlowchartContext& context, EventActionBinder binder);
long bindActorQueries(evfl::FlowchartContext& context, EventQueryBinder binder);
}  // namespace ksys::evt
