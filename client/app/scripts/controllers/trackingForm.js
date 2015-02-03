'use strict';

/**
 * @ngdoc function
 * @name clientApp.controller:CompaniesCtrl
 * @description
 * # CompaniesCtrl
 * Controller of the clientApp
 */
angular.module('clientApp')
  .controller('TrackingFormCtrl', function ($scope, $stateParams, $state, $log, projects, Tracking, tracking, Config) {

    $scope.tracking = tracking;
    if (Config.debug) {
      console.log(tracking);
    }

    // Prepare header for table.
    var endDay = new Date($stateParams.year, $stateParams.month, 0).getDate();
    $scope.days = [];
    for (var i = 1; i <= endDay; i++) {
      $scope.days.push(i);
    }

    $scope.month = $stateParams.month;
    $scope.year = $stateParams.year;
    $scope.day = $stateParams.day;

    // Disable submit button.
    $scope.creating = false;
    // Initialize values.


    $scope.projects = projects;
    $scope.message = '';
    $scope.messageClass = 'alert-success';


    // Prepare form for create new.
    if ($stateParams.id == 'new' || $stateParams.id == 'undefined') {
      $scope.title = 'What have you done on the '  + $stateParams.day + '/' + $stateParams.month + '/' +  $stateParams.year + ' ?';
      $scope.data = {};
      $scope.data.period = 'hour';
      $scope.data.type = 'regular';
      $scope.data.employee = $stateParams.username;
    }
    else {
      $scope.title = 'Your report for the '  + $stateParams.day + '/' + $stateParams.month + '/' +  $stateParams.year + ' ?';
      // Fill with existing nid.
      angular.forEach(tracking[$stateParams.day], function(value, key) {
        if (value.id == $stateParams.id) {
          $scope.data = value;
        }
      });
    }

    $scope.save = function(data) {
      // Indicate we are in the middle of creation.
      $scope.creating = true;

      // Convert date to timestamp.
      var date = $stateParams.year + '-' + $stateParams.month + '-' +  $stateParams.day;
      data.date = new Date(date).getTime() / 1000;

      if (Config.debug) {
        console.log(data);
      }

      // Convert date to timestamp.
      Tracking.save(data).then(function(newData) {
        $scope.creating = false;

        if (newData.error) {
          $scope.messageClass = 'alert-danger';
          $scope.message = 'Error Saving.';
          return;
        }
        // Success.
        $scope.messageClass = 'alert-success';
        $scope.message = 'Saved successfully.';

        // Unpublished item, need to reload.
        if (newData.status == '403') {
          // Redirect to item to update.
          $state.go('dashboard.tracking-form', {
              username: $stateParams.username,
              year: $stateParams.year,
              month: $stateParams.month,
              day: $stateParams.day,
              id: 'new'
            },
            {
              reload: true
            });
          return;
        }

        var trackingItem = newData.data[0];
        // Push new value.
        if (trackingItem.new) {
          tracking[trackingItem.day].push(trackingItem);
          $stateParams.id = trackingItem.id;
        }

        // Redirect to item to update.
        $state.go('dashboard.tracking-form', {
            username: trackingItem.employee,
            year: $stateParams.year,
            month: $stateParams.month,
            day: trackingItem.day,
            id: trackingItem.id
          },
          {
            reload: true
          });
      });
    };

    /**
     * @TODO: Add docs.
     * @param data
     * @returns {*|boolean}
     */
    $scope.owner = function(data) {
      return data.id && $stateParams.username == data.employee;
    };

    /**
     * @TODO: Add docs.
     * @param data
     * @returns {boolean}
     */
    $scope.remove = function(data) {
      if ($stateParams.username != data.employee) {
        return false;
      }
      data.status = 0;

      $scope.save(data);
    };
  });



