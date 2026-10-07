#include "KingSystem/Sound/sndMgr.h"
#include <devenv/seadEnvUtil.h>
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace ksys::snd {

// The original text lookup at 0x710105ef9c is a ten-entry SEAD_ENUM.
SEAD_ENUM(Unk_710105ef9c, SameAsSystem, JPja, USen, EUfr, USfr, EUde, EUes, USes, EUit, EUru)

// The initializer at 0x710105f6c4 writes this prefix before the language string.
// The query at 0x710105e7b4 addresses the string at +0x18 in the same record.
struct Unk_71026157c0 {
    util::InitConstants mConstants;
    util::InitTimeInfo mInitTimeInfo;
    sead::SafeString mVoiceLanguage{"VoiceLanguage"};
};
static Unk_71026157c0 sVoiceData;

const char* sub_710105E898(sead::RegionLanguageID language, bool* flag) {
    if (flag)
        *flag = false;
    switch (language.value()) {
    case sead::RegionLanguageID::USfr:
        if (flag)
            *flag = true;
        return sead::RegionLanguageID::text(sead::RegionLanguageID::EUfr);
    case sead::RegionLanguageID::EUen:
    case sead::RegionLanguageID::EUnl:
        return sead::RegionLanguageID::text(sead::RegionLanguageID::USen);
    case sead::RegionLanguageID::KRko:
    case sead::RegionLanguageID::CNzh:
    case sead::RegionLanguageID::TWzh:
        return sead::RegionLanguageID::text(sead::RegionLanguageID::JPja);
    default:
        return language.text();
    }
}


// NON_MATCHING: the zero-language branch moves before the USfr test and flag-setting exits merge.
const char* sub_710105E7B4(bool* flag) {
    if (flag)
        *flag = false;
    s32 language = 0;
    if (auto* mgr = gdt::Manager::instance()) {
        mgr->getParamBypassPerm().get().getS32(&language, sVoiceData.mVoiceLanguage);
        Unk_710105ef9c voice_language(language);
        if (voice_language == Unk_710105ef9c::USfr) {
            if (flag)
                *flag = true;
            voice_language = Unk_710105ef9c::EUfr;
        }
        if (voice_language != Unk_710105ef9c::SameAsSystem)
            return voice_language.text();
    }
    return sub_710105E898(sead::EnvUtil::getRegionLanguage(), flag);
}

}  // namespace ksys::snd
