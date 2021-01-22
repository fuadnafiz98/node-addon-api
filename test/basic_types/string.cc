#include "napi.h"

using namespace Napi;

const char* UTF8String = "nodejs";
const char16_t* UTF16String = u"\u006e\u006f\u0064\u0065\u006a\u0073";

Value TestString(const CallbackInfo& info) {
  String value = info[0].As<String>();
  String encoding = info[1].As<String>();
  Number length = info[2].As<Number>();
  if (encoding.Utf8Value() == "utf8") {
      std::string testValue = UTF8String;
      if (!length.IsUndefined()) {
        testValue = testValue.substr(0, length.Uint32Value());
      }

      std::string stringValue = value;
      return Boolean::New(info.Env(), stringValue == testValue);
    } else if (encoding.Utf8Value() == "utf16") {
      std::u16string testValue = UTF16String;
      if (!length.IsUndefined()) {
        testValue = testValue.substr(0, length.Uint32Value());
      }

      std::u16string stringValue = value;
      return Boolean::New(info.Env(), stringValue == testValue);
    } else {
      Error::New(info.Env(), "Invalid encoding.").ThrowAsJavaScriptException();
      return Value();
    }
}

Value NewString(const CallbackInfo& info) {
  String encoding = info[0].As<String>();
  Number length = info[1].As<Number>();

  if (encoding.Utf8Value() == "utf8") {
    if (length.IsUndefined()) {
      return String::New(info.Env(), UTF8String);
    } else {
      return String::New(info.Env(), UTF8String, length.Uint32Value());
    }
  } else if (encoding.Utf8Value() == "utf16") {
    if (length.IsUndefined()) {
      return String::New(info.Env(), UTF16String);
    } else {
      return String::New(info.Env(), UTF16String, length.Uint32Value());
    }
  } else {
    Error::New(info.Env(), "Invalid encoding.").ThrowAsJavaScriptException();
    return Value();
  }
}
Object InitBasicTypesString(Env env) {
  Object exports = Object::New(env);

  exports["testString"] = Function::New(env, TestString);
  exports["newString"] = Function::New(env, NewString);

  return exports;
}