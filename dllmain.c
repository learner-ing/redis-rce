#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"
#include "redismodule.h"
#include <stdio.h>
__declspec(dllexport) int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc);

int DoCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
	system("ipconfig >c:\\programdata\\a.txt");
	return REDISMODULE_OK;
}

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
	if (RedisModule_Init(ctx, "system", 1, REDISMODULE_APIVER_1)
		== REDISMODULE_ERR) return REDISMODULE_ERR;

	if (RedisModule_CreateCommand(ctx, "system.exec",
		DoCommand, "readonly", 0, 0, 0) == REDISMODULE_ERR)
		return REDISMODULE_ERR;
	return REDISMODULE_OK;
}