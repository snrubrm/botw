#include "Game/AI/AI/aiChuchuRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/AI/aiUnk_71006F5B14.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/AS/ASList.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actChemical.h"
#include "KingSystem/Physics/RigidBody/physRigidBody.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actAiRoot.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

ChuchuRoot::ChuchuRoot(const InitArg& arg) : EnemyRoot(arg) {}

ChuchuRoot::~ChuchuRoot() = default;

bool ChuchuRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void ChuchuRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);

    auto* actor = mActor;
    if (auto* body = actor->findPhysicsBodyByName(sub_71007A250C()->cstr(), "BgSensor"))
        body->setFlag100000();

    if (auto* as_list = mActor->getASList()) {
        const s32 slot = *mSubASSlot_s;
        if (as_list->x_1(0, slot) != mSubAS_s)
            as_list->startAnimationMaybe(-1.0f, -1.0f, mSubAS_s, 0, slot, true);
    }

    if (auto* chemical = mActor->getChemicalStuff()) {
        chemical->sub_7100D91098(false);
        chemical->sub_7100D90B78();
        chemical->_bf |= 2;
        chemical->sub_7100D90AF4(false);
    }

    setDamageCallbackTiming(mActor, 4, &_220);
}

void ChuchuRoot::calc_() {
    sub_71006F6144(mActor);
    EnemyRoot::calc_();
}

void ChuchuRoot::leave_() {
    sub_71005DA114(mActor, &_220);
    EnemyRoot::leave_();
}

void ChuchuRoot::loadParams_() {
    EnemyRoot::loadParams_();
    getStaticParam(&mSubASSlot_s, "SubASSlot");
    getStaticParam(&mChemicalScaleTime_s, "ChemicalScaleTime");
    getStaticParam(&mClothStiffness30_s, "ClothStiffness30");
    getStaticParam(&mClothStiffness20_s, "ClothStiffness20");
    getStaticParam(&mSubAS_s, "SubAS");
    getStaticParam(&mChemicalFieldKey_s, "ChemicalFieldKey");
    mActor->getRootAi()->getAITreeVariable2(&_218, "IsDrop");
}

void ChuchuRoot::m34(ksys::act::ai::InlineParamPack* params) {
    if (*_218)
        changeToCreateDrop();
    else
        EnemyRoot::m34(params);
}

void ChuchuRoot::changeToCreateDrop() {
    sub_71005D8DE8(mActor, ksys::act::PlayerInfo::getSomeProcLink(), nullptr, nullptr);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(getPlayerPosition(), "TargetPos", -1);
    changeChild("ドロップ生成", &pack);
}

}  // namespace uking::ai
