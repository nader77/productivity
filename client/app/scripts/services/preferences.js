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
     */
    this.getCalendarPreference = function() {
      return localStorageService.get('calendar');
    };

    /**
     * Set user's calendar preference.
     *
     * Called upon changing the calendar state.
     *
     * @param calendar
     *  The current state of the calendar.
     */
    this.setCalendarPreference = function(calendar) {
      localStorageService.set('calendar', calendar);
    };
  });
