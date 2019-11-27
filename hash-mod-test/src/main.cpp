#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "../../shared/utils/typedefs.h"
#include "../../shared/inline-hook/And64InlineHook.hpp"

#include "../../shared/utils/il2cpp-utils.hpp"
#include "../../shared/utils/utils.h"
#include "../../shared/utils/utils-functions.hpp"
#include "../../shared/utils/logging.h"

#define MAIN_ComputeStringHashOffset 0xE3BCEC
#define Sirenix_ComputeStringHashOffset 0xF26B98

MAKE_HOOK(MAIN_ComputeStringHash, MAIN_ComputeStringHashOffset, uint32_t, Il2CppString* s) {
    log(INFO, "Performing Main Namespace Hash on input string: %s", to_utf8(csstrtostr(s)).data());
    auto ret = MAIN_ComputeStringHash(s);
    log(INFO, "Result: %ui", ret);
    return ret;
}

MAKE_HOOK(Sirenix_ComputeStringHash, Sirenix_ComputeStringHashOffset, uint32_t, Il2CppString* s) {
    log(INFO, "Performing Sirenix Hash on input string: %s", to_utf8(csstrtostr(s)).data());
    auto ret = Sirenix_ComputeStringHash(s);
    log(INFO, "Result: %ui", ret);
    return ret;
}

static bool installed = false;
void InstallHooks() {
    if (installed) return;
    log(INFO, "Installing HashMod!");
    INSTALL_HOOK(MAIN_ComputeStringHash);
    log(INFO, "Installed Main Hash hook!");
    INSTALL_HOOK(Sirenix_ComputeStringHash);
    log(INFO, "Installed Sirenix Hash hook!");
    log(INFO, "Installed HashMod!");
    installed = true;
}

__attribute__((constructor)) void lib_main() {
    InstallHooks();
}

void init() {
    InstallHooks();
}

void load() {
    InstallHooks();
}