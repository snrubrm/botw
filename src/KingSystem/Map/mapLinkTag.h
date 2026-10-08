#pragma once

#include <math/seadMatrix.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <thread/seadAtomic.h>
#include "KingSystem/ActorSystem/actBaseProc.h"
#include "KingSystem/ActorSystem/actBaseProcJobHandler.h"
#include "KingSystem/GameData/gdtFlagHandle.h"
#include "KingSystem/Map/mapMubinIter.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::gdt {
class Manager;
}

namespace ksys::map {

class Object;
struct ObjectLink;

// 0x7100d39c9c (CSV GameDataMgr::setS32ByIdxForLinkTag; declaration only; it is called out of line with the game data manager
// as its first argument, so probably gdt::Manager::setS32NoCheck(s32, FlagHandle)): stores `value` in the flag `handle`.
bool setS32ByIdxForLinkTag(gdt::Manager* mgr, s8 value, gdt::FlagHandle handle);

// 0x7100d38070 (CSV isLinkTagNAndOrNOr): whether `name` is "LinkTagNAnd" or "LinkTagNOr".
bool isLinkTagNAndOrNOr(const sead::SafeString& name);

// 0x7100d38170 (declaration only): reads the game data flag of `obj`'s revival / signal into `out`; false if it has none.
bool isFlagSet(bool* out, bool a, const Object* obj);

// The BaseProc of a placed link tag (CSV LinkTag::*; the class name is the CSV's). It follows the links that point
// to its map object (a bit per link in `_1d0`) and drives the placed object's link signals. Only the small virtual
// overrides are decompiled so far.
// TODO: incomplete
class LinkTag : public act::BaseProc {
    SEAD_RTTI_OVERRIDE(LinkTag, act::BaseProc)
public:
    // 0x7100d3778c (CSV LinkTag::construct)
    static LinkTag* construct(const CreateArg& arg, sead::Heap* heap);

    explicit LinkTag(const CreateArg& arg);
    ~LinkTag() override;

    // 0x7100d379f8 (CSV init2; declaration only)
    InitResult init_() override;
    // 0x7100d382a4
    void finalizeInit_(InitContext* context) override;
    // 0x7100d38398 (CSV isDonePreparingForPreDelete)
    PreDeletePrepareResult prepareForPreDelete_() override;
    // 0x7100d382dc (CSV prepareForPreDelete)
    bool startPreparingForPreDelete_() override;
    // 0x7100d38d7c
    void onEnterCalc_() override;
    // 0x7100d38fc0
    IsSpecialJobTypeResult isSpecialJobType_(act::JobType type) override;
    // 0x7100d38fc8
    bool canWakeUp_() override;
    // 0x7100d38f3c
    void queueExtraJobPush_(act::JobType type, int idx) override;
    // 0x7100d38ef0
    bool hasJobType_(act::JobType type) override;
    // 0x7100d3905c
    bool shouldSkipJobPush_(act::JobType type) override;
    // 0x7100d3909c (CSV prePushJob2)
    void onJobPush2_(act::JobType type) override;

    // 0x7100d37858: the calc job (job type 3).
    void calc();

    // 0x7100d39420 (placeholder name; called by ActorAccessor::checkLinkTagActivated): the signal state from the flags at
    // +0x1e0 (bit 2 inverts it).
    bool sub_7100D39420(bool a) const;
    // 0x7100d39d60 (placeholder name; called by ObjectLinkData::sub_7100D4F0F0): copies the matrix of the actor of the
    // link `_1df` to `mtx`; false if there is none.
    bool sub_7100D39D60(sead::Matrix34f* mtx);
    // 0x7100d39de4 (placeholder name; called by deleteAllActors): requests the deletion of the proc; if accepted, marks the
    // object as having its actor created.
    void sub_7100D39DE4();
    // 0x7100d39e2c (placeholder name; called by deleteAllActors): the object's link data's sub_7100D4FBF8, true without one.
    bool sub_7100D39E2C();

private:
    // GenGroup::sub_7100D507F8 directly marks the pre-delete flag at +0x1de.
    friend class GenGroup;
    // 0x7100d383f4 / 0x7100d38534 / 0x7100d38820 (CSV calcCount / calcPulse / calcOther; declaration only): `frame_changed`
    // is whether the frame counter changed since the last calc.
    void calcCount(bool frame_changed);
    void calcPulse(bool frame_changed);
    void calcOther(bool frame_changed);
    // 0x7100d396a0 (CSV isTriggered; declaration only): whether the link `idx` (`link`) of the links to self is on.
    bool isTriggered(const ObjectLink* link, u32 idx);
    // 0x7100d391cc (CSV updateIsFlagSetFlag; declaration only)
    void updateIsFlagSetFlag(bool on, bool a, bool b);
    // 0x7100d39120 (placeholder name): sets the actor job type 3 push flag if the MCMgr value is positive and queues the
    // calc job for a calc-state proc; then stores the MCMgr value in `_1dd`.
    void sub_7100D39120();
    // inline-only in the original; name is a guess: the end of queueExtraJobPush_ and onEnterCalc_ (queues the calc job
    // for the current extra job array unless the proc is deleted).
    void queueCalcJob_();
public:

private:
    friend class act::BaseProcJobHandlerT<LinkTag>;

    /* 0x180 */ act::BaseProcJobHandlerT<LinkTag> mJob{this, &LinkTag::calc};
    // One bit per link of the object's links to self (at most 96; the original stores them as a u64 and a u32).
    /* 0x1d0 */ u64 _1d0 = 0;
    /* 0x1d8 */ u32 _1d8 = 0;
    /* 0x1dc */ s8 _1dc = 0;
    /* 0x1dd */ s8 _1dd = -1;
    /* 0x1de */ u8 _1de = 0;
    /* 0x1df */ s8 _1df = -1;
    // Bit 0: calc done; bit 3: ...; bit 4: ...; bit 15: link data prepared (woken up).
    /* 0x1e0 */ u16 _1e0 = 0;
    // The number of links that are triggered (calcCount / calcPulse).
    /* 0x1e2 */ u8 _1e2 = 0;
    // The frame counter at the last calc.
    /* 0x1e4 */ u32 _1e4 = 0;
    /* 0x1e8 */ s32 _1e8 = 0;
    // One bit per extra job array parity: set while the calc job is queued.
    /* 0x1ec */ sead::Atomic<u32> _1ec = 0;
    /* 0x1f0 */ s32 _1f0 = 0;
    /* 0x1f8 */ MubinIter _1f8;
    /* 0x208 */ Object* mObj = nullptr;
};
KSYS_CHECK_SIZE_NX150(LinkTag, 0x210);

}  // namespace ksys::map
