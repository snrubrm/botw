#include "Game/AI/AI/aiInsectRoot.h"
#include "Game/Damage/dmgDamageManagerBase.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/CharacterController/physCharacterController.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectInsect.h"
#include "KingSystem/Utils/Thread/Message.h"
#include "KingSystem/World/worldManager.h"
#include <cfloat>

// 0x71006e8610 (declaration only; defined in the actor-bind TU): whether the actor's bind object at
// +0xd8 has byte 0x9a8 set.
bool sub_71006E8610(ksys::act::Actor* actor);

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

bool InsectRoot::handleMessage_(const ksys::Message* message) {
    if (message->getType() != 0x3000009 || _10c || isCurrentChild("死亡"))
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

// 0x710044b36c
// NON_MATCHING: the final _b8 stores use three str where the original pairs x/y into stp (tried
// operator-, set() and braced assignment with and without named temps; snippet builds pair, the full
// function does not). Everything else in all paths matches.
void InsectRoot::calc_() {
    auto* awareness = mActor->get548();
    if (awareness->_18._48 <= 0)
        awareness->_18._48 = 1;
    awareness->_18._44 |= 1;

    if (!sub_71006E8610(mActor)) {
        const int level = ksys::world::Manager::instance()->getIgnitedLevel(
            mActor->getMtx().getTranslation());
        const auto* insect = mActor->getParam()->getRes().mGParamList->getInsect();
        const s32 threshold = insect ? insect->mFireResistanceLevel.ref() : 0;
        if (level > threshold) {
            if (isCurrentChild("逃走") || isCurrentChild("死亡")) {
                _100.update();
                if (_100.value > FLT_EPSILON)
                    return;
                mActor->deleteEx(ksys::act::Actor::DeleteType::_1,
                                 ksys::act::BaseProc::DeleteReason::_0, nullptr);
                return;
            }
            _100 = ksys::Timer(20.0f, 20.0f);
            _c4 = ksys::Timer(-1.0f, -1.0f);
            const sead::Vector3f trans = mActor->getMtx().getTranslation();
            const sead::Vector3f front = mActor->getMtx().getBase(2);
            _b8.set(trans.x - front.x, trans.y - front.y, trans.z - front.z);
            m39();
            return;
        }
    }

    if (mActor->get68f() && *mIsEscapeInWater_s) {
        if (isCurrentChild("逃走") || isCurrentChild("死亡")) {
            SimpleWildlifeRoot::calc_();
        } else {
            _c4 = ksys::Timer(-1.0f, -1.0f);
            const sead::Vector3f trans = mActor->getMtx().getTranslation();
            const sead::Vector3f front = mActor->getMtx().getBase(2);
            _b8.set(trans.x - front.x, trans.y - front.y, trans.z - front.z);
            m39();
        }
    } else if (isChangeable() && getCurrentChild()->isFailed()) {
        _c4 = ksys::Timer(-1.0f, -1.0f);
        const sead::Vector3f trans = mActor->getMtx().getTranslation();
        const sead::Vector3f front = mActor->getMtx().getBase(2);
        _b8.set(trans.x - front.x, trans.y - front.y, trans.z - front.z);
        m39();
    } else {
        SimpleWildlifeRoot::calc_();
    }
}

}  // namespace uking::ai
