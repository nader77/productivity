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
      return $q.when(getCache(year, month) || getDataFromBackend(year, month));
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
        setCache(response.data, year, month);
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
    var getCache = function(year, month) {
      // Cache data.
      if (cache[year + '_' + month] != undefined) {
        return cache[year + '_' + month].data;
      }
      return false;
    };


    /**
     * Set the cache from the server.
     *
     * @param data
     *   The data to cache
     */
    var setCache = function(data, year, month) {
      // Cache data.

      cache[year + '_' + month] = {
        data: data,
        timestamp: new Date()
      };

      // Clear cache in 60 seconds.
      $timeout(function() {
        cache = {};
      }, 900000);

      // Broadcast a change event.
      $rootScope.$broadcast(broadcastUpdateEventName);
      };
    $rootScope.$on('clearCache', function() {
      cache = {};
    });

  });
