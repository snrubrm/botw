#include "Game/AI/AI/aiForbidDoubleNoticeSelect.h"
#include "Game/Actor/actEnemy.h"

namespace uking::ai {

ForbidDoubleNoticeSelect::ForbidDoubleNoticeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ForbidDoubleNoticeSelect::~ForbidDoubleNoticeSelect() = default;

bool ForbidDoubleNoticeSelect::isFailed() const {
    return getCurrentChild()->isFailed();
}

bool ForbidDoubleNoticeSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool ForbidDoubleNoticeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ForbidDoubleNoticeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* enemy = sead::DynamicCast<act::Enemy>(mActor);
    if (enemy && enemy->_e74 > 0)
        changeChild("禁止", params);
    else
        changeChild("解禁", params);
}

void ForbidDoubleNoticeSelect::calc_() {}

void ForbidDoubleNoticeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ForbidDoubleNoticeSelect::loadParams_() {}

}  // namespace uking::ai
