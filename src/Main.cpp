/*
 * HEADER
 */
#include "CommonPrecompiled.h"
#include "SystemIncludes.h"

#include "HeapAllocator.h"

int main(int argc, char** argv)
{
  s32 ret = 0;
  ArgParser args(argc, argv);
  args.AddCommand("-w", "-screenWidth", true);
  args.AddCommand("-h", "-screenHeight", true);
  args.AddCommand("-f", "-fullscreen");
  args.AddCommand("-mg", "-customGlobal");
  args.AddCommand("-ro", "-runOneFrame");
  args.AddCommand("-serv", "-server");
  args.Parse();

  LOG((args.Has("-mg") ? "Using Custom Global Mem" : "Not using Custom Global Mem"));
  if(args.Has("-w"))
    LOG("ScreenWidth Override " << args.Get("-w")->val.iVal);
  if(args.Has("-h"))
    LOG("ScreenHeight Override " << args.Get("-h")->val.iVal);

  Run(args);
  
  return ret;
}
