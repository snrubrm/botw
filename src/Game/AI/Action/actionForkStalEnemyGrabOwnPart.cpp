#include "Game/AI/Action/actionForkStalEnemyGrabOwnPart.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_7100724C64.h"
#include "KingSystem/ActorSystem/actActor.h"
#include <gsys/gsysModel.h>
#include <gsys/gsysModelUnit.h>

// 0x7100edd258 (declaration only): default bone name for the actor.
const sead::SafeString& sub_7100EDD258(ksys::act::Actor* actor, int a2);

namespace uking::action {

ForkStalEnemyGrabOwnPart::ForkStalEnemyGrabOwnPart(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkStalEnemyGrabOwnPart::~ForkStalEnemyGrabOwnPart() = default;

bool ForkStalEnemyGrabOwnPart::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: one instruction — ours tests the acquireActor result as `eor + tbnz`
// (clang's default lowering for a named bool, verified in isolation); the original has a
// plain `tbz`, which needs the call result tested directly — impossible here since the call
// precedes the target check. Everything else matches.
void ForkStalEnemyGrabOwnPart::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
    _48 = false;
    _49 = false;
    mFlags.set(Flag::Changeable);
    if (!sub_7100724D7C(mActor))
        setFailed();
    auto* actor = mActor;
    if (!actor->getConnectedCalcChild()) {
        auto* link = &sub_7100724F08(actor, *mPartIndex_d);
        auto* proc = link->getProc(nullptr, nullptr);
        auto* target =
            sead::IsDerivedFrom<ksys::act::Actor>(proc) ? static_cast<ksys::act::Actor*>(proc)
                                                        : nullptr;
        ksys::act::ActorConstDataAccess accessor;
        if (link->hasProc()) {
            bool acquired = ksys::act::acquireActor(link, &accessor);
            if (target) {
                if (acquired) {
                    if (!accessor.isStateSleep()) {
                        setFailed();
                    } else {
                        accessor.setThisActorAsChild(actor, false);
                        sub_71005DC208(actor, target, 0);
                        sub_71005DC41C(target);
                    }
                }
            }
        }
    }
}

void ForkStalEnemyGrabOwnPart::leave_() {
    auto* actor = mActor;
    if (_48 && actor->getConnectedCalcChild()) {
        if (auto* child = sead::DynamicCast<ksys::act::Actor>(actor->getConnectedCalcChild()))
            sub_71005DC41C(child);
    }
    if (_49) {
        _49 = false;
        sub_71007275C8(sub_7100724D7C(actor));
    }
}

void ForkStalEnemyGrabOwnPart::loadParams_() {
    getStaticParam(&mSeqBank_s, "SeqBank");
    getStaticParam(&mTargetBone_s, "TargetBone");
    getStaticParam(&mBoneName_s, "BoneName");
    getDynamicParam(&mPartIndex_d, "PartIndex");
}

// NON_MATCHING: one vtable slot — the original calls ModelUnit slot 0x70, ours resolves
// safeGetBoneWorldMatrix to slot 0x80 (our gsysModelUnit.h has two extra virtuals before it:
// getBoneWorldMatrix + getBoneWorldMatrixPtr). Libwork request logged. Everything else matches.
void ForkStalEnemyGrabOwnPart::calc_() {
    auto* actor = mActor;
    if (_49) {
        _49 = false;
        sub_71007275C8(sub_7100724D7C(actor));
    }
    if (sub_71005DD780(actor, 0x45, nullptr, *mTargetBone_s, *mSeqBank_s)) {
        if (actor->getConnectedCalcChild()) {
            const u32 part = *mPartIndex_d;
            auto* link = &sub_7100724F08(actor, part);
            ksys::act::ActorConstDataAccess accessor;
            if (link->hasProc() && ksys::act::acquireActor(link, &accessor) &&
                accessor.isStateSleep()) {
                auto* model = actor->getModel();
                sead::Matrix34f mtx;
                if (!model) {
                    mtx = actor->getMtx();
                } else {
                    const sead::SafeString& bone_name =
                        mBoneName_s.getStringTop()[0] != sead::SafeString::cNullChar
                            ? mBoneName_s
                            : sub_7100EDD258(actor, 0);
                    auto key = model->searchBone(bone_name);
                    if (key.isValid()) {
                        model->getUnits()(key.model_unit_index)
                            ->mModelUnit->safeGetBoneWorldMatrix(&mtx, key.bone_index);
                    } else {
                        mtx = actor->getMtx();
                    }
                }
                accessor.setProperties(mtx, nullptr, nullptr, nullptr, false, 0, -1);
                sub_71007250E4(actor, part);
                _48 = true;
            }
            sub_710072735C(actor, false, true);
            sub_7100727AA0(actor, part);
            _49 = true;
        }
    }
}

}  // namespace uking::action
