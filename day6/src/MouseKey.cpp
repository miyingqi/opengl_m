#include"MouseKey.h"
PLAYER::PLAYER(std::string path){
    static Model pp(path.c_str());
    p=&pp;
    static Camera cam(glm::vec3(0.0f,0.0f,0.0f));
    p_c=&cam;
}
void PLAYER::Draw(Shader shader,int wid,int heig){
    glm::mat4 proj=glm::perspective(glm::radians( p_c->Zoom), (float)wid/ (float)heig, 0.1f, 100.0f);
    glm::mat4 vi= p_c->GetViewMatrix();
    shader.setMat4("projection", proj);
    shader.setMat4("view", vi);
    shader.setMat4("model",translate(glm::mat4(1.0f),glm::vec3(p_c->Position.x,p_c->Position.y-0.2F,p_c->Position.z)));
    p->Draw(shader);
}