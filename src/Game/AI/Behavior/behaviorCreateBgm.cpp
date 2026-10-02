#include "Game/AI/Behavior/behaviorCreateBgm.h"

namespace uking::behavior {

CreateBgm::CreateBgm(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

void CreateBgm::m7() {}

void CreateBgm::m8() {}

void CreateBgm::m9() {}

void CreateBgm::loadParams() {
    getStaticParam(&mBgmName_s, "BgmName");
}

}  // namespace uking::behavior
