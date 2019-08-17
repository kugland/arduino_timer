#ifndef ARDUINO_TIMER_HPP_2243B123BD6C4A0914C8ED5817D61881DDA0F390
#define ARDUINO_TIMER_HPP_2243B123BD6C4A0914C8ED5817D61881DDA0F390

///
/// Arduino Timer namespace
///
namespace timer {

  // Forward declaration
  template <class... Timers>
  void wait(Timers&... timers);

  ///
  /// @brief      Base timer class
  ///
  /// @tparam     TimeFunc  Timer function (<code>millis</code> or <code>micros</code>)
  /// @tparam     TimeType  Internal type for time-keeping (must be an unsigned integral type)
  /// @tparam     Periodic  True for periodic, false for one-shot
  ///
  template <unsigned long (*TimeFunc)(), typename TimeType, bool Periodic>
  class base_timer
  {
    // There is no <type_traits> in the official Arduino package.
    static_assert(
      static_cast<TimeType>(0) < static_cast<TimeType>(-1),
      "TimeType must be an unsigned integral type"
    );

    TimeType _start_time  = 0;
    TimeType _interval    = 0;
    void   (*_callback)() = nullptr;

  public:

    ///
    /// @brief      Constructs an idle (stopped) timer.
    ///
    base_timer() = default;

    ///
    /// @brief      Constructs a timer and start it immediately.
    ///
    /// @param[in]  interval  Time interval
    /// @param[in]  callback  Callback (can be null)
    ///
    base_timer(TimeType interval, void (*callback)() = nullptr)
    {
      start(interval, callback);
    }

    // Delete copy & move constructor and copy assignment.
    base_timer(const base_timer&)            = delete;
    base_timer(base_timer&&)                 = delete;
    base_timer& operator=(const base_timer&) = delete;

    ///
    /// @brief      Start the timer
    ///
    /// @param[in]  interval  Time interval
    /// @param[in]  callback  Callback (can be null)
    ///
    void start(TimeType interval, void (*callback)() = nullptr)
    {
      _start_time = TimeFunc();
      _interval   = interval;
      _callback   = callback;
    }

    ///
    /// @brief      Stop the timer
    ///
    void stop()
    {
      _interval = 0;
    }

    ///
    /// @brief      Test if interval time has already passed since started,
    ///             calling the callback function when appropriate. If the timer
    ///             is periodic, it is then restarted, otherwise it is stopped.
    ///
    /// @return     True if interval time has already passed, false otherwise.
    ///
    bool tick()
    {
      if (started()) {
        const TimeType now = TimeFunc();
        if ((now - _start_time) > _interval) {
          if (Periodic) _start_time = now;
          else          _interval = 0;
          if (_callback != nullptr)
            _callback();
          return true;
        }
      }
      return false;
    }

    ///
    /// @brief      Tests if timer is started
    ///
    /// @return     True if started, false if stopped.
    ///
    bool started() const
    {
      return _interval != 0;
    }

    ///
    /// @brief      Wait until the next tick of the timer.
    ///
    void wait()
    {
      timer::wait(*this);
    }

  };

  ///
  /// Short-hand for a non-periodic timer
  /// (the same as <code>timer::base_timer</code> with template parameter
  /// <code>Periodic = false</code>)
  ///
  template <unsigned long (*TimeFunc)(), typename TimeType = unsigned long>
  using one_shot = base_timer<TimeFunc, TimeType, false>;

  ///
  /// Short-hand for a periodic timer
  /// (the same as <code>timer::base_timer</code> with template parameter
  /// <code>Periodic = true</code>)
  ///
  template <unsigned long (*TimeFunc)(), typename TimeType = unsigned long>
  using periodic = base_timer<TimeFunc, TimeType, true>;

#ifndef DOXYGEN_SHOULD_SKIP_THIS

  // End recursion in template expansion of wait().
  constexpr bool wait_impl()
  {
    return true;
  }

  // Implementation of wait() function below.
  template <unsigned long (*TimeFunc)(), typename TimeType, class... Other>
  bool wait_impl(timer::one_shot<TimeFunc, TimeType>& timer, Other&... other)
  {
    return (!timer.started() || timer.tick()) & wait_impl(other...);
  }

#endif /* DOXYGEN_SHOULD_SKIP_THIS */

  ///
  /// @brief      Wait for multiple non-periodic (<code>timer::one_shot</code>) timers
  ///
  /// @param      timers  The timers
  ///
  /// @tparam     Timers  Types of the timers (should automatically deducted)
  ///
  template <class... Timers>
  void wait(Timers&... timers)
  {
    while (!wait_impl(timers...));
  }

}

#endif /* ARDUINO_TIMER_HPP_2243B123BD6C4A0914C8ED5817D61881DDA0F390 */
