#include "Game/AI/AI/aiCreateActorWithTarget.h"
#include <math/seadMathCalcCommon.h>
#include <math/seadMatrix.h>
#include <math/seadQuat.h>
#include <math/seadVector.h>
#include <random/seadGlobalRandom.h>
#include "Game/gameResetter.h"
#include "KingSystem/ActorSystem/LOD/actLodState.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::ai {

CreateActorWithTarget::CreateActorWithTarget(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CreateActorWithTarget::~CreateActorWithTarget() = default;

bool CreateActorWithTarget::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CreateActorWithTarget::enter_(ksys::act::ai::InlineParamPack* params) {
    _98 = ksys::Timer(30.0f, 30.0f);
    _a4 = ksys::Timer(*mCreateContinueTime_s, *mCreateContinueTime_s);
    _b0 = ksys::Timer(*mAfterWaitTime_s, *mAfterWaitTime_s);
    for (auto& handle : _c0)
        handle.deleteProc();
    _f0 = 0;
    const f32 num_pos = *mCreateBasePosNum_s + 1;
    const f32 interval = (*mCreateContinueTime_s + 2.0f) / num_pos;
    _f4 = interval;
    _f8 = ksys::Timer(interval, interval);
    mActor->getLodState()->mFlags10.setBit(6);

    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(m35(), "TargetPos", -1);
    changeChild("子ノード", &pack);
}

void CreateActorWithTarget::calc_() {
    _98.update();
    _a4.update();
    _f8.update();
    if (m36()) {
        setFinished();
        return;
    }
    m34();
    getCurrentChild()->setDynamicParam(m35(), "TargetPos");
}

void CreateActorWithTarget::leave_() {
    for (auto& handle : _c0)
        handle.deleteProc();
    mActor->getLodState()->mFlags10.resetBit(6);
}

void CreateActorWithTarget::loadParams_() {
    getStaticParam(&mCreateNewActorInterval_s, "CreateNewActorInterval");
    getStaticParam(&mCreateBasePosNum_s, "CreateBasePosNum");
    getStaticParam(&mCreateContinueTime_s, "CreateContinueTime");
    getStaticParam(&mAfterWaitTime_s, "AfterWaitTime");
    getStaticParam(&mIsAllowCreateNoSafeArea_s, "IsAllowCreateNoSafeArea");
    getStaticParam(&mIsRotateTargetDir_s, "IsRotateTargetDir");
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getStaticParam(&mBaseOffset_s, "BaseOffset");
    getStaticParam(&mCreateRandArea_s, "CreateRandArea");
    getStaticParam(&mProhibitedCreateArea_s, "ProhibitedCreateArea");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

sead::Vector3f CreateActorWithTarget::m35() {
    return *mTargetPos_d;
}

bool CreateActorWithTarget::m36() {
    if (_a4.value <= sead::Mathf::epsilon()) {
        _b0.update();
        if (_b0.value <= sead::Mathf::epsilon())
            return true;
    }
    return false;
}

void CreateActorWithTarget::m37(ksys::act::BaseProcHandle* handle) {}

// NON_MATCHING: backend scheduling/selection only. All calls, branches, values and
// stack layout match except register assignment (dir.x in s8, ours, vs s10; 1.0 in s1 vs s8;
// ez address kept in x21 with value reloads vs single x8 load with values reused) and the
// degenerate makeR(0, pi, 0) branch (fully-folded immediates in the original vs literal-pool
// loads here). Snippet-proven: quat z must be a literal 0.0f (else no fmov-wzr zero cascade);
// makeR is the only source giving the exact 9 values incl. all -0.0s (sinf(pi_float) = -8.74e-8).
void CreateActorWithTarget::sub_710035A00C(ksys::act::InstParamPack* pack,
                                           const sead::Vector3f* pos) {
    if (!pack)
        return;

    if (*mIsRotateTargetDir_s) {
        sead::Vector3f dir = m35() - *pos;
        const f32 len = dir.length();
        if (len > 0.0f) {
            dir *= 1.0f / len;
            const f32 d = dir.dot(sead::Vector3f::ez) + 1.0f;
            sead::Matrix34f mtx;
            if (d <= sead::Mathf::epsilon()) {
                mtx.makeR({0.0f, sead::Mathf::pi(), 0.0f});
            } else {
                const f32 h = sead::Mathf::sqrt(d + d);
                const f32 inv = 1.0f / h;
                sead::Vector3f axis;
                axis.setCross(sead::Vector3f::ez, dir);
                axis *= inv;
                sead::Quatf q;
                q.set(h * 0.5f, axis.x, axis.y, 0.0f);
                mtx.fromQuat(q);
            }
            mtx.setTranslation(*pos);
            pack->getBuffer().addMatrix(mtx);
            return;
        }
    }
    pack->getBuffer().addPosition(*pos);
}

// NON_MATCHING: backend selection only. All calls, branches, values and the handle/timer logic
// match. Residuals: (1) the prohibited-area &-chain lowers to fccmp short-circuit form here vs
// cset+and+ccmp in the original (snippet-proven: <= unswapped gives cset ls, so the source is the
// natural box check; bare & in branch context always fccmp-folds with this toolchain, including
// via a named bool); (2) _f8 > eps gives b.gt vs b.hi; (3) loop tail cmp #6/b.le vs cmp #7/b.lt;
// (4) resulting register/scheduling ripples (center stores, sampling temps).
void CreateActorWithTarget::m34() {
    if (_98.value <= sead::Mathf::epsilon() &&
        uking::Resetter::instance()->finishedReset()) {
        if (_f8.value > sead::Mathf::epsilon() || _f0 >= *mCreateBasePosNum_s) {
            const sead::Vector3f* rand_area = mCreateRandArea_s;
            for (s32 i = 0; i < 7; ++i) {
                const f32 x =
                    (rand_area->x + rand_area->x) * sead::GlobalRandom::instance()->getF32() -
                    rand_area->x;
                const f32 y =
                    (rand_area->y + rand_area->y) * sead::GlobalRandom::instance()->getF32() -
                    rand_area->y;
                const f32 z =
                    (rand_area->z + rand_area->z) * sead::GlobalRandom::instance()->getF32() -
                    rand_area->z;
                const sead::Vector3f* proh = mProhibitedCreateArea_s;
                if ((x >= -proh->x) & (x <= proh->x) & (y >= -proh->y) & (y <= proh->y) &
                    (z >= -proh->z) & (z <= proh->z)) {
                    if (i != 6)
                        continue;
                    if (!*mIsAllowCreateNoSafeArea_s)
                        break;
                }
                const sead::Vector3f target = m35();
                sead::Vector3f center;
                center.x = x + target.x + mBaseOffset_s->x;
                center.y = y + target.y + mBaseOffset_s->y;
                center.z = z + target.z + mBaseOffset_s->z;
                ksys::act::BaseProcHandle* handle = nullptr;
                for (auto& h : _c0) {
                    if (!h.getUnit() && !h.hasFailed()) {
                        handle = &h;
                        break;
                    }
                }
                if (handle) {
                    ksys::act::InstParamPack pack;
                    sub_710035A00C(&pack, &center);
                    ksys::act::ActorCreator::instance()->requestCreateActor(
                        mCreateActorName_s.cstr(),
                        ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), handle,
                        &pack, nullptr, 1);
                }
                break;
            }
        } else {
            ++_f0;
            _f8.reset(_f4);
        }
        _98.reset(*mCreateNewActorInterval_s);
    }
    for (auto& handle : _c0) {
        if (handle.isProcReady()) {
            m37(&handle);
            handle.releaseAndWakeProc();
        } else if (handle.hasProcCreationFailed()) {
            handle.deleteProcIfFailed();
        }
    }
}

}  // namespace uking::ai
