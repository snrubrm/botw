#include "Game/AI/aiUnk_7100724C64.h"
#include "Game/Actor/actEnemy.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

// 0x71024511f8
static const char* const sUnk_71024511f8[] = {
    "StalHead", "StalLeftArm", "StalChin", "StalRib1", "StalRib2", "StalRib3", "StalRib4",
};

// NON_MATCHING: the original builds the part-name SafeString before computing &enemy->_1128
bool sub_7100724C80(ksys::act::Actor* actor, sead::Heap* heap, u32 part) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return false;
    enemy->_1128.sub_7100D3CED8(sUnk_71024511f8[part], heap);
    return true;
}

uking::act::Enemy* sub_7100724D7C(ksys::act::Actor* actor) {
    if (actor) {
        auto* enemy = sead::DynamicCast<uking::act::Enemy>(actor);
        if (ksys::act::hasTag(enemy, ksys::act::tags::StalfosParts))
            return enemy;
    }
    return nullptr;
}

// NON_MATCHING: the original builds the part-name SafeString before computing &enemy->_1128
bool sub_7100724E1C(ksys::act::Actor* actor, u32 part) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return false;
    enemy->_1128.sub_7100D3CFEC(sUnk_71024511f8[part]);
    return true;
}

// NON_MATCHING: the original builds the part-name SafeString before computing &enemy->_1128
ksys::act::BaseProcLink& sub_7100724F08(ksys::act::Actor* actor, u32 part) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return ksys::act::getDummyBaseProcLink();
    return enemy->_1128.getActorPartsActor(sUnk_71024511f8[part]);
}

// NON_MATCHING: the original builds the part-name SafeString before computing &enemy->_1128
bool sub_7100724FE8(ksys::act::Actor* actor, ksys::act::BaseProc* proc, u32 part) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return false;
    return enemy->_1128.sub_7100D3D108(sUnk_71024511f8[part], proc);
}

// NON_MATCHING: the original builds the part-name SafeString before computing &enemy->_1128
bool sub_71007250E4(ksys::act::Actor* actor, u32 part) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return false;
    return enemy->_1128.sub_7100D3D2B4(sUnk_71024511f8[part]);
}

const char* sub_71007251D0() {
    return sUnk_71024511f8[0];
}

const char* sub_71007251DC() {
    return sUnk_71024511f8[1];
}

// NON_MATCHING: the original builds the part-name SafeString before computing &enemy->_1128
bool sub_71007251E8(ksys::act::Actor* actor, sead::Heap* heap) {
    return sub_7100724C80(actor, heap, 0);
}

// NON_MATCHING: the original builds the part-name SafeString before computing &enemy->_1128
bool sub_71007252D4(ksys::act::Actor* actor, sead::Heap* heap) {
    return sub_7100724C80(actor, heap, 1);
}

// NON_MATCHING: the original builds the part-name SafeString before computing &enemy->_1128
bool sub_71007253C0(ksys::act::Actor* actor) {
    return sub_7100724E1C(actor, 0);
}

// NON_MATCHING: the original builds the part-name SafeString before computing &enemy->_1128
bool sub_71007254A4(ksys::act::Actor* actor) {
    return sub_7100724E1C(actor, 1);
}

ksys::act::BaseProcLink& sub_7100725588(ksys::act::Actor* actor) {
    return sub_7100724F08(actor, 0);
}

ksys::act::BaseProcLink& sub_71007255A0(ksys::act::Actor* actor) {
    return sub_7100724F08(actor, 1);
}

// NON_MATCHING: the original builds the part-name SafeString before computing &enemy->_1128
bool sub_71007255B8(ksys::act::Actor* actor, ksys::act::BaseProc* proc) {
    return sub_7100724FE8(actor, proc, 0);
}

// NON_MATCHING: the original builds the part-name SafeString before computing &enemy->_1128
bool sub_71007256A4(ksys::act::Actor* actor, ksys::act::BaseProc* proc) {
    return sub_7100724FE8(actor, proc, 1);
}

// NON_MATCHING: the original builds the part-name SafeString before computing &enemy->_1128
bool sub_7100725790(ksys::act::Actor* actor, const ksys::act::BaseProcLink& link) {
    auto* enemy = sub_7100724D7C(actor);
    if (!enemy)
        return false;
    return enemy->_1128.sub_7100D3D1E0(sUnk_71024511f8[0], link);
}

// NON_MATCHING: the original builds the part-name SafeString before computing &enemy->_1128
bool sub_710072587C(ksys::act::Actor* actor) {
    return sub_71007250E4(actor, 0);
}
