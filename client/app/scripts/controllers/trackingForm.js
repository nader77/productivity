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
    var monthNames = [ "January", "February", "March", "April", "May", "June",
      "July", "August", "September", "October", "November", "December" ];


    $scope.month = $stateParams.month;
    $scope.monthString = monthNames[$scope.month-1];
    $scope.year = $stateParams.year;
    $scope.day = $stateParams.day;
    $scope.employee = $stateParams.username;

    $scope.nextMonth = $scope.month + 1;
    $scope.nextYear =  $scope.year;
    $scope.prevMonth = $scope.month - 1;
    $scope.prevYear =  $scope.year;

    if ($scope.month == 12) {
      $scope.nextMonth = 1;
      $scope.nextYear =  $scope.year + 1;
    }
    if ($scope.month == 1) {
      $scope.prevMonth = 12;
      $scope.prevYear =  $scope.year - 1;
    }

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
          $scope.message = newData.title;
          return;
        }
        // Success.
        $scope.messageClass = 'alert-success';
        $scope.message = 'Saved successfully.';

        // The tracking entity was un-published successfully,
        // need to reload.
        if (newData.data[0].status == 0) {
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
     * Determine if the current user is the owner of the entity (Time tracking).
     *
     * @param data
     *  The data of the entity.
     *
     * @returns {*|boolean}
     */
    $scope.owner = function(data) {
      return data.id && $stateParams.username == data.employee;
    };

    /**
     * Remove entity (Time tracking) from the work log by un-publishing it.
     * Sets status to 0 and call the save function.
     *
     * @param data
     *  The data of the entity.
     */
    $scope.remove = function(data) {
      if ($stateParams.username != data.employee) {
        return false;
      }
      data.status = 0;

      $scope.save(data);
    };
  });



