#include "Game/AI/aiUnk_7100704914.h"
#include <algorithm>
#include <prim/seadFormatPrint.h>
#include "Game/AI/aiUnk_71005D6D10.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerOrEnemy.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/ActorSystem/actActorSensorUtil.h"
#include "KingSystem/ActorSystem/actAiActionBase.h"
#include "KingSystem/ActorSystem/actAttackSensor.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

Unk_7100704914::Unk_7100704914(ksys::act::Actor* actor) : _30(actor) {}

Unk_7100704914::~Unk_7100704914() = default;

void Unk_7100704914::sub_7100704944() {
    _38 = false;
}

// NON_MATCHING: the original loads *cNullChar before the first name byte (isEmpty() loads them the other way round)
void Unk_7100704914::sub_710070507C() {
    if (!_0[0].isEmpty())
        sub_71007A2D7C(_30, _0[0]);
    if (!_0[1].isEmpty())
        sub_71007A2D7C(_30, _0[1]);
}

void Unk_7100704914::sub_7100704D84(ksys::act::ai::ActionBase* action) {
    sead::FixedSafeString<64> key;
    for (u32 i = 0; i < 2; i++) {
        (sead::StringCutOffPrintFormatter(&key) << "AtkBodyName%d", i) << sead::flush;
        action->getStaticParam(&_0[i], key);
    }
    action->getStaticParam(&_20, "CoBodyName");
}

void Unk_7100704914::sub_7100704F1C(const sead::SafeString* name) {
    sead::FixedSafeString<9> type;
    sub_71005D7C94(&type, name);
    auto* sensor = getActorAttackSensor(_30);
    const s32 power = std::max(static_cast<ksys::act::PlayerOrEnemy*>(_30)->getEnemyAtkPower(), 1);
    const auto* attack = _30->getParam()->getRes().mGParamList->getAttack();
    sensor->activateAttackSensor(0x2000, 0x9104, power, attack->mImpulse.ref(), 0.0f,
                                 attack->mGuardBreakPower.ref(), 1, sub_71007A3A8C(&type), false, 1,
                                 -1);
    if (!_0[0].isEmpty())
        sub_71007A2C30(_30, _0[0], nullptr);
    if (!_0[1].isEmpty())
        sub_71007A2C30(_30, _0[1], nullptr);
}
