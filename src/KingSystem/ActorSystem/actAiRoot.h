#pragma once

#include <prim/seadBitFlag.h>
#include <thread/seadAtomic.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiAction.h"
#include "KingSystem/ActorSystem/actAiAi.h"
#include "KingSystem/ActorSystem/actAiBehavior.h"
#include "KingSystem/ActorSystem/actAiParam.h"
#include "KingSystem/ActorSystem/actAiQueries.h"
#include "KingSystem/ActorSystem/actAiQuery.h"
#include "KingSystem/Utils/Types.h"

namespace uking::ai {
class DemoRootAI;
}

namespace ksys::act::ai {

class IRootAi {
public:
    virtual ~IRootAi() = default;
};

enum class RootAiFlag {
    _0 = 0,
    _5 = 5,
    _7 = 7,
    _8 = 8,
};

// TODO: rename
enum class RootAiFlag2 {
    _0 = 0,
    _1 = 1,
    _2 = 2,
    _3 = 3,
    _4 = 4,
};

class RootAi : public Ai, public IRootAi {
    SEAD_RTTI_OVERRIDE(RootAi, Ai)
public:
    explicit RootAi(const InitArg& arg);
    ~RootAi() override;

    bool isChangeable() const override { return true; }
    bool init_(sead::Heap* heap) override;
    void enter_(InlineParamPack* params) override;
    void leave_() override;
    bool handleMessage_(const Message* message) override;
    void calc() override;

    const ParamPack& getMapUnitParams() const { return mMapUnitParams; }
    const ParamPack& getAiTreeParams() const { return mAiTreeParams; }
    u32 getI() const { return mI; }
    void setI(u32 i) { mI = i; }
    s16 getAt() const { return mAt; }
    // 0x7100d66b94 (CSV RootAi::x_0; lane1 s24, name is a guess): sets (`on`) or clears the bits `mask` of the
    // flag word at 0x3c of every Chemical of the actor.
    void setChemicalFlags3cMaybe(u32 mask, bool on);
    bool isActorDeletedOrDeleting() const;
    bool isChildIdx0() const;
    void onActorPreDelete1();
    bool stubbedRet0() const;
    // Public through the root AI (SiteBossSpearRoot::leave_ calls it on `mActor->getRootAi()`; lane2 s20).
    using ActionBase::isActorGoingBackToRootAi;
    // Public through the root AI (LynelRecognizeTarget::enter_ calls it on `mActor->getRootAi()`; lane1 s63).
    using ActionBase::testRootAiFlag2;

    const Actions& getActions() const { return mActions; }
    const Ais& getAis() const { return mAis; }
    const Behaviors& getBehaviors() const { return mBehaviors; }
    const Queries& getQueries() const { return mQueries; }

    bool loadMapUnitParams(const AIDef& def, sead::Heap* heap);
    bool loadAITreeParams(const AIDef& def, sead::Heap* heap);

    bool getMapUnitParam(sead::SafeString* value, const sead::SafeString& key) const;
    bool getMapUnitParam(const s32** value, const sead::SafeString& key) const;
    bool getMapUnitParam(const f32** value, const sead::SafeString& key) const;
    bool getMapUnitParam(const sead::Vector3f** value, const sead::SafeString& key) const;
    bool getMapUnitParam(const bool** value, const sead::SafeString& key) const;

    bool getAITreeVariable(sead::SafeString** value, const sead::SafeString& key) const;
    bool getAITreeVariable(s32** value, const sead::SafeString& key) const;
    bool getAITreeVariable(f32** value, const sead::SafeString& key) const;
    bool getAITreeVariable(sead::Vector3f** value, const sead::SafeString& key) const;
    bool getAITreeVariable(bool** value, const sead::SafeString& key) const;
    bool getAITreeVariable(void** value, const sead::SafeString& key) const;
    bool getAITreeVariable(u32** value, const sead::SafeString& key) const;
    // TODO: rename
    bool getAITreeVariable2(sead::Vector3f** value, const sead::SafeString& key) const;
    // TODO: rename
    bool getAITreeVariable2(bool** value, const sead::SafeString& key) const;

    // 0x7100d64ec8 (CSV RootAi::behaviorStuff): Behavior::x() of every behavior in the six update lists.
    void behaviorStuff();
    // 0x7100d66b48 (CSV RootAi::x): stores the two vectors and the value, sets RootAiFlag 9.
    void sub_7100D66B48(const sead::Vector3f& a, const sead::Vector3f& b, f32 value);
    void setBehavior(Behavior* behavior);
    void resetBehavior(Behavior* behavior);

private:
    friend class ActionBase;
    // DemoRootAI::leave_ reads _140 (the event context cleaned by sub_7100D630AC).
    friend class uking::ai::DemoRootAI;

    // TODO: rename and put this in a different translation unit
    struct SomeStruct {
        SomeStruct();
        virtual ~SomeStruct();

        void* _8{};
    };
    KSYS_CHECK_SIZE_NX150(SomeStruct, 0x10);

    void calc_() override;

    f32 _40 = 1.0;
    u32 _44{};
    Actions mActions;
    Ais mAis;
    Behaviors mBehaviors;
    Queries mQueries;
    sead::SafeArray<Behavior*, 3> mBehaviorsByStopAndCalcTiming[2]{};
    Behavior* _138{};
    SomeStruct* _140{};
    u32 mI{};
    s16 mAt{};
    u8 _14e{};
    sead::Vector3f _150{0, 0, 0};
    sead::Vector3f _15c{0, 0, 0};
    // Written as a plain float by sub_7100D66B48.
    f32 _168 = 1.0;
    // RootAiFlag
    sead::BitFlag16 _16c;
    // RootAiFlag2
    sead::BitFlag16 _16e;
    ParamPack mMapUnitParams;
    ParamPack mAiTreeParams;
};
KSYS_CHECK_SIZE_NX150(RootAi, 0x180);

inline bool ActionBase::testRootAiFlag(RootAiFlag flag) const {
    return mActor->getRootAi()->_16c.isOnBit(int(flag));
}

const char* getDefaultAiName(s32 root_idx);
const char* getDefaultActionName(s32 idx);

inline const char* getDefaultName(ActionType type, s32 idx) {
    if (type == ActionType::AI)
        return getDefaultAiName(idx);
    return getDefaultActionName(idx);
}

}  // namespace ksys::act::ai
