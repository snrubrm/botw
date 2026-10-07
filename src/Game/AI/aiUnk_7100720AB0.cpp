#include "Game/AI/aiUnk_7100720AB0.h"
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actActorParam.h"
#include "KingSystem/Resource/Actor/resResourceGParamList.h"
#include "KingSystem/Resource/GeneralParamList/resGParamListObjectAttack.h"

Unk_7100720ab0::Unk_7100720ab0(ksys::act::Actor* actor) : mActor(actor) {}

Unk_7100720ab0::~Unk_7100720ab0() {}

void Unk_7100720ab0::sub_7100720AF4() {
    _8 = mActor->getParam()->getRes().mGParamList->getAttack()->mImpulse.ref();
    _10 = 0;
}
