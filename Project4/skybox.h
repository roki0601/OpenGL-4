#pragma once
#ifndef SKYBOX_H
#define	SKYBOX_H

#include "camera.h"
#include "skybox_technique.h"
#include "cubemap_texture.h"
#include "mesh.h"

/*Класс скайбокса включает несколько различных элементов - метод, кубическая текстура и модель сферы или куба.*/

class SkyBox
{
public:
    SkyBox(const Camera* pCamera, const PersProjInfo& p);

    ~SkyBox();

    bool Init(const string& Directory,
        const string& PosXFilename,
        const string& NegXFilename,
        const string& PosYFilename,
        const string& NegYFilename,
        const string& PosZFilename,
        const string& NegZFilename);

    void Render();

private:
    SkyboxTechnique* m_pSkyboxTechnique;
    const Camera* m_pCamera;
    CubemapTexture* m_pCubemapTex;
    Mesh* m_pMesh;
    PersProjInfo m_persProjInfo;
};

#endif	/* SKYBOX_H */
