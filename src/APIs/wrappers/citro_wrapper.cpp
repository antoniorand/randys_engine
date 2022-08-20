
#ifdef __3DS__
#include "citro_wrapper.hpp"
namespace RandysEngine{

    #define DISPLAY_TRANSFER_FLAGS \
	(GX_TRANSFER_FLIP_VERT(0) | GX_TRANSFER_OUT_TILED(0) | GX_TRANSFER_RAW_COPY(0) | \
	GX_TRANSFER_IN_FORMAT(GX_TRANSFER_FMT_RGBA8) | GX_TRANSFER_OUT_FORMAT(GX_TRANSFER_FMT_RGB8) | \
	GX_TRANSFER_SCALING(GX_TRANSFER_SCALE_NO))

    float verticesConverter(float point, unsigned int axis){
        float devolver= 0;

        switch(axis){
            case(0):
                devolver = 200*point + 200;
            break;
            case(1):
                devolver = 120*point + 120;
            break;
            case(2):
                devolver = point;
            break;
        } 
        std::cout << devolver << std::endl;
        return devolver;
    }

    citro_mesh_resource::citro_mesh_resource(std::string input) noexcept{
        float convertedVertices[9] =
        {200.0f, 200.0f, 0.5f ,
	     100.0f, 40.0f, 0.5f ,
	     300.0f, 40.0f, 0.5f };

        /*for(unsigned int i = 0; i < 9; i++){
            convertedVertices[i] = verticesConverter(
                vertices[i], i/3);
        }*/

        sizeVertices = sizeof(convertedVertices);
        numberVertices = sizeVertices/sizeof(convertedVertices[0]);

        vbo_data = linearAlloc(sizeVertices);
        memcpy(vbo_data,convertedVertices, sizeVertices);

        // Configure buffers
        C3D_BufInfo* bufInfo = C3D_GetBufInfo();
        BufInfo_Init(bufInfo);
        BufInfo_Add(bufInfo, vbo_data, sizeVertices, 1, 0x0);
    }

    citro_mesh_resource::~citro_mesh_resource() noexcept{
        linearFree(vbo_data);
    }

    void citro_mesh_resource::draw() const noexcept{
        
        // Draw the VBO
        C3D_DrawArrays(GPU_TRIANGLES, 0, numberVertices);

    }

    citro_shader::citro_shader() noexcept{
        // Load the vertex shader, create a shader program and bind it
        vshader_dvlb = DVLB_ParseFile((u32*)vshader_shbin,
        vshader_shbin_size);
        shaderProgramInit(&shaderProgram);
        shaderProgramSetVsh(&shaderProgram, &vshader_dvlb->DVLE[0]);
        C3D_BindProgram(&shaderProgram);

        // Get the location of the uniforms
	    uLoc_projection = shaderInstanceGetUniformLocation(shaderProgram.vertexShader, "projection");
        
        // Configure attributes for use with the vertex shader
        C3D_AttrInfo* attrInfo = C3D_GetAttrInfo();
        AttrInfo_Init(attrInfo);
        AttrInfo_AddLoader(attrInfo, 0, GPU_FLOAT, 3); // v0=position
        AttrInfo_AddFixed(attrInfo, 1); // v1=color

        // Set the fixed attribute (color) to solid white
        C3D_FixedAttribSet(1, 1.0, 1.0, 1.0, 1.0);

        // Compute the projection matrix
        Mtx_OrthoTilt(&projection, 0.0, 400.0, 0.0, 240.0, 0.0, 1.0, true);
        
        // Configure the first fragment shading substage to just pass through the vertex color
        // See https://www.opengl.org/sdk/docs/man2/xhtml/glTexEnv.xml for more insight
        C3D_TexEnv* env = C3D_GetTexEnv(0);
        C3D_TexEnvInit(env);
        C3D_TexEnvSrc(env, C3D_Both, GPU_PRIMARY_COLOR, (GPU_TEVSRC)0, (GPU_TEVSRC)0);
        C3D_TexEnvFunc(env, C3D_Both, GPU_REPLACE);
    }

    citro_shader::~citro_shader() noexcept{
        shaderProgramFree(&shaderProgram);
        DVLB_Free(vshader_dvlb);
    }

    void citro_shader::useShader() const noexcept{
        // Update the uniforms
    	C3D_FVUnifMtx4x4(GPU_VERTEX_SHADER, uLoc_projection, &projection);
    }

    citro_screen::citro_screen() noexcept{
        
        C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
        target = 
        C3D_RenderTargetCreate(
            240, 400, GPU_RB_RGBA8, GPU_RB_DEPTH24_STENCIL8);
        C3D_RenderTargetSetOutput(
            target, GFX_TOP, GFX_LEFT, DISPLAY_TRANSFER_FLAGS);
    };

    citro_screen::~citro_screen() noexcept{
        C3D_Fini();
    }

    bool citro_screen::isAppRunning() const noexcept{
        return (aptMainLoop() && running);
    }

    void citro_screen::closeApp() noexcept{
        running = false;
    }

    bool citro_screen::getInputPressed(KeyInput input) const noexcept{
        bool devolver = false;
        hidScanInput();
        u32 kDown = hidKeysDown();
        switch (input){
            case KeyInput::exit :
                if((kDown & KEY_START))
                    devolver = true;
            break;
            default: 
            break;
        }
        return devolver;
    }

    constexpr int CLEAR_COLOR = 0x68B0D8FF;

    void citro_screen::swapBuffers() const noexcept{
        C3D_FrameEnd(0);
    };

    void citro_screen::prepareDraw() const noexcept{
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C3D_RenderTargetClear(target, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
		C3D_FrameDrawOn(target);
    }

    citro_main::citro_main() noexcept{

        gfxInitDefault();
        consoleInit(GFX_BOTTOM, NULL);
        std::cout << "Hemlo\n";

    };

    citro_main::~citro_main() noexcept{
        gfxExit();
    }

}
#endif