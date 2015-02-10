'use strict';

/**
 * @ngdoc service
 * @name clientApp.companies
 * @description
 * # companies
 * Service in the clientApp.
 */
angular.module('clientApp')
  .service('Tracking', function ($q, $http, $timeout, Config, $rootScope, localStorageService) {

    // A private cache key.
    var cache = {};

    // Update event broadcast name.
    var broadcastUpdateEventName = 'ProductivityTrackingChange';

    /**
     * Return the promise with the events list, from cache or the server.
     *
     * @returns {*}
     */
    this.get = function(year, month, employee) {
      return $q.when(cache.data || getDataFromBackend(year, month, employee));
    };

    /**
     * Save time tracking.
     *
     * @param data
     *   Object with data to be saved.
     */
    this.save = function(data) {
      var deferred = $q.defer();
      var url = Config.backend + '/api/tracking';
      var method = 'POST';

      // Update existing.
      if (data.id) {
        method = 'PATCH';
        url += '/' + data.id;
      }
      // Debug mode.
      if (Config.debug) {
        url += '?XDEBUG_SESSION_START=13261';
      }

      $http({
        method: method,
        url: url,
        data: data
      }).
        success(function(data, status, headers, config) {
          // this callback will be called asynchronously
          // when the response is available.
          data.error = false;
          deferred.resolve(data);
      }).
        error(function(data, status, headers, config) {
          // called asynchronously if an error occurs
          // or server returns response with an error status.
          data.error = true;
          deferred.resolve(data);
      });

      return deferred.promise;
    };


    /**
     * Return events array from the server.
     *
     * @returns {$q.promise}
     */
    var getDataFromBackend = function(year, month, employee) {
      var deferred = $q.defer();

      var url = Config.backend + '/api/tracking?year=' + year + '&month=' + month;

      if (employee != undefined) {
        url += '&employee=' + employee;
      }

      // Debug mode.
      if (Config.debug) {
        url += '&XDEBUG_SESSION_START=13261';
      }

      $http({
        method: 'GET',
        url: url
      }).success(function(response) {
        // Create header days.
        //setCache(response.data);
        deferred.resolve(response.data);
      });

      return deferred.promise;
    };

    /**
     * Set the cache from the server.
     *
     * @param data
     *   The data to cache
     */
    var setCache = function(data) {
      // Cache data.
      cache = {
        data: data,
        timestamp: new Date()
      };

      // Clear cache in 60 seconds.
      $timeout(function() {
        cache = {};
      }, 60000);

      // Broadcast a change event.
      $rootScope.$broadcast(broadcastUpdateEventName);
    }
    $rootScope.$on('clearCache', function() {
      cache = {};
    });

  });
