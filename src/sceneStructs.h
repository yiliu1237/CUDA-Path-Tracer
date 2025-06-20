#pragma once

#include <string>
#include <vector>
#include <cuda_runtime.h>
#include "glm/glm.hpp"

#include "texture.h"

#define BACKGROUND_COLOR (glm::vec3(0.0f))


struct Ray
{
    glm::vec3 origin;
    glm::vec3 direction;
};


struct Triangle {
    glm::vec3 v0, v1, v2;
    glm::vec3 normal;

    glm::vec2 uv0;
    glm::vec2 uv1;
    glm::vec2 uv2;
};



struct Material
{
    glm::vec3 color;
    struct
    {
        float exponent;
        glm::vec3 color;
    } specular;
    float hasReflective;
    float hasRefractive;
    float indexOfRefraction;
    float emittance;
    float roughness;

    HostTexture<unsigned char> albedoMapData;
    HostTexture<unsigned char> normalMapData;
    HostTexture<float> envMapData;

    // Device-side CUDA texture objects
    Texture albedoMapTex;
    Texture normalMapTex;

    Texture envMap;
    bool is_env;
    float envMap_intensity = 1.0f;
   
};



struct Camera
{
    glm::ivec2 resolution;
    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 view;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec2 fov;
    glm::vec2 pixelLength;
    float lensRadius;     // controls aperture size
    float focalDistance;  // distance to focal plane


};

struct RenderState
{
    Camera camera;
    unsigned int iterations;
    int traceDepth;
    std::vector<glm::vec3> image;
    std::string imageName;
};

struct PathSegment
{
    Ray ray;
    glm::vec3 color;
    int pixelIndex;
    int remainingBounces;
};

// Use with a corresponding PathSegment to do:
// 1) color contribution computation
// 2) BSDF evaluation: generate a new ray
struct ShadeableIntersection
{
  float t;
  glm::vec3 surfaceNormal;
  int materialId;

  glm::vec2 uv;
};
