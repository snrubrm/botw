#include "Game/AI/AI/aiChuchuTypeSelect.h"
#include "Game/AI/aiUnk_71006F5B14.h"

namespace uking::ai {

ChuchuTypeSelect::ChuchuTypeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ChuchuTypeSelect::~ChuchuTypeSelect() = default;

bool ChuchuTypeSelect::isFailed() const {
    return ksys::act::ai::Ai::isFailed() || getCurrentChild()->isFailed();
}

bool ChuchuTypeSelect::isFinished() const {
    return getCurrentChild()->isFinished();
}

bool ChuchuTypeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ChuchuTypeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    switch (sub_71006F5694(mActor).value()) {
    case Unk_71006F5DB0::Fire:
        changeChild("ファイア", params);
        break;
    case Unk_71006F5DB0::Electric:
        changeChild("エレキ", params);
        break;
    case Unk_71006F5DB0::Ice:
        changeChild("アイス", params);
        break;
    default:
        changeChild("ノーマル", params);
        break;
    }
}

void ChuchuTypeSelect::calc_() {}

void ChuchuTypeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ChuchuTypeSelect::loadParams_() {}

}  // namespace uking::ai
