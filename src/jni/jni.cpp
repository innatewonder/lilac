#include "CommonPrecompiled.h"
#include <jni.h>

#include "GLESClass.h"

void on_surface_created() 
{
  LOG("SURFACE CREATED");
  ArgParser parser;
  Run(parser);
}

void on_surface_changed(int width, int height) 
{
  Message* m = MESSAGE(Message::MSG_RESIZE);
  m->AddData(DAT(width));
  m->AddData(DAT(height));
  gCore->SendMessage(m);
}

void on_draw_frame() 
{
  //notify the GLESClass that it can draw a frame and wait for it to finish
  Graphics::glesStartSync.Notify();
  Graphics::glesEndSync.Wait();
}

static JNINativeMethod methodTable[] = {
  {"on_surface_created", "()V", (void *) on_surface_created},
  {"on_surface_changed", "(II)V", (void *) on_surface_changed},
  {"on_draw_frame", "()V", (void *) on_draw_frame},
};

static JNIEnv* env;
jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    if (vm->GetEnv((void**)&env, JNI_VERSION_1_6) != JNI_OK) {
		return -1;
	}
    env->RegisterNatives(env->FindClass("io/projektiris/silver/JNIWrapper"),
                        methodTable,
                        sizeof(methodTable) / sizeof(methodTable[0]));
    return JNI_VERSION_1_6;
}
