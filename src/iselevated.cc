#include <node_api.h>

#if defined(_WIN32) || defined(WIN32)
// Windows
#include <windows.h>
#include <shlobj.h>
#else
// Unix (macOS, Linux)
#include <unistd.h>
#endif

namespace
{
  napi_value IsElevated(napi_env env, napi_callback_info info)
  {
    bool bIsElevated = false;

    #if defined(_WIN32) || defined(WIN32)
    // Based on https://stackoverflow.com/questions/4230602
    BOOL isMember = false;
    PSID administratorsGroup = nullptr;
    SID_IDENTIFIER_AUTHORITY SIDAuthNT = SECURITY_NT_AUTHORITY;

    if (AllocateAndInitializeSid(
      &SIDAuthNT, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS,
      0, 0, 0, 0, 0, 0, &administratorsGroup
    ))
    {
      CheckTokenMembership(nullptr, administratorsGroup, &isMember);
    }

    if (administratorsGroup)
    {
      FreeSid(administratorsGroup);
    }

    bIsElevated = isMember;
    #else
    bIsElevated = geteuid() == 0;
    #endif

    napi_value napi_result;
    napi_get_boolean(env, bIsElevated, &napi_result);

    return napi_result;
  }

  napi_value Init(napi_env env, napi_value exports)
  {
    napi_value isElevated;
    napi_create_function(env, "isElevated", NAPI_AUTO_LENGTH, IsElevated, NULL, &isElevated);
    napi_set_named_property(env, exports, "isElevated", isElevated);

    return exports;
  }

  NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
}
