#pragma once

#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::map {

class Rail;

// TODO: incomplete
class Placement18 {
public:
    // 0x0000007100d4782c
    ~Placement18();

    // 0x7100d48744 (a stub that tail-calls 0x7100d48254): finds a rail by its unique name
    // (inlined string compare against Rail::getUniqueName; null when there is none). Used by RailMove::enter_.
    Rail* sub_7100D48744(const sead::SafeString& unique_name);
    // 0x7100d48254 (declared only)
    Rail* sub_7100D48254(const sead::SafeString& unique_name);

private:
    void* _0;
    void* _8;
    void* _10;
};
KSYS_CHECK_SIZE_NX150(Placement18, 0x18);

}  // namespace ksys::map
