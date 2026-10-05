#include "Game/AI/AI/aiSiteBossAttackRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::ai {

SiteBossAttackRoot::SiteBossAttackRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossAttackRoot::~SiteBossAttackRoot() = default;

bool SiteBossAttackRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossAttackRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossAttackRoot::calc_() {
    if (!sead::DynamicCast<ksys::act::Actor>(_60[0].getProc(nullptr, nullptr)))
        sub_7100571EB4(*mEquipWeapon_s, 0);
    if (sub_71005DBB60(mActor, 0) == -1)
        sub_710057201C(*mEquipWeapon_s);
    switch (*mEquipWeapon_s) {
    case 0:
        sub_71005721F4();
        break;
    case 1:
        sub_7100572360();
        break;
    case 2:
        sub_71005724C8();
        break;
    case 3:
        sub_7100572634();
        break;
    }
}

void SiteBossAttackRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossAttackRoot::loadParams_() {
    getStaticParam(&mEquipWeapon_s, "EquipWeapon");
}

}  // namespace uking::ai
