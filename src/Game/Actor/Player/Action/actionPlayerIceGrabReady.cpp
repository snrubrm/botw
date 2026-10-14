#include "Game/Actor/Player/Action/actionPlayerIceGrabReady.h"
#include "KingSystem/ActorSystem/Profiles/actPlayer.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"
#include "Game/Actor/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectLiftable.h"

namespace uking::action {

PlayerIceGrabReady::PlayerIceGrabReady(const InitArg& arg) : PlayerAction(arg) {}

PlayerIceGrabReady::~PlayerIceGrabReady() = default;

// NON_MATCHING: scheduling only (the original keeps the connected-child pointer in a register for the
// `_17f0` store and orders the translation stores differently)
void PlayerIceGrabReady::enter_(ksys::act::ai::InlineParamPack* params) {
    PlayerAction::enter_(params);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x1);
    static_cast<ksys::act::Player*>(mActor)->_cec.set(0x20);
    static_cast<ksys::act::Player*>(mActor)->x_8(false, false);
    static_cast<ksys::act::Player*>(mActor)->m228(false);

    bool had_connected_child = false;
    if (mActor->getConnectedCalcChild()) {
        mActor->resetConnectedCalcChild(false);
        had_connected_child = true;
    }
    static_cast<ksys::act::Player*>(mActor)->_17f0 = had_connected_child;

    if (_20.isAllocatedOrFailed())
        _20.deleteProc();

    ksys::act::InstParamPack pack;
    auto* player = static_cast<ksys::act::Player*>(mActor);
    const sead::Vector3f pos = player->_1770;
    sead::Matrix34f mtx = player->_1b18;
    mtx.setTranslation(pos.x, pos.y + 2.0f, pos.z);
    pack->addMatrix(mtx);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        "IceBlock", ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), &_20, &pack, nullptr,
        1);
}

void PlayerIceGrabReady::leave_() {}

void PlayerIceGrabReady::calc_() {
    static_cast<ksys::act::Player*>(mActor)->actionCommon();
    if (static_cast<ksys::act::Player*>(mActor)->_17f0) {
        static_cast<ksys::act::Player*>(mActor)->_17f0 = 0;
        return;
    }

    if (auto* child = static_cast<ksys::act::Actor*>(mActor->getConnectedCalcChild())) {
        if (!static_cast<ksys::act::Player*>(mActor)->_d11) {
            static_cast<ksys::act::Player*>(mActor)->_d11 = 1;
            static_cast<ksys::act::Player*>(mActor)->_20f8 = child->m38();
            if (auto* body = child->getMainBody())
                static_cast<ksys::act::Player*>(mActor)->_20fc = body->getVolume();
            mActor->getASList()->x_6(25, 0, static_cast<ksys::act::Player*>(mActor)->_20f8);
            mActor->getASList()->goLimpFromHeadShotMaybe(
                49, child->getParam()->getRes().mGParamList->getLiftable()->mLiftType.ref(), 0);
            mActor->getASList()->x_6(17, 0, 0.0f);
            static_cast<ksys::act::Player*>(mActor)->x_23("GrabWait", false, -1.0f);
            _20.releaseAndWakeProc();
            sub_71005DC208(mActor, child, 0);
            sub_71005DC41C(child);
            mActor->sendMessage(*child->getMesTransceiverId(), ksys::MessageType(0x3000011), nullptr,
                                true);
        }
        setFinished();
    } else if (_20.isProcReady()) {
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(_20.getProc()))
            actor->setConnectedCalcParent(mActor, false);
    }
}

bool PlayerIceGrabReady::isChangeable() const {
    return false;
}

}  // namespace uking::action
