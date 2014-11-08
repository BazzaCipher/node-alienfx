#include <node.h>
#include <string>

#include "../contracts.h"
#include "../../api/alienfxApi.h"

using namespace v8;
using namespace std;



void ObjectToColor(const Handle<Object> object, LFX_COLOR& color)
{
    color.red = object->Get(String::NewSymbol("red"))->Uint32Value();
    color.green = object->Get(String::NewSymbol("green"))->Uint32Value();
    color.blue = object->Get(String::NewSymbol("blue"))->Uint32Value();
    color.brightness = object->Get(String::NewSymbol("brightness"))->Uint32Value();
}

void ColorToObject(const LFX_COLOR& color, Handle<Object> object)
{
    object->Set(String::NewSymbol("red"), Number::New(color.red));
    object->Set(String::NewSymbol("green"), Number::New(color.green));
    object->Set(String::NewSymbol("blue"), Number::New(color.blue));
    object->Set(String::NewSymbol("brightness"), Number::New(color.brightness));
}


Handle<Value> GetVersion(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 1);
    REQUIRE_OBJECT(scope, args, 0);


    string version(LFX_DEF_STRING_SIZE, 0);


    LFX_RESULT result = ALIENFX_API.GetVersion(
        (char *)version.c_str(),
        version.size());

    if (result == LFX_SUCCESS) {
        Local<Object> out = Local<Object>::Cast(args[0]);
        out->Set(String::NewSymbol("result"), String::New(version.c_str()));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> InitializeSync(const Arguments& args)
{
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Initialize();

    return scope.Close(Number::New(result));
}

Handle<Value> ReleaseSync(const Arguments& args)
{
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Release();

    return scope.Close(Number::New(result));
}

Handle<Value> Reset(const Arguments& args)
{
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Reset();

    return scope.Close(Number::New(result));
}

Handle<Value> Update(const Arguments& args)
{
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.Update();

    return scope.Close(Number::New(result));
}

Handle<Value> UpdateDefault(const Arguments& args)
{
    HandleScope scope;

    LFX_RESULT result = ALIENFX_API.UpdateDefault();

    return scope.Close(Number::New(result));
}

Handle<Value> Light(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 2);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);


    unsigned int locationMask = args[0]->Uint32Value();
    unsigned int colorValue = args[1]->Uint32Value();

    LFX_RESULT result = ALIENFX_API.Light(locationMask, colorValue);

    return scope.Close(Number::New(result));
}

Handle<Value> ActionColor(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 3);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_NUMBER(scope, args, 2);


    unsigned int locationMask = args[0]->Uint32Value();
    unsigned int action = args[1]->Uint32Value();
    unsigned int colorValue = args[2]->Uint32Value();

    LFX_RESULT result = ALIENFX_API.ActionColor(locationMask, action, colorValue);

    return scope.Close(Number::New(result));
}

Handle<Value> ActionColorEx(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 4);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_NUMBER(scope, args, 2);
    REQUIRE_NUMBER(scope, args, 3);


    unsigned int locationMask = args[0]->Uint32Value();
    unsigned int action = args[1]->Uint32Value();
    unsigned int primaryColorValue = args[2]->Uint32Value();
    unsigned int secondaryColorValue = args[3]->Uint32Value();

    LFX_RESULT result = ALIENFX_API.ActionColorEx(locationMask, action, primaryColorValue, secondaryColorValue);

    return scope.Close(Number::New(result));
}

Handle<Value> GetNumDevicesSync(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 1);
    REQUIRE_OBJECT(scope, args, 0);


    unsigned int numberOfDevices = 0;


    LFX_RESULT result = ALIENFX_API.GetNumDevices(&numberOfDevices);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[0]);
        out->Set(String::NewSymbol("numberOfDevices"), Number::New(numberOfDevices));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> GetDeviceDescriptionSync(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 2);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_OBJECT(scope, args, 1);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned char deviceType = 0;
    string deviceDescription(LFX_DEF_STRING_SIZE, 0);


    LFX_RESULT result = ALIENFX_API.GetDeviceDescription(
        deviceIndex,
        (char *)deviceDescription.c_str(),
        deviceDescription.size(),
        &deviceType);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[1]);
        out->Set(String::NewSymbol("model"), String::New(deviceDescription.c_str()));
        out->Set(String::NewSymbol("type"), Number::New(deviceType));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> GetNumLightsSync(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 2);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_OBJECT(scope, args, 1);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int numberOfLights = 0;


    LFX_RESULT result = ALIENFX_API.GetNumLights(deviceIndex, &numberOfLights);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[1]);
        out->Set(String::NewSymbol("numberOfLights"), Number::New(numberOfLights));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> GetLightDescriptionSync(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 3);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_OBJECT(scope, args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();

    string lightDescription(LFX_DEF_STRING_SIZE, 0);


    LFX_RESULT result = ALIENFX_API.GetLightDescription(
        deviceIndex,
        lightIndex,
        (char *)lightDescription.c_str(),
        lightDescription.size());

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[2]);
        out->Set(String::NewSymbol("lightDescription"), String::New(lightDescription.c_str()));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> GetLightLocation(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 3);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_OBJECT(scope, args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();

    LFX_POSITION lightLocation{ 0 };


    LFX_RESULT result = ALIENFX_API.GetLightLocation(deviceIndex, lightIndex, &lightLocation);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[2]);
        out->Set(String::NewSymbol("result"), Number::New(sizeof LFX_POSITION));
    }


    return scope.Close(Number::New(result));
}

Handle<Value> GetLightColor(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 3);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_OBJECT(scope, args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();

    LFX_COLOR lightColor{ 0 };


    LFX_RESULT result = ALIENFX_API.GetLightColor(deviceIndex, lightIndex, &lightColor);

    if (result == LFX_SUCCESS)
    {
        Local<Object> out = Local<Object>::Cast(args[2]);
        ColorToObject(lightColor, out);
    }

    return scope.Close(Number::New(result));
}

Handle<Value> SetLightColor(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 3);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_OBJECT(scope, args, 2);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();
    Local<Object> color = Local<Object>::Cast(args[2]);

    LFX_COLOR lightColor{ 0 };
    ObjectToColor(color, lightColor);


    LFX_RESULT result = ALIENFX_API.SetLightColor(deviceIndex, lightIndex, &lightColor);

    return scope.Close(Number::New(result));
}

Handle<Value> SetLightActionColor(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 4);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_NUMBER(scope, args, 2);
    REQUIRE_OBJECT(scope, args, 3);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();
    unsigned int action = args[2]->Uint32Value();
    Local<Object> color = Local<Object>::Cast(args[3]);

    LFX_COLOR lightColor{ 0 };
    ObjectToColor(color, lightColor);

    LFX_RESULT result = ALIENFX_API.SetLightActionColor(deviceIndex, lightIndex, action, &lightColor);

    return scope.Close(Number::New(result));
}

Handle<Value> SetLightActionColorEx(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 5);
    REQUIRE_NUMBER(scope, args, 0);
    REQUIRE_NUMBER(scope, args, 1);
    REQUIRE_NUMBER(scope, args, 2);
    REQUIRE_OBJECT(scope, args, 3);
    REQUIRE_OBJECT(scope, args, 4);


    unsigned int deviceIndex = args[0]->Uint32Value();
    unsigned int lightIndex = args[1]->Uint32Value();
    unsigned int action = args[2]->Uint32Value();
    Local<Object> primaryColor = Local<Object>::Cast(args[3]);
    Local<Object> secondaryColor = Local<Object>::Cast(args[4]);

    LFX_COLOR primaryLightColor{ 0 };
    ObjectToColor(primaryColor, primaryLightColor);

    LFX_COLOR secondaryLightColor{ 0 };
    ObjectToColor(secondaryColor, secondaryLightColor);


    LFX_RESULT result = ALIENFX_API.SetLightActionColorEx(deviceIndex, lightIndex, action, &primaryLightColor, &secondaryLightColor);

    return scope.Close(Number::New(result));
}

Handle<Value> SetTiming(const Arguments& args)
{
    HandleScope scope;

    REQUIRE_NUMBER_OF_ARGUMENTS(scope, args, 1);
    REQUIRE_NUMBER(scope, args, 0);


    int timing = args[0]->Int32Value();

    LFX_RESULT result = ALIENFX_API.SetTiming(timing);

    return scope.Close(Number::New(result));
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

Handle<Value> CreatePositionObject()
{
    HandleScope scope;

    Local<Object> position = Object::New();

    // Near Z-plane light definitions
    position->Set(String::NewSymbol("FRONT_LOWER_LEFT"), Number::New(LFX_FRONT_LOWER_LEFT));
    position->Set(String::NewSymbol("FRONT_LOWER_CENTER"), Number::New(LFX_FRONT_LOWER_CENTER));
    position->Set(String::NewSymbol("FRONT_LOWER_RIGHT"), Number::New(LFX_FRONT_LOWER_RIGHT));
    position->Set(String::NewSymbol("FRONT_MIDDLE_LEFT"), Number::New(LFX_FRONT_MIDDLE_LEFT));
    position->Set(String::NewSymbol("FRONT_MIDDLE_CENTER"), Number::New(LFX_FRONT_MIDDLE_CENTER));
    position->Set(String::NewSymbol("FRONT_MIDDLE_RIGHT"), Number::New(LFX_FRONT_MIDDLE_RIGHT));
    position->Set(String::NewSymbol("FRONT_UPPER_LEFT"), Number::New(LFX_FRONT_UPPER_LEFT));
    position->Set(String::NewSymbol("FRONT_UPPER_CENTER"), Number::New(LFX_FRONT_UPPER_CENTER));
    position->Set(String::NewSymbol("FRONT_UPPER_RIGHT"), Number::New(LFX_FRONT_UPPER_RIGHT));

    // Mid Z-plane light definitions
    position->Set(String::NewSymbol("MIDDLE_LOWER_LEFT"), Number::New(LFX_MIDDLE_LOWER_LEFT));
    position->Set(String::NewSymbol("MIDDLE_LOWER_CENTER"), Number::New(LFX_MIDDLE_LOWER_CENTER));
    position->Set(String::NewSymbol("MIDDLE_LOWER_RIGHT"), Number::New(LFX_MIDDLE_LOWER_RIGHT));
    position->Set(String::NewSymbol("MIDDLE_MIDDLE_LEFT"), Number::New(LFX_MIDDLE_MIDDLE_LEFT));
    position->Set(String::NewSymbol("MIDDLE_MIDDLE_CENTER"), Number::New(LFX_MIDDLE_MIDDLE_CENTER));
    position->Set(String::NewSymbol("MIDDLE_MIDDLE_RIGHT"), Number::New(LFX_MIDDLE_MIDDLE_RIGHT));
    position->Set(String::NewSymbol("MIDDLE_UPPER_LEFT"), Number::New(LFX_MIDDLE_UPPER_LEFT));
    position->Set(String::NewSymbol("MIDDLE_UPPER_CENTER"), Number::New(LFX_MIDDLE_UPPER_CENTER));
    position->Set(String::NewSymbol("MIDDLE_UPPER_RIGHT"), Number::New(LFX_MIDDLE_UPPER_RIGHT));

    // Far Z-plane light definitions
    position->Set(String::NewSymbol("REAR_LOWER_LEFT"), Number::New(LFX_REAR_LOWER_LEFT));
    position->Set(String::NewSymbol("REAR_LOWER_CENTER"), Number::New(LFX_REAR_LOWER_CENTER));
    position->Set(String::NewSymbol("REAR_LOWER_RIGHT"), Number::New(LFX_REAR_LOWER_RIGHT));
    position->Set(String::NewSymbol("REAR_MIDDLE_LEFT"), Number::New(LFX_REAR_MIDDLE_LEFT));
    position->Set(String::NewSymbol("REAR_MIDDLE_CENTER"), Number::New(LFX_REAR_MIDDLE_CENTER));
    position->Set(String::NewSymbol("REAR_MIDDLE_RIGHT"), Number::New(LFX_REAR_MIDDLE_RIGHT));
    position->Set(String::NewSymbol("REAR_UPPER_LEFT"), Number::New(LFX_REAR_UPPER_LEFT));
    position->Set(String::NewSymbol("REAR_UPPER_CENTER"), Number::New(LFX_REAR_UPPER_CENTER));
    position->Set(String::NewSymbol("REAR_UPPER_RIGHT"), Number::New(LFX_REAR_UPPER_RIGHT));

    // Combination bit masks
    position->Set(String::NewSymbol("ALL"), Number::New(LFX_ALL));
    position->Set(String::NewSymbol("ALL_RIGHT"), Number::New(LFX_ALL_RIGHT));
    position->Set(String::NewSymbol("ALL_LEFT"), Number::New(LFX_ALL_LEFT));
    position->Set(String::NewSymbol("ALL_UPPER"), Number::New(LFX_ALL_UPPER));
    position->Set(String::NewSymbol("ALL_LOWER"), Number::New(LFX_ALL_LOWER));
    position->Set(String::NewSymbol("ALL_FRONT"), Number::New(LFX_ALL_FRONT));
    position->Set(String::NewSymbol("ALL_REAR"), Number::New(LFX_ALL_REAR));

    return scope.Close(position);
}

Handle<Value> CreateResutObject()
{
    HandleScope scope;

    Local<Object> result = Object::New();
    result->Set(String::NewSymbol("SUCCESS"), Number::New(LFX_SUCCESS));
    result->Set(String::NewSymbol("FAILURE"), Number::New(LFX_FAILURE));
    result->Set(String::NewSymbol("NOINIT"), Number::New(LFX_ERROR_NOINIT));
    result->Set(String::NewSymbol("NODEVS"), Number::New(LFX_ERROR_NODEVS));
    result->Set(String::NewSymbol("NOLIGHTS"), Number::New(LFX_ERROR_NOLIGHTS));
    result->Set(String::NewSymbol("BUFFSIZE"), Number::New(LFX_ERROR_BUFFSIZE));

    return scope.Close(result);
}

Handle<Value> CreateActionObject()
{
    HandleScope scope;

    Local<Object> action = Object::New();
    action->Set(String::NewSymbol("MORPH"), Number::New(LFX_ACTION_MORPH));
    action->Set(String::NewSymbol("PULSE"), Number::New(LFX_ACTION_PULSE));
    action->Set(String::NewSymbol("COLOR"), Number::New(LFX_ACTION_COLOR));

    return scope.Close(action);
}



void InitSyncBindings(const v8::Handle<v8::Object>& target)
{
    NODE_SET_METHOD(target, "getVersion", GetVersion);
    NODE_SET_METHOD(target, "initializeSync", InitializeSync);
    NODE_SET_METHOD(target, "releaseSync", ReleaseSync);
    NODE_SET_METHOD(target, "reset", Reset);
    NODE_SET_METHOD(target, "update", Update);
    NODE_SET_METHOD(target, "updateDefault", UpdateDefault);
    NODE_SET_METHOD(target, "light", Light);
    NODE_SET_METHOD(target, "actionColor", ActionColor);
    NODE_SET_METHOD(target, "actionColorEx", ActionColorEx);
    NODE_SET_METHOD(target, "getNumDevicesSync", GetNumDevicesSync);
    NODE_SET_METHOD(target, "getDeviceDescriptionSync", GetDeviceDescriptionSync);
    NODE_SET_METHOD(target, "getNumLightsSync", GetNumLightsSync);
    NODE_SET_METHOD(target, "getLightDescriptionSync", GetLightDescriptionSync);
    NODE_SET_METHOD(target, "getLightLocation", GetLightLocation);
    NODE_SET_METHOD(target, "getLightColor", GetLightColor);
    NODE_SET_METHOD(target, "setLightColor", SetLightColor);
    NODE_SET_METHOD(target, "setLightActionColor", SetLightActionColor);
    NODE_SET_METHOD(target, "setLightActionColorEx", SetLightActionColorEx);
    NODE_SET_METHOD(target, "setTiming", SetTiming);


    target->Set(String::NewSymbol("isAvailable"), Boolean::New(ALIENFX_API.IsAvailable));


    Handle<Value> color = CreateColorObject();
    target->Set(String::NewSymbol("Color"), color);

    Handle<Value> brightness = CreateBrightnessObject();
    target->Set(String::NewSymbol("Brightness"), brightness);

    Handle<Value> deviceType = CreateDeviceTypeObject();
    target->Set(String::NewSymbol("DeviceType"), deviceType);

    Handle<Value> position = CreatePositionObject();
    target->Set(String::NewSymbol("Position"), position);

    Handle<Value> result = CreateResutObject();
    target->Set(String::NewSymbol("Result"), result);

    Handle<Value> action = CreateActionObject();
    target->Set(String::NewSymbol("Action"), action);
}
