#include "Game/AI/AI/aiGerudoQueenBattle.h"
#include "Game/AI/aiUnk_710073033C.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/World/worldEnvMgr.h"
#include "KingSystem/World/worldManager.h"
#include "KingSystem/ActorSystem/actUnk_71024ef620.h"

namespace uking::ai {

GerudoQueenBattle::GerudoQueenBattle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GerudoQueenBattle::~GerudoQueenBattle() = default;

// NON_MATCHING: register numbering (the original keeps `this` in x20 and `&_70` in x19)
bool GerudoQueenBattle::sub_71003F4648() {
    if (!_70.hasProc())
        return false;
    const bool in_range = sub_710073033C(
        mActor, &_70, ksys::world::Manager::instance()->getEnvMgrUnchecked()->get6b548());
    if (!isCurrentChild("雷攻撃無効化"))
        return false;
    ksys::act::acc::PlayerBase player;
    player.getPlayerFromPlayerInfo();
    const bool riding = player.isRidingSandSeal();
    return in_range && riding;
}

bool GerudoQueenBattle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GerudoQueenBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GerudoQueenBattle::leave_() {
    mActor->emitBasicSigOff();
    _40.fade();
    _80->sub_7100EBB518();
    mActor->resetConnectedCalcChild(false);
}

void GerudoQueenBattle::loadParams_() {
    getStaticParam(&mRetireFrame_s, "RetireFrame");
}

bool GerudoQueenBattle::handleMessage_(const ksys::Message* message) {
    const auto type = message->getType();
    switch (type) {
    case ksys::MessageType(0x08000085):
    case ksys::MessageType(0x08000086):
    case ksys::MessageType(0x08000087):
    case ksys::MessageType(0x08000088):
    case ksys::MessageType(0x08000089):
    case ksys::MessageType(0x0800008a):
    case ksys::MessageType(0x0800008b):
    case ksys::MessageType(0x0800008c):
        _fc = type;
        _f8 = true;
        return true;
    case ksys::MessageType(0x0800008d):
        if (_80)
            _80->sub_7100EBB624();
        break;
    case ksys::MessageType(0x0800008e):
        if (_80)
            _80->_60.set(0x10);
        break;
    case ksys::MessageType(0x0800008f):
        if (_80)
            _80->sub_7100EBB60C();
        break;
    case ksys::MessageType(0x08000090):
        if (_88)
            _88 = false;
        if (_89) {
            _80->sub_7100EBB518();
            _89 = false;
        }
        if (_60.hasProc())
            _60.reset();
        break;
    default:
        break;
    }
    return false;
}

}  // namespace uking::ai
