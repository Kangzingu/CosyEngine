#pragma once
// 이 헤더 파일이 한번만 빌드되도록, 여러번 include 되는 걸 막아줌

#include <windows.h>

// Icon에 관한 선언이 resource.h에 대있음
#include "../resource.h"

#define MAX_LEN_OF_NAME_STRING 256
#define HInstance() GetModuleHandle(NULL)