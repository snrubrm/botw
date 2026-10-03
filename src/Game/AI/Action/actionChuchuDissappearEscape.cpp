#include "Game/AI/Action/actionChuchuDissappearEscape.h"
#include "Game/Actor/actGelEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::action {

ChuchuDissappearEscape::ChuchuDissappearEscape(const InitArg& arg)
    : ChuchuDissappearEscapeBase(arg) {}

ChuchuDissappearEscape::~ChuchuDissappearEscape() = default;

bool ChuchuDissappearEscape::init_(sead::Heap* heap) {
    return ChuchuDissappearEscapeBase::init_(heap);
}

void ChuchuDissappearEscape::enter_(ksys::act::ai::InlineParamPack* params) {
    ChuchuDissappearEscapeBase::enter_(params);
    if (auto* gel = sead::DynamicCast<act::GelEnemy>(mActor)) {
        gel->_1678 |= 1;
        gel->sub_71000269C8();
        gel->_1678 |= 2;
    }
}

void ChuchuDissappearEscape::leave_() {
    if (auto* gel = sead::DynamicCast<act::GelEnemy>(mActor)) {
        gel->_1678 &= 0xfe;
        gel->sub_7100026A38();
        gel->_1678 &= 0xfd;
    }
    ChuchuDissappearEscapeBase::leave_();
}

void ChuchuDissappearEscape::loadParams_() {
    ChuchuDissappearEscapeBase::loadParams_();
}

void ChuchuDissappearEscape::calc_() {
    ChuchuDissappearEscapeBase::calc_();
    if (isFinishedAS(0, 0))
        mActor->deleteLater(ksys::act::BaseProc::DeleteReason::_0);
}

bool ChuchuDissappearEscape::isFailed() const {
    return false;
}

bool ChuchuDissappearEscape::isFinished() const {
    return false;
}

}  // namespace uking::action
