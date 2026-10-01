#include "Game/AI/AI/aiArmorSearchKorokRoot.h"

namespace uking::ai {

ArmorSearchKorokRoot::ArmorSearchKorokRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ArmorSearchKorokRoot::~ArmorSearchKorokRoot() = default;

bool ArmorSearchKorokRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ArmorSearchKorokRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    _48 = false;
    _49 = false;
    _4c = 0.0f;
    _50 = sead::Vector3f::zero;
    changeChild("未発見");
}

void ArmorSearchKorokRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ArmorSearchKorokRoot::loadParams_() {
    getStaticParam(&mSearchKorokDis_s, "SearchKorokDis");
    getStaticParam(&mSearchRefreshFrame_s, "SearchRefreshFrame");
}

}  // namespace uking::ai
