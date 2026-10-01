#include "Game/AI/AI/aiChuchuRoot.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Damage/dmgDamageCallback.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiInlineParam.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::ai {

ChuchuRoot::ChuchuRoot(const InitArg& arg) : EnemyRoot(arg) {}

ChuchuRoot::~ChuchuRoot() = default;

bool ChuchuRoot::init_(sead::Heap* heap) {
    return EnemyRoot::init_(heap);
}

void ChuchuRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyRoot::enter_(params);
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
    // FIXME: CALL _ZNK4ksys3act2ai6RootAi18getAITreeVariable2EPPbRKN4sead14SafeStringBaseIcEE @
    // 0x7100d66968
}

void ChuchuRoot::m34() {
    if (*_218)
        sub_710034E090();
    else
        EnemyRoot::m34();
}

void ChuchuRoot::sub_710034E090() {
    sub_71005D8DE8(mActor, ksys::act::PlayerInfo::getSomeProcLink(), nullptr, nullptr);
    mActor->getActorFlags2().set(ksys::act::Actor::ActorFlag2::_2000000);
    ksys::act::ai::InlineParamPack pack;
    pack.addVec3(getPlayerPosition(), "TargetPos", -1);
    changeChild("ドロップ生成", &pack);
}

}  // namespace uking::ai
