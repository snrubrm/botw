#include "Game/Actor/AI/aiRemainElectricCannonBeamAttack.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Utils/Thread/Message.h"
#include <prim/seadDelegate.h>
#include "KingSystem/ActorSystem/actActorNameSearch.h"
#include "KingSystem/ActorSystem/actBaseProcMgr.h"

namespace uking::ai {

static sead::FixedSafeString<64> sUnk_71025bbc78("Npc_oasis033");
static sead::FixedSafeString<64> sUnk_71025bbcd0("Animal_SunazarashiSP_B");

RemainElectricCannonBeamAttack::RemainElectricCannonBeamAttack(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

RemainElectricCannonBeamAttack::~RemainElectricCannonBeamAttack() {
    if (_38.hasProc())
        _38.reset();
    if (_48.hasProc())
        _48.reset();
}

bool RemainElectricCannonBeamAttack::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void RemainElectricCannonBeamAttack::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_710053E864();
    if (_38.hasProc()) {
        ksys::act::ActorLinkConstDataAccess accessor;
        ksys::act::acquireActor(&_38, &accessor);
        _58.sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x8000085), nullptr,
                        true);
    }
    changeChild("溜め");
    mFlags.set(Flag::Changeable);
}

// NON_MATCHING: search record and delegate stack slots differ.
void RemainElectricCannonBeamAttack::sub_710053E864() {
    auto* mgr = ksys::act::BaseProcMgr::instance();
    if (!mgr)
        return;
    if (!_38.hasProc()) {
        ksys::act::BaseProc* result = nullptr;
        ksys::act::ActorNearestSearch search("", mActor, &result, sead::Vector3f::zero);
        sead::Delegate1<ksys::act::ActorNearestSearch, ksys::act::BaseProc*> callback(
            &search, &ksys::act::ActorNearestSearch::sub_7100EDC9E8);
        mgr->forEachProc(sUnk_71025bbc78, callback,
                         ksys::act::BaseProcMgr::ProcFilter::SkipAccessCheck);
        if (result)
            _38.acquire(result, false);
    }
    if (!_48.hasProc()) {
        ksys::act::BaseProc* result = nullptr;
        ksys::act::ActorNearestSearch search("", mActor, &result, sead::Vector3f::zero);
        sead::Delegate1<ksys::act::ActorNearestSearch, ksys::act::BaseProc*> callback(
            &search, &ksys::act::ActorNearestSearch::sub_7100EDC9E8);
        mgr->forEachProc(sUnk_71025bbcd0, callback,
                         ksys::act::BaseProcMgr::ProcFilter::SkipAccessCheck);
        if (result)
            _48.acquire(result, false);
    }
}

void RemainElectricCannonBeamAttack::leave_() {
    ksys::act::ai::Ai::leave_();
}

void RemainElectricCannonBeamAttack::loadParams_() {}

}  // namespace uking::ai
