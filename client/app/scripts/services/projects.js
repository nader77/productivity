'use strict';

/**
 * @ngdoc service
 * @name clientApp.companies
 * @description
 * # companies
 * Service in the clientApp.
 */
angular.module('clientApp')
  .service('Projects', function ($q, $http, $timeout, Config, $rootScope, localStorageService) {

    // A private cache key.
    var cache = {};

    // Update event broadcast name.
    var broadcastUpdateEventName = 'ProductivityProjectsChange';

    /**
     * Return the promise with the events list, from cache or the server.
     *
     * @returns {*}
     */
    this.get = function() {
      return $q.when(cache.data || getDataFromBackend());
    };

    /**
     * Save time tracking.
     *
     * @param data
     *   Object with data to be saved.
     */
    this.save = function(data) {
      var deferred = $q.defer();
      var url = Config.backend + '/api/projects';

      $http({
        method: 'POST',
        url: url,
        data: data
      }).success(function(response) {
      });

      return deferred.promise;
    };


    /**
     * Return events array from the server.
     *
     * @returns {$q.promise}
     */
    var getDataFromBackend = function() {
      var deferred = $q.defer();

      var url = Config.backend + '/api/projects';
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
    }
    $rootScope.$on('clearCache', function() {
      cache = {};
    });

  });
