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
      var url = Config.backend + '/api/tracking?year=' + year + '&month=' + month;

      $http({
        method: 'GET',
        url: url
      }).success(function(response) {
        // Create header days.
        var endDay = new Date(year, month, 0).getDate();
        var days = [];
        for (var i = 1; i <= endDay; i++) {
          days.push(i);
        }
        var res = {};
        res.data = prepareEmployeeJson(response.data, days);
        res.days = days;
        setCache(res);

        deferred.resolve(res);
      });

      return deferred.promise;
    };

    function prepareEmployeeJson(tracking, days) {
      var employee = {};
      angular.forEach(tracking, function(value) {
        if (value.employee == undefined) {
          if (value.type == 'regular') {
            // If no employee use project name.
            value.employee = value.projectName;
          }
          value.employee = value.type;
        }
        if (employee[value.employee] == undefined) {
          employee[value.employee] = {};
        }
        // Convert days to hours.
        if (value.length.period == 'day') {
          value.length.interval = parseInt(value.length.interval) * 8;
        }
        // If no project time, print special day type instead.
        if (value.type != 'regular') {
          value.projectName = value.type;
          value.length.interval = 'S';
        }

        if (employee[value.employee] == undefined) {
          employee[value.employee] = {};
        }
        if (employee[value.employee][value.day] == undefined) {
          employee[value.employee][value.day] = [];
        }
        var day = {};
        day.interval = value.length.interval;
        day.projectName = value.projectName;
        day.type = value.type;
        day.link = value.editLink;
        employee[value.employee][value.day].push(day);
      });

      var employeeRows = {};
      // Fill in empty days.
      angular.forEach(employee, function(value, key) {
        employeeRows[key] = {}
        employeeRows[key].td = {}
        angular.forEach(days, function(day) {
          employeeRows[key].td[day] = [];
          if (value[day] != undefined) {
            angular.forEach(value[day], function(track) {
              employeeRows[key].td[day].push(track);
            });
          }
          else {
            // Fill empty days
            var track = {};
            track.interval = "-";
            track.projectName = "-";
            track.type = "-";
            track.link = "-";
            employeeRows[key].td[day].push(track);
          }
        });
      });

      return employeeRows;
    }

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
        cache.data = {};
      }, 60000);

      // Broadcast a change event.
      $rootScope.$broadcast('prod.tracking.changed');
    }
    $rootScope.$on('clearCache', function() {
      cache = {};
    });

  });
