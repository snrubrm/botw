#include "Game/AI/aiUnk_71007050e4.h"
#include "Game/AI/aiUnk_71005D6D10.h"
#include "Game/Actor/actWeapon.h"
#include "KingSystem/ActorSystem/actAiActionBase.h"

Unk_71007050e4::Unk_71007050e4(ksys::act::Actor* actor) : _8(actor) {}

Unk_71007050e4::~Unk_71007050e4() = default;

void Unk_71007050e4::sub_71007050F0(ksys::act::ai::ActionBase* action) {
    action->getStaticParam(&_0, "WeaponIdx");
}

void Unk_71007050e4::sub_7100705138(const sead::SafeString* name) {
    sub_71005D7ADC(_8, *_0, 0x100c, name, nullptr, 1, 1, 0, 1, 1.0f, 1.0f);
}

void Unk_71007050e4::sub_7100705188() {
    sub_71005D79AC(_8, *_0, uking::act::Unk_71002edaec(1));
}
