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
 * \file
 * \brief
 * \details
 */
#ifndef __INC_HEARTH_CORE_LOGGER_HPP__
#define __INC_HEARTH_CORE_LOGGER_HPP__ 1
#include <memory>
#include <queue>
#include <string_view>
#include <spdlog/spdlog.h>

namespace Hearth {

  /**
   * \brief   ...
   * \details ...
   */
  class ConsoleLogger final {
  public:
    /**
     * \brief   Initializes the logging system.
     * \details Creates the necessary objects for the logging system to perform logs.
     */
    static void initialize();

    /**
     * \brief     Prints a trace level log.
     * \details   A trace level log is a very fine grain log. It usually has very little importance as they are usually
     *            scattered all around to trace issues, hence *trace*.
     * \param[in] log The log to print.
     */
    static void printTrace(std::string_view log) noexcept;

    /**
     * \brief     Prints a debug level log.
     * \details   A debug level log is another fine grain log. It usually has little importance as it is just recounting
     *            or describing actions that happened. They are useful for debugging, hence *debug*, and are often left
     *            in source to keep track of issues or spot new ones.
     * \param[in] log The log to print.
     */
    static void printDebug(std::string_view log) noexcept;

    /**
     * \brief     Prints an info level log.
     * \details   An info level log is less common than a debug. It usually is, as expected, informational. It tells
     *            developers if something they are doing is not as expected, but doesn't necessarily matter.
     * \param[in] log The log to print.
     */
    static void printInfo(std::string_view log) noexcept;

    /**
     * \brief     Prints a warning level log.
     * \details   A warning level log is an important one. It warns developers that something they are doing could
     *            actually break something or worse.
     * \param[in] log The log to print.
     */
    static void printWarning(std::string_view log) noexcept;

    /**
     * \brief     Prints an error level log.
     * \details   An error level log is close to the highest priority issue. It warns developers that something did go
     *            wrong and it lead to unexpected behaviour or even a system crash.
     * \param[in] log The log to print.
     */
    static void printError(std::string_view log) noexcept;

    /**
     * \brief     Prints a critical level log.
     * \details   A critical level log is the highest priority issue. Something went disastrous and it likely lead to
     *            the crash of the application, and potentially left things in a corrupted or undefined state that
     *            cannot be recovered from. Sometimes these are used to provide critical messages instead of issues,
     *            such that, a specific action must be performed or else bad things will happen.
     * \param[in] log The log to print.
     */
    static void printCritical(std::string_view log) noexcept;

    /**
     * \brief     Sets the \c Console severity level.
     * \details   The severity describes at what importance or significance a log is. The \c Logger has a certain
     *            severity level that it will print at. Anything below that level will not get printed.
     * \param[in] level The new severity level for the logger.
     */
    static void setSeverity(spdlog::level::level_enum level) noexcept;

    /**
     * \brief   Gets the spdlog logger instance.
     * \details This allows us to perform more fine grain usage of the logger, such as using the formatting
     *          capabilities. We recommend using the provided macros with this approach.
     * \returns The spdlog logger instance.
     */
    static auto getLoggerInstance() noexcept
      -> std::shared_ptr<spdlog::logger>&;

  private:
    /**
     * \brief   The logger that will be used to print logs.
     * \details ...
     */
    inline static std::shared_ptr<spdlog::logger> m_logger;
  };

}

#if HEARTH_DEBUG
#  define HEARTH_LOGGER_TRACE(...)    ::Hearth::ConsoleLogger::getLoggerInstance()->trace(__VA_ARGS__)
#  define HEARTH_LOGGER_DEBUG(...)    ::Hearth::ConsoleLogger::getLoggerInstance()->debug(__VA_ARGS__)
#  define HEARTH_LOGGER_INFO(...)     ::Hearth::ConsoleLogger::getLoggerInstance()->info(__VA_ARGS__)
#  define HEARTH_LOGGER_WARN(...)     ::Hearth::ConsoleLogger::getLoggerInstance()->warn(__VA_ARGS__)
#  define HEARTH_LOGGER_ERROR(...)    ::Hearth::ConsoleLogger::getLoggerInstance()->error(__VA_ARGS__)
#  define HEARTH_LOGGER_CRITICAL(...) ::Hearth::ConsoleLogger::getLoggerInstance()->critical(__VA_ARGS__)
#else
#  define HEARTH_LOGGER_TRACE(...)
#  define HEARTH_LOGGER_DEBUG(...)
#  define HEARTH_LOGGER_INFO(...)
#  define HEARTH_LOGGER_WARN(...)
#  define HEARTH_LOGGER_ERROR(...)
#  define HEARTH_LOGGER_CRITICAL(...)
#endif

#endif /* __INC_HEARTH_CORE_LOGGER_HPP__ */