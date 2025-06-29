#pragma once

#include <vector>
#include "scene.h"
#include "sceneStructs.h"

#include "texture_utils.h"
#include "texture.h"


void InitDataContainer(GuiDataContainer* guiData);
void pathtraceInit(Scene *scene);
void pathtraceFree(Scene* scene);
void pathtrace(uchar4 *pbo, int frame, int iteration);

