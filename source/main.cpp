﻿#define GLFW_INCLUDE_NONE

#include <stdlib.h>
#include <stdio.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "utils/application.h"
#include "renderer/mesh_filter.h"
#include "renderer/material.h"
#include "renderer/mesh_renderer.h"
#include "renderer/camera.h"
#include "component/game_object.h"
#include "component/transform.h"
#include "control/input.h"
#include "control/key_code.h"

using namespace std;

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}
/// 键盘回调
/// \param window
/// \param key 键盘按键编码
/// \param scancode
/// \param action 0松开 1按下 2一直按下
/// \param mods
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Input::RecordKey(key,action);
}

GLFWwindow* window;

//初始化OpenGL
void init_opengl()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(960, 640, "Simple example", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    glfwSetKeyCallback(window, key_callback);
}

int main(void)
{
    Application::set_data_path("../data/");
    init_opengl();

    //创建模型 GameObject
    GameObject* go=new GameObject("something");
    go->set_layer(0x01);

    //挂上 Transform 组件
    auto transform=dynamic_cast<Transform*>(go->AddComponent("Transform"));

    //挂上 MeshFilter 组件
    auto mesh_filter=dynamic_cast<MeshFilter*>(go->AddComponent("MeshFilter"));
    mesh_filter->LoadMesh("model/fishsoup_pot.mesh");

    //挂上 MeshRenderer 组件
    auto mesh_renderer=dynamic_cast<MeshRenderer*>(go->AddComponent("MeshRenderer"));
    Material* material=new Material();//设置材质
    material->Parse("material/fishsoup_pot.mat");
    mesh_renderer->SetMaterial(material);

    //创建相机2 GameObject
    auto go_camera_2=new GameObject("main_camera");
    //挂上 Transform 组件
    auto transform_camera_2=dynamic_cast<Transform*>(go_camera_2->AddComponent("Transform"));
    transform_camera_2->set_position(glm::vec3(1, 0, 10));
    //挂上 Camera 组件
    auto camera_2=dynamic_cast<Camera*>(go_camera_2->AddComponent("Camera"));
    //第二个相机不能清除之前的颜色。不然用第一个相机矩阵渲染的物体就被清除 没了。
    camera_2->set_clear_flag(GL_DEPTH_BUFFER_BIT);
    camera_2->set_depth(1);
    camera_2->set_culling_mask(0x02);

    //创建相机1 GameObject
    auto go_camera_1=new GameObject("main_camera");
    //挂上 Transform 组件
    auto transform_camera_1=dynamic_cast<Transform*>(go_camera_1->AddComponent("Transform"));
    transform_camera_1->set_position(glm::vec3(0, 0, 10));
    //挂上 Camera 组件
    auto camera_1=dynamic_cast<Camera*>(go_camera_1->AddComponent("Camera"));
    camera_1->set_depth(0);


    while (!glfwWindowShouldClose(window))
    {
        float ratio;
        int width, height;

        glfwGetFramebufferSize(window, &width, &height);
        glViewport(0, 0, width, height);
        ratio = width / (float) height;

        //设置相机1
        camera_1->SetView(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
        camera_1->SetProjection(60.f, ratio, 1.f, 1000.f);

        //设置相机2
        camera_2->SetView(glm::vec3(transform_camera_2->position().x, 0, 0), glm::vec3(0, 1, 0));
        camera_2->SetProjection(60.f, ratio, 1.f, 1000.f);

        //旋转物体
        if(Input::GetKeyDown(KEY_CODE_R) || Input::GetKeyDown(KEY_CODE_RIGHT_ALT)){
            static float rotate_eulerAngle=0.f;
            rotate_eulerAngle+=0.1f;
            glm::vec3 rotation=transform->rotation();
            rotation.x=rotate_eulerAngle;
            transform->set_rotation(rotation);
        }

        //将状态为弹起的按键清理掉
        Input::Update();

        //遍历所有相机，每个相机的View Projection，都用来做一次渲染。
        Camera::Foreach([&](){
            mesh_renderer->Render();
        });

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}