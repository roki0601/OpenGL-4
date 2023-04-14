#include "skybox.h"
#include "pipeline.h"
#include "util.h"

SkyBox::SkyBox(const Camera* pCamera,
    const PersProjInfo& p)
{
    m_pCamera = pCamera;
    m_persProjInfo = p;

    m_pSkyboxTechnique = NULL;
    m_pCubemapTex = NULL;
    m_pMesh = NULL;
}


SkyBox::~SkyBox()
{
    SAFE_DELETE(m_pSkyboxTechnique);
    SAFE_DELETE(m_pCubemapTex);
    SAFE_DELETE(m_pMesh);
}


bool SkyBox::Init(const string& Directory,
    const string& PosXFilename,
    const string& NegXFilename,
    const string& PosYFilename,
    const string& NegYFilename,
    const string& PosZFilename,
    const string& NegZFilename)
{
    m_pSkyboxTechnique = new SkyboxTechnique();

    if (!m_pSkyboxTechnique->Init()) {
        printf("Error initializing the skybox technique\n");
        return false;
    }

    m_pSkyboxTechnique->Enable();
    m_pSkyboxTechnique->SetTextureUnit(0);

    m_pCubemapTex = new CubemapTexture(Directory,
        PosXFilename,
        NegXFilename,
        PosYFilename,
        NegYFilename,
        PosZFilename,
        NegZFilename);

    if (!m_pCubemapTex->Load()) {
        return false;
    }

    m_pMesh = new Mesh();

    return m_pMesh->LoadMesh("C:\\inj\\content\\Content\\sphere.obj");
}

/*Эта функция рендерит скайбокс. Мы начинаем с разрешения метода скайбокса.
  Затем мы встречаемся с новым API OpenGL - glGetIntegerv().
  Эта функция возвращает значение состояния OpenGL для перечисления, указанного в первом параметре.
  Второй параметр - это адрес на массив типа int, который получит состояние (в нашем случае достаточно одного значения в массиве).*/

void SkyBox::Render()
{
    m_pSkyboxTechnique->Enable();

    GLint OldCullFaceMode;
    glGetIntegerv(GL_CULL_FACE_MODE, &OldCullFaceMode);
    GLint OldDepthFuncMode;
    glGetIntegerv(GL_DEPTH_FUNC, &OldDepthFuncMode);

    glCullFace(GL_FRONT);
    glDepthFunc(GL_LEQUAL);

    Pipeline p;
    p.Scale(20.0f, 20.0f, 20.0f);
    p.Rotate(0.0f, 0.0f, 0.0f);
    p.WorldPos(m_pCamera->GetPos().x, m_pCamera->GetPos().y, m_pCamera->GetPos().z);
    p.SetCamera(m_pCamera->GetPos(), m_pCamera->GetTarget(), m_pCamera->GetUp());
    p.SetPerspectiveProj(m_persProjInfo);
    m_pSkyboxTechnique->SetWVP(p.GetWVPTrans());
    m_pCubemapTex->Bind(GL_TEXTURE0);
    m_pMesh->Render();

    glCullFace(OldCullFaceMode);
    glDepthFunc(OldDepthFuncMode);
}