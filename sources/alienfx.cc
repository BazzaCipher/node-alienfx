#include <node.h>
#include <v8.h>
#include <string>

#include "alienfxApi.h"

using namespace v8;

Handle<Value> Initialize(const Arguments& args) {
    HandleScope scope;
    
    LFX_RESULT result = ALIENFX_API.Initialize();

    return scope.Close(Number::New(result));
}

Handle<Value> Release(const Arguments& args) {
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Release();

    return scope.Close(Number::New(result));
}

Handle<Value> Reset(const Arguments& args) {
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Reset();

    return scope.Close(Number::New(result));
}

Handle<Value> Update(const Arguments& args) {
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Update();

    return scope.Close(Number::New(result));
}

Handle<Value> UpdateDefault(const Arguments& args) {
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.UpdateDefault();

    return scope.Close(Number::New(result));
}

Handle<Value> Light(const Arguments& args) {
    HandleScope scope;

    if (args.Length() < 2)
    {
        Local<Value> exception = Exception::TypeError(String::New("Function expects 2 parameters."));
        ThrowException(exception);
    }

    if (!args[0]->IsNumber())
    {
        Local<Value> exception = Exception::TypeError(String::New("First argument must be a number."));
        ThrowException(exception);
    }

    if (!args[1]->IsNumber())
    {
        Local<Value> exception = Exception::TypeError(String::New("Second argument must be a number."));
        ThrowException(exception);
    }


    unsigned int locationMask = args[0]->Uint32Value();
    unsigned int colorValue = args[1]->Uint32Value();

    LFX_RESULT result = ALIENFX_API.Light(locationMask, colorValue);

    return scope.Close(Number::New(result));
}

Handle<Value> GetNumDevices(const Arguments& args)
{
    HandleScope scope;

    unsigned int numberOfDevices = 0;


    LFX_RESULT result = ALIENFX_API.GetNumDevices(&numberOfDevices);

    if (result == LFX_ERROR_NOINIT)
    {
        Local<Value> exception = Exception::Error(String::New("AlienFX is not initialized. Call initialize() prior to accessing AlienFX functionality."));
        ThrowException(exception);
    }

    if (result == LFX_ERROR_NODEVS)
    {
        Local<Value> exception = Exception::Error(String::New("No AlienFX compatible devices are available."));
        ThrowException(exception);
    }

    if (result == LFX_FAILURE)
    {
        Local<Value> exception = Exception::Error(String::New("AlienFX call failed for unknown reason."));
        ThrowException(exception);
    }

    return scope.Close(Number::New(numberOfDevices));
}

Handle<Value> GetDeviceDescription(const Arguments& args)
{
    HandleScope scope;


    if (args.Length() < 1)
    {
        Local<Value> exception = Exception::Error(String::New("Function expects 1 parameter."));
        ThrowException(exception);
    }

    if (!args[0]->IsNumber())
    {
        Local<Value> exception = Exception::Error(String::New("First argument must be a number."));
        ThrowException(exception);
    }


    unsigned int deviceIndex = args[0]->Uint32Value();

    unsigned char deviceType = 0;
    std::string deviceDescription(256, 0);


    LFX_RESULT result = ALIENFX_API.GetDeviceDescription(
        deviceIndex,
        (char *)deviceDescription.c_str(),
        deviceDescription.size(), 
        &deviceType);


    Local<Object> description = Object::New();
    description->Set(String::NewSymbol("model"), String::New(deviceDescription.c_str()));
    description->Set(String::NewSymbol("type"), Number::New(deviceType));

    return scope.Close(description);
}

Handle<Value> GetNumLights(const Arguments& args)
{
    HandleScope scope;


    if (args.Length() < 1)
    {
        Local<Value> exception = Exception::Error(String::New("Function expects 1 parameter."));
        ThrowException(exception);
    }

    if (!args[0]->IsNumber())
    {
        Local<Value> exception = Exception::Error(String::New("First argument must be a number."));
        ThrowException(exception);
    }


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int numberOfLights = 0;

    LFX_RESULT result = ALIENFX_API.GetNumLights(deviceIndex, &numberOfLights);

    if (result == LFX_ERROR_NOINIT)
    {
        Local<Value> exception = Exception::Error(String::New("AlienFX is not initialized. Call initialize() prior to accessing AlienFX functionality."));
        ThrowException(exception);
    }

    if (result == LFX_ERROR_NODEVS)
    {
        Local<Value> exception = Exception::Error(String::New("There are no AlienFX devices at specified index."));
        ThrowException(exception);
    }

    if (result == LFX_ERROR_NOLIGHTS)
    {
        Local<Value> exception = Exception::Error(String::New("There are no lights available at specified device index."));
        ThrowException(exception);
    }

    if (result == LFX_FAILURE)
    {
        Local<Value> exception = Exception::Error(String::New("AlienFX call failed for unknown reason."));
        ThrowException(exception);
    }

    return scope.Close(Number::New(numberOfLights));
}

Handle<Value> GetLightDescription(const Arguments& args)
{
    HandleScope scope;


    if (args.Length() < 1)
    {
        Local<Value> exception = Exception::Error(String::New("Function expects 2 parameters."));
        ThrowException(exception);
    }

    if (!args[0]->IsNumber())
    {
        Local<Value> exception = Exception::Error(String::New("First argument must be a number."));
        ThrowException(exception);
    }

    if (!args[1]->IsNumber())
    {
        Local<Value> exception = Exception::Error(String::New("Second argument must be a number."));
        ThrowException(exception);
    }


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();

    std::string lightDescription(256, 0);


    LFX_RESULT result = ALIENFX_API.GetLightDescription(
        deviceIndex,
        lightIndex,
        (char *)lightDescription.c_str(),
        lightDescription.size());


    return scope.Close(String::New(lightDescription.c_str()));
}


Handle<Value> CreateColorObject()
{
    HandleScope scope;

    Local<Object> color = Object::New();
    color->Set(String::NewSymbol("OFF"), Number::New(LFX_OFF));
    color->Set(String::NewSymbol("BLACK"), Number::New(LFX_BLACK));
    color->Set(String::NewSymbol("RED"), Number::New(LFX_RED));
    color->Set(String::NewSymbol("GREEN"), Number::New(LFX_GREEN));
    color->Set(String::NewSymbol("BLUE"), Number::New(LFX_BLUE));
    color->Set(String::NewSymbol("WHITE"), Number::New(LFX_WHITE));
    color->Set(String::NewSymbol("YELLOW"), Number::New(LFX_YELLOW));
    color->Set(String::NewSymbol("ORANGE"), Number::New(LFX_ORANGE));
    color->Set(String::NewSymbol("PINK"), Number::New(LFX_PINK));
    color->Set(String::NewSymbol("CYAN"), Number::New(LFX_CYAN));

    return scope.Close(color);
}

Handle<Value> CreateBrightnessObject()
{
    HandleScope scope;

    Local<Object> brightness = Object::New();
    brightness->Set(String::NewSymbol("FULL"), Number::New(LFX_FULL_BRIGHTNESS));
    brightness->Set(String::NewSymbol("HALF"), Number::New(LFX_HALF_BRIGHTNESS));
    brightness->Set(String::NewSymbol("MIN"), Number::New(LFX_MIN_BRIGHTNESS));

    return scope.Close(brightness);
}

Handle<Value> CreateDeviceTypeObject()
{
    HandleScope scope;

    Local<Object> deviceType = Object::New();
    deviceType->Set(String::NewSymbol("UNKNOWN"), Number::New(LFX_DEVTYPE_UNKNOWN));
    deviceType->Set(String::NewSymbol("NOTEBOOK"), Number::New(LFX_DEVTYPE_NOTEBOOK));
    deviceType->Set(String::NewSymbol("DESKTOP"), Number::New(LFX_DEVTYPE_DESKTOP));
    deviceType->Set(String::NewSymbol("SERVER"), Number::New(LFX_DEVTYPE_SERVER));
    deviceType->Set(String::NewSymbol("DISPLAY"), Number::New(LFX_DEVTYPE_DISPLAY));
    deviceType->Set(String::NewSymbol("MOUSE"), Number::New(LFX_DEVTYPE_MOUSE));
    deviceType->Set(String::NewSymbol("KEYBOARD"), Number::New(LFX_DEVTYPE_KEYBOARD));
    deviceType->Set(String::NewSymbol("GAMEPAD"), Number::New(LFX_DEVTYPE_GAMEPAD));
    deviceType->Set(String::NewSymbol("SPEAKER"), Number::New(LFX_DEVTYPE_SPEAKER));
    deviceType->Set(String::NewSymbol("OTHER"), Number::New(LFX_DEVTYPE_OTHER));

    return scope.Close(deviceType);
}


void Init(Handle<Object> target) {
    NODE_SET_METHOD(target, "initialize", Initialize);
    NODE_SET_METHOD(target, "release", Release);
    NODE_SET_METHOD(target, "reset", Reset);
    NODE_SET_METHOD(target, "update", Update);
    NODE_SET_METHOD(target, "updateDefault", UpdateDefault);
    NODE_SET_METHOD(target, "light", Light);
    NODE_SET_METHOD(target, "getNumDevices", GetNumDevices);
    NODE_SET_METHOD(target, "getDeviceDescription", GetDeviceDescription);
    NODE_SET_METHOD(target, "getNumLights", GetNumLights);
    NODE_SET_METHOD(target, "getLightDescription", GetLightDescription);

    Handle<Value> color = CreateColorObject();
    target->Set(String::NewSymbol("Color"), color);

    Handle<Value> brightness = CreateBrightnessObject();
    target->Set(String::NewSymbol("Brightness"), brightness);

    Handle<Value> deviceType = CreateDeviceTypeObject();
    target->Set(String::NewSymbol("DeviceType"), deviceType);
}

NODE_MODULE(alienfx, Init)
