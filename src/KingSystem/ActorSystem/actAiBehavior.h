#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::act {
class Actor;
}

namespace ksys::res {
class AIProgram;
}

namespace ksys::act::ai {

class Behavior {
    SEAD_RTTI_BASE(Behavior)

public:
    struct InitArg {
        Actor* actor;
        /// The index of the behavior definition in the actor's AI program.
        s32 def_idx;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x10);

    explicit Behavior(const InitArg& arg);
    virtual ~Behavior() = default;

    bool init(sead::Heap* heap);

    // 0x0000007100d24a10
    bool sub_7100D24A10(Behavior** list, Behavior** pending_list);
    // 0x0000007100d24ac0
    bool sub_7100D24AC0(Behavior** list, Behavior** pending_list);
    // 0x0000007100d24b94
    Behavior* sub_7100D24B94();
    // 0x0000007100d24bd4
    Behavior* sub_7100D24BD4();
    void x();

    s32 getCalcTiming() const;
    bool isNoStop() const;

    bool getStaticParam(sead::SafeString* value, const sead::SafeString& key) const;
    bool getStaticParam(const s32** value, const sead::SafeString& key) const;

    virtual bool hasPreDeleteCb() { return false; }
    virtual bool hasUpdateForPreDeleteCb() { return false; }
    virtual bool m6(sead::Heap* heap) { return true; }
    virtual void m7() {}
    virtual void m8() {}
    virtual void m9() {}
    virtual void m10() {}
    virtual void m11() {}
    virtual bool updateForPreDelete() { return true; }
    virtual void onPreDelete() {}

protected:
    res::AIProgram* getAIProg() const;
    auto& getDef() const;
    void updateState(Behavior** pending_list);

    Actor* mActor{};
    u16 mDefIdx{};
    u8 _12{};
    u8 _13{};
    Behavior* _18{};
    Behavior* _20{};
};
KSYS_CHECK_SIZE_NX150(Behavior, 0x28);

struct BehaviorFactory {
    using CreateFn = Behavior* (*)(const Behavior::InitArg& arg, sead::Heap* heap);
    u32 hash;
    CreateFn create_fn;
};

class Behaviors {
public:
    Behaviors();
    ~Behaviors();

    void finalize();

    bool init(Actor* actor, sead::Heap* heap);
    bool updateForPreDelete() const;
    void onPreDelete() const;

    const sead::Buffer<Behavior*>& getClasses() const { return mClasses; }

    static BehaviorFactory* getFactory(const sead::SafeString& name);
    static void setFactories(int count, BehaviorFactory* factories);

private:
    static inline sead::Buffer<BehaviorFactory> sFactories;
    sead::Buffer<Behavior*> mClasses;
    // Non-owning buffer.
    sead::Buffer<Behavior*> mOnPreDeleteCbs;
    // Non-owning buffer.
    sead::Buffer<Behavior*> mUpdateForPreDeleteCbs;
};

}  // namespace ksys::act::ai
