#include "Game/Actor/AI/aiPriestBossMetaAIRoot.h"
#include "Game/AOC/aocHardModeManager.h"
#include "Game/Actor/actEnemy.h"
#include "Game/UI/uiScreens.h"
#include "KingSystem/ActorSystem/actLifeRecoveryInfo.h"
#include "Game/Actor/Player/actPlayerBase.h"
#include "Game/Actor/Player/actPlayerInfo.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/Attention/actActorAttention.h"
#include "KingSystem/ActorSystem/Attention/actAttClient.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorLinkConstDataAccess.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Physics/RigidBody/physRigidBodyCylinder.h"

namespace uking::ai {

sead::SafeArray<sead::SafeString, 5> sUnk_71025bb7e0{{
    "段階_通常",
    "段階_分身",
    "段階_巨大化",
    "段階_祭り",
    "段階_終了",
}};
sead::SafeArray<sead::SafeString, 5> sUnk_71025bb830{{"Main", "Main", "Main", "Main", "Main"}};
sead::SafeArray<sead::SafeString, 5> sUnk_71025bb880{{"0", "1", "", "", ""}};
const char* sUnk_7102414930 = "Demo644_";

PriestBossMetaAIRoot::PriestBossMetaAIRoot(const InitArg& arg) : PriestBossMeta(arg) {}

PriestBossMetaAIRoot::~PriestBossMetaAIRoot() {
    if (_138) {
        delete _138;
        _138 = nullptr;
    }
}

bool PriestBossMetaAIRoot::init_(sead::Heap* heap) {
    if (!PriestBossMeta::init_(heap))
        return false;

    Unk_7102450fa8::Unk2 arg;
    arg._10 = mActor;
    mActor->getMtx().getTranslation(arg._0);
    arg._18 = &mBowActorName_s;
    arg._20 = &mWeaponActorName_s;
    arg._28 = &mThunderActorName_s;
    _138 = Unk_7102450fa8::sub_7100718360(heap);
    if (!_138)
        return false;
    if (!_138->sub_71007183A4(heap, arg))
        return false;

    *static_cast<Unk_7102450fa8**>(mPriestBossMetaAIUnit_a) = _138;
    *mMetaAILife_a = *mLife_s;
    *mMetaAIMaxLife_a = *mLife_s;
    return true;
}

void PriestBossMetaAIRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossMeta::enter_(params);
    _140 = *mPriestBossStartPhase_m;
    changeChild(sUnk_71025bb7e0[_140].cstr());
    if (auto* awareness = mActor->getAwareness())
        awareness->enable();
    _144 = -1;
}

// NON_MATCHING: block layout only — the original lays out the `setFinished()` block at the very end
// and the phase-3 block after the phase-4 one (the Flag temporary / `arg` slot sharing is solved by the
// by-value `isFlagOn` helper)
void PriestBossMetaAIRoot::calc_() {
    PriestBossMeta::calc_();
    sub_710052618C();

    auto* child = getCurrentChild();
    if (child->isFinished() || child->isFailed()) {
        if (_140 == Unk_7102450fa8::Phase::_4) {
            setFinished();
        } else {
            if (_140 == Unk_7102450fa8::Phase::_0)
                _140 = Unk_7102450fa8::Phase::_1;
            else if (_140 == Unk_7102450fa8::Phase::_1)
                _140 = Unk_7102450fa8::Phase::_2;
            else if (_140 == Unk_7102450fa8::Phase::_2)
                _140 = Unk_7102450fa8::Phase::_3;
            else
                _140 = Unk_7102450fa8::Phase::_4;
            changeChild(sUnk_71025bb7e0[_140].cstr());
        }
    }

    auto* unit = sub_7100525A88();
    if (!unit->isFlagOn(Unk_7102450fa8::Flag::_5)) {
        Unk_7102450fa8::Unk3 arg;
        if (sub_710052656C(&arg))
            unit->sub_710071964C(arg);
    }
    sub_71005266A0();
    sub_7100526918();
}

// NON_MATCHING: the original branches straight to the call / the _89 store instead of testing `ok`; life / max life
// registers swapped
void PriestBossMetaAIRoot::sub_710052618C() {
    const int life = *mMetaAILife_a;
    const int max_life = *mMetaAIMaxLife_a;
    ui::BossGaugeInfo info;
    info.name = mActor->getName();
    info.value = life;
    info.maxValue = max_life;
    info.actorId = mActor->getId();
    info.layoutName = mUniqueNameMessageLabel_m;

    auto* hard_mode = aoc::HardModeManager::instance();
    if (hard_mode && hard_mode->checkFlag(aoc::HardModeManager::Flag::EnableHardMode) &&
        hard_mode->isHardModeChangeOn(aoc::HardModeManager::HardModeChange::EnableLifeRegen)) {
        ksys::act::BaseProcLink link;
        int idx;
        bool ok = true;
        switch (_140) {
        case Unk_7102450fa8::Phase::_0:
            idx = 0;
            break;
        case Unk_7102450fa8::Phase::_1:
            idx = 2;
            break;
        case Unk_7102450fa8::Phase::_2:
        case Unk_7102450fa8::Phase::_3:
            idx = 1;
            break;
        default:
            ok = false;
            break;
        }
        if (ok) {
            ksys::act::ActorLinkConstDataAccess accessor;
            ok = sub_7100525B18(idx, &accessor) && accessor.linkAcquire(&link);
        }
        if (ok)
            sub_71005263F8(&info, &link);
        else
            info._89 = false;
    } else {
        info._89 = false;
    }
    info._88 = false;
    ui::sub_7100A96254(&info);
}

// NON_MATCHING: the flag mask is computed after the getLifeRecoverInfo() call in the original
void PriestBossMetaAIRoot::sub_71005263F8(ui::BossGaugeInfo* info, ksys::act::BaseProcLink* link) {
    auto* actor = sead::DynamicCast<ksys::act::Actor>(link->getProc(nullptr, nullptr));
    auto* enemy = sead::DynamicCast<act::Enemy>(actor);
    if (enemy && enemy->getLifeRecoverInfo()) {
        using Flag = ksys::act::LifeRecoverInfo::Flag;
        info->_89 = (enemy->getLifeRecoverInfo()->mFlags & (1 << int(Flag(Flag::_0)))) != 0;
        info->value += enemy->getLifeRecoverInfo()->mExtraHp1;
    } else {
        info->_89 = false;
    }
}

// NON_MATCHING: payload enum round trip, flag temporary slots and evaluation order.
void PriestBossMetaAIRoot::sub_71005266A0() {
    using Flag = Unk_7102450fa8::Flag;
    auto* player = act::PlayerInfo::instance()->getPlayer();
    _128.update();
    if (player->_d18 != -1) {
        if (_144 == -1) {
            {
                sead::ScopedLock<sead::JobQueueLock> lock(&_b8._18.mLock);
                _b8._18._c = true;
                _b8._18._8 = 1;
            }
            _b8.sub_710070DBB0(_138->_1a0, true);
            _138->_78.resetBit(Flag(Flag::_6));
            for (s32 idx = 11; idx < 19; ++idx) {
                ksys::act::ActorLinkConstDataAccess accessor;
                if (sub_7100525B18(idx, &accessor)) {
                    {
                        sead::ScopedLock<sead::JobQueueLock> lock(&_e8._18.mLock);
                        _e8._18._0 = 1;
                        _e8._18._4 = sead::Vector3f::zero;
                    }
                    _e8.sub_710070DBB0(*accessor.getMessageTransceiverId(), false);
                }
            }
        }
        if (player->_d18 != -1) {
            _128.value = *mPlayerRecoverFromFallFrames_s;
            _128.previous_value = _128.value;
            _144 = player->_d18;
        } else {
            _144 = -1;
        }
    } else {
        _144 = -1;
    }
    if (sub_7100525A88()) {
        sub_7100525A88()->_78.changeBit(Flag(Flag::_11), !(_128.value <= sead::Mathf::epsilon()));
        auto* unit = sub_7100525A88();
        unit->_78.changeBit(Flag(Flag::_15), player->isDarukProtectionEnabled());
    }
}

// NON_MATCHING: flag temporary stack slots and cached attention pointer.
void PriestBossMetaAIRoot::sub_7100526918() {
    using Flag = Unk_7102450fa8::Flag;
    sub_7100525A88()->_78.resetBit(Flag(Flag::_12));
    ksys::act::ActorLinkConstDataAccess accessor;
    ksys::act::BaseProcLink link;
    if (sub_7100525A88()->sub_71007194D4(1, &accessor) && accessor.linkAcquire(&link)) {
        if (auto* actor = sead::DynamicCast<ksys::act::Actor>(link.getProc(nullptr, nullptr))) {
            const auto* attention = actor->getAttention();
            if (attention && attention->getClientByName("LockOn") &&
                attention->getClientByName("LockOn")->sub_7100D7251C(1)) {
                sub_7100525A88()->_78.setBit(Flag(Flag::_12));
            }
        }
    }
}

bool PriestBossMetaAIRoot::sub_710052656C(Unk_7102450fa8::Unk3* out) {
    auto* map_object = mActor->getMapObject();
    if (!map_object)
        return false;

    auto* link_data = map_object->getLinkData();
    if (!link_data || link_data->mObjects.size() < 1)
        return false;

    auto* object = link_data->mObjects[0];
    if (!object)
        return false;

    auto* actor = object->tryGetActor(false);
    if (!actor)
        return false;

    out->_10 = *actor->getMesTransceiverId();
    out->_0 = actor->getMtx().getTranslation();
    auto* body = sead::DynamicCast<ksys::phys::CylinderRigidBody>(
        actor->findPhysicsBodyByName("GeneralSensor", "BattleArea"));
    f32 radius = 50.0f;
    if (body)
        radius = body->getRadius();
    out->_c = radius;
    return true;
}

void PriestBossMetaAIRoot::leave_() {
    PriestBossMeta::leave_();
    if (_138)
        _138->sub_710071918C();
    if (auto* awareness = mActor->getAwareness())
        awareness->sleep();
}

// NON_MATCHING: the original has a discarded stack round trip of a zero (SEAD_ENUM?) value
// before the payload stores (same in every writer of this payload: PriestBossGiantDownSeq, ...)
bool PriestBossMetaAIRoot::handleMessage_(const ksys::Message* message) {
    if (_138->m4(*message))
        return true;
    if (message->getType() != 0x80000d9)
        return false;

    _138->sub_71007190CC(message->getSource());
    {
        sead::ScopedLock<sead::JobQueueLock> lock(&_b8._18.mLock);
        _b8._18._c = false;
        _b8._18._8 = 1;
    }
    _b8.sub_710070DBB0(_138->_1a0, true);
    return true;
}

void PriestBossMetaAIRoot::loadParams_() {
    PriestBossMeta::loadParams_();
    getStaticParam(&mLife_s, "Life");
    getStaticParam(&mPlayerRecoverFromFallFrames_s, "PlayerRecoverFromFallFrames");
    getStaticParam(&mBowActorName_s, "BowActorName");
    getStaticParam(&mArrowActorName_s, "ArrowActorName");
    getStaticParam(&mWeaponActorName_s, "WeaponActorName");
    getStaticParam(&mThunderActorName_s, "ThunderActorName");
    getMapUnitParam(&mPriestBossStartPhase_m, "PriestBossStartPhase");
    getMapUnitParam(&mUniqueNameMessageLabel_m, "UniqueNameMessageLabel");
}

}  // namespace uking::ai
