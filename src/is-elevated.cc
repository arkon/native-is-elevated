#include <node.h>

#ifdef linux
#include <unistd.h>
#endif

#ifdef _WIN32
#include <windows.h>
#endif

namespace is_elevated {
  using v8::Boolean;
  using v8::FunctionCallbackInfo;
  using v8::Isolate;
  using v8::Local;
  using v8::Object;
  using v8::Value;

  void IsElevated(const FunctionCallbackInfo<Value>& args) {
    Isolate *isolate = args.GetIsolate();
    bool bIsElevated = false;

    #ifdef _WIN32
      // Based on http://stackoverflow.com/a/8196291
      HANDLE hToken = NULL;
      if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation(hToken,
                                TokenElevation,
                                &Elevation,
                                sizeof(Elevation),
                                &cbSize)) {
          bIsElevated = Elevation.TokenIsElevated;
        }
      }
      if (hToken) {
        CloseHandle(hToken);
      }
    #else
      bIsElevated = geteuid() == 0;
    #endif

    Local<Boolean> resultBool = Boolean::New(isolate, bIsElevated);
    args.GetReturnValue().Set(resultBool);
  }

  void Init(Local<Object> exports) {
    NODE_SET_METHOD(exports, "isElevated", IsElevated);
  }

  NODE_MODULE(is_elevated, Init)
}
