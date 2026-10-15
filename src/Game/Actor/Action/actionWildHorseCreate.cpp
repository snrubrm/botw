#include "Game/Actor/Action/actionWildHorseCreate.h"
#include <random/seadGlobalRandom.h>
#include <limits>
#include "Game/Actor/Player/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorSystem.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Map/mapPlacementActors.h"
#include "KingSystem/Map/mapPlacementMgr.h"

namespace uking::action {

WildHorseCreate::WildHorseCreate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WildHorseCreate::~WildHorseCreate() {
    _38.freeBuffer();
    _48.freeBuffer();
}

bool WildHorseCreate::init_(sead::Heap* heap) {
    s32 num = *mWildHorseCreateNum_m;
    if (num >= 1) {
        if (num > *mMaxCreateNum_s)
            num = *mMaxCreateNum_s;
    } else {
        const s32 min = *mMinCreateNum_s;
        const s32 max = *mMaxCreateNum_s;
        num = sead::GlobalRandom::instance()->getS32Range(min, max + 1);
    }
    if (num >= 1) {
        _38.tryAllocBuffer(num, heap);
        _48.tryAllocBuffer(num, heap);
    }
    _5c = 0;
    return true;
}

void WildHorseCreate::enter_(ksys::act::ai::InlineParamPack* params) {
    auto* manager = ksys::map::PlacementMgr::instance();
    if (manager && manager->mPlacementActors) {
        const f32 distance = ksys::map::getActorTraverseDist("GameRomHorse01", 1.0f);
        _58 = distance * distance;
    }
}

void WildHorseCreate::leave_() {
    for (s32 i = _48.size() - 1; i >= 0; --i)
        _48[i].deleteProc();
    for (s32 i = 0; i < _38.size(); ++i) {
        ksys::act::ActorLinkConstDataAccess accessor;
        if (ksys::act::acquireActor(&_38[i], &accessor)) {
            mActor->sendMessage(*accessor.getMessageTransceiverId(), ksys::MessageType(0x3800017),
                                nullptr, true);
        }
    }
}

void WildHorseCreate::loadParams_() {
    getStaticParam(&mMinCreateNum_s, "MinCreateNum");
    getStaticParam(&mMaxCreateNum_s, "MaxCreateNum");
    getMapUnitParam(&mWildHorseCreateNum_m, "WildHorseCreateNum");
}

// NON_MATCHING: position registers and creation-state conditional selection differ.
void WildHorseCreate::calc_() {
    switch (_5c) {
    case 0: {
        auto* system = ksys::act::ActorSystem::instance();
        if (!system || !system->getPlayerLink())
            break;
        const f32 x = mActor->getMtx()(0, 3);
        const f32 z = mActor->getMtx()(2, 3);
        auto* player = system->getPlayerLink()->getPlayer();
        if (!player)
            break;
        const f32 dx = x - player->getMtx()(0, 3);
        const f32 dz = z - player->getMtx()(2, 3);
        if (dx * dx + dz * dz < _58)
            _5c = sub_71002B9BC0() ? 1 : 4;
        break;
    }
    case 1: {
        const s32 count = _48.size();
        for (s32 i = 0; i < count; ++i) {
            if (!_48[i].isProcReady() && !_48[i].hasProcCreationFailed())
                return;
        }
        sub_71002B9F00();
        _5c = 2;
        break;
    }
    case 2: {
        f32 distance = std::numeric_limits<f32>::infinity();
        auto* system = ksys::act::ActorSystem::instance();
        if (system && system->getPlayerLink()) {
            const f32 x = mActor->getMtx()(0, 3);
            const f32 z = mActor->getMtx()(2, 3);
            if (auto* player = system->getPlayerLink()->getPlayer()) {
                const f32 dx = x - player->getMtx()(0, 3);
                const f32 dz = z - player->getMtx()(2, 3);
                distance = dx * dx + dz * dz;
            }
        }
        if (distance > _58) {
            for (s32 i = 0; i < _38.size(); ++i) {
                ksys::act::ActorLinkConstDataAccess accessor;
                if (ksys::act::acquireActor(&_38[i], &accessor)) {
                    mActor->sendMessage(*accessor.getMessageTransceiverId(),
                                        ksys::MessageType(0x3800017), nullptr, true);
                }
            }
            _5c = 3;
        }
        break;
    }
    case 3: {
        const s32 count = _38.size();
        for (s32 i = 0; i < count; ++i) {
            if (_38[i].hasProc())
                return;
        }
        _5c = 0;
        break;
    }
    }
}

}  // namespace uking::action
