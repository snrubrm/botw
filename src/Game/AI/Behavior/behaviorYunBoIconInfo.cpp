#include "Game/AI/Behavior/behaviorYunBoIconInfo.h"

namespace uking::behavior {

YunBoIconInfo::YunBoIconInfo(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

YunBoIconInfo::~YunBoIconInfo() = default;

bool YunBoIconInfo::m6(sead::Heap* heap) {
    return true;
}

void YunBoIconInfo::m8() {}

void YunBoIconInfo::m9() {}

void YunBoIconInfo::loadParams() {
    getStaticParam(&mType_s, "Type");
    getStaticParam(&mVisible_s, "Visible");
}

}  // namespace uking::behavior
