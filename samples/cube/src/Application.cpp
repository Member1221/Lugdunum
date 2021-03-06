#include "Application.hpp"

#include <lug/Graphics/Light/Directional.hpp>
#include <lug/Graphics/Scene/MeshInstance.hpp>

// TODO: Remove this when the ResourceManager is done
#include <lug/Graphics/Renderer.hpp>
#include <lug/Graphics/Vulkan/Renderer.hpp>

Application::Application() : lug::Core::Application::Application{{"cube", {0, 1, 0}}} {
    getRenderWindowInfo().windowInitInfo.title = "Hello Cube";
}

Application::~Application() {
    // TODO: Remove this when the ResourceManager is done
    lug::Graphics::Renderer* renderer = _graphics.getRenderer();
    lug::Graphics::Vulkan::Renderer* vkRender = static_cast<lug::Graphics::Vulkan::Renderer*>(renderer);

    vkRender->getDevice().waitIdle();
}

bool Application::init(int argc, char* argv[]) {
    if (!lug::Core::Application::init(argc, argv)) {
        return false;
    }

    // Create the mesh of the cube
    {
        _cube = _graphics.createMesh("Cube");

        // 1. pos
        // 2. color
        // 3. normal
        // 4. texture uv
        _cube->vertices = {
            // Back
            {{-1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}},
            {{1.0f, -1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}},
            {{-1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}},
            {{1.0f, 1.0f, -1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}},

            // Front
            {{-1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 1.0}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}},
            {{1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 1.0}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}},
            {{-1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}},

            // Left
            {{-1.0f, -1.0f, -1.0f}, {1.0f, 0.0f, 0.0}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{-1.0f, -1.0f, 1.0f}, {1.0f, 0.0f, 0.0}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{-1.0f, 1.0f, -1.0f}, {1.0f, 0.0f, 0.0}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},
            {{-1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 0.0}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},

            // Right
            {{1.0f, -1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
            {{1.0f, -1.0f, 1.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}},
            {{1.0f, 1.0f, -1.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}},
            {{1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}},

            // Bottom
            {{-1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}},
            {{-1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}},
            {{1.0f, -1.0f, -1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}},
            {{1.0f, -1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}},

            // Top
            {{-1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 1.0}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}},
            {{-1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
            {{1.0f, 1.0f, -1.0f}, {0.0f, 1.0f, 1.0}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
            {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}
        };

        _cube->indices = {
            // Back
            0, 1, 2,
            1, 3, 2,

            // Front
            6, 5, 4,
            7, 5, 6,

            // Left
            10, 9, 8,
            11, 9, 10,

            // Right
            14, 12, 13,
            15, 14, 13,

            // Bottom
            17, 19, 16,
            19, 18, 16,

            // Top
            23, 21, 20,
            22, 23, 20
        };

        if (!_cube->load()) {
            return false;
        }
    }

    // Create the scene
    _scene = _graphics.createScene();

    // Add cube to scene
    {
        std::unique_ptr<lug::Graphics::Scene::MeshInstance> cubeInstance = _scene->createMeshInstance("cube instance", _cube.get());
        _scene->getRoot()->createSceneNode("cube instance node", std::move(cubeInstance));
    }

    // Add directional light to scene
    {
        std::unique_ptr<lug::Graphics::Light::Light> light = _scene->createLight("light", lug::Graphics::Light::Light::Type::Directional);

        // Set the diffuse to white color and the direction to the viewing direction of the camera
        light->setDiffuse({1.0f, 1.0f, 1.0f});
        static_cast<lug::Graphics::Light::Directional*>(light.get())->setDirection({-10.0f, -10.0f, -10.0f});

        _scene->getRoot()->createSceneNode("light node", std::move(light));
    }

    // Create a camera
    std::unique_ptr<lug::Graphics::Render::Camera> camera = _graphics.createCamera("camera");
    camera->setScene(_scene.get());

    // Add camera to scene
    {
        std::unique_ptr<lug::Graphics::Scene::MovableCamera> movableCamera = _scene->createMovableCamera("movable camera", camera.get());
        _scene->getRoot()->createSceneNode("movable camera node", std::move(movableCamera));
    }

    // Attach camera to RenderView
    {
        auto& renderViews = _graphics.getRenderer()->getWindow()->getRenderViews();
        renderViews[0]->attachCamera(std::move(camera));
    }

    // Set the position and rotation of the camera
    {
        auto& renderViews = _graphics.getRenderer()->getWindow()->getRenderViews();

        renderViews[0]->getCamera()->setPosition({5.0f, 5.0f, 5.0f}, lug::Graphics::Node::TransformSpace::World);
        renderViews[0]->getCamera()->lookAt({0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, lug::Graphics::Node::TransformSpace::World);
    }

    return true;
}

void Application::onEvent(const lug::Window::Event& event) {
    if (event.type == lug::Window::Event::Type::Close) {
        close();
    }
}

void Application::onFrame(const lug::System::Time& elapsedTime) {
    _rotation += (0.001f * elapsedTime.getMilliseconds<float>());

    if (_rotation > 360.0f) {
        _rotation -= 360.0f;
    }

    auto cubeNode = _scene->getSceneNode("cube instance node");

    cubeNode->setRotation(lug::Math::Quatf(_rotation, {0.0f, 1.0f, 0.0f}));
    cubeNode->rotate(lug::Math::Quatf(_rotation, {0.0f, 0.0f, 1.0f}));
}
