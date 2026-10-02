#include "Game/AI/AI/aiPriestBossMetaAIRoot.h"
#include "KingSystem/ActorSystem/Awareness/actAwarenessInstance.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/Map/mapObject.h"
#include "KingSystem/Map/mapObjectLink.h"
#include "KingSystem/Physics/RigidBody/Shape/Cylinder/physCylinderRigidBody.h"

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

// NON_MATCHING: the Flag temporary gets its own stack slot (the original shares it with `arg`); the
// blocks for phases 3 and 4 are laid out in the other order
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
    if (!unit->_78.isOnBit(Unk_7102450fa8::Flag(Unk_7102450fa8::Flag::_5))) {
        Unk_7102450fa8::Unk3 arg;
        if (sub_710052656C(&arg))
            unit->sub_710071964C(arg);
    }
    sub_71005266A0();
    sub_7100526918();
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
bool PriestBossMetaAIRoot::handleMessage_(const ksys::Message& message) {
    if (_138->m4(message))
        return true;
    if (message.getType().value != 0x80000d9)
        return false;

    _138->sub_71007190CC(message.getSource());
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
