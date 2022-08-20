#pragma once
#include "base_wrapper.hpp"
#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>
#include "vshader_shbin.h"

#include <iostream>
#include <string>

namespace RandysEngine{

    struct citro_matrix : matrix_wrapper<citro_matrix>{
        
    };  

    struct citro_mesh_resource : mesh_resource_wrapper<citro_mesh_resource>{
        void* vbo_data;
        std::size_t numberVertices, sizeVertices;
        //C2D_TextBuf staticTextBuf;
        //C2D_Text txt_helloWorld;


        citro_mesh_resource(std::string file) noexcept;
        citro_mesh_resource(const citro_mesh_resource& other) noexcept{
            vbo_data = other.vbo_data;
        }
        citro_mesh_resource& operator=(const citro_mesh_resource& other) noexcept{
            vbo_data = other.vbo_data;
            return *this;
        }
       ~citro_mesh_resource() noexcept;
        void draw() const noexcept;
    
    };

    struct citro_shader : shader_wrapper<citro_shader>{
        DVLB_s* vshader_dvlb;
        shaderProgram_s shaderProgram;
        C3D_Mtx projection;
        int uLoc_projection;

        citro_shader() noexcept;
       ~citro_shader() noexcept;

        void useShader() const noexcept;
    };

    struct citro_screen : screen_wrapper<citro_screen>{

        C3D_RenderTarget* target;
        
        bool running = true;

        citro_screen() noexcept;
       ~citro_screen() noexcept;

        void changeWindowSize(int e_width,int e_height) noexcept{};

        void swapBuffers() const noexcept;

        bool getInputPressed(KeyInput input) const noexcept;

        bool isAppRunning() const noexcept;

        void closeApp() noexcept;

        void prepareDraw() const noexcept;

    };

    struct citro_main : initializer_wrapper<citro_main>{

        citro_main() noexcept;
       ~citro_main() noexcept;

    };

}
