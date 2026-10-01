#include "Game/AI/AI/aiPartsNoticeSelect.h"

namespace uking::ai {

PartsNoticeSelect::PartsNoticeSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PartsNoticeSelect::~PartsNoticeSelect() = default;

bool PartsNoticeSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PartsNoticeSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    if (sub_71004F4C38())
        changeChild("パーツ気づき", params);
    else
        changeChild("パーツ通常", params);
}

void PartsNoticeSelect::calc_() {
    if (!getCurrentChild()->isChangeable())
        return;

    const bool is_on = isCurrentChild("パーツ気づき");
    const bool should_be_on = sub_71004F4C38();
    if (is_on) {
        if (!should_be_on)
            changeChild("パーツ通常");
    } else if (should_be_on) {
        changeChild("パーツ気づき");
    }
}

void PartsNoticeSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PartsNoticeSelect::loadParams_() {
    getStaticParam(&mPartsName_s, "PartsName");
}

}  // namespace uking::ai
