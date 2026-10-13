#include "Game/AI/Action/actionItemAmiiboSelectDropTable.h"
#include "Game/gameAmiiboMgr.h"
#include "Game/UI/uiUtils.h"
#include "KingSystem/ActorSystem/actActorCreator.h"
#include "KingSystem/ActorSystem/actActorHeapUtil.h"
#include "KingSystem/ActorSystem/actInstParamPack.h"

namespace uking::action {

ItemAmiiboSelectDropTable::ItemAmiiboSelectDropTable(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ItemAmiiboSelectDropTable::~ItemAmiiboSelectDropTable() = default;

bool ItemAmiiboSelectDropTable::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

// NON_MATCHING: whole AmiiboInfo assignment combines the ID/data copies; condition scheduling differs.
void ItemAmiiboSelectDropTable::enter_(ksys::act::ai::InlineParamPack* params) {
    const bool new_day = AmiiboMgr::instance()->oneDayHasPassed();
    AmiiboInfo info;
    info = AmiiboMgr::instance()->_148.mInfo;
    _1e0 = s32(info._0);
    _1e4 = s32(info._4);
    const bool unlimited = AmiiboMgr::instance()->noAmiiboUseLimit();
    const s32 count = AmiiboMgr::instance()->queryHistoryToday(info, 0);
    if (!new_day && count - s32(unlimited) > 0) {
        ui::showInfoOverlay(25);
        setFailed();
        mFlags.set(Flag::Changeable);
    } else {
        AmiiboMgr::instance()->registerAmiibo(info);
    }
}

void ItemAmiiboSelectDropTable::leave_() {
    ksys::act::ai::Action::leave_();
}

void ItemAmiiboSelectDropTable::loadParams_() {
    getStaticParam(&mTableCommon_s, "TableCommon");
    getStaticParam(&mTableGanondorf_s, "TableGanondorf");
    getStaticParam(&mTableToonLink_s, "TableToonLink");
    getStaticParam(&mTableSheik_s, "TableSheik");
    getStaticParam(&mTableLink_s, "TableLink");
    getStaticParam(&mTableZelda_s, "TableZelda");
    getStaticParam(&mTableWolfLink_s, "TableWolfLink");
    getStaticParam(&mTableGuardian_s, "TableGuardian");
    getStaticParam(&mTableBokoblin_s, "TableBokoblin");
    getStaticParam(&mTableCross_Ganondorf_s, "TableCross_Ganondorf");
    getStaticParam(&mTableCross_ToonLink_s, "TableCross_ToonLink");
    getStaticParam(&mTableCross_Sheik_s, "TableCross_Sheik");
    getStaticParam(&mTableCross_Link_s, "TableCross_Link");
    getStaticParam(&mTableCross_Zelda_s, "TableCross_Zelda");
    getStaticParam(&mTableKing_WolfLink_s, "TableKing_WolfLink");
    getStaticParam(&mTableKing_Link_Bow_s, "TableKing_Link_Bow");
    getStaticParam(&mTableKing_Link_Horse_s, "TableKing_Link_Horse");
    getStaticParam(&mTableKing_Zelda_Doctor_s, "TableKing_Zelda_Doctor");
    getStaticParam(&mTableKing_Guardian_s, "TableKing_Guardian");
    getStaticParam(&mTableKing_Bokoblin_s, "TableKing_Bokoblin");
    getStaticParam(&mTableKing30th_Link_Ocarina_s, "TableKing30th_Link_Ocarina");
    getStaticParam(&mTableKing30th_Link_Majora_s, "TableKing30th_Link_Majora");
    getStaticParam(&mTableKing30th_Link_Takt_s, "TableKing30th_Link_Takt");
    getStaticParam(&mTableKing30th_Zelda_Takt_s, "TableKing30th_Zelda_Takt");
    getStaticParam(&mTableKing30th_Link_Twilight_s, "TableKing30th_Link_Twilight");
    getStaticParam(&mTableKing30th_Link_Skyward_s, "TableKing30th_Link_Skyward");
    getStaticParam(&mTableKing30th_Link_Dot_s, "TableKing30th_Link_Dot");
    getMapUnitParam(&mAmiiboCharacterId_m, "AmiiboCharacterId");
    getMapUnitParam(&mAmiiboNumberingId_m, "AmiiboNumberingId");
}

// NON_MATCHING: native copied indices and InstParamPack use different stack offsets.
void ItemAmiiboSelectDropTable::calc_() {
    if (isFinished() || isFailed())
        return;
    const s32 character_id = _1e0;
    const s32 numbering_id = _1e4;
    const sead::SafeString actor_name = sub_71001C0E60(&character_id, &numbering_id);
    ksys::act::InstParamPack pack;
    pack->addPosition(AmiiboMgr::instance()->_9c);
    ksys::act::ActorCreator::instance()->requestCreateActor(
        actor_name.cstr(), ksys::act::ActorHeapUtil::instance()->getBaseProcHeap(), nullptr,
        &pack, nullptr, 2);
    setFinished();
}

}  // namespace uking::action
