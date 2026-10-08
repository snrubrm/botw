#include "Game/AI/AI/aiAirOctaWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

AirOctaWait::AirOctaWait(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AirOctaWait::~AirOctaWait() = default;

bool AirOctaWait::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AirOctaWait::enter_(ksys::act::ai::InlineParamPack* params) {
    mFlags.set(Flag::Changeable);
    changeChild("通常");
}

// NON_MATCHING: the original's inlined SafeString comparison loops `i < 0x80000` (the
// SEAD_SAFE_STRING_COMPARE_VERSION=2 form that CMakeLists.txt enables for aiAirOctaState.cpp only; the
// build settings are not changed here), and the two flag stores are not merged.
void AirOctaWait::sub_71002FFEDC() {
    auto* as_list = mActor->getASList();
    if (!as_list)
        return;
    ksys::as::ASList::Unk4 event;
    if (!as_list->x(0x39, &event, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        return;
    if (event.name == "待機可")
        _48 = true;
    else if (event.name == "待機不可")
        _48 = false;
}

void AirOctaWait::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AirOctaWait::loadParams_() {
    getDynamicParam(&mIsSameChange_d, "IsSameChange");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

}  // namespace uking::ai
