
#include "ParticleRenderer.hpp"
#include "ParticleSystem.hpp"

OpenGLRenderer::OpenGLRenderer()
{
    vao = 0;
    position_buf = 0;
    color_buf = 0;
    camera = nullptr;
    shader = nullptr;
}

OpenGLRenderer::~OpenGLRenderer()
{
    Shutdown();
}

void OpenGLRenderer::Init(ParticleSystem *sys)
{
    // particle system information
    assert(sys != nullptr);
    system = sys;

    // setup camera
    camera = new Camera();
    camera->Move(glm::vec3(0,0,1));

    // steup shader
    shader = new Program();
    shader->Add(new Shader("../shaders/vertex_shader.glsl", GL_VERTEX_SHADER));
    shader->Add(new Shader("../shaders/fragment_shader.glsl", GL_FRAGMENT_SHADER));
    shader->Compile();
    shader->Link();
    shader->Use();

    // generate
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // create position buffer
    glGenBuffers(1, &position_buf);
    glBindBuffer(GL_ARRAY_BUFFER, position_buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * system->Count(), system->Data()->position.get(), GL_STREAM_DRAW);
    glEnableVertexAttribArray(shader->GetAttribLocation("vertex"));
    glVertexAttribPointer(shader->GetAttribLocation("vertex"), 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), nullptr);

    // create color buffer
    glGenBuffers(1, &color_buf);
    glBindBuffer(GL_ARRAY_BUFFER, color_buf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * system->Count(), system->Data()->color.get(), GL_STREAM_DRAW);
    glEnableVertexAttribArray(shader->GetAttribLocation("color"));
    glVertexAttribPointer(shader->GetAttribLocation("color"), 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), nullptr);

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void OpenGLRenderer::Update()
{
    // bind
    shader->Use();
    glBindVertexArray(vao);

    // update shader
    shader->SetUniformValue("projection", camera->projection());
    shader->SetUniformValue("modelview", camera->view());

    // update position buffer
    glBindBuffer(GL_ARRAY_BUFFER, position_buf);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * system->AliveCount(), system->Data()->position.get());

    // update color buffer
    glBindBuffer(GL_ARRAY_BUFFER, color_buf);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec4) * system->AliveCount(), system->Data()->color.get());

    // unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
}

void OpenGLRenderer::Render()
{
    // bind
    shader->Use();
    glBindVertexArray(vao);

    // enable point sprite blending
    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);

    // draw
    glEnable(GL_TEXTURE_2D);
    for(size_t i = 0; i < system->AliveCount(); ++i)
    {
        glBindTexture(GL_TEXTURE_2D, system->Data()->textures[i]);
        glDrawArrays(GL_POINTS, (GLsizei) i, 1);
    }
    glDisable(GL_BLEND);

    // bind
    glBindVertexArray(0);
    glUseProgram(0);
}

void OpenGLRenderer::Shutdown()
{
    // delete buffers
    glDeleteBuffers(1, &position_buf);
    glDeleteBuffers(1, &color_buf);
    glDeleteVertexArrays(1, &vao);

    // delete shader
    delete shader;
}
