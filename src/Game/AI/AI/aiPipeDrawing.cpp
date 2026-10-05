#include "Game/AI/AI/aiPipeDrawing.h"
#include "Game/Actor/actWeapon.h"

namespace uking::ai {

PipeDrawing::PipeDrawing(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PipeDrawing::~PipeDrawing() = default;

bool PipeDrawing::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PipeDrawing::enter_(ksys::act::ai::InlineParamPack* params) {
    sub_71004F6298();
}

void PipeDrawing::calc_() {
    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (isCurrentChild("待機"))
            setFinished();
        else
            sub_71004F6298();
    } else if (child->isChangeable()) {
        auto* weapon = sead::DynamicCast<act::Weapon>(mActor);
        if (!weapon)
            setFailed();
        if (isCurrentChild("鳴らす")) {
            if (weapon->_af8._0 != 1)
                sub_71004F6298();
        } else if (weapon->_af8._0 == 1) {
            sub_71004F6650();
        }
    }
}

void PipeDrawing::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PipeDrawing::loadParams_() {}

}  // namespace uking::ai
