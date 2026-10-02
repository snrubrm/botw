#include "Game/AI/AI/aiInsectRoot.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Utils/Thread/Message.h"

namespace uking::ai {

InsectRoot::InsectRoot(const InitArg& arg) : SimpleWildlifeRoot(arg) {}

InsectRoot::~InsectRoot() = default;

bool InsectRoot::init_(sead::Heap* heap) {
    return SimpleWildlifeRoot::init_(heap);
}

void InsectRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleWildlifeRoot::enter_(params);
    _100 = ksys::Timer(20.0f, 20.0f);
    _10c = false;
    if (auto* cc = mActor->getCharacterController()) {
        sead::Vector3f pos;
        if (cc->sub_7100F62EFC(&pos, 0)) {
            f32 value;
            cc->sub_7100F62E74(&value, 0);
        }
    }
}

void InsectRoot::leave_() {
    SimpleWildlifeRoot::leave_();
}

void InsectRoot::loadParams_() {
    SimpleWildlifeRoot::loadParams_();
    getStaticParam(&mIsEscapeInWater_s, "IsEscapeInWater");
}

bool InsectRoot::handleMessage_(const ksys::Message& message) {
    if (message.getType() != 0x3000009 || _10c || isCurrentChild("死亡"))
        return false;

    if (isCurrentChild("逃走"))
        sub_7100343510();
    _c4.reset(1000000.0f);
    _10c = true;
    return true;
}

bool InsectRoot::m34() {
    if (_10c)
        return false;
    return SimpleWildlifeRoot::m34();
}

bool InsectRoot::m35() {
    auto* damage_mgr = mActor->getDamageMgr();
    if (damage_mgr && damage_mgr->getField54() == 0x1c)
        return false;
    return SimpleWildlifeRoot::m35();
}

void InsectRoot::m40() {
    if (isCurrentChild("ロケーターわき出し")) {
        if (auto* cc = mActor->getCharacterController()) {
            const sead::Vector3f impulse = mActor->getMtx().getBase(1) * cc->sub_7100F60370() * 7.0f;
            cc->sub_7100F60398(impulse);
        }
    }
    SimpleWildlifeRoot::m40();
}

}  // namespace uking::ai
