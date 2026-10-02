#include "Game/AI/Action/actionHoverNoticeTurn.h"
#include "Game/AI/aiUnk_71007377D4.h"

namespace uking::action {

HoverNoticeTurn::HoverNoticeTurn(const InitArg& arg) : NoticeTurn(arg) {}

HoverNoticeTurn::~HoverNoticeTurn() = default;

bool HoverNoticeTurn::init_(sead::Heap* heap) {
    return NoticeTurn::init_(heap);
}

void HoverNoticeTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    NoticeTurn::enter_(params);
    _80.sub_710072AFFC(mActor);
}

void HoverNoticeTurn::leave_() {
    _80.sub_710072B078(mActor);
    NoticeTurn::leave_();
}

void HoverNoticeTurn::loadParams_() {
    NoticeTurn::loadParams_();
}

void HoverNoticeTurn::calc_() {
    NoticeTurn::calc_();
}

void HoverNoticeTurn::m32() {
    sub_7100738428(mActor, 0.1f);
}

}  // namespace uking::action
