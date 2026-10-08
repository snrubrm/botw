#include "Game/AI/Action/actionForkFourFootActorLustGrass.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "gsys/gsysModel.h"

namespace uking::action {

ForkFourFootActorLustGrass::ForkFourFootActorLustGrass(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkFourFootActorLustGrass::~ForkFourFootActorLustGrass() = default;

bool ForkFourFootActorLustGrass::init_(sead::Heap* heap) {
    if (auto* model = mActor->getModel()) {
        _b0[0].search(model, mNode1Name_s);
        _b0[1].search(model, mNode2Name_s);
        _b0[2].search(model, mNode3Name_s);
        _b0[3].search(model, mNode4Name_s);
    }
    _190 = -1;
    _198 = -1;
    return true;
}

void ForkFourFootActorLustGrass::enter_(ksys::act::ai::InlineParamPack* params) {
    _88._8._10 = *mMinRadius_s;
    _88._8._14 = *mMinRadius_s;
    _88._8._18 = *mMinRadius_s;
    _88._8._1c = *mMinRadius_s;
    _1a0 = 0;
    mFlags.set(Flag::Changeable);
}

void ForkFourFootActorLustGrass::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkFourFootActorLustGrass::loadParams_() {
    getStaticParam(&mMaxRadius_s, "MaxRadius");
    getStaticParam(&mMinRadius_s, "MinRadius");
    getStaticParam(&mNode1Name_s, "Node1Name");
    getStaticParam(&mNode2Name_s, "Node2Name");
    getStaticParam(&mNode3Name_s, "Node3Name");
    getStaticParam(&mNode4Name_s, "Node4Name");
    getStaticParam(&mWorldOffset_s, "WorldOffset");
    getStaticParam(&mRadSpd_s, "RadSpd");
    getAITreeVariable(&mGanonBeastGrudgeMarkMgr_a, "GanonBeastGrudgeMarkMgr");
}

// NON_MATCHING: the event-name strlen differs — the original addresses all three byte checks
// through one shared str+len+2 base (unscaled -2/-1 loads plus [str, len+2]) where ours computes
// separate addresses, and ours merges the bound-exceeded fixup test with the negativity test into
// a ccmp where the original keeps a separate cmp. Calls, loop structure, constants identical.
void ForkFourFootActorLustGrass::calc_() {
    _1a0 = 0;
    if (!mActor->getModel())
        return;

    ksys::as::ASList::EventQueryResults results;
    if (!mActor->getASList()->sub_710115FB60(&results, 6, 0, 0,
                                            &ksys::as::ASList::Unk2::sub_7101163908, true)) {
        return;
    }
    if (results.count < 1)
        return;

    for (s64 i = 0; i < results.count; ++i) {
        u32 bit;
        if (results.events[0].name.isEmpty()) {
            bit = 1;
        } else {
            const auto& event = results.events.mBuffer[i < 16ul ? i : 0];
            event.name.cstr();
            const char* str = event.name.getStringTop();
            int len = 0;
            while (len + 2 < 0x80000) {
                if (str[len] == sead::SafeString::cNullChar)
                    break;
                if (str[len + 1] == sead::SafeString::cNullChar) {
                    ++len;
                    break;
                }
                if (str[len + 2] == sead::SafeString::cNullChar) {
                    len += 2;
                    break;
                }
                len += 3;
            }
            if (len + 2 >= 0x80000)
                len = 0;
            const char* p = len < 0 ? &sead::SafeString::cNullChar : str;
            bit = 1 << s8(*p - 0x30);
        }
        _1a0 |= bit;
    }
}

bool ForkFourFootActorLustGrass::hasUpdateForPreDeleteCb() {
    return true;
}

bool ForkFourFootActorLustGrass::updateForPreDelete() {
    _88._8._0.sub_71007444AC();
    return true;
}

}  // namespace uking::action
