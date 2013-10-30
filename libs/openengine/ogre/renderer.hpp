#ifndef OENGINE_OGRE_RENDERER_H
#define OENGINE_OGRE_RENDERER_H

/*
  Ogre renderer class
 */

#include <string>

// Static plugin headers
#ifdef ENABLE_PLUGIN_CgProgramManager
# include "OgreCgPlugin.h"
#endif
#ifdef ENABLE_PLUGIN_OctreeSceneManager
# include "OgreOctreePlugin.h"
#endif
#ifdef ENABLE_PLUGIN_ParticleFX
# include "OgreParticleFXPlugin.h"
#endif
#ifdef ENABLE_PLUGIN_GL
# include "OgreGLPlugin.h"
#endif
#ifdef ENABLE_PLUGIN_Direct3D9
# include "OgreD3D9Plugin.h"
#endif

#include "OgreTexture.h"
#include <OgreWindowEventUtilities.h>


struct SDL_Window;
struct SDL_Surface;

namespace Ogre
{
    class Root;
    class RenderWindow;
    class SceneManager;
    class Camera;
    class Viewport;
    class ParticleEmitterFactory;
    class ParticleAffectorFactory;
}

namespace OEngine
{
    namespace Render
    {
        struct WindowSettings
        {
            bool vsync;
            bool fullscreen;
            int window_x, window_y;
            int screen;
            std::string fsaa;
            std::string icon;
        };

        class Fader;

        class WindowSizeListener
        {
        public:
            virtual void windowResized (int x, int y) = 0;
        };

        class OgreRenderer
        {
            Ogre::Root *mRoot;
            Ogre::RenderWindow *mWindow;
            SDL_Window *mSDLWindow;
            Ogre::SceneManager *mScene;
            Ogre::Camera *mCamera;
            Ogre::Viewport *mView;
            #ifdef ENABLE_PLUGIN_CgProgramManager
            Ogre::CgPlugin* mCgPlugin;
            #endif
            #ifdef ENABLE_PLUGIN_OctreeSceneManager
            Ogre::OctreePlugin* mOctreePlugin;
            #endif
            #ifdef ENABLE_PLUGIN_ParticleFX
            Ogre::ParticleFXPlugin* mParticleFXPlugin;
            #endif
            #ifdef ENABLE_PLUGIN_GL
            Ogre::GLPlugin* mGLPlugin;
            #endif
            #ifdef ENABLE_PLUGIN_Direct3D9
            Ogre::D3D9Plugin* mD3D9Plugin;
            #endif
            Fader* mFader;
            std::vector<Ogre::ParticleEmitterFactory*> mEmitterFactories;
            std::vector<Ogre::ParticleAffectorFactory*> mAffectorFactories;

            WindowSizeListener* mWindowListener;

        public:
            OgreRenderer()
            : mRoot(NULL)
            , mWindow(NULL)
            , mSDLWindow(NULL)
            , mScene(NULL)
            , mCamera(NULL)
            , mView(NULL)
            , mWindowListener(NULL)
            #ifdef ENABLE_PLUGIN_CgProgramManager
            , mCgPlugin(NULL)
            #endif
            #ifdef ENABLE_PLUGIN_OctreeSceneManager
            , mOctreePlugin(NULL)
            #endif
            #ifdef ENABLE_PLUGIN_ParticleFX
            , mParticleFXPlugin(NULL)
            #endif
            #ifdef ENABLE_PLUGIN_GL
            , mGLPlugin(NULL)
            #endif
            #ifdef ENABLE_PLUGIN_Direct3D9
            , mD3D9Plugin(NULL)
            #endif
            , mFader(NULL)
            {
            }

            ~OgreRenderer() { cleanup(); }

            /** Configure the renderer. This will load configuration files and
            set up the Root and logging classes. */
            void configure(
                const std::string &logPath, // Path to directory where to store log files
                const std::string &renderSystem,
                const std::string &rttMode,
                bool _logging);      // Enable or disable logging

            /// Create a window with the given title
            void createWindow(const std::string &title, const WindowSettings& settings);

            /// Set up the scene manager, camera and viewport
            void adjustCamera(
                float fov=55,                      // Field of view angle
                float nearClip=5                   // Near clip distance
            );

            void setFov(float fov);

            /// Kill the renderer.
            void cleanup();

            void loadPlugins();

            void unloadPlugins();

            void update(float dt);

            /// Write a screenshot to file
            void screenshot(const std::string &file);

            float getFPS();

            void windowResized(int x, int y);

            /// Get the Root
            Ogre::Root *getRoot() { return mRoot; }

            /// Get the rendering window
            Ogre::RenderWindow *getWindow() { return mWindow; }

            /// Get the SDL Window
            SDL_Window *getSDLWindow() { return mSDLWindow; }

            /// Get the scene manager
            Ogre::SceneManager *getScene() { return mScene; }

            /// Get the screen colour fader
            Fader *getFader() { return mFader; }

            /// Camera
            Ogre::Camera *getCamera() { return mCamera; }

            /// Viewport
            Ogre::Viewport *getViewport() { return mView; }

            void setWindowListener(WindowSizeListener* listener) { mWindowListener = listener; }

            void adjustViewport();
        };
    }
}
#endif
