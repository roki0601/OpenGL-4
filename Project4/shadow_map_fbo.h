#ifndef SHADOWMAPFBO_H
#define SHADOWMAPFBO_H

#include <GL/glew.h>

class ShadowMapFBO
{
public:
    ShadowMapFBO();

    ~ShadowMapFBO();

    bool Init(unsigned int WindowWidth, unsigned int WindowHeight);

    void BindForWriting();

    void BindForReading(GLenum TextureUnit);

private:
    GLuint m_fbo; //указатель на текущий FBO
    GLuint m_shadowMap; //указатель на текстуру, которая будет использована для прикрепления к DEPTH_ATTACHMENT
};

#endif /* SHADOWMAPFBO_H */