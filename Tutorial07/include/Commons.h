#pragma once

struct SimpleVertex
{
    XMFLOAT3 Pos;
    XMFLOAT2 Tex;

};



struct CBChangesEveryFrame
{
    XMMATRIX mWorld;
    XMFLOAT4 vMeshColor;
};
struct Vector3
    //we put a vector structure to help us move the cube,
    //we initialize everything to 0 so that there is no error
{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct Camera
{
    XMMATRIX mView;
    XMMATRIX mProjection;
};
