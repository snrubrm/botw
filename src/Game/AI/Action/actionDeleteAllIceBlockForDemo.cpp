#include "Game/AI/Action/actionDeleteAllIceBlockForDemo.h"
#include "Game/gameIceBlockMgr.h"

namespace uking::action {

DeleteAllIceBlockForDemo::DeleteAllIceBlockForDemo(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DeleteAllIceBlockForDemo::~DeleteAllIceBlockForDemo() = default;

bool DeleteAllIceBlockForDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

bool DeleteAllIceBlockForDemo::oneShot_() {
    if (auto* manager = IceBlockMgr::instance())
        manager->sub_710066F8C4();
    return true;
}

void DeleteAllIceBlockForDemo::loadParams_() {}

}  // namespace uking::action
