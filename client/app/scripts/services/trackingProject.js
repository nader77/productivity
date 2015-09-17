'use strict';

/**
 * @ngdoc service
 * @name clientApp.companies
 * @description
 * # companies
 * Service in the clientApp.
 */
angular.module('clientApp')
  .service('TrackingProject', function ($q, $http, $timeout, Config, $rootScope) {

    // A private cache key.
    var cache = {};

    // Update event broadcast name.
    var broadcastUpdateEventName = 'ProductivityTrackingProjectChange';

    /**
     * Return the promise with the events list, from cache or the server.
     *
     * @returns {*}
     */
    this.get = function(year, month) {
      return $q.when(cache.data || getDataFromBackend(year, month));
    };

    /**
     * Return events array from the server.
     *
     * @returns {$q.promise}
     */
    var getDataFromBackend = function(year, month) {
      var deferred = $q.defer();
      var url = Config.backend + '/api/tracking-project?year=' + year + '&month=' + month;
      console.log(url);
      // Debug mode.
      if (Config.debug) {
        url += '&XDEBUG_SESSION_START=14241';
      }

      $http({
        method: 'GET',
        url: url
      }).success(function(response) {
        // Create header days.
        setCache(response.data);
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
      };
    $rootScope.$on('clearCache', function() {
      cache = {};
    });

  });
