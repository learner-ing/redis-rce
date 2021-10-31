#include "pch.h"
#include "redismodule.h"
#include <stdio.h>


__declspec(dllexport) int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc);

int DoCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
	if (argc == 2) {
		size_t cmd_len;
		size_t size = 1024;
		char *cmd = RedisModule_StringPtrLen(argv[1], &cmd_len);
		FILE *fp = _popen(cmd, "r");
		char *buf, *output;
		buf = (char *)malloc(size);
		output = (char *)malloc(size);
		while (fgets(buf, sizeof(buf), fp) != 0) {
			if (strlen(buf) + strlen(output) >= size) {
				output = realloc(output, size << 2);
				size <<= 1;
			}
			strcat_s(output,size, buf);
		}
		RedisModuleString *ret = RedisModule_CreateString(ctx, output, strlen(output));
		RedisModule_ReplyWithString(ctx, ret);
		_pclose(fp);
	}
	else {
		return RedisModule_WrongArity(ctx);
	}
	return REDISMODULE_OK;

}

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
	if (RedisModule_Init(ctx, "system", 1, REDISMODULE_APIVER_1)
		== REDISMODULE_ERR) return REDISMODULE_ERR;

	if (RedisModule_CreateCommand(ctx, "system.exec",
		DoCommand, "readonly", 1, 1, 1) == REDISMODULE_ERR)
		return REDISMODULE_ERR;
	return REDISMODULE_OK;
}
