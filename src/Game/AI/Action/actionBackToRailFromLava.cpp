#include "Game/AI/Action/actionBackToRailFromLava.h"
#include "Game/AI/aiUnk_71024f15c0.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapRail.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"

namespace uking::action {

BackToRailFromLava::BackToRailFromLava(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BackToRailFromLava::~BackToRailFromLava() = default;

bool BackToRailFromLava::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: canonicalization only — ours compares the rail point count as `n >= 1`
// (cmp #1 + b.lt); the original has `n <= 0` (cmp #0 + b.le). Same semantics; the <= form is
// unreachable from natural source here (it needs a goto into the shared setFailed tail).
// Everything else matches.
void BackToRailFromLava::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->getASList()->sub_710115C11C();
    mActor->getASList()->sub_710115B01C(2, 0, true);
    mActor->getActorFlags2().reset(ksys::act::Actor::ActorFlag2::_20);
    if (auto* cc = mActor->getCharacterController()) {
        cc->sub_7100F60604();
        cc->sub_7100F62BC0(false);
    }
    if (mActor->get6fc() == 11 && mActor->get68f()) {
        if (auto* rail = sub_7100EEF034(mActor, 0)) {
            const s32 n = rail->getNumPoints();
            if (n > 0) {
                const sead::Vector3f actor_pos = mActor->getMtx().getTranslation();
                sead::Vector3f best_pos = rail->calcTranslate(0.0f);
                f32 best = (best_pos - actor_pos).length();
                for (s32 i = 0; i != n; ++i) {
                    const f32 d = (rail->calcTranslate(i) - actor_pos).length();
                    if (d < best) {
                        best = d;
                        best_pos = rail->calcTranslate(i);
                    }
                }
                if (auto* cc = mActor->getCharacterController()) {
                    cc->warpActorToPosition(best_pos);
                    setFinished();
                    return;
                }
            }
        }
    }
    setFailed();
}

void BackToRailFromLava::leave_() {
    ksys::act::ai::Action::leave_();
}

void BackToRailFromLava::loadParams_() {}

void BackToRailFromLava::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
