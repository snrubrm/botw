#pragma once

#include <basis/seadTypes.h>
#include <container/seadPtrArray.h>

namespace evfl {
struct ResActor;
}

namespace sead {
class Heap;
}

namespace ksys::evt {

class ActorBinding;

class ActorBindings {
public:
    ActorBindings() = default;
    virtual ~ActorBindings();

    void allocBindings(sead::Heap* heap);
    void allocBindingsActions(sead::Heap* heap);
    void allocBindingsQueries(sead::Heap* heap);
    ActorBinding* bindActor(const evfl::ResActor* res_actor, sead::Heap* heap);

    int isInitialized() const { return mInitialized; }
    int getNumBindings() const { return mBindings.size(); }
    // inline-only in the original; name is a guess (EventActorSet::allocActors reads the array with the range check)
    ActorBinding* getBinding(s32 index) const { return mBindings.at(index); }

private:
    sead::PtrArray<ActorBinding> mBindings;
    int mNumActorsToAlloc = 0;
    int mInitialized = 0;
};

}  // namespace ksys::evt
