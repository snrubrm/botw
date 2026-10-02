#include "Game/AI/Action/actionGetCapturedActor.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

GetCapturedActor::GetCapturedActor(const InitArg& arg) : GetItem(arg) {}

GetCapturedActor::~GetCapturedActor() = default;

bool GetCapturedActor::init_(sead::Heap* heap) {
    return GetItem::init_(heap);
}

void GetCapturedActor::enter_(ksys::act::ai::InlineParamPack* params) {
    playAS("Wait", false, 0, 0, -1.0f);
    mActor->getASList()->x_3(0, 0, &ksys::as::ASList::Unk2::sub_71011631BC, 0.0f);
    GetItem::enter_(params);
}

void GetCapturedActor::leave_() {
    GetItem::leave_();
}

void GetCapturedActor::loadParams_() {
    GetItem::loadParams_();
}

void GetCapturedActor::calc_() {
    GetItem::calc_();
}

void GetCapturedActor::m32() {
    mActor->deleteAndEmit(1);
}

}  // namespace uking::action
