'use strict';

/**
 * @ngdoc service
 * @name clientApp.Preferences
 * @description
 * # Preferences
 * Service in the clientApp, to get and set the user's preferences.
 */
angular.module('clientApp')
  .service('Preferences', function (localStorageService) {

    /**
     * Get user's calendar preference (opened or closed).
     *
     * @returns string
     *  The state of the calendar.
     */
    this.getCalendarPreference = function() {
      return localStorageService.get('calendar');
    };

    /**
     * Set user's calendar preference.
     *
     * Called upon changing the calendar state.
     *
     * @param calendarState
     *  The current state of the calendar.
     */
    this.setCalendarPreference = function(calendarState) {
      localStorageService.set('calendar', calendarState);
    };
  });
