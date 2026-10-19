#include "Game/Actor/Query/queryCheckPictureBookVacancy.h"
#include <evfl/Query.h>
#include "Game/UI/uiUtils.h"
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckPictureBookVacancy::CheckPictureBookVacancy(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPictureBookVacancy::~CheckPictureBookVacancy() = default;

// The query's category is the actor category; the vacancy helpers take the photo item name.
// NON_MATCHING: only the final return differs (the original branches to a `return 1` block and shares
// the `return 0` block with the manager check; ours uses cset).
int CheckPictureBookVacancy::doQuery() {
    if (!ksys::gdt::Manager::instance())
        return 0;

    const char* photo_name;
    if (mCategory == "Creature")
        photo_name = "Obj_Photo_Animal";
    else if (mCategory == "Enemy")
        photo_name = "Obj_Photo_Enemy";
    else if (mCategory == "Boss")
        photo_name = "Obj_Photo_BossEnemy";
    else if (mCategory == "Material")
        photo_name = "Obj_Photo_Material";
    else if (mCategory == "Weapon")
        photo_name = "Obj_Photo_Weapon";
    else
        photo_name = "Obj_Photo_Other";

    const sead::SafeString category(photo_name);
    const s32 vacancy = uking::ui::sub_7100A98808(uking::ui::sub_7100A985DC(category));
    if (*mVacancyNum > vacancy)
        return 0;
    return 1;
}

void CheckPictureBookVacancy::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "VacancyNum");
    loadString(arg.param_accessor, "Category");
}

void CheckPictureBookVacancy::loadParams() {
    getDynamicParam(&mVacancyNum, "VacancyNum");
    getDynamicParam(&mCategory, "Category");
}

}  // namespace uking::query
