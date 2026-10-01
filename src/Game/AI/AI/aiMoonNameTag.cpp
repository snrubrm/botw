#include "Game/AI/AI/aiMoonNameTag.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/World/worldManager.h"

namespace uking::ai {

MoonNameTag::MoonNameTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MoonNameTag::~MoonNameTag() = default;

bool MoonNameTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MoonNameTag::enter_(ksys::act::ai::InlineParamPack* params) {
    mActor->m107();
    if (static_cast<int>(ksys::world::Manager::instance()->getTimeMgr()->getMoonType()) ==
        *mMoonNameType_m) {
        changeChild("オン");
    } else {
        changeChild("オフ");
    }
}

void MoonNameTag::calc_() {
    mActor->m107();
    if (static_cast<int>(ksys::world::Manager::instance()->getTimeMgr()->getMoonType()) ==
        *mMoonNameType_m) {
        if (isCurrentChild("オフ"))
            changeChild("オン");
    } else {
        if (isCurrentChild("オン"))
            changeChild("オフ");
    }
}

void MoonNameTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MoonNameTag::loadParams_() {
    getMapUnitParam(&mMoonNameType_m, "MoonNameType");
}

}  // namespace uking::ai
