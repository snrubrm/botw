#include "Game/AI/Behavior/behaviorCreateBgm.h"
#include "Game/AI/aiUnk_7100FFD79C.h"

namespace uking::behavior {

CreateBgm::CreateBgm(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

CreateBgm::~CreateBgm() {
    if (_38 != 41) {
        if (auto* bgm = sub_7100FFD79C())
            bgm->_8.sub_7100FF7BE0(_38);
    }
}

void CreateBgm::m7() {}

void CreateBgm::m8() {}

void CreateBgm::m9() {}

void CreateBgm::loadParams() {
    getStaticParam(&mBgmName_s, "BgmName");
}

}  // namespace uking::behavior
