﻿
#ifndef UNTITLED_APPLICATION_H
#define UNTITLED_APPLICATION_H

#include <string>
#include <glad/gl.h>
#include <GLFW/glfw3.h>

class Application {
public:
    static const std::string& data_path(){return data_path_;}
    static void set_data_path(std::string data_path){data_path_=data_path;}

    /// 初始化OpenGL
    static void InitOpengl();

    static void Run();

    static void UpdateScreenSize();

    /// 每一帧内逻辑代码。
    static void Update();

    /// 逻辑代码执行后，应用到渲染。
    static void Render();

private:
    static std::string data_path_;//资源目录

    static GLFWwindow* glfw_window_;

};


#endif //UNTITLED_APPLICATION_H
