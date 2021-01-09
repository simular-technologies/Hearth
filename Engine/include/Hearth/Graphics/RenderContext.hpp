//
// Created by root on 11/2/2020.
//

/* Copyright (c) 2020 Simular Games, LLC.
 * -------------------------------------------------------------------------------------------------
 *
 * MIT License
 * -------------------------------------------------------------------------------------------------
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * -------------------------------------------------------------------------------------------------
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/**
 * \file    RenderContext.hpp
 * \brief   ...
 * \details ...
 */
#ifndef __HEARTH_GFX_RENDER_CONTEXT_HPP__
#define __HEARTH_GFX_RENDER_CONTEXT_HPP__ 1
#include <memory>
#include "../Core/Config.hpp"
#include "Surface.hpp"

namespace Hearth {

  // Foward.
  class Application;
  struct IWindow;

  /**
   * \brief   Describes the different types of graphics API's available.
   * \details ...
   */
  enum struct GraphicsAPI {
    Undefined,
    OpenGL,
    Vulkan,
    DirectX11,
    DirectX12,
    Metal,
  };

  /**
   * \brief   The information needed to create a new render context.
   * \details ...
   */
  struct RenderContextCreateInfo {
    /**
     * \brief   The application to register the render context with.
     * \details Application's can have multiple render contexts. But the contexts are not owned by
     *          the Application. They are owned by the renderer they come from.
     */
    const Application* app;

    /**
     * \brief   The requested graphics API to be used by the render context.
     * \details If graphics API that is not enabled is selected, a runtime error will be thrown.
     */
    GraphicsAPI requestedAPI;
  };

  /**
   * \brief   Represents
   * \details Render contexts are responsible for creating resources that pertain to the graphics
   *          API the context was create for. All resources are shared by from the render context
   *          therefore the render context handles their allocations and deallocations.
   */
  struct IRenderContext {
    /**
     * \brief   Default destructor.
     * \details ...
     */
    virtual ~IRenderContext() noexcept = default;

    /**
     * \brief     Creates a new surface from the given window.
     * \details   ...
     * \param[in] wnd The window to create a surface from.
     * \returns   The created surface if successful or nullptr if failed.
     */
    virtual ISurface* createSurface(const IWindow* wnd) noexcept = 0;

    /**
     * \brief     Destroys a provided surface.
     * \details   Because of
     * \param[in] surface The surface to destroy.
     */
    virtual void destroySurface(ISurface* surface) noexcept = 0;

  public:
    /**
     * \brief   Gets the graphics API for the render context.
     * \details ...
     * \returns The graphics API the render context was created with.
     */
    [[nodiscard]]
    GraphicsAPI gfxApi() const noexcept { return mGraphicsAPI; }

  private:
    /**
     * \brief   The graphics API the render context was created with.
     * \details ...
     */
    GraphicsAPI mGraphicsAPI = GraphicsAPI::Undefined;
  };

  /**
   * \brief   Creates a render context from the given information.
   * \details The returned render context will be valid if provided create information is also
   *          valid. A case where the information may not be valid is, if the application or
   *          window is null, or if the requested graphics API is not enabled for the platform.
   * \returns A pointer to a render context instance, if created, otherwise nullptr.
   */
  HEARTHAPI  IRenderContext*
  HEARTHCALL createRenderContext(const RenderContextCreateInfo* createInfo) noexcept;

  /**
   * \brief     Destroys a render context.
   * \details   ...
   * \param[in] rdrctx The render context to destroy.
   * */
  HEARTHAPI  void
  HEARTHCALL destroyRenderContext(IRenderContext* rdrctx) noexcept;

}

#endif /* __HEARTH_GFX_RENDER_CONTEXT_HPP__ */