#include "Game/Actor/Behavior/behaviorCreateBgm.h"
#include "Game/Actor/aiUnk_7100FFD79C.h"

namespace uking::behavior {

CreateBgm::CreateBgm(const InitArg& arg) : ksys::act::ai::Behavior(arg) {}

CreateBgm::~CreateBgm() {
    if (_38 != 41) {
        if (auto* bgm = sub_7100FFD79C())
            bgm->_8.sub_7100FF7BE0(_38);
    }
}

void CreateBgm::calc() {}

void CreateBgm::enter() {}

void CreateBgm::leave() {}

void CreateBgm::loadParams() {
    getStaticParam(&mBgmName_s, "BgmName");
}

}  // namespace uking::behavior
