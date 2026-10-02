#include "Game/AI/Action/actionStopASIgnite.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

StopASIgnite::StopASIgnite(const InitArg& arg) : OnetimeStopASPlay(arg) {}

bool StopASIgnite::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void StopASIgnite::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void StopASIgnite::leave_() {
    OnetimeStopASPlay::leave_();
}

void StopASIgnite::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteVelocityDir_s, "IgniteVelocityDir");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
    getAITreeVariable(&mGeneratedActorLink_a, "GeneratedActorLink");
}

// NON_MATCHING: the original loads the argument before the vtable (C++14 evaluation order)
void StopASIgnite::calc_() {
    OnetimeStopASPlay::calc_();
    if (mActor->getASList()->x(0x47, nullptr, 0, 0, &ksys::as::ASList::Unk2::sub_71011637EC, true))
        m32(*mIgniteHandle_d);
}

const sead::Matrix34f& StopASIgnite::m33() {
    return mActor->getMtx();
}

}  // namespace uking::action
