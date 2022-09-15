#include "core.hpp"

constexpr double averageTick = 1/60.0;
int main(){

	RandysEngine::Rendering_Engine renderer;

    renderer.addLayerBack<RandysEngine::layer_minitree>();
    
    auto node1 = renderer.createNode<RandysEngine::layer_minitree>(0);

    auto node2 = renderer.createNode<RandysEngine::layer_minitree>(node1);

    renderer.addModel<RandysEngine::layer_minitree>(node2);

    unsigned int meshN = renderer.addMesh<RandysEngine::layer_minitree>(node2,"triangle");

    renderer.addTexture<RandysEngine::layer_minitree>(node2,meshN,"romfs:/gfx/face.t3x");

    while(renderer.isAppRunning()){
        if(renderer.readKeyPressed(RandysEngine::KeyInput::exit)){
            renderer.closeApp();
        }
        renderer.runFrame();
    }

    return 0;

}
