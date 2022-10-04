#pragma once

#include <cstddef>
#include <string>
#include <array>


namespace RandysEngine{

    struct matrix_wrapper{

        std::array<float,3> translation{0.0f,0.0f,0.0f};
        std::array<float,3> rotation{0.0f,0.0f,0.0f};
        std::array<float,3> scalation{1.0f,1.0f,1.0f};

        float fov{0.0f}, aspect{0.0f}, near{0.0f}, far{0.0f};
        
        bool changed{true},perspective{false};

    };

    struct Vertex{
        float x, y, z; //Position
        float coordX, coordY; //Texture position
    };

    template<typename api>
    struct mesh_resource_wrapper{ 

        std::size_t size_loadedVertices{0}, count_loadedVertices{0};

        virtual ~mesh_resource_wrapper() noexcept{};

        void draw() const noexcept {
            static_cast<api*>(this)->draw();
        }

        protected:

            std::vector<Vertex> loadModel(std::string file) noexcept{
                return static_cast<api*>(this)->loadModel(file);
            }
    };

    template<typename api>
    struct texture_resource_wrapper{

        virtual ~texture_resource_wrapper() noexcept{};

        void use() noexcept{
            static_cast<api*>(this)->use();
        }
        void unlink() noexcept{
            static_cast<api*>(this)->unlink();
        }
    };

    template<typename api>
    struct shader_wrapper{

        virtual ~shader_wrapper() noexcept{};

        void useShader() noexcept{
            static_cast<api*>(this)->useShader();
        }

        // utility uniform functions
        void setBool(const std::string &name, bool value) const{
            static_cast<api*>(this)->setBool(name,value);
        }
        void setInt(const std::string &name, int value) const{
            static_cast<api*>(this)->setInt(name,value);
        }
        void setFloat(const std::string &name, float value) const{
            static_cast<api*>(this)->setFloat(name,value);
        }
        
    };

    template<typename api>
    struct initializer_wrapper {
        
        initializer_wrapper() noexcept{};
        virtual ~initializer_wrapper() noexcept{};

    };

    
    enum class KeyInput : unsigned int{
        exit = 0,
        left = 1,
        right = 2,
        up = 3,
        down = 4,
        a_button = 5,
        b_button = 6,
        x_button = 7,
        y_button = 8
    };

    template<typename api>
    struct screen_wrapper{

        int width {400},height{240};

        virtual ~screen_wrapper() noexcept{};

        void changeWindowSize(int e_width, int e_height) noexcept{
            static_cast<api*>(this)->changeWindowSize(e_width,e_height);
        }

        void swapBuffers() const noexcept{
            static_cast<api*>(this)->swapBuffers();
        }

        void clearDepth() const noexcept{
            static_cast<api*>(this)->clearDepth();
        }

        bool getInputPressed(KeyInput input) const noexcept{
            return static_cast<api*>(this)->getInput();
        }

        bool isAppRunning() const noexcept{
            return static_cast<api*>(this)->isAppRunning();
        }

        void closeApp() noexcept{
            return static_cast<api*>(this)->closeApp();
        }

        void prepareDraw() const noexcept{
            static_cast<api*>(this)->prepareDraw();
        }

    };

}
