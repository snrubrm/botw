#include "Game/Actor/AI/aiAirOctaWait.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "Game/Actor/actMotorcycleUtil.h"
#include "Game/Actor/AI/aiAirOctaDataMgr.h"

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

void AirOctaWait::calc_() {
    auto* mgr = sead::DynamicCast<AirOctaDataMgr>(*mAirOctaDataMgr_a);
    if (!mgr)
        return;
    auto* data = mgr->sub_71002FB32C();
    if (!data)
        return;

    // The angle between the actor's up axis and the world up axis.
    const auto calcTilt = [this] {
        sead::Vector3f up;
        mActor->getMtx().getBase(up, 1);
        up.normalize();
        return act::angleBetweenVectors(up, sead::Vector3f::ey);
    };

    const sead::Vector3f& move = data->_24;
    if ((move.x == 0.0f && move.y == 0.0f && move.z == 0.0f) || (mgr->mFlags & 0x10) ||
        (_48 && calcTilt() < 0.2617994f)) {
        if (isCurrentChild("水上") || *mIsSameChange_d) {
            changeChild("通常");
            _48 = true;
            *mIsSameChange_d = false;
        }
    } else if (!isCurrentChild("通常") && !*mIsSameChange_d) {
        sub_71002FFBBC(move);
    } else if (calcTilt() >= 0.43633232f) {
        changeChild("水上");
        _48 = false;
        *mIsSameChange_d = false;
    }

    if (isCurrentChild("水上"))
        sub_71002FFEDC();
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
