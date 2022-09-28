#include "core.hpp"

constexpr double averageTick = 1/60.0;
int main(){

	RandysEngine::Rendering_Engine renderer;

    renderer.addLayerBack<RandysEngine::layer_minitree>();
    
    auto node1 = renderer.createNode<RandysEngine::layer_minitree>(0);

    auto node2 = renderer.createNode<RandysEngine::layer_minitree>(node1);

    auto nodeCamera = renderer.createNode<RandysEngine::layer_minitree>(node1);

    renderer.addModel<RandysEngine::layer_minitree>(node2);

    renderer.addCamera<RandysEngine::layer_minitree>(nodeCamera);
    renderer.setActiveCamera<RandysEngine::layer_minitree>(nodeCamera);

    unsigned int meshN = renderer.addMesh<RandysEngine::layer_minitree>(node2,"resources/cube.obj");
#ifndef __3DS__
    renderer.addTexture<RandysEngine::layer_minitree>(node2,meshN,"resources/face.jpg");
#else
    renderer.addTexture<RandysEngine::layer_minitree>(node2,meshN,"romfs:/gfx/kitten.t3x");
#endif

    renderer.setTranslateNode(node2, 0.0f,0.0f,-5.0f);

    while(renderer.isAppRunning()){
        if(renderer.readKeyPressed(RandysEngine::KeyInput::exit)){
            renderer.closeApp();
        }
        if(renderer.readKeyPressed(RandysEngine::KeyInput::left)){
            renderer.RotateNode(node2,0.0f,-0.001f,0.0f);
        }
        if(renderer.readKeyPressed(RandysEngine::KeyInput::right)){
            renderer.RotateNode(node2,0.0f,0.001f,0.0f);
        }
        if(renderer.readKeyPressed(RandysEngine::KeyInput::up)){
            renderer.ScaleNode(node1,0.0f,0.0001f,0.0f);
        }
        if(renderer.readKeyPressed(RandysEngine::KeyInput::down)){
            renderer.ScaleNode(node1,0.0f,-0.0001f,0.0f);
        }

        renderer.runFrame();
    }

    return 0;

}
